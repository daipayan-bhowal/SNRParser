
# Stackless Non-Recursive(SNR) Parser for C Programming Language

**Note: This repo is designed in Visual Studio 2019, this parser only validates the syntax doesn't generate any form of tree, if any syntax error is there it throws error**

## SNR Parser is a Dynamic Programming(DP)-based handwritten parser which is stackless and non-recursive in nature that is designed for parsing C Programming Language

## Disadvantages of Legacy parsers

1. **Limited Grammar Support**:
   - These parsers struggle with left-recursive, ambiguous, or highly complex grammars without significant transformations or enhancements.

2. **Ambiguity Handling**:
   - None of these parsers can naturally handle ambiguous grammars (e.g., the "dangling else" problem) without additional logic or grammar restructuring.

3. **Error Recovery Challenges**:
   - Robust error recovery mechanisms are difficult to implement, which impacts usability in compilers and IDEs.

4. **Grammar Transformations**:
   - Preprocessing like left-factoring, removing left recursion, or grammar simplification is often required, adding to development complexity.

5. **Scalability Issues**:
   - As grammars grow larger or more intricate, maintaining parsing rules or tables becomes increasingly cumbersome.

6. **Performance Overheads**:
   - Recursive parsers may suffer from stack overflow or excessive backtracking, while table-driven parsers like SLR have large memory overheads for parsing tables.

---

## Why Choose SNR Parser?
1. **Resource Efficiency**:
   - Ideal for low-resource environments where memory usage is a critical factor.

2. **High-Performance and Low memory**:
   - Provides high-performance, low-overhead & low-memory as stack driven parsers have lot of memorization which consumes lot of space and execution time, recursive parsers
     are also slow as the call stack has overhead during calling of the function.   

2. **Robustness**:
   - Reduced risk of stack overflow compared to recursive parsers.
   
3. **Scalability**:
   - This type of parser is very easy to scale, as it is more modular in nature.

4. **Clarity**:
   - Provides clarity and precision in defining parsing rules and workflows.

5. **Limited backtracking**:
   - It has limited backtracking and cases are very clear and understandable.

---

## Advantages
1. **Efficiency**:
   - The SNR parser avoids the overhead of recursion and stack usage, reducing memory consumption and increasing performance, especially for large programs.

2. **Scalability**:
   - The parser can handle complex C constructs without the risk of stack overflow, making it suitable for parsing deeply nested structures.

3. **Error Handling**:
   - Errors are detected and reported immediately during parsing, providing precise feedback about the source of the error.

4. **Real-time Parsing**:
   - Suitable for environments where real-time feedback is critical, such as Integrated Development Environments (IDEs) or code editors.

5. **Customizability**:
   - The modular design allows easy adaptation for other programming languages or specific grammar extensions.

---

## Applications
1. **Compilers**:
   - Parsing source code written in C during the compilation process.

2. **Integrated Development Environments (IDEs)**:
   - Real-time syntax checking and error detection for C programming.

3. **Code Analysis Tools**:
   - Static analysis to detect coding errors, vulnerabilities, or inefficiencies.

4. **Embedded Systems**:
   - Efficiently parsing code in memory-constrained environments where recursion or deep stacks are not feasible.

5. **Custom Scripting Languages**:
   - Serving as the base for domain-specific languages or C-like scripting languages.

6. **Educational Tools**:
   - Teaching parsing concepts and demonstrating how to process programming language constructs.

---

## Definitions

1. **TokenStream**:  
   The sequence of tokens `{t₁, t₂, ..., tₙ}` obtained by tokenizing the input program.  
   Let `tᵢ` denote the i-th token.

2. **Parsing States**:  
   The finite set `S` = {`IsMultipleDecl`, `IsFunctionDef`, `IsFunctionDecl`, `IsBlockEnd`, `IsEnumDef`, `IsEnumFunctionDef`,  
   `IsEnumFunctionDecl`, `IsStructDef`, `IsStructDecl`, `IsStructFunctionDef`,  
   `IsStructFunctionDecl`, `IsFunctionCaller`, `IsStatement`}.

3. **Parsing Check**:  
   A function `P(s)` that evaluates whether a token `tᵢ` belongs to the grammar rules of state `s`.  
   - `P(s) ← TRUE`: `tᵢ` satisfies the rules for state `s`.  
   - `P(s) ← FALSE`: `tᵢ` does not satisfy the rules for state `s`.

4. **Distance Calculation**:  
   Distance for state `s`:  
   `dist(s) = i - startToken(s)`

5. **Error State**:  
   If `∀ s ∈ S, P(s) = FALSE`, the current token `tᵢ` is invalid.

---

## Algorithm

### 1. Initialization:
   - Define `TokenStream` = `{t₁, t₂, ..., tₙ}`.
   - Initialize parsing states:  
     `P(s) ← FALSE, startToken(s) ← 0, ∀ s ∈ S`.

### 2. Grammar Check Function:
   - Evaluates whether `tᵢ` satisfies grammar rules for states:
     - `MultipleDeclaration(tᵢ)` (M): Checks for multiple declarations.
     - `FunctionDefinitionOrDeclaration(tᵢ)` (F): Verifies function definitions or declarations.
     - `BlockEndStatement(tᵢ)` (B): Checks for block ends.
     - `EnumDefinition(tᵢ)` (E): Evaluates enum definitions.
     - `StructDefinitionOrDeclaration(tᵢ)` (S): Identifies struct-related rules.
     - `FunctionCaller(tᵢ)` (C): Checks for function calls.
     - `Statement(tᵢ)` (St): Identifies statements.

### 3. Parsing Workflow:
   - For each token `tᵢ ∈ TokenStream`:
     - Record token position:  
       `startToken(s) ← i, ∀ s ∈ S`.
     - Check grammar rules:  
       - `P(IsMultipleDecl) ← M(tᵢ)`  
       - `P(IsFunctionDef), P(IsFunctionDecl) ← F(tᵢ)`  
       - `P(IsBlockEnd) ← B(tᵢ)`
       - `P(IsEnumDef), P(IsEnumFunctionDef), P(IsEnumFunctionDecl) ← E(tᵢ)`, etc.

### 4. Compute Distance:
   - If `P(s) = TRUE` for any state `s`:  
     `dist(s) = i - startToken(s)`.
   - Report matched construct.

### 5. Error Handling:
   - If no parsing state matches:  
     `∀ s ∈ S, P(s) = FALSE`,  
     report an error and terminate.

### 6. Reinitialize Parsing Table:
   - Reset: `P(s) ← FALSE, ∀ s ∈ S`.

### 7. Exit Condition:
   - Terminate when `tᵢ = EOF`.  
   - Parsing is successful if all tokens are processed without errors.

---
## System Requirements
 **Windows 11 and Visual Studio 2019**
 
---
## Summary
This document outlines a stackless, non-recursive (SNR) parser algorithm for parsing C language constructs efficiently. It employs mathematical abstractions for initialization, grammar checks, error handling, and state reinitialization to ensure robust and structured parsing.
