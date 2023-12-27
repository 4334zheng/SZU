.ORIG x3000
BRnzp pre_main			; ��main������ʼ

print	ST R0, save_R0		; ����Ĵ���
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

	AND R1, R1, #0		; R1=6
	ADD R1, R1, #6
	LEA R3, mat0x		; R3��������׵�ַ

pr_Loop1	
	AND R2, R2, #0		; R2=6
	ADD R2, R2, #6
		
pr_Loop2	
	LDR R4, R3, #0		; R4=M[R3]ȡ��������
	ADD R3, R3, #1		; R3+=1
	ADD R5, R4, #0		; ��ת�ж�
	BRz pr_NULL		;
	BRn pr_X		;���С��0����ʾ��Ҷ�����
	BRp pr_O		;�������0����ʾ���һ����
	
pr_O	LD R0, O		; ���1���1����
	TRAP x21
	BRnzp pr_L2end	
pr_X	LD R0, X		; ���2���2����
	TRAP x21
	BRnzp pr_L2end	
pr_NULL	LD R0, NULL		; ���3������
	TRAP x21	

pr_L2end	
	LD R0, space		; ��ӡ�ո�
	TRAP x21
	ADD R2, R2, #-1	
	BRp pr_Loop2		; ѭ��2���˽���
	LD R0, nextLi		; ��ӡ�س�
	TRAP x21
	ADD R1, R1, #-1
	BRp pr_Loop1		; ѭ��1���˽���
	
	LD R0, save_R0		; �ָ��Ĵ���
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

judge1	ST R0, save_R0		; ����Ĵ���
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; �ж�|
	AND R1, R1, #0
	ADD R1, R1, #3		; R1=3��ѭ��������
	LEA R3, mat0x		; R3���е�ַ

j1_Loop1	AND R2, R2, #0
		ADD R2, R2, #6		; R2=6��ѭ��������

j1_Loop2	ADD R4, R3, #-1		; ��ȡ��ǰ�е�ַ(ƫ��-1��0��ʼ)
		ADD R4, R4, R2		; R4������ƫ�Ƶ�ַ
		AND R5, R5, #0		; R5��¼���1������Ŀ
		LDR R0, R4, #0	
		BRz j1_L2end		; �������0ֱ��break
		ADD R0, R0, #-1
		BRnp j1_ad1 
		ADD R5, R5, #1
j1_ad1	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #0	
	BRz j1_L2end		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j1_ad2 
	ADD R5, R5, #1
j1_ad2	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #0	
	BRz j1_L2end		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j1_ad3 
	ADD R5, R5, #1
j1_ad3	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #0	
	BRz j1_L2end		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j1_ad4 
	ADD R5, R5, #1
j1_ad4	ADD R6, R5, #-4		; ֻҪ���ߵ�����ض�Ϊ4��1��2
	BRz winc1_pre		; ���p1������Ϊ4��p1Ӯ
	ADD R5, R5, #0
	BRz winc2_pre		; ���p1������Ϊ0��p2Ӯ

j1_L2end	ADD R2, R2, #-1
		BRp j1_Loop2		; ��ѭ�����˽���
	
		ADD R3, R3, #6		; R3ָ����һ��
		ADD R1, R1, #-1
		BRp j1_Loop1		; ��ѭ�����˽���
; �ж�|����
	
	LD R0, save_R0		; �ָ��Ĵ���
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

judge2	ST R0, save_R0		; ����Ĵ���
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; �ж�\
	AND R1, R1, #0
	ADD R1, R1, #3		; R1=3��ѭ��������
	LEA R3, mat0x		; R3���е�ַ

j2_Loop1	AND R2, R2, #0
		ADD R2, R2, #3		; R2=3��ѭ��������

j2_Loop2	ADD R4, R3, #-1		; ��ȡ��ǰ�е�ַ(ƫ��-1��0��ʼ)
		ADD R4, R4, R2		; R4������ƫ�Ƶ�ַ
		AND R5, R5, #0		; R5��¼���1������Ŀ
		LDR R0, R4, #0	
		BRz j2_L2end		; �������0ֱ��break
		ADD R0, R0, #-1
		BRnp j2_ad1 
		ADD R5, R5, #1
j2_ad1	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #1	
	BRz j2_L2end		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j2_ad2 
	ADD R5, R5, #1
j2_ad2	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #2	
	BRz j2_L2end		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j2_ad3 
	ADD R5, R5, #1
j2_ad3	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #3	
	BRz j2_L2end		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j2_ad4 
	ADD R5, R5, #1
j2_ad4	ADD R6, R5, #-4		; ֻҪ���ߵ�����ض�Ϊ4��1��2
	BRz winc1_pre		; ���p1������Ϊ4��p1Ӯ
	ADD R5, R5, #0
	BRz winc2_pre		; ���p1������Ϊ0��p2Ӯ

