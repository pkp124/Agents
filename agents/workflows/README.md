# Workflow Patterns

This directory contains pre-defined workflow patterns that compose multiple agents for common development scenarios.

## Available Workflows

| Workflow | Description | Primary Agents |
|----------|-------------|----------------|
| `new-feature.md` | End-to-end new feature development | All phases |
| `bug-fix.md` | Bug investigation and fix | TDD + Traceability |
| `refactor.md` | Safe refactoring with test coverage | Test + Quality |
| `requirements-update.md` | Modify existing requirements | Requirements + Traceability |
| `design-review.md` | Prepare and conduct CDR | Design + Review |

## Workflow Selection Guide

### When to Use Each Workflow

**New Feature** (`new-feature.md`)
- Starting work on a new capability
- Implementing a user story from scratch
- Adding significant new functionality

**Bug Fix** (`bug-fix.md`)
- Fixing a reported defect
- Addressing regression
- Correcting unexpected behavior

**Refactor** (`refactor.md`)
- Improving code without changing behavior
- Reducing technical debt
- Restructuring for maintainability

**Requirements Update** (`requirements-update.md`)
- Changing existing requirements
- Adding derived requirements
- Updating verification methods

**Design Review** (`design-review.md`)
- Preparing for Critical Design Review
- Getting feedback on architecture
- Validating design decisions
