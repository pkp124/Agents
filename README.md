# Development Practices Agents (C++ & Python)

This repository is a **collection of reusable AI agents, workflows, skills, rules, and tools** to help teams follow:

- **Test Driven Development (TDD)** - Red → Green → Refactor
- **V-model development** - Requirements → Design → Implementation → Verification
- **Critical design reviews (CDR)** and document reviews
- **Bidirectional traceability** - REQ ↔ Design ↔ Test
- **Change-aware documentation** - Docs evolve with code
- **CI enforcement** - Automated quality gates

## Quick Start

```bash
# 1. Check current traceability status
python tools/traceability/check_traceability.py --docs docs --tests tests

# 2. Find next available IDs
python tools/traceability/find_next_id.py

# 3. Validate requirement quality
python tools/traceability/validate_requirements.py

# 4. Run tests
pytest
```

## Repository Structure

```
.cursor/
  rules/            # Contextual rules (auto-applied based on file patterns)
  prompts/          # Reusable prompt templates for common workflows

agents/
  orchestrator.md   # Meta-agent: coordinates workflows
  workflows/        # Pre-defined workflow patterns
  skills/           # Reusable task-focused capabilities
  *.md              # Role-focused agent playbooks

docs/
  product/          # PRDs, customer/user goals, roadmap notes
  requirements/     # Verifiable requirements (REQ-xxxx) - YAML
  use_cases/        # Use cases (UC-xxxx) - Markdown
  design/           # Design specs (DES-xxxx) - Markdown
  verification/     # Verification plans - YAML
  test_plans/       # Test plans - YAML
  traceability/     # Traceability conventions + reports
  reviews/          # Review checklists and gates
  user/             # User-facing docs and guides

src/                # Production source code (C++/Python)
tests/              # Unit/integration/system tests
tools/              # Repository tooling (traceability, validation)
.github/workflows/  # CI/CD workflows
```

## ID Conventions (Traceability)

All artifacts use stable, traceable IDs:

| Type | Format | Example | Location |
|------|--------|---------|----------|
| Requirement | `REQ-XXXX` | `REQ-0001` | `docs/requirements/` |
| Use Case | `UC-XXXX` | `UC-0001` | `docs/use_cases/` |
| Design | `DES-XXXX` | `DES-0001` | `docs/design/` |
| Test | `TST-XXXX` | `TST-0001` | `tests/` (optional) |

### Referencing Rules

- Design documents **must reference requirements** (e.g., `Traces to: REQ-0001`)
- Tests **must reference requirements** (e.g., comment `# REQ-0001`)
- CI enforces that every requirement has design and test coverage

## The Agents

### Agent Hierarchy

```
┌─────────────────────────────────────────────────────────────────┐
│                       ORCHESTRATOR                               │
│            Coordinates workflow, selects sub-agents              │
└─────────────────────────────────────────────────────────────────┘
                              │
        ┌─────────────────────┼─────────────────────┐
        ▼                     ▼                     ▼
   REQUIREMENTS           DESIGN              IMPLEMENTATION
   - requirements-author  - design-author     - tdd-coach
   - requirements-reviewer- cdr-reviewer      - test-generator
   - use-case-author                          - test-reviewer
                                              - cpp-quality-enforcer
                                              - python-quality-enforcer
        └─────────────────────┼─────────────────────┘
                              ▼
                        CROSS-CUTTING
                        - traceability-manager
                        - ci-impact-reviewer
                        - doc-change-manager
                        - user-doc-reviewer
```

### How to Use Agents

1. **Start with the orchestrator** (`agents/orchestrator.md`) to determine workflow
2. **Pick the appropriate agent** for your current task
3. **Follow pre-defined workflows** in `agents/workflows/` for common scenarios
4. **Use prompt templates** in `.cursor/prompts/` for quick access

See `agents/README.md` for the complete agent catalog.

## Cursor Integration

This repository includes Cursor-specific configurations:

### Global Rules (`.cursorrules`)
Applied to all interactions, defining project conventions.

### Contextual Rules (`.cursor/rules/*.mdc`)
Auto-applied based on file patterns:
- `requirements.mdc` - When editing `docs/requirements/**`
- `design.mdc` - When editing `docs/design/**`
- `tests.mdc` - When editing `tests/**`
- `python-src.mdc` - When editing `**/*.py`
- `cpp-src.mdc` - When editing `**/*.cpp`, `**/*.h`
- `ci-workflows.mdc` - When editing `.github/workflows/**`

### Prompt Templates (`.cursor/prompts/`)
Ready-to-use prompts for:
- TDD cycle: `tdd-red.md`, `tdd-green.md`, `tdd-refactor.md`
- Requirements: `new-requirement.md`, `create-design.md`
- Quality: `generate-tests.md`, `check-traceability.md`, `code-review.md`

## Tools

### Traceability Check (CI Required)
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

### Generate Traceability Matrix
```bash
python tools/traceability/generate_matrix.py --output docs/traceability/matrix.md
```

### Find Next Available ID
```bash
python tools/traceability/find_next_id.py
```

### Validate Requirements
```bash
python tools/traceability/validate_requirements.py
```

## Development Workflows

### New Feature (Full V-Model)
```
1. requirements-author    → Create REQ-xxxx
2. requirements-reviewer  → Validate requirements
3. design-author         → Create DES-xxxx with REQ refs
4. cdr-reviewer          → Critical design review
5. traceability-manager  → Verify REQ↔DES links
6. tdd-coach             → Write failing tests (Red)
7. [implement]           → Make tests pass (Green)
8. [refactor]            → Improve code quality
9. test-reviewer         → Review test quality
10. ci-impact-reviewer   → Ensure CI coverage
```

### Bug Fix (TDD)
```
1. Identify affected REQ-xxxx
2. Write failing test reproducing bug
3. Fix with minimal change
4. Verify all tests pass
5. Run traceability check
```

### Refactoring
```
1. Verify test coverage
2. Add tests for gaps
3. Refactor in small steps (keep tests green)
4. Run traceability check
```

## Pre-Commit Hooks

Install git hooks to enforce TDD + V-model practices before every commit:

```bash
# Install hooks
./tools/hooks/install-hooks.sh

# Or manually
pip install pre-commit && pre-commit install
```

### What Gets Checked Automatically

| Check | Description |
|-------|-------------|
| Ruff lint/format | Python code quality |
| Traceability | REQ↔DES↔TEST links complete |
| Requirement validation | Quality of requirement statements |
| Test REQ references | Tests must reference REQ-xxxx |
| Design traces | Design docs must have "Traces to" |

See `tools/hooks/README.md` for details.

## CI Integration

The GitHub Actions workflow (`.github/workflows/quality.yml`) runs:

1. **Ruff lint** - Python style
2. **Ruff format** - Python formatting
3. **Pytest** - Test execution
4. **Traceability check** - REQ↔DES↔TEST coverage

All checks must pass before merging.

## Getting Started

### Adding Your First Requirement

1. Find next ID:
   ```bash
   python tools/traceability/find_next_id.py --type REQ
   ```

2. Create requirement file:
   ```bash
   cp docs/requirements/requirements-template.yaml docs/requirements/REQ-0002-my-feature.yaml
   ```

3. Edit with your requirement details

4. Create matching design:
   ```bash
   cp docs/design/design-template.md docs/design/DES-0002-my-feature.md
   ```

5. Add `Traces to: REQ-0002` in design doc

6. Write tests with `# REQ-0002` comments

7. Verify traceability:
   ```bash
   python tools/traceability/check_traceability.py --docs docs --tests tests
   ```

## License

See [LICENSE](LICENSE) file.
