# Workflow: Safe Refactoring

## Overview
Workflow for improving code structure while ensuring behavior is preserved through comprehensive testing.

## Prerequisites
- Clear refactoring goal (reduce duplication, improve naming, restructure)
- Existing test coverage for affected code
- No simultaneous feature changes

## Golden Rule
**Refactoring changes structure, not behavior. Tests must pass before, during, and after.**

## Workflow Steps

### Step 1: Assess Test Coverage
**Agent**: `test-reviewer.md`

**Actions**:
1. Identify code to be refactored
2. Review existing test coverage
3. Identify coverage gaps

**Checkpoint**: Understand what is/isn't tested

---

### Step 2: Add Missing Tests (If Needed)
**Agent**: `test-generator.md` + `tdd-coach.md`

**Actions**:
1. Write tests for uncovered behavior
2. Tests must pass with current code
3. Tests should be behavior-focused, not implementation-focused

**Checkpoint**: Sufficient coverage to detect regressions

---

### Step 3: Verify All Tests Pass
**No specific agent**

**Actions**:
```bash
pytest  # or your test runner
```

**Checkpoint**: All tests green before refactoring

---

### Step 4: Refactor in Small Steps
**Agent**: `python-quality-enforcer.md` or `cpp-quality-enforcer.md`

**Actions**:
1. Make one small refactoring change
2. Run tests
3. If tests pass, commit
4. If tests fail, revert and try smaller step
5. Repeat until refactoring complete

**Pattern**:
```
change → test → green? → commit → next change
                  ↓
                revert → rethink
```

**Checkpoint**: Each step keeps tests green

---

### Step 5: Code Quality Review
**Agent**: `python-quality-enforcer.md` or `cpp-quality-enforcer.md`

**Actions**:
1. Review refactored code for quality
2. Check naming, structure, patterns
3. Verify no new technical debt introduced

**Checkpoint**: Code quality improved

---

### Step 6: Final Test Verification
**No specific agent**

**Actions**:
```bash
pytest
ruff check .  # for Python
```

**Checkpoint**: All tests pass, linting clean

---

### Step 7: Traceability Check
**Agent**: `traceability-manager.md`

**Actions**:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```
1. Verify no traceability broken (moved test files, renamed functions)
2. Update REQ-xxxx references if test files moved

**Checkpoint**: Traceability maintained

---

## Refactoring Patterns

### Extract Function/Method
1. Identify duplicated or long code
2. Write test covering the behavior
3. Extract to named function
4. Run tests
5. Commit

### Rename
1. Choose clear, descriptive name
2. Use IDE/tool for safe rename
3. Update documentation references
4. Run tests
5. Commit

### Move/Restructure
1. Identify better location
2. Move with tests
3. Update imports/includes
4. Run tests
5. Update traceability references if needed
6. Commit

### Simplify Conditionals
1. Write tests for all branches
2. Simplify logic
3. Run tests
4. Commit

## Refactoring Checklist

- [ ] Test coverage reviewed and gaps filled
- [ ] All tests pass before starting
- [ ] Refactored in small, testable steps
- [ ] Tests run after each change
- [ ] No behavior changes introduced
- [ ] Code quality improved
- [ ] Traceability maintained
- [ ] Final linting clean
