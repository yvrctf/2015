# wildblueyonder

## description

No description provided

## exploitation

This is a slightly more interesting problem. There are two bugs: one is a
buffer overflow in reroll\_char which allows you to smash the stack with
alphanum only. This is designed to be relatively easy to find. The slightly
more complex bug is the interger signed to unsigned conversion out of atoi()
before the mmap. This, along with the specified address allows you to map
0x20202020, which will allow you to exploit the buffer overflow. 
