.name "test"
.comment "ld test"

live:	live %1
		ld -42, r1
		ld %:live, r1
