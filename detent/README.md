# detent

## description

```text
Very much not the same thing as a détente.

detent.termsec.net 9182

Edit: Note that hostname in the binary is incorrect.
```

## exploitation

This is a correct key: `CKCKCACGOGCKIJL\`

The flag was `flag{th3_fly3st_c4v3-4g3d_ch33s3}`

## details

At a high level, this program interprets the key as a program over some
internal state, treating each character as a command that updates the
state, and then validates whether the final state is the expected final
state. It does this in addition to various other checks on the possible
sequences of characters (and therefore instructions) allowed.

The key space for this program is not actually particularly
large, as it rejects any input that contains ASCII characters not in the
range of (65...96) and ignores any input beyond 16 characters, leaving
only 2\*\*(32\*16) possibilities remaining. It then pulls the remaining
characters down to the range(0...31), so they fit in five bits, and
rejects any sequence in which adjacent characters differ by more than
a single bit, e.g. the sequence BFE is not rejected, as the sequence of
bit patterns goes

```text
    - [start] 0b00000
    - B       0b00001 <- bit 0 flipped
    - F       0b00101 <- bit 2 flipped
    - E       0b00100 <- bit 0 flipped
```

whereas a sequence like BAD is rejected

```text
    - [start] 0b00000
    - B       0b00001 <- bit 0 flipped
    - A       0b00000 <- bit 0 flipped
    - D       0b00011 <- bits 0 *and* 1 flipped
```

Finally, the sequence of letters is traversed and interpreted as a
command that describes updates to a set of three 32-bit values. Each
character is treated as a set of three two-bit commands that apply to
each of the three numbers, in which 0b00 does not change the number, 0b01
increments it, 0b10 decrements it, and 0b11 flips the bits in the number.
For example, the character 'T' is interpreted as a command:

```text
    T: 0b010011
         ||||||
         ||||++- bit-flip the x value
         ||++--- do not change the y value
         ++----- increment the z value
```

(As the quantities in question are only five bits, highest bit will always
be zero, which means that the z value cannot be bit-flipped or decremented.)
After performing this process, the quantities of x, y, and z must be

```text
    { .x = 1
    , .y = -8
    , .z = 7
    }
```

in which case the key is accepted by the program.
