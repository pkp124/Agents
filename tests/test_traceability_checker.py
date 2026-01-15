from __future__ import annotations

from pathlib import Path

from tools.traceability.check_traceability import build_report


def _write(p: Path, text: str) -> None:
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(text, encoding="utf-8")


def test_report_flags_missing_design_and_tests(tmp_path: Path) -> None:
    docs = tmp_path / "docs"
    tests = tmp_path / "tests"

    _write(docs / "requirements" / "reqs.md", "### REQ-0001: foo\n")
    unknown = "REQ-" + "9999"
    _write(docs / "design" / "d.md", f"Traces to: {unknown}\n")
    _write(tests / "test_x.py", f"# {unknown}\n")

    report = build_report(docs_dir=docs, tests_dir=tests)

    assert report.defined_requirements == {"REQ-0001"}
    assert report.missing_design == {"REQ-0001"}
    assert report.missing_tests == {"REQ-0001"}
    assert report.unknown_in_design == {unknown}
    assert report.unknown_in_tests == {unknown}


def test_report_ok_when_req_is_referenced(tmp_path: Path) -> None:
    docs = tmp_path / "docs"
    tests = tmp_path / "tests"

    _write(docs / "requirements" / "reqs.md", "### REQ-0001: foo\n")
    _write(docs / "design" / "d.md", "Traces to: REQ-0001\n")
    _write(tests / "test_x.py", "# REQ-0001\n")

    report = build_report(docs_dir=docs, tests_dir=tests)
    assert not report.missing_design
    assert not report.missing_tests
    assert not report.unknown_in_design
    assert not report.unknown_in_tests
