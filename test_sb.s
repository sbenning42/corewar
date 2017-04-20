#by zaz, still not as good as rainbowdash though
#2013

.name		"TEST"
.comment	"test each instruction"

live %42
ld %42, r2
ld 42, r2
st r2, r3
st r2, 42
add r2, r3, r4
sub r2, r3, r4
and r2, r3, r4
and %42, %42, r2
and 42, 42, r2
and r3, %42, r2
and 42, r3, r2
and 42, %42, r2
or %42, %42, r2
or 42, 42, r2
or r3, %42, r2
or 42, r3, r2
or 42, %42, r2
xor %42, %42, r2
xor 42, 42, r2
xor r3, %42, r2
xor 42, r3, r2
xor 42, %42, r2
zjmp %42
ldi r2, r3, r4
ldi %42, r3, r4
ldi 42, r3, r4
ldi r2, %42, r4
ldi 42, %42, r4
sti r2, r3, r4
sti r2, %42, %42
sti r2, 42, r3
sti r2, %42, %42
sti r2, 42, r3
fork %42
