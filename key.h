# ifndef __KEY_H__
# define __KEY_H__

# define Key_Pin_Group					P1

typedef enum{
	KEY_P1 = 0x01,
	KEY_P2 = 0x02,
	KEY_P3 = 0x04,
	KEY_P4 = 0x08,
	KEY_P5 = 0x10,
	KEY_P6 = 0x20,
	KEY_P7 = 0x40,
	KEY_P8 = 0x80,
}KEY_PIN;

# define Key_Sensitivity				30
/* Key_Sensitivity 为稳定阈值(按键灵敏度) */

extern void Key_Read_Judge(void);
extern unsigned char Key_GetValue(void);
extern void Key_DoTask(KEY_PIN KEY_Px, void (*Key_Task) (void));

# endif /* __KEY_H__ */
