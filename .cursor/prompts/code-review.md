# Code Review (TDD + V-Model)

## Description
Review code changes for quality, traceability, and test coverage.

## Prompt

Please review the following code changes:

**Files changed**: {{FILES}}
**Related requirements**: {{REQ_IDS}}
**PR/Change description**: {{DESCRIPTION}}

Perform a comprehensive review checking:

## 1. Traceability
- [ ] All new functionality traces to a requirement (REQ-xxxx)
- [ ] Tests reference the requirements they verify
- [ ] Design docs updated if needed

## 2. Test Coverage
- [ ] New code has corresponding tests
- [ ] Tests cover happy path and edge cases
- [ ] Tests are deterministic
- [ ] Tests reference REQ-xxxx

## 3. Code Quality (Python)
- [ ] Type annotations present
- [ ] Docstrings for public APIs
- [ ] No obvious bugs or security issues
- [ ] Follows project style (ruff)

## 4. Code Quality (C++)
- [ ] Modern C++ idioms
- [ ] Memory safety (smart pointers)
- [ ] Exception safety
- [ ] Follows project conventions

## 5. Design Alignment
- [ ] Implementation matches design doc
- [ ] Interfaces match specification
- [ ] Error handling per design

Run verification:
```bash
ruff check .
pytest
python tools/traceability/check_traceability.py --docs docs --tests tests
```

## Output Format

### Summary
- **Decision**: Approve / Request Changes / Reject
- **Critical issues**: (must fix)
- **Suggestions**: (nice to have)

### Detailed Findings
| Severity | File:Line | Issue | Suggestion |
|----------|-----------|-------|------------|

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values.
