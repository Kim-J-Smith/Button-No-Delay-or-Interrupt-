# include <STC89C5xRC.H>
# include "TaskSlice.h"
# include "UART.H"
# include "Key.H"
# include "INTRINS.H"

TASK TASK_Queue[TASK_MAX_NUM];
void Task_1_Func(void);
void Task_2_Func(void);
void Task_3_Func(void);
void Task_4_Func(void);
void Key_P2_Task(void);
void Key_P1_Task(void);

int main(void)
{
	UART_Init();
	TASK_Queue[0].TASK_EnableFlag = 1;
	TASK_Queue[0].TASK_RunTime = 10;
	TASK_Queue[0].TASK_Func = Task_1_Func;
	TASK_Queue[1].TASK_EnableFlag = 1;
	TASK_Queue[1].TASK_RunTime = 10;
	TASK_Queue[1].TASK_Func = Task_2_Func;
	TASK_Queue[2].TASK_EnableFlag = 0;
	TASK_Queue[2].TASK_RunTime = 10;
	TASK_Queue[2].TASK_Func = Task_3_Func;
	TASK_Queue[3].TASK_EnableFlag = 1;
	TASK_Queue[3].TASK_RunTime = 10;
	TASK_Queue[3].TASK_Func = Task_4_Func;
	
	TASK_Clock_Init();
	while(1)
	{
		TASK_RunCircle();
	}
}

void Task_1_Func(void)
{
	Key_Read_Judge();
}
void Task_2_Func(void)
{
	Key_DoTask(KEY_P2, Key_P2_Task);
	Key_DoTask(KEY_P1, Key_P1_Task);
	TASK_PASS_();
}
void Task_3_Func(void)
{
	UART_SendByte(0x66);
}
void Task_4_Func(void)
{
	UART_SendByte(Key_GetValue());
}


void Key_P2_Task(void)
{
	TASK_Queue[2].TASK_EnableFlag = !TASK_Queue[2].TASK_EnableFlag;
	_nop_();
	
}
void Key_P1_Task(void)
{
	TASK_Queue[3].TASK_EnableFlag = !TASK_Queue[3].TASK_EnableFlag;
}


