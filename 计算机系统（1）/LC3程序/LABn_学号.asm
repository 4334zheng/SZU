.ORIG X3000                   
AND R0,R0,#0    ;�����Ƚ���ѧ���ɼ�����
ADD R0,R0,#15
ADD R0,R0,#1
AND R1,R1,#0
ADD R1,R1,#15
;;ADD R1,R1,#1            ;����ѭ��
          
	LD R2,A         ;;R23Ϊ����ָ��
	LD R3,A

THIRD	LDR R4,R2,#0    ;Ȼ��R4����ɼ�
         	
FIRST		ADD R3,R3,#1		;;��һ��ѭ��
		LDR R5,R3,#0 	;;r5Ϊ��һλ�ɼ�
		NOT R5,R5       ;;r5ȡ��   
		ADD R5,R5,#1	
		ADD R6,R4,R5	;;r6=r4+r5
		BRn CHANGE	;;���r4<r5 jmp

CONTINUE	ADD R1,R1,#-1   ;;ѭ������1
		BRZ SECOND	;;��һ��ѭ��������־
		BRnzp FIRST	;;��������ת
			
SECOND		;;�ڶ���ѭ��
		ADD R2,R2,#1
		ADD R3,R2,#0     ;;R3 R1 ��Ҫ��ԭ ���еڶ���ѭ��
		ADD R0,R0,#-1
		ADD R1,R0,#-1
		BRZ NEXT	;;�ڶ���ѭ��������־
		BRnzp THIRD

CHANGE				;;��r4����r5
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
	ADD R0,R0,#1		;;��x3200��С����װ��x4000
LOADING
	LDR R3,R2,#0
	STR R3,R4,#0
	ADD R4,R4,#1
	ADD R2,R2,#1
	ADD R0,R0,#-1
	BRZ NEXT1
	BRNZP LOADING	
NEXT1	
	AND R7,R7,#0			;;�ж�ABC  A��320C֮���� ��Ϊ֮ǰ�Ѿ���С�����ź����� R7����B��ѧ��
	AND R0,R0,#0
	ADD R0,R0,#5	
	LD R2,A
	LD R3,D				;;R3 85
	NOT R3,R3
	ADD R3,R3,#1
NEXT2
	LDR R4,R2,#0
	ADD R2,R2,#1			;;�ж��ĸ�ѧ���ͺ���
	ADD R0,R0,#-1
	BRZ NEXT3			;;���ĸ�ѧ�����Ѿ��ж���ɿ�ʼ�ж�Bѧ��
	ADD R5,R4,R3			;;����0����
	BRZP ALEVEL
	BRNZP NEXT2
ALEVEL
	ADD R7,R7,#1
	STI R7,C
	BRNZP NEXT2

NEXT3	
	AND R6,R6,#0			;�ж�B�ĸ�������x3200��ʼ�ж�8����
	AND R0,R0,#0
	ADD R0,R0,#9			;�ж�8��ѧ��
	LD R2,A
	LD R3,E				;;R3 75
	NOT R3,R3
	ADD R3,R3,#1
NEXT4
	LDR R4,R2,#0
	ADD R2,R2,#1
	ADD R0,R0,#-1
	BRZ THEEND			;
	ADD R5,R4,R3		;;����0����
	BRZP BLEVEL
	BRNZP NEXT4
BLEVEL
	ADD R6,R6,#1		;�õ�ǰ8��ѧ���гɼ�����75��ѧ��
	NOT R1,R7
	ADD R1,R1,#1
	ADD R1,R6,R1		;��ȥԭ�����жϵ�A�ȼ���ѧ�����õ�B�ȼ���ѧ��
	STI R1,F
	BRNZP NEXT4
	
THEEND	TRAP X25


A .FILL X3200           ;;����ɼ���ʼ���ڴ��ַ x3200
B .FILL X4000           ;;x4000��ʼ����ɼ� x4000��ͳɼ� ��������
C .FILL X4100
D .FILL #85
E .FILL #75
F .FILL X4101
.END