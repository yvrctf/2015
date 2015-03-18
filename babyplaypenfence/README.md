# baby playpen fence

## description

```text
You're in a little baby sandbox. Escape and read the flag.

babyplaypenfence.termsec.net 25887

Edit: The sandbox is running on a stock install of Ubuntu Server 14.04.2
```

## exploitation

This was meant to be a basic seccomp example and turned out to be a little
harder than expected. There were also some implementation errors on my part:
mea culpa.

The binary accepts shellcode from clients and executes it in a sandbox.

The meat of the seccomp filter was this:

```c
     struct sock_filter filter[] = {
         SC_CHECK_ARCH,
         SC_LOAD_SYSCALL,
         SC_DENY_SYSCALL(open, EINVAL),
         SC_DENY_SYSCALL(mmap, EINVAL),
         SC_DENY_SYSCALL(openat, EINVAL),
         SC_DENY_SYSCALL(open_by_handle_at, EINVAL),
         SC_DENY_SYSCALL(ptrace, EINVAL),
         SC_ALLOW
     };
```

Any attempts to use open, mmap, openat, open_by_handle_at or ptrace would
result in an EINVAL return. There was also a prctl call with PR_SET_DUMPABLE to
block ptrace and related functions, but it was called on the child instead of
the parent, which theoretically opened up the ability to abuse the parent
process outside the sandbox. That was unintentional, but is starting to sound
like an interesting challenge for the future...

Since 3.4 the Linux kernel has had a feature called the [X32
ABI](http://en.wikipedia.org/wiki/X32_ABI); 64bit syscalls with 32bit pointers. 

```
/usr/include/x86_64-linux-gnu/asm/unistd_x32.h:#define __NR_open (__X32_SYSCALL_BIT + 2)
```

Using that syscall, you can bypass the seccomp filter. Blacklisting is bad.

## Honorable mention

You might have noticed that process_vm_readv and process_vm_writev aren't
blocked either (the mongols did.) This was an oversight, but on Ubuntu those
will be blocked in this context by the ptrace restrictions in the yama lkm. On
other distros, that should have just worked.

Also, it's a cooler solution. :)
