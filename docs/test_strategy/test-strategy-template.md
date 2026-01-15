# Test Strategy: <Feature/Subsystem>

## Scope and goals
- What quality risks this strategy addresses.
- What is explicitly out of scope.

## Test levels
- Unit tests:
  - what is mocked vs not mocked
  - determinism guidance
- Integration tests:
  - external dependencies and how they are simulated
- System/E2E tests:
  - when they run and what they prove

## Coverage strategy
- Boundaries and equivalence classes
- Negative testing and failure modes
- Concurrency/time-based behavior strategy (if applicable)
- Regression policy

## Tooling and CI
- Which tests run on PR vs nightly
- Timeouts, flake control, and quarantine policy

## Traceability
- How tests will reference `REQ-xxxx`
- How verification/test plans map `REQ-xxxx` to planned tests

