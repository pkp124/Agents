# Pattern: ReAct (Reasoning + Acting)

## Overview

ReAct interleaves reasoning (thinking) with acting (tool use/actions) in a loop. The agent reasons about what to do, takes an action, observes the result, and reasons again.

## Pattern Structure

```
┌─────────────────────────────────────────────────────────────────┐
│                         ReAct Loop                               │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│    ┌──────────┐     ┌──────────┐     ┌──────────┐              │
│    │ THOUGHT  │────▶│  ACTION  │────▶│OBSERVATION│             │
│    │          │     │          │     │          │              │
│    │ Reason   │     │ Execute  │     │ See      │              │
│    │ about    │     │ tool or  │     │ result   │              │
│    │ next step│     │ action   │     │          │              │
│    └──────────┘     └──────────┘     └────┬─────┘              │
│         ▲                                  │                    │
│         │                                  │                    │
│         └──────────────────────────────────┘                    │
│                    (loop until done)                            │
└─────────────────────────────────────────────────────────────────┘
```

## Template

```markdown
## Task: [Description]

### Step 1
**Thought**: [Reasoning about what to do next]
**Action**: [Specific action to take]
**Observation**: [Result of the action]

### Step 2
**Thought**: [Based on observation, what next?]
**Action**: [Next action]
**Observation**: [Result]

... (continue until task complete)

### Conclusion
**Thought**: [Final reasoning]
**Result**: [Final output]
```

## Example: Bug Investigation

```markdown
## Task: Investigate failing test in test_calculator.cpp

### Step 1
**Thought**: I need to understand what test is failing and why.
**Action**: Run the failing test with verbose output
**Observation**: 
```
test_divide: FAILED
Expected: 3.333333
Actual: 3
```

### Step 2
**Thought**: The division result is truncated. This suggests integer division.
**Action**: Read the divide implementation in calculator.cpp
**Observation**:
```cpp
double Calculator::divide(double a, double b) {
    return (int)a / (int)b;  // Bug: casting to int
}
```

### Step 3
**Thought**: Found the bug - unnecessary cast to int. I should fix it.
**Action**: Remove the int casts
**Observation**: Code changed to `return a / b;`

### Step 4
**Thought**: Need to verify the fix works.
**Action**: Run tests
**Observation**: All tests pass

### Conclusion
**Thought**: Bug was integer division due to explicit casts. Fixed by removing casts.
**Result**: Bug fixed, all tests passing.
```

## When to Use

- Complex debugging tasks
- Multi-step investigations
- Tasks requiring tool use
- When you need to show reasoning

## Integration with Agents

Agents that use ReAct pattern:
- `tdd-coach.md` - TDD cycle with reasoning
- `traceability-manager.md` - Gap analysis
- `test-coverage-analyst.md` - Coverage investigation

## Implementation Tips

1. **Be explicit about thoughts** - Write out reasoning
2. **Keep actions atomic** - One action per step
3. **Observe before concluding** - Don't assume results
4. **Know when to stop** - Define completion criteria
