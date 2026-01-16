# Agentic Design Patterns

This directory contains reusable agentic design patterns inspired by best practices from the AI agent community. These patterns can be composed to create more sophisticated agent behaviors.

## Pattern Catalog

### Core Patterns

| Pattern | Description | Use Case |
|---------|-------------|----------|
| [ReAct](react.md) | Reasoning + Acting loop | Complex problem solving |
| [Reflection](reflection.md) | Self-critique and improvement | Quality enhancement |
| [Planning](planning.md) | Decompose into subtasks | Multi-step tasks |
| [Tool Use](tool-use.md) | Structured tool invocation | External system interaction |
| [Chain of Thought](chain-of-thought.md) | Step-by-step reasoning | Complex reasoning |
| [Multi-Agent](multi-agent.md) | Agent collaboration | Specialized expertise |

### Context Engineering Patterns

| Pattern | Description | Use Case |
|---------|-------------|----------|
| [Context Management](context-management.md) | Manage context window | Long conversations |
| [Memory](memory.md) | Persistent state | Cross-session continuity |
| [Skill Composition](skill-composition.md) | Combine atomic skills | Complex capabilities |

## How Patterns Compose with Agents

```
┌─────────────────────────────────────────────────────────────────┐
│                        ORCHESTRATOR                              │
│                    (uses Planning pattern)                       │
└─────────────────────────────────────────────────────────────────┘
                              │
         ┌────────────────────┼────────────────────┐
         │                    │                    │
         ▼                    ▼                    ▼
┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐
│  requirements-  │  │  senior-        │  │  tdd-coach      │
│    author       │  │  architect      │  │                 │
│                 │  │                 │  │                 │
│ Uses:           │  │ Uses:           │  │ Uses:           │
│ - Chain of      │  │ - Reflection    │  │ - ReAct         │
│   Thought       │  │ - Multi-Agent   │  │ - Tool Use      │
│ - Reflection    │  │                 │  │                 │
└─────────────────┘  └─────────────────┘  └─────────────────┘
```

## Pattern Application Examples

### Example 1: Requirements Engineering with Reflection

```
1. Generate requirements (Chain of Thought)
2. Self-critique requirements (Reflection)
3. Identify gaps and ambiguities
4. Revise requirements
5. Validate against checklist
```

### Example 2: Design Review with Multi-Agent

```
1. Design Author creates design
2. CDR Reviewer critiques
3. Senior Architect validates architecture
4. Security Reviewer checks security
5. Consolidate findings
```

### Example 3: TDD with ReAct

```
Thought: I need to test the divide function
Action: Write test for happy path
Observation: Test written
Thought: I need to test error cases
Action: Write test for division by zero
Observation: Test written
Thought: All cases covered
Action: Run tests
Observation: Tests pass
```
