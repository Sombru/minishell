*This project has been created as part of the 42 curriculum by pkostura.*

# ft_printf

## Description
`ft_printf` is a reimplementation of the standard C `printf` function as a static library.
The main goal is to understand variable number of arguments, format-string parsing, and low-level output using `write`.

This implementation parses formatting tokens after `%` and dispatches each conversion to dedicated handlers.
It supports core specifiers and common flags used in the 42 mandatory scope.

### Project Goal
- Build a reliable formatted output function without using the original `printf`.
- Practice parsing logic, edge-case handling, and modular C design.
- Return the exact number of printed characters, like the standard function.

### Supported Conversions
- `%c` character
- `%s` string
- `%p` pointer
- `%d` / `%i` signed decimal
- `%u` unsigned decimal
- `%x` / `%X` hexadecimal
- `%%` literal percent

### Supported Formatting Features
- Flags: `#`, `+`, ` ` (space), `-`, `0`
- Width handling
- Dot/precision behavior used by this parser

## Instructions
### 1. Compile
From the project root:

```bash
make
```

This builds:
- `libft/libft.a`
- `libftprintf.a`

### 2. Clean Artifacts
```bash
make clean
make fclean
make re
```

### 3. Optional Debug Binary
```bash
make debug
./ft_printf.out
```

### 4. Use in Another Project
Link the library and include the header:

```c
#include "ft_printf.h"
```

Example build command:

```bash
cc main.c -L. -lftprintf -I. -o app
```

## Algorithm And Data Structure Choices (Detailed)
This implementation follows a linear, single-pass parsing strategy over the input format string.

### High-Level Algorithm
1. Iterate through the input string character by character.
2. If the current char is not `%`, write it directly to stdout and increment the global count.
3. If `%` is found:
- Extract the full format fragment until the specifier (`cspdiuxX%`).
- Initialize a formatting state structure.
- Parse flags/width/dot-related fields.
- Resolve conflicting flags (for example `0` with `-`, `+` with space).
- Parse final specifier.
- Dispatch to the conversion handler.
4. Add printed length returned by the handler to the total count.
5. Continue until the end of the input string.

### Time Complexity
- Let `n` be input format length.
- Main traversal is O(n).
- Each conversion includes small extra work proportional to argument text length (number/string conversion).
- Total behavior remains effectively linear for typical usage: O(n + total_output_digits).

### Core Data Structure

#### `t_format`
Stores parser state for one conversion token:
- Boolean-like fields for flags (`hash`, `minus`, `plus`, `dot`, `space`, `zero`, `default_`)
- `field_witdh` numeric width/precision-like parsed value
- `precision` field (reserved in struct)
- `specifier` selected conversion type

## Resources
### Classic References
- Linux man pages: `man 3 printf`, `man 3 stdarg`, `man 2 write`
- C11/C17 references for variadic functions and integer formatting
- 42 project subject and peer correction guidelines
- Existing libc behavior checked by comparing against system `printf` outputs

### Test Resources
- Opensourse printf tester from 42 student `https://github.com/Tripouille/printfTester`
- Manual comparisons using small custom test cases and return-value checks

### AI Usage Disclosure
AI tools were used as a support layer, not as a replacement for implementation work.

Used for:
- Reviewing README wording and structure.
- Explaining and validating high-level algorithm documentation.
- Refactoring code to norminette standart
