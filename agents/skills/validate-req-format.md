# Skill: Validate Requirement Format

## Purpose
Check that a requirement meets quality standards for verifiability and clarity.

## Input
- Requirement statement
- Requirement ID

## Output
- `valid`: boolean
- `issues`: list of problems found
- `suggestions`: list of improvements

## Validation Rules

### Must Pass
1. **Has ID**: Format `REQ-\d{4}`
2. **Uses "shall"**: Mandatory behavior uses "shall"
3. **Is atomic**: Single idea (no "and" joining independent requirements)
4. **Is verifiable**: Has measurable/observable criterion

### Should Pass
5. **Avoids ambiguity**: No words like "fast", "robust", "user-friendly" without quantification
6. **Has rationale**: Explains why requirement exists
7. **Has verification method**: Specifies Test/Analysis/Inspection/Demonstration
8. **Has priority**: Must/Should/Could

## Problematic Patterns

| Pattern | Issue | Fix |
|---------|-------|-----|
| "shall be fast" | Ambiguous | "shall respond within 100ms" |
| "shall be robust" | Unmeasurable | "shall handle 1000 concurrent users" |
| "shall be user-friendly" | Subjective | "shall complete task in < 3 clicks" |
| "shall X and Y" | Multiple requirements | Split into REQ-n and REQ-n+1 |
| "should" | Weak | Use "shall" for mandatory |

## Output Format
```yaml
validation:
  id: REQ-0001
  valid: false
  issues:
    - type: ambiguity
      text: "Statement uses 'fast' without quantification"
      severity: major
  suggestions:
    - "Replace 'fast' with specific timing requirement (e.g., '< 100ms')"
    - "Add verification_method field"
```

## Example

**Input**:
```yaml
id: REQ-0001
statement: "The system shall be fast and robust"
```

**Output**:
```yaml
validation:
  id: REQ-0001
  valid: false
  issues:
    - type: ambiguity
      text: "'fast' is not quantified"
      severity: major
    - type: ambiguity
      text: "'robust' is not measurable"
      severity: major
    - type: atomicity
      text: "Contains 'and' joining independent concepts"
      severity: minor
  suggestions:
    - "Split into two requirements"
    - "Define 'fast' as specific response time"
    - "Define 'robust' as specific failure handling"
```

## Used By
- `requirements-reviewer.md`
