# Tools

This directory contains repository tooling for TDD and V-model development practices.

## Available Tools

### Traceability

| Tool | Description | Usage |
|------|-------------|-------|
| `traceability/check_traceability.py` | Verify REQ↔DES↔TEST links | `python tools/traceability/check_traceability.py --docs docs --tests tests` |
| `traceability/generate_matrix.py` | Generate traceability matrix | `python tools/traceability/generate_matrix.py --output docs/traceability/matrix.md` |
| `traceability/find_next_id.py` | Find next available IDs | `python tools/traceability/find_next_id.py` |
| `traceability/validate_requirements.py` | Validate requirement quality | `python tools/traceability/validate_requirements.py` |

## Quick Reference

### Check Traceability (CI Required)
```bash
python tools/traceability/check_traceability.py --docs docs --tests tests
```

Exit codes:
- `0`: All requirements have design and test coverage
- `1`: Missing coverage or unknown IDs found
- `2`: No requirements found (with `--fail-if-no-requirements`)

### Generate Traceability Matrix
```bash
# Print to stdout
python tools/traceability/generate_matrix.py

# Write to file
python tools/traceability/generate_matrix.py --output docs/traceability/matrix.md
```

### Find Next Available ID
```bash
# Show all next IDs
python tools/traceability/find_next_id.py

# Get specific type
python tools/traceability/find_next_id.py --type REQ
python tools/traceability/find_next_id.py --type DES
```

### Validate Requirements
```bash
# Check for issues
python tools/traceability/validate_requirements.py

# Verbose output
python tools/traceability/validate_requirements.py --verbose
```

## Adding New Tools

When adding new tools:

1. Place in appropriate subdirectory (`traceability/`, etc.)
2. Include docstring with purpose and usage
3. Use `argparse` for CLI arguments
4. Return proper exit codes (0 = success, non-zero = failure)
5. Update this README
6. Add tests in `tests/`

## Integration with CI

The GitHub Actions workflow in `.github/workflows/quality.yml` runs:

```yaml
- name: Traceability check
  run: python tools/traceability/check_traceability.py --docs docs --tests tests --fail-if-no-requirements
```

All tools should be designed to work in CI environments:
- Deterministic output
- Clear exit codes
- No interactive prompts
