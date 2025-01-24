# include <STC89C5xRC.H>
# include "TaskSlice.h"

unsigned char TASK_Queue_Now = 0;
unsigned char TASK_Wait_Time = 0xFE;
unsigned char TASK_Timer_Count = 0;

/**
  *  @brief  进入任务循环
  *  @param  无
  *  @retval 无
  */
void TASK_RunCircle(void)
{
	unsigned char i;
	TASK_PASS:
	for(i = 0; i < TASK_MAX_NUM; i++)
	{
		if(TASK_Queue_Now == i){
			if(TASK_Queue[i].TASK_EnableFlag == 1)
			{
				TASK_Wait_Time = TASK_Queue[i].TASK_RunTime;
				TASK_Queue[i].TASK_Func();
			}
			else
			{
				TASK_Queue_Now ++;					// core step
				if(TASK_Queue_Now >= TASK_MAX_NUM){
					TASK_Queue_Now = 0;
				}
				goto TASK_PASS;
			}
		}
	}
}

/**
  *  @brief  启动定时器2，开启对应中断，1毫秒@11.0592MHz
  *  @param  无
  *  @retval 无
  *  @attention 紧贴着while循环启动，最后启动！
  */
void TASK_Clock_Init(void)		
{
	T2MOD = 0;				
	T2CON = 0;				
	TL2 = 0x66;				
	TH2 = 0xFC;				
	RCAP2L = 0x66;			
	RCAP2H = 0xFC;	
	EA = 1;
	ET2 = 1;
	PT2 = 1;
	TR2 = 1;				
}

void Timer2_Rountine(void)  interrupt 5
{
	TASK_Timer_Count ++;
	if(TASK_Timer_Count > TASK_Wait_Time){
		TASK_Timer_Count = 0;
		TASK_Queue_Now ++;					// core step
		if(TASK_Queue_Now >= TASK_MAX_NUM){
			TASK_Queue_Now = 0;
		}
	}
	TF2 = 0;
}

/*
TASK_Queue[i].TASK_EnableFlag == 1 && 
*/
