.ORIG X3000                   
AND R0,R0,#0    ;以下先进行学生成绩排行(冒泡排序)
ADD R0,R0,#15
ADD R0,R0,#1
AND R1,R1,#0
ADD R1,R1,#15
;;ADD R1,R1,#1            ;二重循环
          
	LD R2,A         ;R2,R3为代表指针
	LD R3,A

THIRD	LDR R4,R2,#0    ;R4代表成绩
         	
FIRST		ADD R3,R3,#1		;第一次循环
		LDR R5,R3,#0 		;r5为下一位成绩
		NOT R5,R5       	 
		ADD R5,R5,#1		;得到R5的相反数
		ADD R6,R4,R5		;;r6=r4+r5
		BRn CHANGE		;;如果r4<r5 交换

CONTINUE	ADD R1,R1,#-1   ;循环变量1
		BRZ SECOND	;第一轮循环结束标志
		BRnzp FIRST	;无条件跳转
			
SECOND		;;第二次循环
		ADD R2,R2,#1
		ADD R3,R2,#0     ;R3 R1 都要还原 进行第二次循环
		ADD R0,R0,#-1
		ADD R1,R0,#-1
		BRZ NEXT	;第二次循环结束
		BRnzp THIRD

CHANGE				;后一个数大于前一个数时进行交换
	STR R4,R3,#0
	NOT R5,R5
	ADD R5,R5,#1
	STR R5,R2,#0
	LDR R4,R2,#0
	BRNZP CONTINUE
NEXT	
	LD R2,A
	LD R4,B
	AND R0,R0,#0 		
	ADD R0,R0,#15
	ADD R0,R0,#1		;将x3200从小到大复制到x4000
LOADING
	LDR R3,R2,#0
	STR R3,R4,#0
	ADD R4,R4,#1
	ADD R2,R2,#1
	ADD R0,R0,#-1
	BRZ NEXT1
	BRNZP LOADING	
NEXT1					;判断ABC  
	AND R7,R7,#0			;因为之前已经从大到小排好序了 A存放在x3200~x3204  R7放置A的学生个数
	AND R0,R0,#0
	ADD R0,R0,#5	
	LD R2,A
	LD R3,D				
	NOT R3,R3
	ADD R3,R3,#1			;得到85的相反数，即R3取反加一
NEXT2
	LDR R4,R2,#0
	ADD R2,R2,#1			;判断四个学生就好了
	ADD R0,R0,#-1
	BRZ NEXT3			;若四个学生都已经判断完成开始判断B学生
	ADD R5,R4,R3			;大于0就跳
	BRZP ALEVEL
	BRNZP NEXT2
ALEVEL
	ADD R7,R7,#1
	STI R7,C
	BRNZP NEXT2

NEXT3	
	AND R6,R6,#0			;判断B的个数，从x3200开始判断8个数
	AND R0,R0,#0
	ADD R0,R0,#9			;判断8个学生
	LD R2,A
	LD R3,E				
	NOT R3,R3
	ADD R3,R3,#1			;得到75的相反数，即R3取反加一
NEXT4
	LDR R4,R2,#0
	ADD R2,R2,#1
	ADD R0,R0,#-1
	BRZ THEEND			;判断完成
	ADD R5,R4,R3			;大于0就跳
	BRZP BLEVEL
	BRNZP NEXT4
BLEVEL
	ADD R6,R6,#1		;得到前8个学生中成绩大于75的学生
	NOT R1,R7
	ADD R1,R1,#1
	ADD R1,R6,R1		;减去原先已判断的A等级的学生，得到B等级的学生
	STI R1,F
	BRNZP NEXT4
	
THEEND	TRAP X25


A .FILL X3200           ;储存成绩开始的内存地址 x3200
B .FILL X4000           ;x4000开始储存成绩 x4000最高成绩 
C .FILL X4100
D .FILL #85
E .FILL #75
F .FILL X4101
.END