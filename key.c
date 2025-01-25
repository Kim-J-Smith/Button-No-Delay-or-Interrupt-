# include <STC89C5xRC.H>
# include "Key.h"

unsigned char Key_Trg;
unsigned char Key_Cont;
unsigned char Key_JudgeCount;
unsigned char xdata Key_OnceFlag;
unsigned char xdata Key_StableValue = 0x00;

/**
  *  @brief  Key_Read读取按键信息，Key_Judge过滤抖动，
  *  	最终稳定的按键信息存入Key_StableValue中。
  *  @param  无
  *  @retval 无
  */
void Key_Read_Judge(void)
{
	unsigned char ReadData;
	ReadData = ~Key_Pin_Group;
	Key_Trg = ReadData & (ReadData^Key_Cont);
	Key_Cont = ReadData;
	
	/* 上面一部分是 Key_Read 的部分 */
	
	if(Key_Trg == 0)
	{
		Key_JudgeCount ++;
		if(Key_JudgeCount > Key_Sensitivity)    	// 稳定值达到阈值
		{
			Key_StableValue = Key_Cont;
		}
	}
	else
	{
		Key_JudgeCount = 0;
	}
	/* 上面一部分是 Key_Judge 的部分 */
}


/**
  *  @brief  直接获取稳定后的按键值
  *  @param  无
  *  @retval 稳定后的按键值
  */
unsigned char Key_GetValue(void)
{
	return Key_StableValue;
}	


/**
  *  @brief  执行按键对应的功能
  *  @param  KEY_Px: 一个枚举类型，选择要判断的引脚，KEY_PIN在头文件中定义
  *  @param  Key_Task: 要执行的函数指针（无返回值 无参数）
  *  @retval 无
  */
void Key_DoTask(KEY_PIN KEY_Px, void (*Key_Task) (void))
{
	unsigned char temp = (unsigned char)KEY_Px;
	if((Key_StableValue & temp) != 0 && (Key_OnceFlag & temp) == 0)
	{
		Key_Task();//要短按实现的功能
		Key_OnceFlag |= temp;
	}
	else if((Key_StableValue & temp) == 0)
	{
		Key_OnceFlag &= (~temp);
	}
}



