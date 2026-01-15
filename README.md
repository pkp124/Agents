# Development Practices Agents (C++ & Python)

This repository is a **collection of reusable “agents” (prompt playbooks)** plus **templates, conventions, and CI checks** to help teams follow:

- **Test Driven Development (TDD)**
- **V-model development** (requirements → design → implementation → verification)
- **Critical design reviews (CDR)** and document reviews
- **Bidirectional traceability**:
  - Requirement ↔ Design
  - Requirement ↔ Test
  - (optional) Design ↔ Test
- **Change-aware documentation** (docs evolve with code)
- **CI impact review** (new tests added to CI; CI config changes reviewed)

## Repository structure (recommended)

```
docs/
  product/        # PRDs, customer/user goals, roadmap notes
  requirements/   # verifiable requirements (REQ-xxxx)
  use_cases/      # use cases (UC-xxxx)
  design/         # design specs (DES-xxxx)
  user/           # user-facing docs and guides
  traceability/   # traceability conventions + reports
  reviews/        # review checklists and gates

src/              # product source code (C++ and/or Python)
tests/            # unit/integration/system tests
tools/            # repo tooling (traceability checks, doc lint, generators)
ci/               # helper scripts used by CI
.github/workflows # GitHub Actions workflows
agents/           # agent prompt playbooks (role-focused)
```

## ID conventions (traceability)

This repo uses stable IDs so traceability can be enforced by automation.

- **Requirements**: `REQ-0001`, `REQ-0002`, …
- **Use cases**: `UC-0001`, …
- **Design items**: `DES-0001`, …
- **Tests** (optional): `TST-0001`, …

### Referencing rules

- A **design document must reference the requirements** it satisfies (e.g. `Traces to: REQ-0001`).
- A **test must reference the requirements** it verifies (e.g. a comment/docstring containing `REQ-0001`).
- CI enforces that **every requirement has at least one design reference and at least one test reference** (configurable in `tools/traceability/check_traceability.py`).

## The “agents”

See `agents/README.md` for the list of agent roles and how to use them for:

- TDD coaching and test planning
- Requirements authoring and review
- Design authoring and critical design review
- Traceability management and enforcement
- CI impact review
- C++ and Python style / quality enforcement

## Quick start

- Start with the templates in `docs/**`.
- Add a requirement in `docs/requirements/`.
- Add a matching design in `docs/design/` that references the requirement.
- Add tests under `tests/` that reference the requirement ID.
- Run the traceability check:

```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

CI will run the same checks on every PR.

