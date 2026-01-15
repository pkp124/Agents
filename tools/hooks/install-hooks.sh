#!/bin/bash
# Install pre-commit hooks for TDD + V-model enforcement
#
# Usage: ./tools/hooks/install-hooks.sh

set -e

echo "Installing pre-commit hooks for TDD + V-model enforcement..."

# Check if pre-commit is installed
if ! command -v pre-commit &> /dev/null; then
    echo "Installing pre-commit..."
    pip install pre-commit
fi

# Install the hooks
pre-commit install

# Also install commit-msg hook for conventional commits (optional)
# pre-commit install --hook-type commit-msg

echo ""
echo "✅ Pre-commit hooks installed!"
echo ""
echo "Hooks will run automatically on 'git commit'."
echo ""
echo "Installed checks:"
echo "  - Ruff (Python linting + formatting)"
echo "  - Traceability check (REQ↔DES↔TEST)"
echo "  - Requirement quality validation"
echo "  - Test file requirement references"
echo "  - Design doc 'Traces to' section"
echo ""
echo "To run manually: pre-commit run --all-files"
echo "To skip hooks:   git commit --no-verify"
