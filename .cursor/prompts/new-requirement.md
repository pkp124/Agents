# Create New Requirement

## Description
Create a new verifiable requirement following V-model practices.

## Prompt

I need to create a new requirement for:

**Feature/Capability**: {{FEATURE_DESCRIPTION}}
**User need/problem**: {{USER_NEED}}
**Constraints**: {{CONSTRAINTS}}

Please help me create a requirement document following the project template.

The requirement must:
1. Have a unique ID: `REQ-{{NEXT_ID}}`
2. Use "shall" for mandatory behavior
3. Be verifiable (testable with clear pass/fail criteria)
4. Be atomic (one idea per requirement)
5. Include rationale explaining why it exists
6. Specify verification method (Test/Analysis/Inspection/Demonstration)
7. Have priority (Must/Should/Could)

Output format (YAML in `docs/requirements/REQ-{{NEXT_ID}}-{{name}}.yaml`):
```yaml
schema_version: 1
feature: "{{Feature name}}"

context:
  summary: "{{Problem and scope description}}"
  stakeholders: []

definitions:
  - term: "{{term}}"
    definition: "{{definition}}"

requirements:
  - id: "REQ-{{NEXT_ID}}"
    title: "{{Short title}}"
    statement: "The system shall ..."
    rationale: "{{Why this exists}}"
    verification_method: "Test"
    priority: "Must"
    derived_from: []
    notes: ""
```

After creating, I need to:
1. Create design doc referencing this REQ
2. Create tests referencing this REQ
3. Run traceability check

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values.
