.ORIG x3000

; initialize the stack pointer
	LD R6,stptr	;栈指针

; set up the keyboard interrupt vector table entry
	LD R0,ptr
	LD R1,func
	STR R1,R0,#0

; enable keyboard interrupts
	LD R2,IE
	STI R2,KBSR	;使能中断位

; start of actual user program to print ICS checkerboard
m_loop	LEA R0,str1
	TRAP x22	;打印字符串1
	LD R0,ENDL
	TRAP x21	;打印回车
	JSR DELAY

	LEA R0,str2	;打印字符串2
	TRAP x22
	LD R0,ENDL
	TRAP x21 	;打印回车
	JSR DELAY
	BRnzp m_loop
	HALT

ptr	.FILL x0180
func	.FILL x2000
stptr	.FILL x3000
str1	.STRINGZ "ICS   ICS   ICS   ICS   ICS   ICS"
str2	.STRINGZ "   ICS   ICS   ICS   ICS   ICS   "
KBSR	.FILL xfe00
IE	.FILL x4000
ENDL	.FILL 0x0D

DELAY	ST R1,SaveR1
	LD R1,COUNT
REP	ADD R1,R1,#-1
	BRp REP
	LD R1,SaveR1
	RET

COUNT	.FILL #25000
SaveR1	.BLKW 1

.END
	