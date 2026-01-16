# Pattern: Multi-Agent Collaboration

## Overview

The Multi-Agent pattern involves multiple specialized agents working together on a task. Each agent has specific expertise, and they collaborate through defined interfaces.

## Pattern Structure

```
┌─────────────────────────────────────────────────────────────────┐
│                    Multi-Agent Collaboration                     │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│                      ┌──────────────┐                           │
│                      │ COORDINATOR  │                           │
│                      │              │                           │
│                      │ Orchestrates │                           │
│                      │ workflow     │                           │
│                      └──────┬───────┘                           │
│                             │                                    │
│            ┌────────────────┼────────────────┐                  │
│            │                │                │                  │
│            ▼                ▼                ▼                  │
│     ┌──────────┐     ┌──────────┐     ┌──────────┐            │
│     │ AGENT A  │     │ AGENT B  │     │ AGENT C  │            │
│     │          │     │          │     │          │            │
│     │ Expert   │     │ Expert   │     │ Expert   │            │
│     │ domain 1 │     │ domain 2 │     │ domain 3 │            │
│     └────┬─────┘     └────┬─────┘     └────┬─────┘            │
│          │                │                │                    │
│          └────────────────┴────────────────┘                    │
│                           │                                      │
│                           ▼                                      │
│                    ┌──────────────┐                             │
│                    │  SYNTHESIZER │                             │
│                    │              │                             │
│                    │  Combines    │                             │
│                    │  results     │                             │
│                    └──────────────┘                             │
└─────────────────────────────────────────────────────────────────┘
```

## Collaboration Modes

### 1. Sequential Pipeline
Agents work one after another:
```
Agent A → Agent B → Agent C → Result
```

Example: Requirements → Design → Implementation

### 2. Parallel Review
Multiple agents review simultaneously:
```
        ┌─→ Agent A ─┐
Input ──┼─→ Agent B ─┼──→ Combine
        └─→ Agent C ─┘
```

Example: CDR with multiple reviewers

### 3. Debate/Adversarial
Agents challenge each other:
```
Agent A (Proposer) ←→ Agent B (Critic)
         ↓
    Refined Result
```

Example: Design author + CDR reviewer

### 4. Hierarchical
Agents organized in hierarchy:
```
         Senior
           │
    ┌──────┼──────┐
    │      │      │
  Junior Junior Junior
```

Example: Senior architect overseeing design authors

## Template: Multi-Agent Review

```markdown
## Artifact: [What's being reviewed]

### Agent 1: [Role] Review
**Focus**: [What this agent checks]
**Findings**:
- [Finding 1]
- [Finding 2]
**Verdict**: Approve / Request Changes / Reject

### Agent 2: [Role] Review
**Focus**: [What this agent checks]
**Findings**:
- [Finding 1]
- [Finding 2]
**Verdict**: Approve / Request Changes / Reject

### Agent 3: [Role] Review
**Focus**: [What this agent checks]
**Findings**:
- [Finding 1]
**Verdict**: Approve / Request Changes / Reject

### Synthesized Decision
**Overall Verdict**: [Combined decision]
**Consolidated Findings**:
1. [Priority finding]
2. [Priority finding]
**Required Actions**:
- [ ] [Action 1]
- [ ] [Action 2]
```

## Example: Critical Design Review

```markdown
## Artifact: DES-0001 MathUtils Library Design

### Agent 1: CDR Reviewer
**Focus**: Design completeness and traceability
**Findings**:
- All requirements traced ✓
- Missing failure mode for numeric overflow
- Test strategy covers main paths
**Verdict**: Approve with Conditions

### Agent 2: Senior Architect
**Focus**: Architecture patterns and cross-cutting concerns
**Findings**:
- Good use of static methods for stateless operations ✓
- Thread safety well addressed ✓
- Consider adding logging for production debugging
**Verdict**: Approve

### Agent 3: Security Reviewer
**Focus**: Security implications
**Findings**:
- No external input validation needed (internal library)
- No security concerns identified
**Verdict**: Approve

### Synthesized Decision
**Overall Verdict**: Approve with Conditions
**Consolidated Findings**:
1. Add failure mode documentation for numeric overflow
2. Consider optional logging support
**Required Actions**:
- [ ] Document overflow behavior in design
- [ ] Add note about logging in future version
```

## Agent Communication Protocol

### Message Format
```yaml
from: <agent_id>
to: <agent_id or "all">
type: request | response | finding | decision
content:
  summary: <brief description>
  details: <full content>
  artifacts: [<list of referenced files>]
  priority: low | medium | high | critical
```

### Example Exchange
```yaml
# Request
from: review-coordinator
to: cdr-reviewer
type: request
content:
  summary: Review design document
  details: Please review DES-0001 for completeness
  artifacts: [docs/design/DES-0001.md]
  priority: high

# Response
from: cdr-reviewer
to: review-coordinator
type: response
content:
  summary: Review complete - minor issues
  details: Found 2 minor issues, design is sound
  findings:
    - severity: minor
      description: Missing overflow documentation
  verdict: approve_with_conditions
```

## When to Use

- Complex reviews requiring multiple perspectives
- Tasks requiring diverse expertise
- When checks and balances are needed
- For safety-critical decisions

## Integration with Agents

Multi-agent scenarios in this framework:
- **CDR**: `design-author` + `cdr-reviewer` + `senior-architect`
- **Requirements**: `requirements-author` + `requirements-reviewer`
- **Safety**: `hazard-analyst` + `safety-reviewer` + `senior-architect`
- **Full Review**: `review-coordinator` orchestrating all reviewers
