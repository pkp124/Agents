# Git Hooks for TDD + V-Model Enforcement

This directory contains git hooks that enforce TDD and V-model practices before commits.

## What Gets Checked

| Check | Trigger | Description |
|-------|---------|-------------|
| Ruff lint | All commits | Python code quality |
| Ruff format | All commits | Python code formatting |
| Traceability | All commits | REQ↔DES↔TEST links complete |
| Requirement quality | Requirements changed | Validates requirement format |
| Test REQ references | Test files changed | Tests must reference REQ-xxxx |
| Design traces | Design files changed | Design docs must have "Traces to" |

## Installation Options

### Option 1: Using pre-commit (Recommended)

```bash
# Install pre-commit framework
pip install pre-commit

# Install hooks
./tools/hooks/install-hooks.sh

# Or manually:
pre-commit install
```

### Option 2: Manual Hook

```bash
# Copy the manual hook script
cp tools/hooks/pre-commit-manual .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

## Usage

### Automatic (on every commit)
Once installed, hooks run automatically on `git commit`.

### Manual Run
```bash
# Run all checks
pre-commit run --all-files

# Run specific check
pre-commit run traceability-check
pre-commit run validate-requirements
```

### Skip Hooks (Emergency)
```bash
git commit --no-verify -m "message"
```

## Customization

Edit `.pre-commit-config.yaml` to:
- Add/remove checks
- Change which files trigger checks
- Enable/disable pytest on commit

## Troubleshooting

### "Traceability check failed"
```bash
# See detailed report
python3 tools/traceability/check_traceability.py --docs docs --tests tests
```

### "Test files missing REQ references"
Add a requirement reference in your test file:
```python
def test_something():
    """Test description.
    
    Traces to: REQ-0001
    """
    pass

# Or as a comment:
# REQ-0001
def test_something():
    pass
```

### "Design docs missing Traces section"
Add to your design document:
```markdown
## Traces to
- Requirements: REQ-0001, REQ-0002
```
