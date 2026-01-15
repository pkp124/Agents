# Traceability guidelines (REQ↔DES↔TEST)

## ID formats

- Requirements: `REQ-0001`
- Use cases: `UC-0001`
- Design items: `DES-0001`
- Tests (optional): `TST-0001`

## Where IDs must appear

- **Requirements** live in `docs/requirements/**` as **YAML** and define the source-of-truth set of `REQ-xxxx`.
- **Design documents** in `docs/design/**` must reference requirements they satisfy in a `Traces to` section.
- **Tests** under `tests/**` must reference the requirement IDs they verify (comment or docstring is fine).

## Automation

`tools/traceability/check_traceability.py` enforces:

- each `REQ-xxxx` has at least one reference in `docs/design/**`
- each `REQ-xxxx` has at least one reference in `tests/**`
- design/test references do not point to unknown requirement IDs

## Recommended patterns

### In design docs

```
## Traces to
- Requirements: REQ-0001, REQ-0002
```

### In tests

```python
def test_some_behavior():
    # REQ-0001
    ...
```

```cpp
TEST(Foo, DoesThing) {
  // REQ-0001
}
```

