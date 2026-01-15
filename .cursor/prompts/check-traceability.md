# Check Traceability

## Description
Verify REQ↔DES↔TEST traceability and fix gaps.

## Prompt

Please check the traceability status of this repository:

1. **Run the traceability checker**:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

2. **Analyze the report** and identify:
   - Requirements missing design references
   - Requirements missing test references
   - Unknown IDs referenced in design/tests

3. **For each gap, suggest fixes**:
   - If REQ missing design: create or update design doc
   - If REQ missing test: create test with REQ reference
   - If unknown ID: fix typo or remove stale reference

4. **Generate a traceability matrix** showing:
   - REQ-xxxx → DES-xxxx → Test file(s)

After fixing gaps, verify again:
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

The check should pass (exit code 0) before committing.

---

## Expected Output Format

### Gap Report
| Issue Type | ID | Suggested Fix |
|------------|----|--------------| 
| Missing design | REQ-0042 | Create DES-xxxx referencing REQ-0042 |
| Missing test | REQ-0043 | Add test with REQ-0043 comment |

### Traceability Matrix
| Requirement | Design | Tests |
|-------------|--------|-------|
| REQ-0001 | DES-0001 | test_example.py |
