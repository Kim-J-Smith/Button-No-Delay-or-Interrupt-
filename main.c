# include <STC89C5xRC.H>
# include "TaskSlice.h"
# include "UART.H"
# include "Key.H"

TASK TASK_Queue[TASK_MAX_NUM];
void Task_1_Func(void);
void Task_2_Func(void);
void Task_3_Func(void);

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
	TASK_Clock_Init();
	while(1)
	{
		TASK_RunCircle();
	}
}

void Task_1_Func(void)
{
	if(Key_StableValue != 0 && Key_OnceFlag == 0)
	{
		TASK_Queue[2].TASK_EnableFlag = !TASK_Queue[2].TASK_EnableFlag;
		Key_OnceFlag = 1;
	}
	else if(Key_StableValue == 0)
	{
		Key_OnceFlag = 0;
	}
}
void Task_2_Func(void)
{
	Key_Read();
	Key_Judge();
}
void Task_3_Func(void)
{
	UART_SendByte(0x66);
}

