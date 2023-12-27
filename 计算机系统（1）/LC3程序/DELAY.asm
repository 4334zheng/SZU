.ORIG x3000
	LD R0,itptr
	LD R1,itfunc
	STR R1,R0,#0
	LD R0,kbsr
	LD R1,X_4000
	STR R1,R0,#0
	LD R6,stptr

m_loop	LEA R0,str1
	TRAP x22
	AND R0,R0,#0
	ADD R0,R0,#13
	TRAP x21
	AND R0,R0,#0
	LD R0,lpcnt
wait1	ADD R0,R0,#-1
	BRp wait1

	LEA R0,str2
	TRAP x22
	AND R0,R0,#0
	ADD R0,R0,#13
	TRAP x21
	AND R0,R0,#0
	LD R0,lpcnt
wait2	ADD R0,R0,#-1
	BRp wait2
	BRnzp m_loop

itptr	.FILL 0x180
itfunc	.FILL 0x2000
stptr	.FILL x3000
lpcnt	.FILL #25000
str1	.STRINGZ "ICS   ICS   ICS   ICS   ICS   ICS"
str2	.STRINGZ "   ICS   ICS   ICS   ICS   ICS   "
kbsr	.FILL 0xfe00
X_4000	.FILL x4000

.END