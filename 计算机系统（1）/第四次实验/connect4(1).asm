.ORIG x3000
BRnzp pre_main			; 从main函数开始

print	ST R0, save_R0		; 保存寄存器
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

	AND R1, R1, #0		; R1=6
	ADD R1, R1, #6
	LEA R3, mat0x		; R3保存矩阵首地址

pr_Loop1	
	AND R2, R2, #0		; R2=6
	ADD R2, R2, #6
		
pr_Loop2	
	LDR R4, R3, #0		; R4=M[R3]取矩阵数据
	ADD R3, R3, #1		; R3+=1
	ADD R5, R4, #0		; 跳转判断
	BRz pr_NULL		;
	BRn pr_X		;如果小于0，表示玩家二棋子
	BRp pr_O		;如果大于0，表示玩家一棋子
	
pr_O	LD R0, O		; 情况1玩家1棋子
	TRAP x21
	BRnzp pr_L2end	
pr_X	LD R0, X		; 情况2玩家2棋子
	TRAP x21
	BRnzp pr_L2end	
pr_NULL	LD R0, NULL		; 情况3无棋子
	TRAP x21	

pr_L2end	
	LD R0, space		; 打印空格
	TRAP x21
	ADD R2, R2, #-1	
	BRp pr_Loop2		; 循环2到此结束
	LD R0, nextLi		; 打印回车
	TRAP x21
	ADD R1, R1, #-1
	BRp pr_Loop1		; 循环1到此结束
	
	LD R0, save_R0		; 恢复寄存器
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

judge1	ST R0, save_R0		; 保存寄存器
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; 判断|
	AND R1, R1, #0
	ADD R1, R1, #3		; R1=3外循环迭代器
	LEA R3, mat0x		; R3首行地址

j1_Loop1	AND R2, R2, #0
		ADD R2, R2, #6		; R2=6内循环迭代器

j1_Loop2	ADD R4, R3, #-1		; 获取当前行地址(偏移-1从0开始)
		ADD R4, R4, R2		; R4计算列偏移地址
		AND R5, R5, #0		; R5记录玩家1棋子数目
		LDR R0, R4, #0	
		BRz j1_L2end		; 如果遇到0直接break
		ADD R0, R0, #-1
		BRnp j1_ad1 
		ADD R5, R5, #1
j1_ad1	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #0	
	BRz j1_L2end		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j1_ad2 
	ADD R5, R5, #1
j1_ad2	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #0	
	BRz j1_L2end		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j1_ad3 
	ADD R5, R5, #1
j1_ad3	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #0	
	BRz j1_L2end		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j1_ad4 
	ADD R5, R5, #1
j1_ad4	ADD R6, R5, #-4		; 只要能走到这里必定为4个1或2
	BRz winc1_pre		; 如果p1计数器为4则p1赢
	ADD R5, R5, #0
	BRz winc2_pre		; 如果p1计数器为0则p2赢

j1_L2end	ADD R2, R2, #-1
		BRp j1_Loop2		; 内循环到此结束
	
		ADD R3, R3, #6		; R3指向下一行
		ADD R1, R1, #-1
		BRp j1_Loop1		; 外循环到此结束
; 判断|结束
	
	LD R0, save_R0		; 恢复寄存器
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

judge2	ST R0, save_R0		; 保存寄存器
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; 判断\
	AND R1, R1, #0
	ADD R1, R1, #3		; R1=3外循环迭代器
	LEA R3, mat0x		; R3首行地址

j2_Loop1	AND R2, R2, #0
		ADD R2, R2, #3		; R2=3内循环迭代器

j2_Loop2	ADD R4, R3, #-1		; 获取当前行地址(偏移-1从0开始)
		ADD R4, R4, R2		; R4计算列偏移地址
		AND R5, R5, #0		; R5记录玩家1棋子数目
		LDR R0, R4, #0	
		BRz j2_L2end		; 如果遇到0直接break
		ADD R0, R0, #-1
		BRnp j2_ad1 
		ADD R5, R5, #1
j2_ad1	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #1	
	BRz j2_L2end		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j2_ad2 
	ADD R5, R5, #1
j2_ad2	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #2	
	BRz j2_L2end		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j2_ad3 
	ADD R5, R5, #1
j2_ad3	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #3	
	BRz j2_L2end		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j2_ad4 
	ADD R5, R5, #1
j2_ad4	ADD R6, R5, #-4		; 只要能走到这里必定为4个1或2
	BRz winc1_pre		; 如果p1计数器为4则p1赢
	ADD R5, R5, #0
	BRz winc2_pre		; 如果p1计数器为0则p2赢

