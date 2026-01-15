# Create Design Document

## Description
Create a design document that traces to requirements.

## Prompt

I need to create a design document for:

**Requirements to address**: {{REQ_IDS}}
**System/Component**: {{COMPONENT_NAME}}
**Constraints**: {{CONSTRAINTS}}

Please help me create a design document following the V-model template.

The design must:
1. Have a unique ID: `DES-{{NEXT_ID}}`
2. Include `## Traces to` section with REQ-xxxx references
3. Define clear interfaces and boundaries
4. Document failure modes
5. Specify test strategy

Output location: `docs/design/DES-{{NEXT_ID}}-{{name}}.md`

Required sections:
1. Overview
2. Goals / Non-goals
3. **Traces to** (REQ-xxxx list)
4. Architecture
5. Data model / Invariants
6. Algorithms (if applicable)
7. Failure modes
8. Security/Safety considerations
9. Test strategy
10. Alternatives considered
11. Open questions / Risks

After creating, verify:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

---

## Usage
Replace `{{PLACEHOLDERS}}` with your specific values.

## Example

**Requirements**: REQ-0015, REQ-0016, REQ-0017
**Component**: User Authentication Module
**Constraints**: Must support OAuth2, response time < 100ms
