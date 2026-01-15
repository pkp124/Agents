# Cursor Prompts (Commands)

These prompt templates provide structured workflows for common TDD and V-model development tasks.

## Available Prompts

### TDD Cycle
| Prompt | Description |
|--------|-------------|
| `tdd-red.md` | Write failing test (Red phase) |
| `tdd-green.md` | Implement minimal code (Green phase) |
| `tdd-refactor.md` | Improve code quality (Refactor phase) |

### Requirements & Design
| Prompt | Description |
|--------|-------------|
| `new-requirement.md` | Create a new requirement (REQ-xxxx) |
| `create-design.md` | Create a design document (DES-xxxx) |

### Testing & Quality
| Prompt | Description |
|--------|-------------|
| `generate-tests.md` | Generate tests from requirements |
| `check-traceability.md` | Verify REQ↔DES↔TEST links |
| `code-review.md` | Review code for quality and traceability |

## How to Use

1. Open the prompt file you need
2. Replace `{{PLACEHOLDERS}}` with your specific values
3. Copy the prompt to your AI assistant
4. Follow the structured workflow

## Typical Workflow

### Adding a New Feature
1. `new-requirement.md` → Create REQ-xxxx
2. `create-design.md` → Create DES-xxxx  
3. `tdd-red.md` → Write failing tests
4. `tdd-green.md` → Implement
5. `tdd-refactor.md` → Clean up
6. `check-traceability.md` → Verify links

### Fixing a Bug
1. `tdd-red.md` → Write failing test that reproduces bug
2. `tdd-green.md` → Fix the bug
3. `check-traceability.md` → Verify links

### Code Review
1. `code-review.md` → Comprehensive review
