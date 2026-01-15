# Skill: Parse Requirements

## Purpose
Extract requirement IDs and metadata from YAML requirement files.

## Input
- Path to requirements directory: `docs/requirements/`
- File pattern: `*.yaml`, `*.yml`

## Output
List of requirements with:
- `id`: REQ-xxxx
- `title`: Short title
- `statement`: The "shall" statement
- `verification_method`: Test|Analysis|Inspection|Demonstration
- `priority`: Must|Should|Could
- `source_file`: Path to defining file

## Algorithm
```python
for each .yaml/.yml file in docs/requirements/:
    parse YAML
    for each item in requirements[]:
        extract id matching REQ-\d{4}
        extract title, statement, verification_method, priority
        yield requirement record
```

## Output Format
```yaml
requirements:
  - id: REQ-0001
    title: "Example requirement"
    statement: "The system shall..."
    verification_method: Test
    priority: Must
    source_file: docs/requirements/REQ-0001-example.yaml
```

## Error Handling
- Skip files that fail to parse
- Log warning for requirements missing ID
- Continue processing on individual file errors

## Used By
- `traceability-manager.md`
- `check_traceability.py`
