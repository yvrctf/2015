# delphi

## description

No description given

## exploitation

There are technically two ways to solve this challenge.  One is through command
injection and the other is through a buffer overflow.  In either case, there is
an integer overflow that must be used.

### easy solution:

When you run the `main` program, you're dropped into a game shell.  It really
wants to play twenty questions. The easy solution is simply this:

```text
> go ;/bin/sh 65498
```

### harder solution:

The harder solution still needs the integer overflow, the only difference is
that you'd exploit a buffer overflow and go from there. There is no PoC
provided for that route.
