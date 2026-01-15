# TDD Green Phase: Make Test Pass

## Description
Implement the minimal code to make the failing test pass.

## Prompt

I have a failing test and need to implement the minimal code to make it pass (TDD "Green" phase).

**Failing test file**: {{TEST_FILE_PATH}}
**Test function**: {{TEST_FUNCTION_NAME}}
**Related requirement**: {{REQ_ID}}

Please help me:

1. **Analyze the test** to understand what behavior is expected
2. **Implement the minimal code** that makes the test pass
3. **Keep it simple** - no premature optimization or extra features
4. **Verify all existing tests still pass**

Implementation rules:
- Write the simplest code that works
- Don't add features not required by the test
- Follow project coding standards
- Make the code obviously correct

After implementation, run:
```bash
pytest {{TEST_FILE_PATH}}
```

If all tests pass, we move to the Refactor phase.

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values.

## Example

**Failing test file**: tests/test_auth.py
**Test function**: test_invalid_credentials_rejected
**Related requirement**: REQ-0015
