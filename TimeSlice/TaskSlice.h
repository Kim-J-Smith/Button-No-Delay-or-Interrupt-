# ifndef __TASK_SLICE_H__
# define __TASK_SLICE_H__

/*******************************************************************************
  ** @attention  Timer2 has been occupied! 
  ******************************************************************************
  */

/**
  *  @brief  任务结构体
  *  @param  TASK_EnableFlag: enable-->1  disable-->0
  *  @param  TASK_RunTime: How many ms this task need.
  *  @param  TASK_Func: The function this task need to deal.
  */
typedef struct{
	unsigned char TASK_EnableFlag;
	unsigned char TASK_RunTime;
	void (*TASK_Func) (void);
}TASK;

# define TASK_MAX_NUM						6
# define TASK_MIN_TIME						100

extern unsigned char TASK_Queue_Now;
extern unsigned char TASK_Wait_Time;
extern unsigned char TASK_Timer_Count;
extern TASK TASK_Queue[TASK_MAX_NUM];
/* TASK_Queue[] 需要在主函数文件中定义为全局变量 */

extern void TASK_RunCircle(void);
extern void TASK_Clock_Init(void);

# endif /* __TASK_SLICE_H__ */


