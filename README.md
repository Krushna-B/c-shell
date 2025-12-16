# C Shell

A minimal Unix-like shell written in C. This project was built to understand core operating-system concepts such as process creation (`fork`), program execution (`execvp`), process synchronization (`waitpid`), and command-line input parsing.

## Features

- Interactive shell prompt
- Executes external programs (ex. `ls`, `cat`, `touch`)
- Built-in commands:
  - `cd <directory>`
  - `help`
  - `exit`
- Tokenizes user input into `argv`-style arguments
- Written using standard POSIX system calls

## Build & Compile

### Requirements

- macOS or Linux (POSIX-compliant)
- `gcc` or `clang`
- `make`

### Compile with Makefile

```
make run
```

## Project Structure

.
├── src/
│ └── main.c
├── Makefile
└── README.md
