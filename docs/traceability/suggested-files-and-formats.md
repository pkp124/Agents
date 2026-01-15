# Suggested files and formats (V-model + TDD)

This document defines **recommended file locations, naming, and required sections** so requirements, designs, tests, and CI can be reviewed consistently and traced automatically.

## Canonical folders

- `docs/product/`: PRDs, problem statements, release notes drafts
- `docs/requirements/`: verifiable requirements (source of truth)
- `docs/use_cases/`: use cases and alternate flows
- `docs/design/`: design specs
- `docs/user/`: user-facing docs and guides
- `docs/traceability/`: traceability rules and generated reports
- `docs/reviews/`: review checklists and gates
- `src/`: implementation
- `tests/`: verification (unit/integration/system)
- `.github/workflows/`: CI enforcement
- `tools/`: repo tooling (traceability, generators, doc checks)

## File naming conventions

### Requirements
- **Path**: `docs/requirements/REQ-0001-<slug>.yaml` (or `.yml`)
- **Example**: `docs/requirements/REQ-0042-rate-limiter.yaml`

### Use cases
- **Path**: `docs/use_cases/UC-0001-<slug>.md`

### Design
- **Path**: `docs/design/DES-0001-<slug>.md`

### Tests
Keep tests under `tests/` and group by level:

- `tests/unit/...`
- `tests/integration/...`
- `tests/system/...`

Each test file should contain the requirement IDs it verifies (e.g. `REQ-0042`) in comments/docstrings.

## Required content format (recommended)

### Requirement document (`REQ-xxxx-*.yml` / `REQ-xxxx-*.yaml`)

Minimum required fields (recommended schema):

- `schema_version`
- `feature`
- `context`
- `definitions`
- `requirements[]` with:
  - `id` (`REQ-xxxx`)
  - `title`
  - `statement` (“shall”)
  - `rationale`
  - `verification_method`
  - `priority`

Use `docs/requirements/requirements-template.yaml` as the starting point.

### Use case document (`UC-xxxx-*.md`)

Minimum required sections:

- Primary actor
- Preconditions / Trigger
- Main success scenario
- Extensions / alternate flows (failure modes!)
- Postconditions
- Linked requirements (`REQ-xxxx`)

Use `docs/use_cases/use-case-template.md`.

### Design document (`DES-xxxx-*.md`)

Minimum required sections:

- Overview, Goals/non-goals
- **Traces to** (explicit list of `REQ-xxxx` and optionally `UC-xxxx`)
- Architecture (components, boundaries, interfaces)
- Invariants / failure modes
- Test strategy (or reference to a `docs/test_strategy/*.md` document)
- Alternatives considered

Use `docs/design/design-template.md`.

### Test references (in `tests/**`)

Recommended patterns:

```python
def test_behavior():
    # REQ-0042
    ...
```

```cpp
TEST(Foo, Behavior) {
  // REQ-0042
}
```

## Automation

### Traceability check (CI enforced)

Run:

```bash
python3 tools/traceability/check_traceability.py --docs docs --tests tests
```

It enforces:
- each `REQ-xxxx` is referenced by at least one design doc in `docs/design/`
- each `REQ-xxxx` is referenced by at least one test under `tests/`
- design/tests do not reference unknown `REQ-xxxx`

### Traceability matrix generation (recommended)

Generate a simple matrix report:

```bash
python3 tools/traceability/generate_matrix.py --docs docs --tests tests --output docs/traceability/traceability-matrix.md
```

### Verification and test plans (YAML)

- Verification plans: `docs/verification/*.yaml`
- Test plans: `docs/test_plans/*.yaml`

