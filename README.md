# minishell$>
## Overview
Minishell is a simple shell program written in C that mimics the basic functionality of a Unix shell. It provides a user-friendly interface for executing commands, managing environment variables, handling redirections, and piping.
![Screenshot from 2024-12-26 16-43-45](https://github.com/user-attachments/assets/7ab752eb-65d6-417d-be9c-72ebfb54910c)
## Features
### Built-in Functions
- **echo**: Supports the `-n` option to suppress the trailing newline.
- **cd**: Changes the current directory using relative or absolute paths.
- **pwd**: Prints the current working directory.
- **pwd**: Prints the current working directory.
- **export**: Sets environment variables.
- **unset**: Unsets environment variables.
- **env**: Displays all environment variables.
- **exit**: Exits the shell.
### Redirections
- `<`: Input redirection from a file.
- `>`: Output redirection to a file.
- `<<`: Heredoc functionality.
- `>>`: Append redirection to a file.
### Piping
- Supports the pipe (`|`) operator to connect the output of one command to the input of another.
### Environment Variables
- Supports environment variables prefixed with `$` (e.g., `$HOME`).
- Handles `$?` to display the exit status of the last executed command.
### Signal Handling
- **Ctrl-C**: Displays a new prompt on a new line.
- **Ctrl-D**: Exits the shell.
- **Ctrl-\\**: Does nothing.
### Additional Features
- Command history.
- Executes the correct executable based on the `$PATH` variable.
  - Example: Typing `ls` launches `/bin/ls` without needing the full path.
- Handles unmatched quotes.
## Usage
Run the program to start the shell. Use it to execute commands, manage environment variables, and interact with the file system.
### Examples
- Redirect input and output:
  ```sh
  cat < input.txt > output.txt
  ```
- Use pipes:
  ```sh
  ls | grep minishell
  ```
- Set and unset environment variables:
  ```sh
  export MY_VAR=value
  echo $MY_VAR
  unset MY_VAR
  ```
- Exit the shell:
  ```sh
  exit
  ```
## Installation
Compile the source code using `make` and run the resulting executable:
```sh
./minishell
```
## Notes
- Ensure that the `readline` library is installed on your system.
- Any memory leaks are confined to the `readline` function, as all other leaks have been addressed.
