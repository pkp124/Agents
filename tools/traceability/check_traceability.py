#!/usr/bin/env python3
"""
Repository traceability checker.

Enforces:
- Every requirement ID (REQ-xxxx) defined under docs/requirements is referenced by:
  - at least one design doc under docs/design
  - at least one test file under tests
- Design/tests do not reference unknown requirement IDs
"""

from __future__ import annotations

import argparse
import re
import sys
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path

REQ_ID_RE = re.compile(r"\bREQ-\d{4}\b")


def _iter_files(root: Path, *, include_suffixes: set[str] | None = None) -> Iterable[Path]:
    if not root.exists():
        return []
    for p in root.rglob("*"):
        if not p.is_file():
            continue
        if "__pycache__" in p.parts:
            continue
        if include_suffixes is not None and p.suffix not in include_suffixes:
            continue
        yield p


def _read_text(path: Path) -> str:
    # Best-effort: treat unknown encodings as non-fatal and scan what we can.
    return path.read_text(encoding="utf-8", errors="ignore")


def collect_req_ids_defined(requirements_dir: Path) -> set[str]:
    ids: set[str] = set()
    for p in _iter_files(requirements_dir, include_suffixes={".yml", ".yaml"}):
        ids.update(REQ_ID_RE.findall(_read_text(p)))
    return ids


def collect_req_ids_referenced(
    root: Path, *, include_suffixes: set[str] | None
) -> dict[str, set[Path]]:
    refs: dict[str, set[Path]] = {}
    for p in _iter_files(root, include_suffixes=include_suffixes):
        text = _read_text(p)
        for req_id in set(REQ_ID_RE.findall(text)):
            refs.setdefault(req_id, set()).add(p)
    return refs


@dataclass(frozen=True)
class TraceabilityReport:
    defined_requirements: set[str]
    design_refs: dict[str, set[Path]]
    test_refs: dict[str, set[Path]]
    missing_design: set[str]
    missing_tests: set[str]
    unknown_in_design: set[str]
    unknown_in_tests: set[str]


def build_report(*, docs_dir: Path, tests_dir: Path) -> TraceabilityReport:
    requirements_dir = docs_dir / "requirements"
    design_dir = docs_dir / "design"

    defined = collect_req_ids_defined(requirements_dir)
    design_refs = collect_req_ids_referenced(design_dir, include_suffixes={".md", ".txt", ".rst"})
    test_refs = collect_req_ids_referenced(
        tests_dir,
        include_suffixes={
            ".py",
            ".cpp",
            ".cc",
            ".cxx",
            ".c",
            ".h",
            ".hpp",
            ".md",
            ".txt",
            ".rst",
            ".sh",
        },
    )

    missing_design = {r for r in defined if r not in design_refs}
    missing_tests = {r for r in defined if r not in test_refs}

    unknown_in_design = {r for r in design_refs.keys() if r not in defined}
    unknown_in_tests = {r for r in test_refs.keys() if r not in defined}

    return TraceabilityReport(
        defined_requirements=defined,
        design_refs=design_refs,
        test_refs=test_refs,
        missing_design=missing_design,
        missing_tests=missing_tests,
        unknown_in_design=unknown_in_design,
        unknown_in_tests=unknown_in_tests,
    )


def format_report(report: TraceabilityReport) -> str:
    lines: list[str] = []
    lines.append("Traceability report")
    lines.append("===================")
    lines.append(f"Requirements defined: {len(report.defined_requirements)}")
    lines.append(f"Requirements referenced by design: {len(report.design_refs)}")
    lines.append(f"Requirements referenced by tests: {len(report.test_refs)}")
    lines.append("")

    def _section(title: str, ids: set[str]) -> None:
        lines.append(title)
        lines.append("-" * len(title))
        if not ids:
            lines.append("(none)")
            lines.append("")
            return
        for r in sorted(ids):
            lines.append(f"- {r}")
        lines.append("")

    _section(
        "Missing design references (REQ defined but not referenced in docs/design)",
        report.missing_design,
    )
    _section(
        "Missing test references (REQ defined but not referenced in tests)",
        report.missing_tests,
    )
    _section(
        "Unknown requirement IDs referenced in design (not defined in docs/requirements)",
        report.unknown_in_design,
    )
    _section(
        "Unknown requirement IDs referenced in tests (not defined in docs/requirements)",
        report.unknown_in_tests,
    )

    return "\n".join(lines).rstrip() + "\n"


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description="Enforce REQ↔DES↔TEST traceability.")
    parser.add_argument(
        "--docs",
        type=Path,
        default=Path("docs"),
        help="Docs root (default: docs)",
    )
    parser.add_argument(
        "--tests",
        type=Path,
        default=Path("tests"),
        help="Tests root (default: tests)",
    )
    parser.add_argument(
        "--fail-if-no-requirements",
        action="store_true",
        help="Fail if no REQ-xxxx IDs are found under docs/requirements.",
    )
    args = parser.parse_args(argv)

    report = build_report(docs_dir=args.docs, tests_dir=args.tests)

    if args.fail_if_no_requirements and not report.defined_requirements:
        sys.stderr.write("No requirements found under docs/requirements (no REQ-xxxx IDs).\n")
        return 2

    failed = bool(
        report.missing_design
        or report.missing_tests
        or report.unknown_in_design
        or report.unknown_in_tests
    )

    out = sys.stderr if failed else sys.stdout
    out.write(format_report(report))
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
