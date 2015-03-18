# gloriousmodern

## description

No description provided

## exploitation

A basic read-what-where vuln. There is a super ghetto sprintf into a fixed
size buffer. You can control the padding up to two digits (99) being the max
obviously. The buffer is 90b wide, giving you a write9 on the heap.
Conviently, this overlaps with the array index. The basic program is a
non-sensical parody of a cpp. Basically you have a linked list of 16 elements
which contain an index into an array which store the actual values. You
overwrite this index, which lets you get your read8 (presuming the index is
null free.) This allows you to leak the flag.

Because it's kinda weird, here's an ascii diagram:

```text
Linked list:
[undef] -> [undef] -> [1] -> [0]

[5,6, ... ]
```

So element 2 in the linked list (assuming 0 indexing) points to array position
1 in the value array. Element 3 points to array position 0. These are the
indexes that get overwritten.
