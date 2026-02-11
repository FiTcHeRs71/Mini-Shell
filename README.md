_This project has been created as part of the 42 curriculum by lgranger & fducrot._
# Minishell - As beautiful as a shell


## Description
Minishell is a simplified version of a Bash shell. The goal of this project is to create an interactive command-line interface capable of executing binaries, managing environment variables, and handling complex command pipelines.

This implementation includes a custom lexical analyzer (lexer), a recursive descent parser that builds an Abstract Syntax Tree (AST), and an executor that handles process creation and file descriptor redirections. It focuses on rigorous memory management and signal handling to mimic the behavior of a real shell.


## Key Features

Interactive Prompt: Displays a prompt when waiting for new commands.

Command Execution: Searches and launches executables using the PATH variable or absolute/relative paths.

Built-in Commands: Fully implemented echo (with -n), cd, pwd, export, unset, env, and exit.

Redirections: Handles input (<), output (>), append mode (>>), and heredoc (<<).

Pipes: Supports multiple pipelines (|) where the output of one command is connected to the input of the next.

Environment Variables: Handles expansion of $ variables and the $? exit status.

Signal Handling: Replicates Bash behavior for ctrl-C (new prompt), ctrl-D (exit), and ctrl-\ (do nothing) in interactive mode.

Bonus Features: * Logical operators && and || with parentheses for command priority.

Wildcards (*) for the current working directory.

## Instructions
Compilation
The project requires the readline library. To compile the program, use the provided Makefile: 

Bash

## Compilation

### Compile the minishell executable
make

./minishell

### Compile using Valgrind
make valgrind

### Remove object files and the executable
make fclean

### Recompile the project
make re

## Resources && References

Bash Reference Manual: Primary source for shell behavior and syntax requirements.

GNU Readline Library: Documentation for handling line editing and command history.

Man pages: execve(2), fork(2), pipe(2), waitpid(2), sigaction(2).

## AI Usage
AI tools (specifically Large Language Models) were utilized during the development of this project for the following tasks: 

Code Review & Debugging: Assisting in identifying potential memory leaks and edge cases in the recursive AST execution logic.

Technical Explanations: Clarifying the nuances of signal handling between parent and child processes.

Documentation: Generating initial drafts for the README and internal code comments to ensure clarity and professional standards.

Logic Verification: Walking through the logic of the wildcard pattern matching and logical operator priority.