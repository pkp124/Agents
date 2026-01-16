# Pattern: Planning (Task Decomposition)

## Overview

The Planning pattern decomposes complex tasks into smaller, manageable subtasks. Each subtask can be executed independently or delegated to specialized agents.

## Pattern Structure

```
┌─────────────────────────────────────────────────────────────────┐
│                         Planning                                 │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│    ┌──────────┐     ┌──────────┐     ┌──────────┐              │
│    │ ANALYZE  │────▶│DECOMPOSE │────▶│ EXECUTE  │              │
│    │          │     │          │     │          │              │
│    │ Understand│    │ Break    │     │ Run each │              │
│    │ the goal │     │ into     │     │ subtask  │              │
│    │          │     │ subtasks │     │          │              │
│    └──────────┘     └──────────┘     └────┬─────┘              │
│                                           │                     │
│                                           ▼                     │
│                                    ┌──────────┐                │
│                                    │SYNTHESIZE│                │
│                                    │          │                │
│                                    │ Combine  │                │
│                                    │ results  │                │
│                                    └──────────┘                │
└─────────────────────────────────────────────────────────────────┘
```

## Template

```markdown
## Goal
[High-level objective]

## Analysis
- What is the desired outcome?
- What are the constraints?
- What dependencies exist?

## Plan
### Phase 1: [Name]
- [ ] Task 1.1: [Description]
- [ ] Task 1.2: [Description]

### Phase 2: [Name]
- [ ] Task 2.1: [Description] (depends on 1.1)
- [ ] Task 2.2: [Description]

### Phase 3: [Name]
- [ ] Task 3.1: [Description] (depends on 2.1, 2.2)

## Execution
[Track progress through tasks]

## Synthesis
[Combine results into final deliverable]
```

## Example: New Feature Planning

```markdown
## Goal
Add a `median()` function to the Statistics class.

## Analysis
- **Outcome**: Working median function with tests and docs
- **Constraints**: Must follow existing code patterns, maintain traceability
- **Dependencies**: Existing Statistics class, test framework

## Plan

### Phase 1: Requirements (Day 1)
- [ ] Task 1.1: Add REQ-0006 for median calculation
- [ ] Task 1.2: Review requirement with `requirements-reviewer`

### Phase 2: Design (Day 1)
- [ ] Task 2.1: Update DES-0001 with median design
- [ ] Task 2.2: Document algorithm and complexity
- [ ] Task 2.3: Add to "Traces to" section

### Phase 3: Test (TDD Red) (Day 2)
- [ ] Task 3.1: Write test_median() function
- [ ] Task 3.2: Include REQ-0006 reference
- [ ] Task 3.3: Cover edge cases (empty, single, even, odd)
- [ ] Task 3.4: Verify test fails

### Phase 4: Implementation (TDD Green) (Day 2)
- [ ] Task 4.1: Add declaration to statistics.hpp
- [ ] Task 4.2: Implement in statistics.cpp
- [ ] Task 4.3: Run tests - verify pass

### Phase 5: Refactor (Day 2)
- [ ] Task 5.1: Review code quality
- [ ] Task 5.2: Optimize if needed
- [ ] Task 5.3: Run tests - verify still pass

### Phase 6: Documentation (Day 3)
- [ ] Task 6.1: Update API reference
- [ ] Task 6.2: Add usage example to getting-started.md
- [ ] Task 6.3: Update README

### Phase 7: Verification (Day 3)
- [ ] Task 7.1: Run traceability check
- [ ] Task 7.2: Run full test suite
- [ ] Task 7.3: Review with `test-reviewer`

## Execution
[Update checkboxes as tasks complete]

## Synthesis
All phases complete. Median function ready for merge.
```

## Planning with Agent Delegation

```markdown
## Plan with Agent Assignments

| Task | Agent | Status |
|------|-------|--------|
| Create requirement | `requirements-author` | ⬜ |
| Review requirement | `requirements-reviewer` | ⬜ |
| Update design | `design-author` | ⬜ |
| Write tests | `tdd-coach` | ⬜ |
| Implement | (developer) | ⬜ |
| Review code | `cpp-quality-enforcer` | ⬜ |
| Check traceability | `traceability-manager` | ⬜ |
| Update docs | `doc-change-manager` | ⬜ |
```

## Plan Adjustment

Plans should be dynamic:

```markdown
## Plan Revision
**Trigger**: Task 3.4 revealed missing edge case
**Adjustment**: Added Task 3.5: Test for NaN handling
**Impact**: Phase 4 delayed by 1 hour
```

## When to Use

- Complex features with multiple phases
- Tasks spanning multiple days
- Work requiring coordination
- When visibility of progress is needed

## Integration with Agents

Agents that use Planning pattern:
- `orchestrator.md` - Master workflow planning
- `review-coordinator.md` - Review process planning
- `senior-architect.md` - Architecture planning
