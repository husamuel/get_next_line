# Get_Next_Line 

<img width="1400" height="700" alt="image" src="https://github.com/user-attachments/assets/5a70a347-6226-46cb-a3ca-6a020a2c6a13" />

### Description

Get_Next_Line is a 42 project that involves creating a function to read a line from a file descriptor, returning one line at a time, including the newline character (`\n`), until the end of the file is reached. The function is designed to handle multiple file descriptors and is optimized for memory management.

#### Allowed Functions
`read`, `malloc`, `free`


### Features

- Reads a line (terminated by `\n`) from a file descriptor.
- Supports multiple file descriptors simultaneously.
- Manages a static buffer to store unread data between calls.
- Returns the line read, or `NULL` if the end of file is reached or an error occurs.

### Usage

#### Requirements
- **cc compiler**
- Standard C libraries

#### Compilation
Compile `get_next_line` with your project:
```shell
cd path/to/get_next_line && make
```

This will generate the necessary object files. Link them with your program, for example:
```shell
cc -Wall -Wextra -Werror main.c get_next_line.o get_next_line_utils.o -o program
```

#### Example
To read lines from a file:
```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

#### Makefile Commands
- `make` or `make all`: Builds the object files.
- `make clean`: Removes object files.
- `make fclean`: Removes object files and any generated binaries.
- `make re`: Recompiles the project.

### Implementation Notes

- Uses a static buffer to store leftover data, reducing the number of `read` calls.
- Handles edge cases such as empty files, lines with no newline, or invalid file descriptors.
- Compliant with 42's Norm:
  - Functions limited to 25 lines.
  - Variables declared at the top.
  - Only allowed functions used.

### Disclaimer

This project adheres to 42's Norm, which may result in unconventional code structure to meet specific requirements, such as function length limits and restricted function usage.
