
# Stackless Non-Recursive(SNR) Parser: A Dynamic Programming-based parser which is stackless and non-recursive in nature that is designed for parsing C Programming Language


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
       - `P(IsBlockEnd) ← B(tᵢ)`, etc.

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

## Summary
This document outlines a stackless, non-recursive (SNR) parser algorithm for parsing C language constructs efficiently. It employs mathematical abstractions for initialization, grammar checks, error handling, and state reinitialization to ensure robust and structured parsing.
