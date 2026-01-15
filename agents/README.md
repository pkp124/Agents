# Agents (prompt playbooks)

These files are **role-focused prompt playbooks** you can paste into your assistant tool of choice (Cursor Agents, Copilot Chat, etc.). They’re designed to enforce **TDD + V-model + traceability** in a single repository that contains docs, code, tests, and CI.

## How to use

- Pick the agent matching the task.
- Provide the relevant inputs (linked files, requirements/design IDs, acceptance criteria).
- Ask the agent to produce outputs in the requested format (usually a checklist + concrete file edits).
- Run CI locally (or rely on CI) and ensure traceability checks pass.

## Agent catalog

- `tdd-coach.md`: drives TDD flow (red→green→refactor), test plan, coverage strategy.
- `requirements-author.md`: creates verifiable requirements with IDs, rationale, and testability.
- `requirements-reviewer.md`: reviews requirements for ambiguity, verifiability, completeness, and consistency.
- `use-case-author.md`: writes use cases and edge cases; ensures they map to requirements.
- `design-author.md`: writes design docs with requirement links, risks, alternatives, and test strategy.
- `cdr-reviewer.md`: runs a critical design review checklist and calls out gaps/risks.
- `test-generator.md`: generates high-value tests from requirements/design, maximizes coverage.
- `test-reviewer.md`: reviews tests for quality, determinism, and coverage realism.
- `traceability-manager.md`: maintains requirement↔design↔test links; resolves missing trace links.
- `ci-impact-reviewer.md`: reviews CI config changes; ensures new tests are wired into CI.
- `cpp-quality-enforcer.md`: C++ conventions, safety, build/test structure, and review checklist.
- `python-quality-enforcer.md`: Python conventions, typing, packaging, and review checklist.
- `doc-change-manager.md`: ensures documents and user-facing docs stay synchronized with code changes.
- `user-doc-reviewer.md`: reviews user-facing docs for clarity, accuracy, and change impact.

## ID conventions

All agents assume these IDs:

- Requirements: `REQ-0001`
- Use cases: `UC-0001`
- Design items: `DES-0001`
- Tests (optional): `TST-0001`

## CI enforcement

The repository includes a traceability checker in `tools/traceability/check_traceability.py` and a GitHub Actions workflow that fails if:

- a requirement has **no design reference**, or
- a requirement has **no test reference**.

