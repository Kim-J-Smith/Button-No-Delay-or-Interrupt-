# include <STC89C5xRC.H>
# include "Key.h"

unsigned char Key_Trg;
unsigned char Key_Cont;
unsigned char xdata Key_StableValue = 0x00;
unsigned char Key_JudgeCount;
unsigned char xdata Key_OnceFlag_1;
unsigned char xdata Key_OnceFlag_2;

void Key_Read(void)
{
	unsigned char ReadData;
	ReadData = ~Key_Pin_Group;
	Key_Trg = ReadData & (ReadData^Key_Cont);
	Key_Cont = ReadData;
}

void Key_Judge(void)
{
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
}


