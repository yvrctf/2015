# www

## description

No description provided.

## exploitation

www (write what where) is a contrived stack canary situation with a home made
canary. If you overflow too far, it will just segfault. If you overflow just
enough to overwrite saved EIP, you will get a "STACK SMASHING DETECTED"
warning. To solve, you need to use the consecutive strcpys to overwrite the
puts() call in the GoT and then have that trigger a call to your shellcode.
puts() gets called before the stack smash detection, so a proper exploit should
have no problem bypassing that.
