# Traceability tooling

## What it enforces

`check_traceability.py` enforces:

- Every `REQ-xxxx` defined under `docs/requirements/` is referenced by:
  - at least one design doc in `docs/design/`
  - at least one test file in `tests/`
- Design/tests do not reference unknown `REQ-xxxx` IDs.

## Run locally

```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

