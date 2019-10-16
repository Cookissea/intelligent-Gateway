#ifndef __SYSINIT_H
#define __SYSINIT_H

/*****************************************************************************
Copyright:     2016-2017, Firework.
File name:     sysinit.h
Description:   ���ļ���Ҫ��ɼ�ͥ����ϵͳ������ʼ������ز�����ʹ������ݮ����
               ��wiringPi����ΪGPIO���ƿ�
Author:        YU SHAO YANG
Version:       1.0
Date:          2016.04.02
History:       NONE
*****************************************************************************/

/*�ĸ������˿ں�Ϊ0��1��2��3��wPi����£�*/
/*�ֱ��D:\Technology Innovation\enterpreneur project\Intelligent network pro\gateway\sysinit.hӦGPIO17��18��27��22��BCM����£�*/
#define Key1 0
#define Key2 1
#define Key3 2
#define Key4 3

extern void key_interrupt_1(void);
extern void key_interrupt_2(void);
extern void key_interrupt_3(void);
extern void key_interrupt_4(void);

void gateway_init(void);
void delay_us(unsigned int useconds);
void delay_ms(unsigned int mseconds);
void delay_s(unsigned int seconds);

#endif
