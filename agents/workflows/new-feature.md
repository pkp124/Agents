# Workflow: New Feature Development

## Overview
Complete workflow for developing a new feature from requirements through implementation with full traceability.

## Prerequisites
- Clear understanding of user need or PRD section
- Access to existing requirements (if extending)
- Knowledge of target language/framework

## Workflow Steps

### Step 1: Requirements Capture
**Agent**: `requirements-author.md`

**Inputs**:
- User story or feature description
- Stakeholders
- Constraints (performance, security, etc.)

**Actions**:
1. Create `docs/requirements/REQ-XXXX-feature-name.yaml`
2. Define verifiable requirements with IDs
3. Specify verification methods

**Checkpoint**: Requirements are atomic, testable, and prioritized

---

### Step 2: Requirements Review
**Agent**: `requirements-reviewer.md`

**Inputs**:
- Requirements file from Step 1

**Actions**:
1. Review for ambiguity and completeness
2. Verify testability
3. Check consistency with existing requirements

**Checkpoint**: Requirements approved or feedback addressed

---

### Step 3: Use Case Definition (Optional)
**Agent**: `use-case-author.md`

**Inputs**:
- Approved requirements
- User personas

**Actions**:
1. Create `docs/use_cases/UC-XXXX.md`
2. Define main flow and alternatives
3. Map to requirements

**Checkpoint**: Use cases cover happy path and edge cases

---

### Step 4: Design Specification
**Agent**: `design-author.md`

**Inputs**:
- Requirements (REQ-xxxx)
- Use cases (UC-xxxx)
- Architecture context

**Actions**:
1. Create `docs/design/DES-XXXX-feature-name.md`
2. Include `Traces to:` section with REQ references
3. Define architecture, interfaces, failure modes
4. Specify test strategy

**Checkpoint**: Design traces to all requirements

---

### Step 5: Critical Design Review
**Agent**: `cdr-reviewer.md`

**Inputs**:
- Design document from Step 4
- Requirements

**Actions**:
1. Run CDR checklist
2. Identify gaps, risks, missing coverage
3. Provide decision: Approve / Revise / Reject

**Checkpoint**: Design approved (possibly with changes)

---

### Step 6: Traceability Verification (REQ↔DES)
**Agent**: `traceability-manager.md`

**Actions**:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```
1. Verify all new requirements have design references
2. Fix any gaps before proceeding

**Checkpoint**: No missing design references

---

### Step 7: Test Planning (TDD Red Phase)
**Agent**: `tdd-coach.md` + `test-generator.md`

**Inputs**:
- Requirements and design
- Test framework constraints

**Actions**:
1. Create test plan
2. Write failing tests that express requirements
3. Each test references REQ-xxxx

**Checkpoint**: Tests fail for the right reason (feature not implemented)

---

### Step 8: Implementation (TDD Green Phase)
**No specific agent** - developer implements

**Actions**:
1. Write minimal code to pass tests
2. Keep implementation simple
3. Focus on behavior, not optimization

**Checkpoint**: All tests pass

---

### Step 9: Refactoring (TDD Refactor Phase)
**Agent**: `python-quality-enforcer.md` or `cpp-quality-enforcer.md`

**Actions**:
1. Improve code structure
2. Remove duplication
3. Enhance readability
4. Keep tests green

**Checkpoint**: Code quality approved

---

### Step 10: Test Review
**Agent**: `test-reviewer.md`

**Inputs**:
- Test files created in Step 7

**Actions**:
1. Review test quality (determinism, value, coverage)
2. Verify requirement references
3. Check boundary and negative cases

**Checkpoint**: Tests are high-quality and complete

---

### Step 11: Traceability Verification (REQ↔TEST)
**Agent**: `traceability-manager.md`

**Actions**:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```
1. Verify all requirements have test references
2. Verify no unknown IDs in tests

**Checkpoint**: Full traceability REQ↔DES↔TEST

---

### Step 12: CI Integration
**Agent**: `ci-impact-reviewer.md`

**Actions**:
1. Ensure new tests run in CI
2. Verify workflow permissions
3. Check for flakiness risks

**Checkpoint**: CI covers new tests

---

### Step 13: Documentation Update
**Agent**: `doc-change-manager.md` + `user-doc-reviewer.md`

**Actions**:
1. Update user-facing documentation
2. Add examples and usage instructions
3. Review for accuracy and clarity

**Checkpoint**: Documentation complete

---

## Final Verification

```bash
# All checks must pass
ruff check .
ruff format --check .
pytest
python tools/traceability/check_traceability.py --docs docs --tests tests
```

## Artifacts Produced

| Artifact | Location |
|----------|----------|
| Requirement | `docs/requirements/REQ-XXXX-*.yaml` |
| Use Case | `docs/use_cases/UC-XXXX.md` (optional) |
| Design | `docs/design/DES-XXXX-*.md` |
| Tests | `tests/test_*.py` or `tests/*_test.cpp` |
| Source | `src/**` |
| User Docs | `docs/user/**` |