j2_L2end	ADD R2, R2, #-1
		BRp j2_Loop2		; 内循环到此结束
		
		ADD R3, R3, #6		; R3指向下一行
		ADD R1, R1, #-1
		BRp j2_Loop1		; 外循环到此结束
; 判断\结束
	
	LD R0, save_R0		; 恢复寄存器
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

pre_main BRnzp p_main	; main函数过远 中转

; ----------------------------------------------------

; 字符存放
space	.FILL 0x20
NULL	.FILL 0x2D
O	.FILL 0x4F
X	.FILL 0x58
nextLi	.FILL 0x0D

; 矩阵存放
mat0x	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
mat1x	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
mat2x	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
mat3x	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
mat4x	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
	.FILL #0
mat50	.FILL #0
mat51	.FILL #0
mat52	.FILL #0
mat53	.FILL #0
mat54	.FILL #0
mat55	.FILL #0

; 寄存器存放
save_R0	.FILL #0
save_R1	.FILL #0
save_R2	.FILL #0
save_R3	.FILL #0
save_R4	.FILL #0
save_R5	.FILL #0
save_R6	.FILL #0
save_R7	.FILL #0

; ----------------------------------------------------

p_main BRnzp main		; main函数过于远 中转
winc1_pre BRnzp winc1		; 中转
winc2_pre BRnzp winc2

; ----------------------------------------------------

; judge3 判断斜向四连 / 的情况

judge3	ST R0, save_R0		; 保存寄存器
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; 判断/
	AND R1, R1, #0
	ADD R1, R1, #3		; R1=3外循环迭代器
	LEA R3, mat0x		; R3首行地址

j3_l1	AND R2, R2, #0
	ADD R2, R2, #3		; R2=3内循环迭代器

j3_l2	ADD R4, R3, #-1		; 获取当前行地址(偏移-1从0开始)
	ADD R4, R4, R2		; R4计算列偏移地址
	ADD R4, R4, #3
	AND R5, R5, #0		; R5记录玩家1棋子数目

	LDR R0, R4, #0	
	BRz j3_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j3_ad1 
	ADD R5, R5, #1
j3_ad1	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #-1	
	BRz j3_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j3_ad2 
	ADD R5, R5, #1
j3_ad2	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #-2	
	BRz j3_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j3_ad3 
	ADD R5, R5, #1
j3_ad3	ADD R4, R4, #6		; R4指向下一行
	LDR R0, R4, #-3	
	BRz j3_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j3_ad4 
	ADD R5, R5, #1
j3_ad4	ADD R6, R5, #-4		; 只要能走到这里必定为4个1或2
	BRz winc1_pre		; 如果p1计数器为4则p1赢
	ADD R5, R5, #0
	BRz winc2_pre		; 如果p1计数器为0则p2赢

j3_l2ed	ADD R2, R2, #-1
	BRp j3_l2		; 内循环到此结束
	
	ADD R3, R3, #6		; R3指向下一行
	ADD R1, R1, #-1
	BRp j3_l1		; 外循环到此结束
; 判断/结束
		
	LD R0, save_R0		; 恢复寄存器
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

; judge4 判断横向四连 即 - 的情况

judge4	ST R0, save_R0		; 保存寄存器
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; 判断-
	AND R1, R1, #0
	ADD R1, R1, #6		; R1=6外循环迭代器
	LEA R3, mat0x		; R3首行地址

j4_l1	AND R2, R2, #0
	ADD R2, R2, #3		; R2=3内循环迭代器

j4_l2	ADD R4, R3, #-1		; 获取当前行地址(偏移-1从0开始)
	ADD R4, R4, R2		; R4计算列偏移地址
	AND R5, R5, #0		; R5记录玩家1棋子数目

	LDR R0, R4, #0	
	BRz j4_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j4_ad1 
	ADD R5, R5, #1
j4_ad1	LDR R0, R4, #1	
	BRz j4_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j4_ad2 
	ADD R5, R5, #1
j4_ad2	LDR R0, R4, #2	
	BRz j4_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j4_ad3 
	ADD R5, R5, #1
j4_ad3	LDR R0, R4, #3	
	BRz j4_l2ed		; 如果遇到0直接break
	ADD R0, R0, #-1
	BRnp j4_ad4 
	ADD R5, R5, #1
j4_ad4	ADD R6, R5, #-4		; 只要能走到这里必定为4个1或2
	BRz winc1_pre		; 如果p1计数器为4则p1赢
	ADD R5, R5, #0
	BRz winc2_pre		; 如果p1计数器为0则p2赢

j4_l2ed	ADD R2, R2, #-1
	BRp j4_l2		; 内循环到此结束
	
	ADD R3, R3, #6		; R3指向下一行
	ADD R1, R1, #-1
	BRp j4_l1		; 外循环到此结束
