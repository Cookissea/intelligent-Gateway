#ifndef __INTERRUPT_H
#define __INTERRUPT_H

/*****************************************************************************
Copyright:     2016-2017, Firework.
File name:     interrupt.h
Description:   ���ļ���Ҫ��ɼ�ͥ����ϵͳ���������жϺ���������ز�����
Author:        YU SHAO YANG
Version:       1.0
Date:          2016.04.02
History:       NONE
*****************************************************************************/


/*���ð�������ʱ��Ϊ100����*/
#define DebouncingTime 100

extern void Voice_Thread(void);
extern void create_emergency_LV1(void);
extern void create_emergency_LV2(void);
extern void create_emergency_LV3(void);

void key_interrupt_1(void);
void key_interrupt_2(void);
void key_interrupt_3(void);
void key_interrupt_4(void);

#endif
