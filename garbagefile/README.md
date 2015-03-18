# garbagefile

## description

```text
Your buddy Joey left a USB key with some data he needs your help with. He
pulled it from the firewall logs at a 'secure file format'-as-a-Service
provider, so he's pretty sure it might be protected or obfuscated somehow.
```

## exploitation

The pcap contains some TFTP traffic, containing some compressed files. The
format is this:

```text
size | offset | junk | content | junk
```

Where `size` is the length of the content, and `offset` is the byte position it
starts. The `junk` regions are random compressed data, and the content is
base64 encoded.

The encoded content is xor encrypted with the offset value from before as the
key.

Once decrypted you are left with a PNG of the flag.
