#!/usr/bin/env python3
"""
Validate requirement quality.

Checks that requirements follow best practices:
- Use "shall" for mandatory behavior
- Are atomic (no compound requirements with "and")
- Avoid ambiguous words without quantification
- Have required fields

"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

import yaml

AMBIGUOUS_WORDS = {
    "fast",
    "slow",
    "quick",
    "robust",
    "reliable",
    "stable",
    "user-friendly",
    "intuitive",
    "easy",
    "simple",
    "efficient",
    "effective",
    "flexible",
    "scalable",
    "secure",
    "safe",
    "appropriate",
    "reasonable",
    "adequate",
    "sufficient",
    "minimal",
    "maximal",
}

REQUIRED_FIELDS = {"id", "statement"}
RECOMMENDED_FIELDS = {"title", "rationale", "verification_method", "priority"}


@dataclass
class Issue:
    severity: str  # error | warning
    message: str
    field: str = ""


@dataclass
class RequirementValidation:
    req_id: str
    file: Path
    valid: bool
    issues: list[Issue] = field(default_factory=list)


def validate_requirement(req: dict, file: Path) -> RequirementValidation:
    """Validate a single requirement."""
    issues: list[Issue] = []
    req_id = req.get("id", "UNKNOWN")

    # Check required fields
    for field_name in REQUIRED_FIELDS:
        if field_name not in req or not req[field_name]:
            issues.append(Issue("error", f"Missing required field: {field_name}", field_name))

    # Check recommended fields
    for field_name in RECOMMENDED_FIELDS:
        if field_name not in req or not req[field_name]:
            issues.append(Issue("warning", f"Missing recommended field: {field_name}", field_name))

    # Validate statement
    statement = req.get("statement", "")
    if statement:
        # Check for "shall"
        if "shall" not in statement.lower():
            issues.append(
                Issue("warning", "Statement should use 'shall' for mandatory behavior", "statement")
            )

        # Check for compound requirements
        if re.search(r"\bshall\b.*\band\b.*\bshall\b", statement.lower()):
            issues.append(
                Issue(
                    "warning",
                    "Statement may contain multiple requirements (multiple 'shall')",
                    "statement",
                )
            )

        # Check for ambiguous words
        statement_lower = statement.lower()
        found_ambiguous = [word for word in AMBIGUOUS_WORDS if word in statement_lower]
        for word in found_ambiguous:
            # Check if it's quantified (has a number nearby)
            pattern = rf"\b{word}\b"
            for match in re.finditer(pattern, statement_lower):
                # Look for numbers within 50 chars on either side
                start = max(0, match.start() - 50)
                end = min(len(statement_lower), match.end() + 50)
                context = statement_lower[start:end]
                if not re.search(r"\d+", context):
                    issues.append(
                        Issue(
                            "warning",
                            f"Ambiguous word '{word}' without quantification",
                            "statement",
                        )
                    )
                    break

    # Validate ID format
    if not re.match(r"^REQ-\d{4}$", req_id):
        issues.append(Issue("error", f"Invalid ID format: {req_id} (expected REQ-XXXX)", "id"))

    valid = not any(issue.severity == "error" for issue in issues)

    return RequirementValidation(req_id=req_id, file=file, valid=valid, issues=issues)


def validate_file(file: Path) -> list[RequirementValidation]:
    """Validate all requirements in a file."""
    results: list[RequirementValidation] = []

    try:
        content = file.read_text(encoding="utf-8")
        data = yaml.safe_load(content)
    except Exception as e:
        return [
            RequirementValidation(
                req_id="FILE_ERROR",
                file=file,
                valid=False,
                issues=[Issue("error", f"Failed to parse file: {e}")],
            )
        ]

    if not data or "requirements" not in data:
        return results

    requirements = data.get("requirements", [])
    if not isinstance(requirements, list):
        return results

    for req in requirements:
        if isinstance(req, dict):
            results.append(validate_requirement(req, file))

    return results


def format_results(results: list[RequirementValidation], *, verbose: bool = False) -> str:
    """Format validation results as text."""
    lines: list[str] = []

    errors = sum(1 for r in results if not r.valid)
    warnings = sum(len([i for i in r.issues if i.severity == "warning"]) for r in results)

    lines.append("Requirement Validation Report")
    lines.append("=" * 30)
    lines.append(f"Requirements checked: {len(results)}")
    lines.append(f"Errors: {errors}")
    lines.append(f"Warnings: {warnings}")
    lines.append("")

    for result in results:
        if not result.issues and not verbose:
            continue

        lines.append(f"{result.req_id} ({result.file})")
        for issue in result.issues:
            prefix = "  [ERROR]" if issue.severity == "error" else "  [WARN]"
            lines.append(f"{prefix} {issue.message}")
        lines.append("")

    return "\n".join(lines)


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description="Validate requirement quality.")
    parser.add_argument(
        "--requirements",
        type=Path,
        default=Path("docs/requirements"),
        help="Requirements directory (default: docs/requirements)",
    )
    parser.add_argument("--verbose", "-v", action="store_true", help="Show all requirements")
    args = parser.parse_args(argv)

    if not args.requirements.exists():
        sys.stderr.write(f"Directory not found: {args.requirements}\n")
        return 2

    all_results: list[RequirementValidation] = []

    for file in args.requirements.glob("*.yaml"):
        all_results.extend(validate_file(file))
    for file in args.requirements.glob("*.yml"):
        all_results.extend(validate_file(file))

    print(format_results(all_results, verbose=args.verbose))

    has_errors = any(not r.valid for r in all_results)
    return 1 if has_errors else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
