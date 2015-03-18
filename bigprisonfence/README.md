# big prison fence

## description

```text
You're in a big prison sandbox now. We like to kick sand castles, do you?

bigprisonfence.termsec.net 49782

Edit: fixed binary
```

## exploitation

This was meant to be a slightly harder seccomp example that turned out to be
the easier one.

Go figure.

Like the baby version, this binary accepts shellcode from clients and executes
it in a sandbox. This time the sandbox was just using SECCOMP_MODE_STRICT,
which only allows read, write, _exit and _sigreturn. No x32 dodge this time.

The shellcode is read into a structure like this, along with a name:

```c
     struct prog {
         char *prog_data;
         char prog_name[32];
         char *secret;
         uint32_t length;
     } p = {
         .prog_data = 0,
         .prog_name = { 0 },
         .secret = flag,
         .length = 0
     };
```
 
The original plan was to require the shellcode to perform some kind of
operation on the flag to provide a plausible reason for it to be there. In this
version of the binary there are no such requirements.

```c
/* kinda gross, don't care */
uint32_t read_line(int fd, char *target, char delim, uint32_t length) {
    uint32_t total_bytes_read = 0;
    char c;

    while (total_bytes_read++ < length && read(fd, &c, 1) == 1)
        if (c == delim) {
            *target = 0;
            return total_bytes_read;
        } else
            *target++ = c;

    while (read(fd, &c, 1) == 1 && c != '\n');

    return total_bytes_read;
}
```

The name is read in using this function, which won't null-terminate the string
if it reaches the max length, allowing you to leak the pointer to the flag. All
fds are closed though, and the open() syscall is blocked.

```c
     waitpid(pid, &x, 0);
     if (!WIFEXITED(x) || WEXITSTATUS(x))
         abort();
```

The tail end of the runner function checks the status of the child process and
exits immediately. Otherwise control returns to the main function which prints
a thank you message and closes the connection.

Using this, you can leak one bit of the flag at a time. I chose a binary search
approach, but in retrospect it would probably have been cleaner to explicitly
test each bit directly.
