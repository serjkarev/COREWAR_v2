.name "test"
.comment "make it live"

live %-1
ld -2,r12
ld 7, r7
st r13, -3
st r12, -24
add r7, r12, r2
st r2, 30
and %22, %4, r3
st	r3, 150
or	r2, r1, r4
xor	r12, 3, r5
or	r3, r4, r6
xor	r5, r6, r7
st	r7, 50
xor	r8, r9, r7
live %42
zjmp %100
