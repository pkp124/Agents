# Generate Tests from Requirements

## Description
Generate high-coverage tests from requirements and design.

## Prompt

I need to generate tests for the following requirements:

**Requirements**: {{REQ_IDS}}
**Design doc** (if available): {{DES_FILE}}
**Test framework**: {{pytest|googletest|catch2}}

Please help me generate comprehensive tests:

1. **Create test inventory** mapping tests to requirements:
   | Test Name | Type | REQ-xxxx | Behavior Verified |
   |-----------|------|----------|-------------------|

2. **Generate test cases** for each requirement:
   - Happy path
   - Boundary values (min, max, empty, overflow)
   - Invalid inputs
   - Error conditions
   - Edge cases from design failure modes

3. **Each test must include**:
   - REQ-xxxx reference in docstring/comment
   - Clear Given/When/Then structure
   - Deterministic assertions

4. **Output test files** in `tests/` directory

Test quality requirements:
- Deterministic (no flaky tests)
- Fast (unit tests < 1s)
- Hermetic (no external dependencies)
- Behavioral (test observable outcomes)

After generating:
```bash
pytest tests/
python tools/traceability/check_traceability.py --docs docs --tests tests
```

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values.

## Example

**Requirements**: REQ-0015, REQ-0016
**Design doc**: docs/design/DES-0005-auth.md
**Test framework**: pytest

## Output Format (Python)
```python
"""Tests for authentication module.

Traces to: REQ-0015, REQ-0016
"""
import pytest

class TestAuthentication:
    def test_valid_credentials_succeed(self):
        """User with valid credentials can authenticate.
        
        Traces to: REQ-0015
        """
        pass
    
    @pytest.mark.parametrize("invalid_input", [...])
    def test_invalid_credentials_rejected(self, invalid_input):
        """Invalid credentials are rejected.
        
        Traces to: REQ-0016
        """
        pass
```