j2_L2end	ADD R2, R2, #-1
		BRp j2_Loop2		; ��ѭ�����˽���
		
		ADD R3, R3, #6		; R3ָ����һ��
		ADD R1, R1, #-1
		BRp j2_Loop1		; ��ѭ�����˽���
; �ж�\����
	
	LD R0, save_R0		; �ָ��Ĵ���
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

pre_main BRnzp p_main	; main������Զ ��ת

; ----------------------------------------------------

; �ַ����
space	.FILL 0x20
NULL	.FILL 0x2D
O	.FILL 0x4F
X	.FILL 0x58
nextLi	.FILL 0x0D

; ������
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

; �Ĵ������
save_R0	.FILL #0
save_R1	.FILL #0
save_R2	.FILL #0
save_R3	.FILL #0
save_R4	.FILL #0
save_R5	.FILL #0
save_R6	.FILL #0
save_R7	.FILL #0

; ----------------------------------------------------

p_main BRnzp main		; main��������Զ ��ת
winc1_pre BRnzp winc1		; ��ת
winc2_pre BRnzp winc2

; ----------------------------------------------------

; judge3 �ж�б������ / �����

judge3	ST R0, save_R0		; ����Ĵ���
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; �ж�/
	AND R1, R1, #0
	ADD R1, R1, #3		; R1=3��ѭ��������
	LEA R3, mat0x		; R3���е�ַ

j3_l1	AND R2, R2, #0
	ADD R2, R2, #3		; R2=3��ѭ��������

j3_l2	ADD R4, R3, #-1		; ��ȡ��ǰ�е�ַ(ƫ��-1��0��ʼ)
	ADD R4, R4, R2		; R4������ƫ�Ƶ�ַ
	ADD R4, R4, #3
	AND R5, R5, #0		; R5��¼���1������Ŀ

	LDR R0, R4, #0	
	BRz j3_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j3_ad1 
	ADD R5, R5, #1
j3_ad1	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #-1	
	BRz j3_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j3_ad2 
	ADD R5, R5, #1
j3_ad2	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #-2	
	BRz j3_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j3_ad3 
	ADD R5, R5, #1
j3_ad3	ADD R4, R4, #6		; R4ָ����һ��
	LDR R0, R4, #-3	
	BRz j3_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j3_ad4 
	ADD R5, R5, #1
j3_ad4	ADD R6, R5, #-4		; ֻҪ���ߵ�����ض�Ϊ4��1��2
	BRz winc1_pre		; ���p1������Ϊ4��p1Ӯ
	ADD R5, R5, #0
	BRz winc2_pre		; ���p1������Ϊ0��p2Ӯ

j3_l2ed	ADD R2, R2, #-1
	BRp j3_l2		; ��ѭ�����˽���
	
	ADD R3, R3, #6		; R3ָ����һ��
	ADD R1, R1, #-1
	BRp j3_l1		; ��ѭ�����˽���
; �ж�/����
		
	LD R0, save_R0		; �ָ��Ĵ���
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

; judge4 �жϺ������� �� - �����

judge4	ST R0, save_R0		; ����Ĵ���
	ST R1, save_R1
	ST R2, save_R2
	ST R3, save_R3
	ST R4, save_R4
	ST R5, save_R5
	ST R6, save_R6
	ST R7, save_R7

; �ж�-
	AND R1, R1, #0
	ADD R1, R1, #6		; R1=6��ѭ��������
	LEA R3, mat0x		; R3���е�ַ

j4_l1	AND R2, R2, #0
	ADD R2, R2, #3		; R2=3��ѭ��������

j4_l2	ADD R4, R3, #-1		; ��ȡ��ǰ�е�ַ(ƫ��-1��0��ʼ)
	ADD R4, R4, R2		; R4������ƫ�Ƶ�ַ
	AND R5, R5, #0		; R5��¼���1������Ŀ

	LDR R0, R4, #0	
	BRz j4_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j4_ad1 
	ADD R5, R5, #1
j4_ad1	LDR R0, R4, #1	
	BRz j4_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j4_ad2 
	ADD R5, R5, #1
j4_ad2	LDR R0, R4, #2	
	BRz j4_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j4_ad3 
	ADD R5, R5, #1
j4_ad3	LDR R0, R4, #3	
	BRz j4_l2ed		; �������0ֱ��break
	ADD R0, R0, #-1
	BRnp j4_ad4 
	ADD R5, R5, #1
j4_ad4	ADD R6, R5, #-4		; ֻҪ���ߵ�����ض�Ϊ4��1��2
	BRz winc1_pre		; ���p1������Ϊ4��p1Ӯ
	ADD R5, R5, #0
	BRz winc2_pre		; ���p1������Ϊ0��p2Ӯ

j4_l2ed	ADD R2, R2, #-1
	BRp j4_l2		; ��ѭ�����˽���
	
	ADD R3, R3, #6		; R3ָ����һ��
	ADD R1, R1, #-1
	BRp j4_l1		; ��ѭ�����˽���
