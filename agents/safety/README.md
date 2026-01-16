# Functional Safety Agents

This directory contains agents for functional safety development following standards like:
- **ISO 26262** - Automotive functional safety
- **IEC 61508** - Functional safety of electrical/electronic/programmable electronic systems
- **DO-178C** - Software considerations in airborne systems
- **IEC 62304** - Medical device software lifecycle

## Safety Development Lifecycle

```
┌─────────────────────────────────────────────────────────────────┐
│                  FUNCTIONAL SAFETY V-MODEL                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  Concept                                          Safety         │
│  Phase     ┌─────────────┐          ┌─────────────┐ Validation  │
│      ──────│ Hazard &    │          │  Safety     │──────       │
│            │ Risk        │          │  Validation │             │
│            │ Analysis    │          │             │             │
│            └──────┬──────┘          └──────▲──────┘             │
│                   │                        │                     │
│  Safety     ┌─────▼─────┐          ┌──────┴──────┐ Safety      │
│  Reqts ─────│  Safety   │          │  Safety     │───── Tests  │
│             │  Goals &  │          │  Integration│              │
│             │  Reqts    │          │  Testing    │              │
│             └─────┬─────┘          └──────▲──────┘              │
│                   │                        │                     │
│  Design     ┌─────▼─────┐          ┌──────┴──────┐ Safety      │
│        ─────│  Safety   │          │  Safety     │───── V&V    │
│             │  Design   │          │  Verification│             │
│             └─────┬─────┘          └──────▲──────┘              │
│                   │                        │                     │
│                   └────────┬───────────────┘                     │
│                            │                                     │
│                    ┌───────▼───────┐                            │
│                    │Implementation │                            │
│                    │ & Unit Test   │                            │
│                    └───────────────┘                            │
└─────────────────────────────────────────────────────────────────┘
```

## Agent Catalog

### Hazard Analysis
| Agent | Purpose | Standards |
|-------|---------|-----------|
| `hazard-analyst.md` | Identify hazards and hazardous events | All |
| `fmea-analyst.md` | Failure Mode and Effects Analysis | ISO 26262, IEC 61508 |
| `fta-analyst.md` | Fault Tree Analysis | All |

### Safety Requirements
| Agent | Purpose | Standards |
|-------|---------|-----------|
| `safety-requirements-author.md` | Create safety requirements with ASIL/SIL | All |
| `safety-requirements-reviewer.md` | Review safety requirements | All |

### Safety Design
| Agent | Purpose | Standards |
|-------|---------|-----------|
| `safety-architect.md` | Safety architecture and mechanisms | All |
| `safety-design-reviewer.md` | Review safety design | All |

### Safety Verification
| Agent | Purpose | Standards |
|-------|---------|-----------|
| `safety-test-generator.md` | Generate safety tests | All |
| `safety-verifier.md` | Verify safety requirements | All |

### Safety Case
| Agent | Purpose | Standards |
|-------|---------|-----------|
| `safety-case-author.md` | Create safety case/argument | All |
| `safety-auditor.md` | Audit safety compliance | All |

## ASIL/SIL Levels

### ISO 26262 ASIL (Automotive)
| Level | Severity | Probability | Controllability |
|-------|----------|-------------|-----------------|
| QM | - | - | - |
| ASIL A | Low risk | | |
| ASIL B | | | |
| ASIL C | | | |
| ASIL D | Highest risk | | |

### IEC 61508 SIL (Industrial)
| Level | PFH (per hour) | Risk Reduction |
|-------|----------------|----------------|
| SIL 1 | 10⁻⁶ to 10⁻⁵ | Low |
| SIL 2 | 10⁻⁷ to 10⁻⁶ | Medium |
| SIL 3 | 10⁻⁸ to 10⁻⁷ | High |
| SIL 4 | 10⁻⁹ to 10⁻⁸ | Very High |

## Safety Workflow

```
1. hazard-analyst        → Identify hazards
2. fmea-analyst          → Analyze failure modes
3. fta-analyst           → Build fault trees
4. safety-requirements   → Define safety requirements (SAF-xxxx)
   -author
5. safety-architect      → Design safety mechanisms
6. safety-test-generator → Generate safety tests
7. safety-verifier       → Verify safety requirements
8. safety-case-author    → Build safety argument
9. safety-auditor        → Audit compliance
```

## ID Conventions

| Type | Format | Example |
|------|--------|---------|
| Hazard | `HAZ-XXXX` | HAZ-0001 |
| Safety Goal | `SG-XXXX` | SG-0001 |
| Safety Requirement | `SAF-XXXX` | SAF-0001 |
| FMEA Item | `FMEA-XXXX` | FMEA-0001 |
| FTA Gate | `FT-XXXX` | FT-0001 |
