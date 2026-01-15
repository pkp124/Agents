# Skill: Write Pytest Test

## Purpose
Generate a properly structured pytest test with requirement traceability.

## Input
- `behavior`: Description of behavior to test
- `req_id`: Requirement ID (REQ-xxxx)
- `test_type`: unit | integration | system
- `given`: Preconditions
- `when`: Action
- `then`: Expected outcome

## Output
Complete pytest test function with:
- Descriptive name
- Docstring with requirement reference
- Arrange/Act/Assert structure
- Proper assertions

## Template
```python
def test_{{behavior_snake_case}}_{{expected_outcome}}():
    """{{Description of what is being tested}}.
    
    Traces to: {{req_id}}
    
    Given: {{given}}
    When: {{when}}
    Then: {{then}}
    """
    # Arrange
    {{setup_code}}
    
    # Act
    {{action_code}}
    
    # Assert
    {{assertion_code}}
```

## Example

**Input**:
- behavior: User authentication
- req_id: REQ-0015
- given: Valid user credentials
- when: User attempts to login
- then: Authentication succeeds

**Output**:
```python
def test_user_authentication_succeeds_with_valid_credentials():
    """User with valid credentials can authenticate successfully.
    
    Traces to: REQ-0015
    
    Given: Valid user credentials
    When: User attempts to login
    Then: Authentication succeeds
    """
    # Arrange
    credentials = Credentials(username="valid_user", password="correct_pass")
    auth_service = AuthService()
    
    # Act
    result = auth_service.authenticate(credentials)
    
    # Assert
    assert result.success is True
    assert result.user_id is not None
```

## Parameterized Variant
```python
@pytest.mark.parametrize("input_value,expected", [
    (valid_input_1, expected_1),
    (valid_input_2, expected_2),
    (boundary_min, expected_min),
    (boundary_max, expected_max),
])
def test_{{behavior}}_with_various_inputs(input_value, expected):
    """{{Description}}.
    
    Traces to: {{req_id}}
    """
    result = function_under_test(input_value)
    assert result == expected
```

## Used By
- `tdd-coach.md`
- `test-generator.md`
