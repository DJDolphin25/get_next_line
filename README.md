*This project has been created as part of the 42 curriculum by <theoppon>.*

# get_next_line

## Description

The **get_next_line** project consists of implementing a function that reads a file descriptor line by line, returning one line per function call. The goal is to gain a deep understanding of:

* Static variables
* File descriptors
* Buffered input
* Dynamic memory management in C

The function must handle multiple successive calls, preserve unread data between calls, and correctly return lines terminated by a newline character (`\n`), except in the case where the end of file is reached without a trailing newline.

This project emphasizes robustness, defensive programming, and correct handling of edge cases such as varying buffer sizes, end-of-file conditions, and memory allocation failures.

---

## Instructions

### Compilation

The project must be compiled with a user-defined buffer size using the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The implementation is designed to work correctly with any valid `BUFFER_SIZE` value, including very small (e.g., 1) and very large values.

### Usage

Example usage:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

The function can also be used with standard input (`fd = 0`).

---

## Algorithm Explanation

The implementation relies on a **static buffer** that preserves unread data between successive calls to `get_next_line`.

### High-level approach

1. **Persistent storage**
   A static pointer (`saved`) stores leftover data that was read from the file descriptor but not yet returned as a full line.

2. **Incremental reading**
   Data is read from the file descriptor into a temporary buffer of size `BUFFER_SIZE` using `read()`. Reading continues until either:

   * a newline character (`\n`) is found, or
   * the end of file is reached.

3. **String concatenation**
   Each newly read chunk is appended to `saved`, ensuring previously unread data is preserved. Memory is always managed to avoid leaks, freeing the old `saved` after concatenation.

4. **Line extraction**
   When a newline is present (or EOF is reached), the function:

   * extracts the line up to and including `\n`
   * updates `saved` to contain only the remaining data
   * returns the extracted line

5. **End-of-file handling**
   If no data remains after extraction, `saved` is freed and reset to `NULL`.

### Why this approach

* Ensures **minimal reading** per function call
* Avoids reading the entire file at once
* Handles arbitrary buffer sizes
* Preserves correctness across multiple calls
* Meets all constraints of the subject (no `lseek`, no global variables)

---

## Bonus Implementation

This project includes the bonus part, which extends the functionality to handle **multiple file descriptors simultaneously**.

### Key Features

* **Single static variable**: Uses an array `static char *saved[MAX_FD]` where each index corresponds to a file descriptor
* **Independent tracking**: Each file descriptor maintains its own reading state independently
* **Seamless switching**: Can read from different file descriptors in any order without losing track of position

### Example Usage

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
int fd3 = open("file3.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // Read from file1
char *line2 = get_next_line(fd2);  // Read from file2
char *line3 = get_next_line(fd1);  // Continue reading file1
char *line4 = get_next_line(fd3);  // Read from file3

// Each fd maintains its own state independently
```

### Implementation Details

* Maximum file descriptors supported: `MAX_FD` (default: 1024)
* Each fd is validated: `fd >= 0 && fd < MAX_FD`
* Memory management remains robust across all file descriptors
* No memory leaks even when switching between multiple fds

---

## Memory Management and Safety

* All dynamic allocations are checked for failure.
* Memory is freed as soon as it is no longer needed.
* The implementation is robust against:

  * `malloc` failures
  * invalid file descriptors
  * empty files
  * files without a trailing newline

Special care is taken to avoid NULL dereferencing, as required by strict testing environments such as Francinette.

---

## Testing Results

### Official Tests (without --strict)
✅ **100% Pass Rate**
- gnlTester: All tests passing
- fsoares: All tests passing
- Multiple buffer sizes: 1, 10, 42, 1000000
- Bonus: Multiple file descriptors working correctly

### Strict Mode Tests
⚠️ **99% Pass Rate**
- One known timeout in extreme conditions:
  - Test: `giant_line.txt` (20,000 characters)
  - BUFFER_SIZE: 10
  - Condition: NULL_CHECK test
  
This timeout is caused by O(n²) complexity in string concatenation with very large lines and very small buffer sizes. This is a known and acceptable limitation that does not affect real-world usage or project evaluation.

---

## Resources

### Technical References

* `man 2 read`
* `man 3 malloc`
* `man 3 free`
* `man 2 open`
* `man 2 close`
* The Open Group POSIX specification
* 42 Network documentation on file descriptors and static variables
* Classic tutorials on buffered I/O in C

### Use of Artificial Intelligence

AI tools were used **as a learning and review aid only**, specifically to:

* Clarify edge cases and memory management pitfalls
* Review logic and defensive programming practices
* Validate understanding of the subject requirements
* Debug complex issues through guided reasoning

All code was written, tested, and debugged by the author. **No AI-generated code was copied directly into the project.** The learning process emphasized understanding over shortcuts, with AI serving as a mentor rather than a solution provider.

---

## Notes

* The behavior of `get_next_line` is undefined if the file is modified between calls before reaching EOF, as specified in the subject.
* Binary files are not supported and may produce undefined behavior.
* The implementation works correctly for very small (`BUFFER_SIZE=1`) and very large buffer sizes.
* Static variables are used intentionally to preserve leftover data between calls without using global variables.
* **Bonus**: The bonus implementation supports up to `MAX_FD` (1024) simultaneous file descriptors, each with independent state management.
* **Performance note**: With very small BUFFER_SIZE values (e.g., 10) and extremely large lines (20,000+ characters), performance may degrade due to O(n²) string concatenation complexity. This is a known limitation of the malloc-based concatenation approach and does not affect correctness or real-world usability.

---

## Project Status

- ✅ Mandatory part: Complete and tested
- ✅ Bonus part: Complete and tested
- ✅ Norminette: Passed
- ✅ Memory leaks: None detected
- ✅ Edge cases: Handled
- ✅ Multiple file descriptors: Supported

**Final Grade: 125/100**
