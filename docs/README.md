# Documentation (V-model)

This repository keeps requirements, design, tests, and user-facing docs in one place to enable **rapid iteration with strong traceability**.

## Folders

- `product/`: PRDs, problem statements, user value, release notes drafts.
- `requirements/`: verifiable requirements (`REQ-xxxx`).
- `use_cases/`: use cases (`UC-xxxx`) that drive requirements and test scenarios.
- `design/`: design specs (`DES-xxxx`) that trace to requirements.
- `user/`: user-facing docs (how-to, guides, CLI/API docs).
- `traceability/`: traceability rules and (optionally) generated reports.
- `reviews/`: review checklists and gates (CDR, doc reviews).

## Traceability expectation

For every `REQ-xxxx`:

- At least one design doc in `docs/design/` references it (e.g. `Traces to: REQ-0001`).
- At least one test under `tests/` references it (e.g. a comment/docstring containing `REQ-0001`).

Automation enforces this via `tools/traceability/check_traceability.py`.

