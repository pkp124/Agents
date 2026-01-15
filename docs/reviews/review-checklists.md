# Review checklists

## Critical Design Review (CDR)

- **Traceability**: design traces to `REQ-xxxx` (explicit list) and maps verification strategy.
- **Goals/non-goals** are explicit and align with PRD/use cases.
- **Interfaces**: clear boundaries, ownership, invariants, contracts.
- **Failure modes**: timeouts, retries, partial failures, resource limits.
- **Concurrency**: threading model and ordering constraints specified.
- **Security/safety**: threat model or safety hazards addressed where relevant.
- **Test strategy**: unit vs integration split; deterministic tests; coverage of edge cases.
- **Alternatives**: at least one credible alternative compared with rationale.
- **Operational impact**: migrations, rollout, backwards compatibility.

## Requirements review

- **Unambiguous**: no vague adjectives without measurable definitions.
- **Verifiable**: each requirement specifies how it is verified.
- **Atomic**: one idea per requirement; consistent terminology.
- **Complete**: includes error behavior and boundaries.
- **Prioritized**: Must/Should/Could (or equivalent).

## Test review

- **Deterministic**: no flaky timing; no uncontrolled randomness.
- **Value**: tests behavior, not private implementation.
- **Coverage**: boundaries + negative cases; critical failure modes.
- **Traceability**: tests reference `REQ-xxxx` they verify.

## User-facing documentation review

- **Correctness**: matches implemented behavior and defaults.
- **Clarity**: runnable steps; examples; defined terms.
- **Change impact**: migration notes and compatibility constraints included.
- **Troubleshooting**: common failure modes documented.

## CI impact review

- New tests are added to CI (or explicitly documented why not).
- Workflows remain least-privilege and reproducible.
- Caches are scoped; timeouts are sane; flakiness risks addressed.
- Traceability check remains enforced (not bypassed).

