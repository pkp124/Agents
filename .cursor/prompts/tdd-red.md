# TDD Red Phase: Write Failing Test

## Description
Start the TDD cycle by writing a failing test that expresses the desired behavior.

## Prompt

I need to write a failing test (TDD "Red" phase) for the following behavior:

**Behavior to test**: {{BEHAVIOR_DESCRIPTION}}
**Related requirement**: {{REQ_ID}}
**Test framework**: {{pytest|googletest|catch2}}

Please help me:

1. **Clarify the behavior** with Given/When/Then format
2. **Write the minimal failing test** that expresses this behavior
3. **Include the REQ-xxxx reference** in the test (comment or docstring)
4. **Verify the test fails** for the right reason (not syntax error)

The test should:
- Be deterministic (no flaky timing)
- Test observable behavior, not implementation
- Use clear, descriptive naming
- Include boundary cases if applicable

After writing the test, I'll implement the minimal code to make it pass (Green phase).

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values before running.

## Example

**Behavior to test**: User authentication rejects invalid credentials
**Related requirement**: REQ-0015
**Test framework**: pytest

## Output Format
```python
def test_{{behavior}}_{{expected_outcome}}():
    """{{Description}}.
    
    Traces to: REQ-xxxx
    """
    # Arrange
    ...
    # Act
    ...
    # Assert
    ...
```
