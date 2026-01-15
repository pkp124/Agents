# Workflow: Bug Fix

## Overview
TDD-based workflow for fixing bugs while maintaining traceability and preventing regressions.

## Prerequisites
- Bug report or reproduction steps
- Access to affected code and tests
- Understanding of expected vs actual behavior

## Workflow Steps

### Step 1: Identify Affected Requirements
**Agent**: `traceability-manager.md`

**Actions**:
1. Determine which requirement(s) the bug violates
2. Find existing tests for those requirements
3. Check if tests are missing or incorrect

**Output**: List of REQ-xxxx affected, existing test coverage

---

### Step 2: Write Failing Test (TDD Red)
**Agent**: `tdd-coach.md`

**Actions**:
1. Write a test that reproduces the bug
2. Test must fail with current code
3. Include REQ-xxxx reference in test

```python
def test_bug_12345_invalid_input_crash():
    """Regression test for bug #12345.
    
    Traces to: REQ-0042
    """
    # This should not raise, but currently does
    result = process(invalid_input)
    assert result.is_error()  # Expected behavior
```

**Checkpoint**: Test fails, demonstrating the bug

---

### Step 3: Implement Fix (TDD Green)
**No specific agent** - developer fixes

**Actions**:
1. Make minimal change to fix the bug
2. Avoid unrelated changes
3. Run all tests to ensure no regressions

**Checkpoint**: New test passes, all other tests still pass

---

### Step 4: Review Fix
**Agent**: `test-reviewer.md` + quality enforcer

**Actions**:
1. Review test quality
2. Review fix for correctness and style
3. Ensure fix addresses root cause

**Checkpoint**: Fix approved

---

### Step 5: Verify Traceability
**Agent**: `traceability-manager.md`

**Actions**:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```
1. Confirm new test references correct REQ-xxxx
2. No traceability gaps introduced

**Checkpoint**: Traceability maintained

---

### Step 6: Update Documentation (If Needed)
**Agent**: `doc-change-manager.md`

**Actions**:
1. If bug revealed unclear documentation, update it
2. Add troubleshooting guidance if applicable

**Checkpoint**: Documentation accurate

---

## Final Verification

```bash
pytest
python tools/traceability/check_traceability.py --docs docs --tests tests
```

## Bug Fix Checklist

- [ ] Bug reproduced with a failing test
- [ ] Test references affected REQ-xxxx
- [ ] Fix is minimal and focused
- [ ] All existing tests still pass
- [ ] Traceability check passes
- [ ] Code review completed
- [ ] Documentation updated if needed
