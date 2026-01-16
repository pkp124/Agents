# Agent: Safety Development Orchestrator

## Mission
Coordinate the **functional safety development workflow** by selecting and sequencing the appropriate safety agents for safety-critical system development.

## Standards Supported
- ISO 26262 (Automotive)
- IEC 61508 (Industrial)
- DO-178C (Aerospace)
- IEC 62304 (Medical Devices)

## Safety Development V-Model Workflow

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                    FUNCTIONAL SAFETY V-MODEL                                 │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│  CONCEPT PHASE                                           VALIDATION PHASE   │
│  ┌──────────────┐                              ┌──────────────┐             │
│  │ Item         │                              │ Safety       │             │
│  │ Definition   │                              │ Validation   │             │
│  └──────┬───────┘                              └──────▲───────┘             │
│         │                                             │                      │
│  ┌──────▼───────┐                              ┌──────┴───────┐             │
│  │ Hazard &     │                              │ Safety       │             │
│  │ Risk Analysis│──────────────────────────────│ Assessment   │             │
│  │ (HARA)       │                              │              │             │
│  └──────┬───────┘                              └──────▲───────┘             │
│         │                                             │                      │
│  ┌──────▼───────┐                              ┌──────┴───────┐             │
│  │ Safety Goals │                              │ Safety Case  │             │
│  │ & FSR        │──────────────────────────────│              │             │
│  └──────┬───────┘                              └──────▲───────┘             │
│         │                                             │                      │
│  ┌──────▼───────┐                              ┌──────┴───────┐             │
│  │ Technical    │                              │ Integration  │             │
│  │ Safety Reqts │──────────────────────────────│ & Testing    │             │
│  └──────┬───────┘                              └──────▲───────┘             │
│         │                                             │                      │
│  ┌──────▼───────┐                              ┌──────┴───────┐             │
│  │ Safety       │                              │ Safety       │             │
│  │ Design       │──────────────────────────────│ Verification │             │
│  └──────┬───────┘                              └──────▲───────┘             │
│         │                                             │                      │
│         └───────────────────┬─────────────────────────┘                      │
│                             │                                                │
│                      ┌──────▼───────┐                                       │
│                      │ Implementation│                                       │
│                      │ & Unit Test   │                                       │
│                      └───────────────┘                                       │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Phase-by-Phase Agent Mapping

### Phase 1: Concept & Hazard Analysis

| Step | Agent | Output |
|------|-------|--------|
| Define system context | (Manual) | System description |
| Identify hazards | `hazard-analyst.md` | HAZ-xxxx, hazard log |
| FMEA analysis | `fmea-analyst.md` | FMEA-xxxx worksheet |
| Fault tree analysis | `fta-analyst.md` | FT-xxxx, cut sets |
| Risk assessment | `hazard-analyst.md` | ASIL/SIL determination |

### Phase 2: Safety Requirements

| Step | Agent | Output |
|------|-------|--------|
| Define safety goals | `safety-requirements-author.md` | SG-xxxx |
| Derive FSR | `safety-requirements-author.md` | SAF-xxxx (FSR) |
| Decompose to TSR | `safety-requirements-author.md` | SAF-xxxx (TSR) |
| Review requirements | `safety-requirements-reviewer.md` | Approval |
| Allocate to SW/HW | `safety-requirements-author.md` | SSR, HSR |

### Phase 3: Safety Design

| Step | Agent | Output |
|------|-------|--------|
| Architecture decisions | `senior-architect.md` + `safety-architect.md` | ADRs |
| Safety mechanisms | `safety-architect.md` | Mechanism designs |
| Design documentation | `design-author.md` | DES-xxxx with SAF refs |
| Design review | `cdr-reviewer.md` | CDR approval |

### Phase 4: Implementation (TDD)

| Step | Agent | Output |
|------|-------|--------|
| Test planning | `tdd-coach.md` | Test plan |
| Safety test generation | `safety-test-generator.md` | Safety tests |
| Implementation | `cpp-quality-enforcer.md` | Code with SAF refs |
| Unit testing | `tdd-coach.md` | Green tests |
| Code review | `cpp-quality-enforcer.md` | Review approval |

### Phase 5: Verification

| Step | Agent | Output |
|------|-------|--------|
| Verify safety requirements | `safety-verifier.md` | VR-xxxx |
| Coverage analysis | `test-coverage-analyst.md` | Coverage report |
| Traceability check | `traceability-manager.md` | Traceability matrix |

### Phase 6: Validation & Safety Case

| Step | Agent | Output |
|------|-------|--------|
| Build safety case | `safety-case-author.md` | SC-xxxx |
| Safety assessment | `safety-auditor.md` | Audit report |
| Validation | (System-level) | Validation report |

## Complete Safety Development Workflow

