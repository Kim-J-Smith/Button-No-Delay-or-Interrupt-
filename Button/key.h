# ifndef __KEY_H__
# define __KEY_H__

# define Key_Pin_Group					P1
# define Key_Sensitivity				3
/* Key_Sensitivity 为稳定阈值 */

extern unsigned char Key_Trg;
extern unsigned char Key_Cont;
extern unsigned char Key_JudgeCount;
extern unsigned char xdata Key_OnceFlag_1;
extern unsigned char xdata Key_OnceFlag_2;
extern unsigned char xdata Key_StableValue;
/* Key_Judge 会将稳定后的按键值放置于 Key_StableValue 中 */

/*
if((Key_StableValue & 0x02) != 0 && Key_OnceFlag_x == 0)
	{
		//要短按实现的功能
		Key_OnceFlag_x = 1;
	}
	else if((Key_StableValue & 0x02) == 0)
	{
		Key_OnceFlag_x = 0;
	}
*/

extern void Key_Read(void);
extern void Key_Judge(void);

# endif /* __KEY_H__ */
