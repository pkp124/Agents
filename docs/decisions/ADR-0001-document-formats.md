# ADR-0001: Document formats (YAML requirements, MD design/use-cases, YAML plans)

## Status
Accepted

## Decision
Use:

- **Requirements**: structured **YAML** in `docs/requirements/*.yml|*.yaml`
- **Design specifications**: **Markdown** in `docs/design/*.md`
- **Use cases**: **Markdown** in `docs/use_cases/*.md`
- **Assumptions of use**: **Markdown** in `docs/assumptions/*.md`
- **Verification plans**: structured **YAML** in `docs/verification/*.yml|*.yaml`
- **Test plans**: structured **YAML** in `docs/test_plans/*.yml|*.yaml`
- **Test strategy**: **Markdown** in `docs/test_strategy/*.md`

## Rationale (critical review)

### Why YAML for requirements/plans
- **Machine-readable**: enables automated traceability checks, dashboards, and “missing coverage” reports.
- **Consistency**: forces required fields (priority, verification method, rationale).
- **Diffability**: stable keys reduce “wordsmith churn” when reviewing changes.

### Risks / downsides (and how we mitigate them)
- **Narrative loss**: YAML is poor for long-form reasoning and diagrams.
  - Mitigation: keep **design/test strategy** in Markdown.
- **Schema drift**: without a schema, YAML becomes inconsistent.
  - Mitigation: maintain templates + (optionally) add a schema validator later.
- **Merge conflicts / ordering churn**: list re-ordering creates noisy diffs.
  - Mitigation: keep `requirements[]` sorted by `id`; prefer additive changes.
- **Over-structuring**: forcing every nuance into fields can hide real ambiguity.
  - Mitigation: allow a `notes` field and keep clarifications in design/use-cases.

### Why Markdown for design/use-cases/test strategy/assumptions
- **Human review**: critical reviews need readable narrative, trade-offs, and context.
- **Structure with flexibility**: headings/checklists work well for CDR and doc reviews.
- **Better for examples**: code blocks, tables, and diagrams integrate naturally.

## Implications
- `tools/traceability/check_traceability.py` treats YAML requirement files as the **source of truth** for `REQ-xxxx` IDs.
- Design and tests must still reference `REQ-xxxx` in text/comments for traceability.
- Verification/test plans can be used to plan coverage before code exists, and later reconciled with implemented tests.

