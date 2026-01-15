#!/usr/bin/env python3
"""
Find the next available ID for requirements, designs, use cases, and tests.

Scans existing files to determine the highest used ID for each type and
suggests the next available ID.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ID_PATTERNS = {
    "REQ": re.compile(r"\bREQ-(\d{4})\b"),
    "DES": re.compile(r"\bDES-(\d{4})\b"),
    "UC": re.compile(r"\bUC-(\d{4})\b"),
    "TST": re.compile(r"\bTST-(\d{4})\b"),
}


def _iter_files(root: Path) -> list[Path]:
    if not root.exists():
        return []
    return [
        p
        for p in root.rglob("*")
        if p.is_file()
        and "__pycache__" not in p.parts
        and p.suffix in {".yaml", ".yml", ".md", ".py", ".cpp", ".h", ".hpp", ".txt", ".rst"}
    ]


def find_max_id(root: Path, id_type: str) -> int:
    """Find the maximum ID number for a given ID type."""
    pattern = ID_PATTERNS.get(id_type)
    if not pattern:
        return 0

    max_id = 0
    for file_path in _iter_files(root):
        try:
            content = file_path.read_text(encoding="utf-8", errors="ignore")
            for match in pattern.finditer(content):
                id_num = int(match.group(1))
                max_id = max(max_id, id_num)
        except Exception:
            continue

    return max_id


def find_all_next_ids(docs_dir: Path, tests_dir: Path) -> dict[str, str]:
    """Find next available IDs for all types."""
    results = {}

    # REQ: scan docs/requirements
    req_max = find_max_id(docs_dir / "requirements", "REQ")
    results["REQ"] = f"REQ-{req_max + 1:04d}"

    # DES: scan docs/design
    des_max = find_max_id(docs_dir / "design", "DES")
    results["DES"] = f"DES-{des_max + 1:04d}"

    # UC: scan docs/use_cases
    uc_max = find_max_id(docs_dir / "use_cases", "UC")
    results["UC"] = f"UC-{uc_max + 1:04d}"

    # TST: scan tests
    tst_max = find_max_id(tests_dir, "TST")
    results["TST"] = f"TST-{tst_max + 1:04d}"

    return results


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description="Find next available IDs for REQ/DES/UC/TST.")
    parser.add_argument("--docs", type=Path, default=Path("docs"), help="Docs root (default: docs)")
    parser.add_argument(
        "--tests", type=Path, default=Path("tests"), help="Tests root (default: tests)"
    )
    parser.add_argument(
        "--type",
        choices=["REQ", "DES", "UC", "TST", "all"],
        default="all",
        help="ID type to find (default: all)",
    )
    args = parser.parse_args(argv)

    next_ids = find_all_next_ids(args.docs, args.tests)

    if args.type == "all":
        print("Next available IDs:")
        print(f"  Requirement: {next_ids['REQ']}")
        print(f"  Design:      {next_ids['DES']}")
        print(f"  Use Case:    {next_ids['UC']}")
        print(f"  Test:        {next_ids['TST']}")
    else:
        print(next_ids[args.type])

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
