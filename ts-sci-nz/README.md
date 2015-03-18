# ts-sci-nz

## description

```text
*** TOP SECRET MUST NOT BE SHARED OUTSIDE NZHQ ***

Hello,

We intercepted this transmission sent yesterday morning being sent to Adelaide. Based on our observations it came from Canberra so we can only assume it was a government transmission. Based on new intelligence, they're using a new machine to encipher their text and at this time we're unsure of what they're doing to get the message across.

Please decipher this at the earliest possible and deliver it to my handler in Christchurch. We must not let the Queen take back our land.

8e8b1f2c4f7a4e5c9f3a0d8b3f4c0d3a
3e1a6f0c4d9c2e5a1e5b3d4b5d3a7f1c
3e7a4f5b5f0c2d1a8e8b6d4b1e1c4f8a
6f6b0e3a6d9a4e2a0d7a0e0c2d5a2e3c
6d9a2e4b2d6a7e7c0f4a2e2b7e4b5d3a
6e4c6d9a4e8c0d9b8e5a2e3a0e3c5e3c
7f4b5d3a1d7a3e5a7f9a7f5b8f1b9f8a
6d6c4f7b0d7b8f1a4d7b9e7a0d7b8d5b
8f0b8f2c9e0a8d7a6f1a5d6b6f1c9d0b
8d7a4e5c9f3a0d8b3f4c0d3a3e1a1f9c
2e5a5d1c3f4c0d3b5e3a1d2b2f4c1e1c
8e9a5e6a4d9c2e7a4f7b7e1a8d5a9d8b
3f5a7f6c0d3c8f1b1e3a6d9a6d9a4f9a
9f3a7f3b1f2c1e6c8d5c5f3a3f1c4e7a
0d6b3e1a6f9b4d7a9d0b3f1a4f4a5e3a
1d0c9e9a5f2b0d7a4d8b7e5a5f3c6e6b
0d0a4d2c4d3a2f7a2e5c2e3a9e1a4d3a
2f7a0f5c6e9a4d5c2d5a2d1c4e3c7f9a
5e0b4d8c4e2c3f2b7e1a4d1a4d4c2f5b
5e9a3e3a9e8c8f8b3f5a8d8a3e1a6e5a
2f8b6d9a8d6a2d3c7e5a8d8b6d6a0d3c
8d5c8e7a4d3a2f7a0e2b0d8a6f5c9e8b
9d7a6e6a0d9a6e6b1e8b6d6a2e3c2f5b
2d9a2e2c4d7a0e2b0d4a5e8c8f3c9e4b
1e2a0d9a8f3a2d9b9e7a5f8c3d7b5e2c
4d9b8d4b0e5c8e8b2d5b1e9c9d1a1e9a
2d9a2d7c2d2c6d0b0d6b5f5c5e0c2d5a
5f3c6e9a9d5c7f8c4d1a9e0b6d9a9d5c
0d7b4d7b3e1c6d3c7f5b2d5a0e8a6d9c
0d5b2d4a6f5a0e5a2f0c1f3c2f5c4d8c
1f5a5d1b4f9a9d5c7f8c4d9a4e1c1d2b
0d0c8f1b4d3a2f7a0d9a9d3a6f1a8f1b
0d7a0f1a7e1a4d1a4d4a0e1c0f3b0d8a
8f7c0e3a6d6c4f7b0d0a6f8c9f5a8e0b
8d6a7e7c0f7c7d8b9d7a7d3c8d5b2d6c
2e2b4d1b1e6b0d4a5e1a6d9c1f4c7d3b
3e7b2d2c0f3b6d3a1e2b8d1a0d7b7e5a
2f0c1f3c2f5c4d8c1f5a3d2c1e1a7f4b
2d0a1e1c4f1c1d2b0d9a6e6b0d5a5d1c
6d3b0d9a6e6b4d8c2f2c3f5c9d5c8e7a
4d8c1f9a2d7a4e4b9d5a6f0b8d1a1e6c
2d8b5e5a2d2a9e4b6d3b6e7c9e1a8e4a
9e7a2e5c7d4b2d1a8e7a4d7a6d3b4f8c
2d9a7e2c3f9a2d2b0d7a4d8b7e2c6d1c
6d9a8d7c2d2c0f3b6d4c0d2c3e6c1f2c
0f3b3e4c8d3c6e1a9f1b6f7c9e4c5f9a
4f7b2d1a8e8b6d6a0d6b0d4b5f6c0f2b
4d3a2f5b4f8c0d6b1e5a4d1b4f5a2d8c

Yours truly in defeating the Australians,
Minister Stevensons
```

## solution

This is a standard substitution cipher with rotation.

Firstly, the Australian dial-pad is used to substitute the letters based on the following 
keys:

```
1 - QZ, 2 - ABC, 3 - DEF
4 - GHI, 5 - JKL, 6 - MNO
7 - PRS, 8 - TUV, 9 - WXY
0 - Space
```

Secondly, when the dial-pad is being used, positioning within the key is determined using 
the letters 'A', 'B', 'C'. This means that the letter 'B' would become '2B' or 'O' would 
become '6C'. Under this scheme, `hello` would become `4B3B5C5C6C`.

To avoid frequency analysis, the encrypting party will need to set a 'shift' to start at 
between 0 and 9. Using this shift, the encrypter will then increase the value by 1 as 
it enciphers the text. This means at 'H' it would be at 1, 'E' at 2, and so forth. If we 
started at '1', then the `4B3B5C5C6C` would become `6C6B9C0C2C` as the enciphering 
increases the shift before encrypting each letter. The decrypting party needs to know 
what the value was at the encryption time in order to reverse the text.

If the shift value goes beyond '9', the lowest place value is taken as the shift value.
Thus, '10' would be a shift value of '0' and '16' would be '6'.

To add a level of obfuscation and to confuse people, the letters are then substited every 
other letter with 'DEF', thus 'A' become 'D' et cetera. This is to trick people into 
thinking that these are MD5 values. This relies on the message being a sufficient length 
to keep this up.

Deciphering this is really easy. You just need to substitute those letters and then 
count backwards then assign the letters based on the dial-pad value and place.
