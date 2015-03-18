# sushi

## description

```text
sushi.termsec.net 4000

Sushi is great in Vancouver. It's cheap, it's delicious, and it's everywhere.

Read flag.txt
```

## exploitation

This is a straight-forward buffer overflow with an exec stack and gets().
The only slightly tricky part at all is that its amd64 instead of x86 and ASLR
is on. The ASLR is mitigated by being provided the address of the buffer you
return to.

The provided exploit spawns a shell, cat flag.txt
