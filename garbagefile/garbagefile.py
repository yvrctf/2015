#!/usr/bin/env python
import struct
from itertools import cycle, izip


with open('flag', 'rb') as flag:
    bytez = flag.read()
    (length,) = struct.unpack('!i', bytez[0:4])
    key = ''.join(bytez[4:8])
    (offset,) = struct.unpack('!i', bytez[4:8])
    flag.seek(offset)
    raw = flag.read(length)
    content = raw.decode('zlib_codec').decode('base64')
    data = ''.join(chr(ord(c) ^ ord(k)) for c, k in izip(content, cycle(key)))
    with open('restored', 'wb') as restored:
        restored.write(data)