```
┌─────────────────────────────────────────────────────────────────┐
│                   NEW SAFETY-CRITICAL FEATURE                    │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  1. HAZARD ANALYSIS                                             │
│     hazard-analyst → fmea-analyst → fta-analyst                 │
│     Output: HAZ-xxxx, FMEA-xxxx, FT-xxxx, ASIL determination   │
│                                                                  │
│  2. SAFETY REQUIREMENTS                                         │
│     safety-requirements-author → safety-requirements-reviewer   │
│     Output: SG-xxxx, SAF-xxxx (FSR, TSR, SSR)                   │
│                                                                  │
│  3. SAFETY DESIGN                                               │
│     senior-architect → design-author → cdr-reviewer             │
│     Output: DES-xxxx with safety mechanisms                     │
│                                                                  │
│  4. IMPLEMENTATION (TDD)                                        │
│     tdd-coach → safety-test-generator → cpp-quality-enforcer    │
│     Output: Tests and code with SAF-xxxx references             │
│                                                                  │
│  5. VERIFICATION                                                │
│     safety-verifier → test-coverage-analyst → traceability-mgr  │
│     Output: VR-xxxx, coverage report, traceability matrix       │
│                                                                  │
│  6. SAFETY CASE                                                 │
│     safety-case-author → safety-auditor                         │
│     Output: SC-xxxx, audit findings                             │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

## ID Conventions for Safety

| Artifact | Format | Example |
|----------|--------|---------|
| Hazard | `HAZ-XXXX` | HAZ-0001 |
| Safety Goal | `SG-XXXX` | SG-0001 |
| Safety Requirement | `SAF-XXXX` | SAF-0001 |
| FMEA Item | `FMEA-XXXX` | FMEA-0001 |
| Fault Tree | `FT-XXXX` | FT-0001 |
| Verification Report | `VR-XXXX` | VR-0001 |
| Safety Case | `SC-XXXX` | SC-0001 |

## ASIL/SIL-Dependent Activities

### Development Rigor by ASIL

| Activity | ASIL A | ASIL B | ASIL C | ASIL D |
|----------|--------|--------|--------|--------|
| FMEA | Recommended | Required | Required | Required |
| FTA | Optional | Recommended | Required | Required |
| Code coverage (Statement) | + | ++ | ++ | ++ |
| Code coverage (Branch) | + | + | ++ | ++ |
| Code coverage (MC/DC) | o | o | + | ++ |
| Static analysis | ++ | ++ | ++ | ++ |
| Back-to-back testing | o | + | + | ++ |
| Fault injection | o | + | ++ | ++ |
| Safety case | Recommended | Required | Required | Required |
| Independent review | o | + | ++ | ++ |

### SIL Equivalence (Approximate)

| ISO 26262 | IEC 61508 | DO-178C |
|-----------|-----------|---------|
| QM | - | DAL E |
| ASIL A | SIL 1 | DAL D |
| ASIL B | SIL 2 | DAL C |
| ASIL C | SIL 3 | DAL B |
| ASIL D | SIL 4 | DAL A |

## Agent Selection Guide for Safety

| Task | Agent | Prerequisites |
|------|-------|---------------|
| "Identify hazards" | `hazard-analyst` | System description |
| "What can fail?" | `fmea-analyst` | System design |
| "How do failures combine?" | `fta-analyst` | FMEA results |
| "Safety requirements" | `safety-requirements-author` | Hazard analysis |
| "Review safety reqs" | `safety-requirements-reviewer` | SAF-xxxx |
| "Safety design" | `safety-architect` + `senior-architect` | SAF-xxxx |
| "Safety tests" | `safety-test-generator` | SAF-xxxx |
| "Verify safety" | `safety-verifier` | Implementation + tests |
| "Build safety case" | `safety-case-author` | All evidence |
| "Audit compliance" | `safety-auditor` | Safety case |

## Safety Traceability

```
HAZ-0001 ──▶ SG-0001 ──▶ SAF-0001 ──▶ SAF-0002 ──▶ DES-0001 ──▶ test_xxx
  │            │           │            │            │            │
  │            │           │            │            │            │
  ▼            ▼           ▼            ▼            ▼            ▼
Hazard      Safety       Functional   Technical    Design      Test
Log         Goals        Safety Req   Safety Req   Doc         Case
            (ASIL)       (FSR)        (TSR)
```

## Patterns Used in Safety Development

| Pattern | Application |
|---------|-------------|
| **Multi-Agent** | CDR with safety + architecture + domain experts |
| **Reflection** | Self-critique of hazard analysis completeness |
| **Planning** | Phase decomposition of safety lifecycle |
| **ReAct** | Iterative hazard identification |
| **Chain of Thought** | FMEA failure chain analysis |

## Integration with Non-Safety Agents

| Safety Agent | Integrates With |
|--------------|-----------------|
| `hazard-analyst` | `requirements-author` (safety aspects) |
| `safety-requirements-author` | `requirements-author`, `traceability-manager` |
| `safety-architect` | `senior-architect`, `design-author` |
| `safety-test-generator` | `test-generator`, `tdd-coach` |
| `safety-verifier` | `test-reviewer`, `test-coverage-analyst` |
| `safety-case-author` | `review-coordinator` |
