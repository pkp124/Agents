# Agents (Prompt Playbooks)

These files are **role-focused prompt playbooks** designed for AI coding assistants (Cursor, Copilot, etc.). They enforce **TDD + V-model + traceability** practices.

## Quick Start

1. **Start with the Orchestrator**: Use `orchestrator.md` to determine the right workflow
2. **Pick the appropriate agent(s)** for your task
3. **Provide required inputs** (files, IDs, acceptance criteria)
4. **Follow agent outputs** (checklists, file edits)
5. **Run traceability check** before committing

## Agent Hierarchy

```
┌─────────────────────────────────────────────────────────────────┐
│                       ORCHESTRATOR                               │
│                    (orchestrator.md)                             │
│          Coordinates workflow, selects sub-agents                │
└─────────────────────────────────────────────────────────────────┘
                              │
    ┌─────────────────────────┼─────────────────────────┐
    │                         │                         │
    ▼                         ▼                         ▼
┌─────────────────┐   ┌─────────────────┐   ┌─────────────────┐
│  REQUIREMENTS   │   │    DESIGN &     │   │ IMPLEMENTATION  │
│   ENGINEERING   │   │  ARCHITECTURE   │   │   & TESTING     │
├─────────────────┤   ├─────────────────┤   ├─────────────────┤
│ requirements-   │   │ senior-         │   │ tdd-coach       │
│   author ⭐     │   │   architect ⭐  │   │ test-generator  │
│ requirements-   │   │ design-author   │   │ test-reviewer   │
│   reviewer      │   │ cdr-reviewer    │   │ test-coverage-  │
│ use-case-author │   │                 │   │   analyst ⭐    │
│                 │   │                 │   │ python-quality- │
│                 │   │                 │   │   enforcer      │
│                 │   │                 │   │ cpp-quality-    │
│                 │   │                 │   │   enforcer      │
└─────────────────┘   └─────────────────┘   └─────────────────┘
    │                         │                         │
    └─────────────────────────┼─────────────────────────┘
                              │
                              ▼
              ┌───────────────────────────────┐
              │        CROSS-CUTTING          │
              ├───────────────────────────────┤
              │ review-coordinator ⭐         │
              │ traceability-manager (enhanced)│
              │ ci-impact-reviewer            │
              │ doc-change-manager            │
              │ user-doc-reviewer             │
              └───────────────────────────────┘

⭐ = New or significantly enhanced agent
```

## Agent Catalog

### Meta-Agent
| Agent | Purpose |
|-------|---------|
| `orchestrator.md` | Coordinates workflow, selects sub-agents, manages phases |

### Requirements Engineering
| Agent | Purpose |
|-------|---------|
| `requirements-author.md` ⭐ | **Full RE lifecycle**: elicitation, analysis, specification, validation, management |
| `requirements-reviewer.md` | Reviews requirements for quality (verifiable, unambiguous, complete) |
| `use-case-author.md` | Writes use cases (UC-xxxx) and user scenarios |

### Architecture & Design
| Agent | Purpose |
|-------|---------|
| `senior-architect.md` ⭐ | **System-level architecture**: cross-cutting concerns, ADRs, patterns, mentoring |
| `design-author.md` | Creates detailed design documents (DES-xxxx) |
| `cdr-reviewer.md` | Runs Critical Design Review |

### Testing & Coverage
| Agent | Purpose |
|-------|---------|
| `tdd-coach.md` | Guides TDD workflow (red→green→refactor) |
| `test-generator.md` | Generates tests from requirements |
| `test-reviewer.md` | Reviews test quality (determinism, value, traceability) |
| `test-coverage-analyst.md` ⭐ | **Coverage strategy**: gap analysis, risk-based testing, coverage reports |

### Code Quality
| Agent | Purpose |
|-------|---------|
| `cpp-quality-enforcer.md` | C++ code quality and conventions |
| `python-quality-enforcer.md` | Python code quality and conventions |

### Reviews & Coordination
| Agent | Purpose |
|-------|---------|
| `review-coordinator.md` ⭐ | **Unified review process**: orchestrates reviews, manages findings, tracks approval |

### Traceability & Documentation
| Agent | Purpose |
|-------|---------|
| `traceability-manager.md` ⭐ | REQ↔DES↔TEST links, **impact analysis**, gap reports |
| `ci-impact-reviewer.md` | Reviews CI/CD changes |
| `doc-change-manager.md` | Keeps docs in sync with code |
| `user-doc-reviewer.md` | Reviews user documentation |

**⭐ = New or significantly enhanced in latest update**

## Agent Composition Patterns

### Pattern 1: Author → Reviewer Chain
```
requirements-author → requirements-reviewer → [approved/revise]
design-author → cdr-reviewer → [approved/revise]
test-generator → test-reviewer → [approved/revise]
```

### Pattern 2: TDD Cycle
```
tdd-coach (plan) → test-generator (red) → [implement] (green) → [refactor]
                                    ↑__________________________|
```

### Pattern 3: Traceability Verification
```
[any authoring agent] → traceability-manager → [gap report] → [fix gaps]
```

### Pattern 4: Full Feature Workflow
```
requirements-author → requirements-reviewer
        ↓
use-case-author (optional)
        ↓
design-author → cdr-reviewer
        ↓
traceability-manager (verify REQ↔DES)
        ↓
tdd-coach → test-generator → [implement] → test-reviewer
        ↓
traceability-manager (verify REQ↔TEST)
        ↓
ci-impact-reviewer → doc-change-manager → user-doc-reviewer
```

## ID Conventions

All agents use consistent ID formats:
- Requirements: `REQ-0001`, `REQ-0002`, ...
- Use Cases: `UC-0001`, ...
- Design Items: `DES-0001`, ...
- Tests (optional): `TST-0001`, ...

## How to Use an Agent

1. **Read the agent file** to understand inputs/outputs
2. **Gather required inputs** (linked files, IDs, criteria)
3. **Invoke the agent** in your AI assistant
4. **Follow the checklist** the agent produces
5. **Apply file edits** as directed
6. **Run verification** (traceability check, tests, linting)

## CI Enforcement

The repository includes automated checks:
- `tools/traceability/check_traceability.py` - Verifies REQ↔DES↔TEST links
- GitHub Actions workflow runs on every PR

## Adding New Agents

When creating a new agent:
1. Follow the existing format (Mission, Inputs, Outputs, Rules, Checklist)
2. Define clear inputs and expected outputs
3. Include relevant ID conventions
4. Add traceability requirements where applicable
5. Update this README with the new agent
6. Consider where it fits in the hierarchy