; 判断-结束
	
	LD R0, save_R0		; 恢复寄存器
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

; 列指针存放
ptr0	.FILL #0
ptr1	.FILL #0
ptr2	.FILL #0
ptr3	.FILL #0
ptr4	.FILL #0
ptr5	.FILL #0

; ----------------------------------------------------

main	AND R1, R1, #0		; R1=18 迭代变量
	ADD R1, R1, #15
	ADD R1, R1, #3
	
	JSR print
	
	LEA R0, mat50		; 列指针赋值	
	ST R0, ptr0
	LEA R0, mat51		
	ST R0, ptr1
	LEA R0, mat52		
	ST R0, ptr2
	LEA R0, mat53		
	ST R0, ptr3
	LEA R0, mat54		
	ST R0, ptr4
	LEA R0, mat55		
	ST R0, ptr5

ma_Lp1	ADD R0, R0, #0

in1	LEA R0, p1inp 		; 打印输入提示
	TRAP x22
	TRAP x20		; 玩家1输入
	TRAP x21		; 回显
	ADD R0, R0, #-16
	ADD R0, R0, #-16
	ADD R0, R0, #-16 	; 输入-48 ascii转数字
	
	ADD R2, R0, #0		
	LD R0, nextLi_		; 输出回车
	TRAP x21
	ADD R0, R2, #0
	BRp i1t2		; 判断输入是否>'0'
	LEA R0, error		; 输出错误提示
	TRAP x22
	BRnzp in1

i1t2	ADD R2, R0, #-7 	; R2 = 输入-'7'
	BRn i1ed		; 判断输入是否<'7'
	LEA R0, error			
	TRAP x22
	BRnzp in1
	
i1ed	AND R2, R2, #0
	ADD R2, R2, #1		; 玩家1填数字1
	LEA R3, ptr0		; R3取列指针地址
	ADD R3, R3, R0		; R3列指针按照输入偏移
	LDR R4, R3, #-1		; 读取指针数据
	STR R2, R4, #0		; 将数据写入R3指向的地址
	ADD R4, R4, #-6		; 指针--
	STR R4, R3, #-1		; 将偏移后的值存回去
		
	JSR print
	JSR judge1		; 判断 | 输赢
	JSR judge2		; 判断 \ 输赢
	JSR judge3		; 判断 / 输赢
	JSR judge4		; 判断 - 输赢

in2	LEA R0, p2inp 		; 打印:请玩家2输入
	TRAP x22
	TRAP x20		; 玩家2输入
	TRAP x21
	ADD R0, R0, #-16
	ADD R0, R0, #-16
	ADD R0, R0, #-16 	; 输入-48 ascii转数字
	
	ADD R2, R0, #0		; 输出回车
	LD R0, nextLi_
	TRAP x21
	ADD R0, R2, #0
	BRp i2t2		; 判断输入是否>'0'
	LEA R0, error		; 输出错误提示
	TRAP x22
	BRnzp in2

i2t2	ADD R2, R0, #-7 	; R2=输入-'7'
	BRn i2ed		; 判断输入是否<'7'
	LEA R0, error		
	TRAP x22
	BRnzp in2
		
i2ed	AND R2, R2, #0		
	ADD R2,R2,#-1		; 玩家2填数字-1
	LEA R3, ptr0		; R3取列指针地址
	ADD R3, R3, R0		; R3列指针按照输入偏移
	LDR R4, R3, #-1		; 读取指针数据
	STR R2, R4, #0		; 将数据写入R3指向的地址
	ADD R4, R4, #-6		; 指针--
	STR R4, R3, #-1		; 将偏移后的值存回去
		
	JSR print
	JSR judge1		; 判断 | 输赢
	JSR judge2		; 判断 \ 输赢
	JSR judge3		; 判断 / 输赢
	JSR judge4		; 判断 —输赢
	
	ADD R1, R1, #-1	
	BRp ma_Lp1		; 循环到此结束
	
TieGame	LEA R0, Tie		; 平局
	TRAP x22
	BRnzp EOM

winc1	LEA R0, p1win		; p1赢了
	TRAP x22
	BRnzp EOM

winc2	LEA R0, p2win		; p2赢了
	TRAP x22
	BRnzp EOM

EOM	AND R0, R0, #0		; main函数结束

; ----------------------------------------------------

; 字符存放
nextLi_	.FILL 0x0D
; 字符串存放
p1inp	.STRINGZ "player 1 choose a cloumn:"
p2inp	.STRINGZ "player 2 choose a cloumn:"
Tie	.STRINGZ "Tie Game\n"
error	.STRINGZ "Invalid move. Try again.\n"
p1win	.STRINGZ "player 1 win\n"
p2win	.STRINGZ "player 2 win\n"

.END
