# TDD Refactor Phase: Improve Code Quality

## Description
Improve code structure while keeping all tests passing.

## Prompt

Tests are passing, now I need to refactor the code (TDD "Refactor" phase).

**Source file(s)**: {{SOURCE_FILES}}
**Test file(s)**: {{TEST_FILES}}

Please help me:

1. **Identify improvement opportunities**:
   - Duplicated code
   - Poor naming
   - Complex conditionals
   - Long functions
   - Missing abstractions

2. **Suggest specific refactorings** with rationale

3. **Apply refactorings one at a time**:
   - Make change
   - Run tests
   - If green, commit
   - If red, revert

4. **Verify all tests still pass** after each change

Refactoring rules:
- Change structure, not behavior
- Tests must pass after each step
- Small, incremental changes
- Keep the code clean and readable

After refactoring:
```bash
pytest
ruff check .
ruff format --check .
```

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values.

## Refactoring Checklist
- [ ] Removed duplication
- [ ] Improved naming
- [ ] Simplified complex logic
- [ ] Extracted reusable functions
- [ ] All tests still pass
- [ ] Linting passes
