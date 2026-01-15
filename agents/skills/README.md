# Skills (Reusable Capabilities)

Skills are focused, reusable capabilities that agents can invoke. Unlike agents (which are role-focused), skills are task-focused building blocks.

## Skill Catalog

### Traceability Skills
| Skill | Description | Used By |
|-------|-------------|---------|
| `parse-requirements.md` | Extract REQ-xxxx from YAML files | traceability-manager |
| `parse-design-refs.md` | Extract REQ refs from design docs | traceability-manager |
| `parse-test-refs.md` | Extract REQ refs from test files | traceability-manager |
| `generate-matrix.md` | Create traceability matrix | traceability-manager |

### Test Skills
| Skill | Description | Used By |
|-------|-------------|---------|
| `write-pytest-test.md` | Generate pytest test structure | test-generator, tdd-coach |
| `write-gtest-test.md` | Generate GoogleTest test structure | test-generator, tdd-coach |
| `parameterize-test.md` | Convert test to parameterized/table-driven | test-generator |

### Documentation Skills
| Skill | Description | Used By |
|-------|-------------|---------|
| `yaml-requirement.md` | Format requirement as YAML | requirements-author |
| `markdown-design.md` | Format design doc | design-author |
| `extract-interfaces.md` | Extract API interfaces from code | design-author |

### Analysis Skills
| Skill | Description | Used By |
|-------|-------------|---------|
| `find-coverage-gaps.md` | Identify untested code paths | test-reviewer |
| `check-determinism.md` | Check test for non-determinism | test-reviewer |
| `validate-req-format.md` | Validate requirement quality | requirements-reviewer |

## Skill vs Agent

| Aspect | Agent | Skill |
|--------|-------|-------|
| Focus | Role/persona | Single task |
| Scope | End-to-end workflow | Building block |
| Output | Multiple artifacts | Single artifact |
| Invocation | User invokes | Agent invokes |

## Adding New Skills

1. Create skill file in `agents/skills/`
2. Define:
   - Purpose (single responsibility)
   - Inputs (specific, typed)
   - Output (well-defined format)
3. Document which agents use it
4. Update this README
