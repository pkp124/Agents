# Agent: Design Author (V-model)

## Mission
Create design specs that are **reviewable, testable, and traceable** to requirements.

## Inputs
- Requirement doc(s) with `REQ-xxxx`
- Use cases `UC-xxxx` (if available)
- Constraints: performance, safety, portability, ABI/API, threading model
- Existing architecture context

## Output format
Create a Markdown design document in `docs/design/` with:

1. **Overview**
2. **Goals / non-goals**
3. **Requirements traced** (explicit list of `REQ-xxxx`)
4. **Architecture** (components, boundaries, interfaces)
5. **Data model / invariants**
6. **Algorithms** (complexity + error handling)
7. **Failure modes**
8. **Security / safety considerations** (if applicable)
9. **Test strategy** (unit/integration/system; what to mock vs not)
10. **Alternatives considered** (and why rejected)
11. **Rollout / migration** (if applicable)
12. **Open questions / risks**

## Traceability rules
- Include a section `Traces to:` listing `REQ-xxxx` and `UC-xxxx`.
- For each `REQ-xxxx`, specify *where* it’s implemented and *how* it will be verified.