; �ж�-����
	
	LD R0, save_R0		; �ָ��Ĵ���
	LD R1, save_R1
	LD R2, save_R2
	LD R3, save_R3
	LD R4, save_R4
	LD R5, save_R5
	LD R6, save_R6
	LD R7, save_R7	
	RET

; ----------------------------------------------------

; ��ָ����
ptr0	.FILL #0
ptr1	.FILL #0
ptr2	.FILL #0
ptr3	.FILL #0
ptr4	.FILL #0
ptr5	.FILL #0

; ----------------------------------------------------

main	AND R1, R1, #0		; R1=18 ��������
	ADD R1, R1, #15
	ADD R1, R1, #3
	
	JSR print
	
	LEA R0, mat50		; ��ָ�븳ֵ	
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

in1	LEA R0, p1inp 		; ��ӡ������ʾ
	TRAP x22
	TRAP x20		; ���1����
	TRAP x21		; ����
	ADD R0, R0, #-16
	ADD R0, R0, #-16
	ADD R0, R0, #-16 	; ����-48 asciiת����
	
	ADD R2, R0, #0		
	LD R0, nextLi_		; ����س�
	TRAP x21
	ADD R0, R2, #0
	BRp i1t2		; �ж������Ƿ�>'0'
	LEA R0, error		; ���������ʾ
	TRAP x22
	BRnzp in1

i1t2	ADD R2, R0, #-7 	; R2 = ����-'7'
	BRn i1ed		; �ж������Ƿ�<'7'
	LEA R0, error			
	TRAP x22
	BRnzp in1
	
i1ed	AND R2, R2, #0
	ADD R2, R2, #1		; ���1������1
	LEA R3, ptr0		; R3ȡ��ָ���ַ
	ADD R3, R3, R0		; R3��ָ�밴������ƫ��
	LDR R4, R3, #-1		; ��ȡָ������
	STR R2, R4, #0		; ������д��R3ָ��ĵ�ַ
	ADD R4, R4, #-6		; ָ��--
	STR R4, R3, #-1		; ��ƫ�ƺ��ֵ���ȥ
		
	JSR print
	JSR judge1		; �ж� | ��Ӯ
	JSR judge2		; �ж� \ ��Ӯ
	JSR judge3		; �ж� / ��Ӯ
	JSR judge4		; �ж� - ��Ӯ

in2	LEA R0, p2inp 		; ��ӡ:�����2����
	TRAP x22
	TRAP x20		; ���2����
	TRAP x21
	ADD R0, R0, #-16
	ADD R0, R0, #-16
	ADD R0, R0, #-16 	; ����-48 asciiת����
	
	ADD R2, R0, #0		; ����س�
	LD R0, nextLi_
	TRAP x21
	ADD R0, R2, #0
	BRp i2t2		; �ж������Ƿ�>'0'
	LEA R0, error		; ���������ʾ
	TRAP x22
	BRnzp in2

i2t2	ADD R2, R0, #-7 	; R2=����-'7'
	BRn i2ed		; �ж������Ƿ�<'7'
	LEA R0, error		
	TRAP x22
	BRnzp in2
		
i2ed	AND R2, R2, #0		
	ADD R2,R2,#-1		; ���2������-1
	LEA R3, ptr0		; R3ȡ��ָ���ַ
	ADD R3, R3, R0		; R3��ָ�밴������ƫ��
	LDR R4, R3, #-1		; ��ȡָ������
	STR R2, R4, #0		; ������д��R3ָ��ĵ�ַ
	ADD R4, R4, #-6		; ָ��--
	STR R4, R3, #-1		; ��ƫ�ƺ��ֵ���ȥ
		
	JSR print
	JSR judge1		; �ж� | ��Ӯ
	JSR judge2		; �ж� \ ��Ӯ
	JSR judge3		; �ж� / ��Ӯ
	JSR judge4		; �ж� ����Ӯ
	
	ADD R1, R1, #-1	
	BRp ma_Lp1		; ѭ�����˽���
	
TieGame	LEA R0, Tie		; ƽ��
	TRAP x22
	BRnzp EOM

winc1	LEA R0, p1win		; p1Ӯ��
	TRAP x22
	BRnzp EOM

winc2	LEA R0, p2win		; p2Ӯ��
	TRAP x22
	BRnzp EOM

EOM	AND R0, R0, #0		; main��������

; ----------------------------------------------------

; �ַ����
nextLi_	.FILL 0x0D
; �ַ������
p1inp	.STRINGZ "player 1 choose a cloumn:"
p2inp	.STRINGZ "player 2 choose a cloumn:"
Tie	.STRINGZ "Tie Game\n"
error	.STRINGZ "Invalid move. Try again.\n"
p1win	.STRINGZ "player 1 win\n"
p2win	.STRINGZ "player 2 win\n"

.END
