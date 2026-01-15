# Design: Traceability Checker

## Overview
Provide a lightweight repository tool that enforces traceability between requirements, design documentation, and tests.

## Goals / non-goals
- Goals:
  - Enforce that each `REQ-xxxx` is referenced by at least one design doc and at least one test.
  - Fail CI with an actionable report if traceability is missing.
- Non-goals:
  - Full requirements management system.
  - Enforcing design↔test traceability (optional in the future).

## Traces to
- Requirements: `REQ-0001`

## Architecture
`tools/traceability/check_traceability.py` scans:

- `docs/requirements/**` to establish the set of known requirement IDs.
- `docs/design/**` to find references to known requirement IDs.
- `tests/**` to find references to known requirement IDs.

It exits non-zero if any requirement is missing design/test references or if unknown requirement IDs are referenced.

## Test strategy
- Unit tests validate the checker behavior on a temporary directory structure.
- CI runs the checker against the repository docs and tests.

