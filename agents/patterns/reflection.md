# Pattern: Reflection (Self-Critique)

## Overview

The Reflection pattern involves an agent generating output, then critiquing its own output to identify issues and improve it. This creates a self-improvement loop.

## Pattern Structure

```
┌─────────────────────────────────────────────────────────────────┐
│                       Reflection Loop                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│    ┌──────────┐     ┌──────────┐     ┌──────────┐              │
│    │ GENERATE │────▶│ CRITIQUE │────▶│  REVISE  │              │
│    │          │     │          │     │          │              │
│    │ Create   │     │ Find     │     │ Fix      │              │
│    │ initial  │     │ issues   │     │ issues   │              │
│    │ output   │     │          │     │          │              │
│    └──────────┘     └──────────┘     └────┬─────┘              │
│         ▲                                  │                    │
│         │                                  │                    │
│         └──────────────────────────────────┘                    │
│                  (loop until satisfied)                         │
└─────────────────────────────────────────────────────────────────┘
```

## Template

```markdown
## Initial Output
[First attempt at the task]

## Self-Critique
### What's Good
- [Positive aspect 1]
- [Positive aspect 2]

### What's Wrong
- [Issue 1]: [Explanation]
- [Issue 2]: [Explanation]

### Missing Elements
- [Missing 1]
- [Missing 2]

## Revised Output
[Improved version addressing the critique]

## Final Check
- [ ] Issue 1 addressed
- [ ] Issue 2 addressed
- [ ] Missing elements added
```

## Example: Requirement Writing with Reflection

```markdown
## Initial Output
**REQ-0010**: The system shall be fast.

## Self-Critique
### What's Good
- Uses "shall" correctly
- Has an ID

### What's Wrong
- **Ambiguous**: "fast" is not quantified
- **Not verifiable**: No measurable criterion
- **Incomplete**: No context about what operation

### Missing Elements
- Specific performance target
- Verification method
- Rationale

## Revised Output
**REQ-0010**: Response Time
- **Statement**: The system shall respond to API requests within 100 milliseconds at the 99th percentile under normal load (1000 concurrent users).
- **Rationale**: User experience studies show response times over 100ms are perceived as slow.
- **Verification**: Performance test under load

## Final Check
- [x] Quantified (100ms, p99)
- [x] Verifiable (performance test)
- [x] Context provided (API requests, load conditions)
```

## When to Use

- After generating any artifact (requirements, design, code, tests)
- When quality is critical
- For learning and improvement
- Before finalizing deliverables

## Reflection Prompts

### For Requirements
- Is it verifiable with a test?
- Is there only one interpretation?
- Does it use "shall" correctly?
- Is it atomic (one idea)?

### For Design
- Does it trace to requirements?
- Are failure modes covered?
- Is the test strategy clear?

### For Code
- Is it readable?
- Is it testable?
- Does it handle errors?

### For Tests
- Is it deterministic?
- Does it test behavior, not implementation?
- Are edge cases covered?

## Multi-Turn Reflection

For complex artifacts, use multiple reflection rounds:

```
Round 1: Check structure and completeness
Round 2: Check correctness and logic
Round 3: Check style and clarity
Round 4: Final polish
```

## Integration with Agents

Agents that use Reflection pattern:
- `requirements-reviewer.md` - Critiques requirements
- `cdr-reviewer.md` - Critiques design
- `test-reviewer.md` - Critiques tests
- `senior-architect.md` - Reflects on architecture
