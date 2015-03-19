# matasano

## description

```text
Keys open doors.
Keys open doors.

PwMUFVsbOghWAAcbMU4RHlZSKxwTFAUEF11zDgMTE1sFNgpUTksRLxwAFVsTKh0Q
Jx9BLlsKLRRCBgcHMEMGF18eOhdDQxsJCBRlFUBBExMcOBIdTkYaO04XF0MCOgFOUB0LFw
IQkVRxIHfxVZD1NUPh0WWhMDKhoAX1IDBQ50SkwNDhAMfzNQA0YQPgA
LxhGFFsdNwBFTlUVL04VHlYcMB4GWh0LRDlvCEwlBh8Ic0FXG0Qffz4KBkMT
PwMURxwGK0FFAQcXPgIJVl4XfzURVRwGDQ4gK0IpSVs+NwhFCw
LwIVBhAMfw1YCU8AfxoKHVYBc1MXWwYARBRyCQI
MQ0SRw8GMwURB0lULAYKGUcdKgcQGFIWEBx5RgAOEFsIMQURBUIRL04DH0EbMVQ
LQkEF1sMJxVDDwcXMwcVBRMUMAFDUQoRFhwgFQQIEw
MQQOQAhJMQRJGgcAME4DGloCfxwNFAYNBQkgBQ0VRwwAKwkRGk8VK04CBFoCfxwNFAAEFA
MgQERxYGLBURHU8VOxdJVhsmOh8PFDcIRVQgIB4ACRAAOkFTD0UN
JwUPQA9JMQ4RGkIYMwcLERMFNxYRUVIsRBBhH0wDAg
Kw0YRwgMOkFcCwcdMU4hWHBcfxIXFDoKExxyAkwpCBYMPA5cB0kT
MQUVD1sEJkFcD0lUHA8VGV0Xc1MEQR8IDRNnSkwJBhgCNg9WTlQbMgsRHlocOA
```

## exploitation

The title is a nod to [the Matasano crypto challenges](http://cryptopals.com/), which are excellent and everyone should look at.

Aside from that, there are a couple of hints on how to approach it:
* The limited alphabet (and the lone '+') looks like the message is base64 encoded, albeit with the padding '=' bytes removed.
* The non-aligned line breaks mean each line is probably encoded individually.
* The description suggests that it's a repeated key
* The line lengths don't have a common factor >1, after decoding, suggesting it's a stream cipher.
* It's only worth 50 points.

Pretty likely it's repeating key xor. I chose the dumb way to solve it.

## the dumb way

I assumed the content was english, and that it was likely ` the ` was present
in the plaintext. The idea is to xor ` the ` against the first line, first
'slot' of ciphertext, then xor the result against the same 'slot' of every
other line.

```text
ABCDEF
GHIJKL
MNOPQR
STUVWX
```

For example, in this case we would xor ` the ` against `ABCDE`, then xor the
result against `GHIJK`, `MNOPQ` and `STUVW`. If the result looks like
gibberish, try the next position on the first line, `BCDEF`. If no position on
the first line works, try the second, and so forth. If the result from those
other lines looks like plausible plaintext, then it's a starting point.

If you try ` the ` on this ciphertext, you'll get a bunch of false positives,
but also this:

```text
pos 13:  the
pos 13: -call
pos 13: ss, q
pos 13:  phen
pos 13: ll me
pos 13: tokes
pos 13: hooto
pos 13: ips f
pos 13:  flip
pos 13: y, (T
pos 13: ing w
pos 13:  D.C.
pos 13: apone
pos 13:
Guessed key: nev3r
```
 
Well that looks promising. Offset 13 of the first line has " the ". You can
build from there, for example line 7 looks like it's probably ` shootouts `:

```text
pos 11: on the top,
pos 11: so-called {
pos 11:  ass, quicg
pos 11: ap phenomeb
pos 11: call me Frm
pos 11: t tokes, tc
pos 11:  shootouts
pos 11: clips for i
pos 11: to flip on,
pos 11: ady, (Tell,
pos 11: lling wheri
pos 11: in D.C. at,
pos 11:  Capone, gy
pos 11:
Guessed key: t_nev3r_sc8
```

Okay that doesn't quite look right. To paraphrase Jules Winnfield, quicg ain't
no word I ever heard of. So it's probably not ` shootouts `, that last
character could be punctuation, could be something else. Line 4 looks like it's
probably ` rap phenomenon ` though.

If you keep building on known plaintext, you'll eventually get something like this:

```text
pos 0: Your reign on the top was short like leprechauns
pos 0: As I crush so-called willies, thugs, and rapper-dons
pos 0: Get in that ass, quick fast, like Ramadan
pos 0: It's that rap phenomenon Don Dada, fuck Poppa
pos 0: You got to call me Francis M.H. White
pos 0: Intake light tokes, tote iron
pos 0: Was told in shootouts, stay low and keep firin'
pos 0: Keep extra clips for extra shit
pos 0: Who's next to flip on that cat with that grip on rap
pos 0: The most shady, (Tell Em!) Frankie baby
pos 0: Ain't no telling where I may be
pos 0: May see me in D.C. at Howard Homecoming
pos 0: With my man Capone, gumming, hacking something
Guessed key: flag{i_a1n't_nev3r_sc4red}^@flag{i_a1n't_nev3r_sc4re
```

Keys open doors.

## note

In retrospect this was a badly designed challenge: if you decide it was CTR
mode instead, you can still solve for the original plaintext but your key will
be complete gibberish. I'm only aware of one person who did it that way, but if
anyone else did and gave up, sorry!
