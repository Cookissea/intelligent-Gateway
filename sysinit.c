#include<stdio.h>
#include<wiringPi.h>
#include <unistd.h>
#include"sysinit.h"
#include"interrupt.h"

/*************************************************
Function:       gateway_init
Description:    �ú�������ִ���ĸ������ĳ�ʼ�����ж�
                ���ù�����
Calls:          wiringPi.h(
                            int wiringPiSetup(void);
                            void pinMode(int pin, int mode);
                            void pullUpDnControl(int pin, int pud);
                            int wiringPiISR(int pin, int edgeType,
                                       void(*function)(void));
                          )
Called By:      main.c
Input:          NONE
Output:         void KeyInterrupt1(void);
                void KeyInterrupt2(void);
                void KeyInterrupt3(void);
                void KeyInterrupt4(void);
Return:         NONE
Others:         NONE
*************************************************/
void gateway_init()
{

    /*wiringPi���ʼ����������ҪROOTȨ��ִ��*/
    widshlringPiSetup();

    /*���ĸ�����ģʽ������Ϊ���벶��ģʽ*/
	pinMode(Key1,INPUT);
	pinMode(Key2,INPUT);
	pinMode(Key3,INPUT);
	pinMode(Key4,INPUT);

	/*���ĸ���������Ӧ�Ķ˿�����Ϊ����������ģʽ���ڲ���ѹ������3.3V*/
	pullUpDnControl(Key1, PUD_UP);
	pullUpDnControl(Key2, PUD_UP);
	pullUpDnControl(Key3, PUD_UP);
	pullUpDnControl(Key4, PUD_UP);

	/*�����ĸ�����Ϊ�½��ش����жϣ��������жϷ��������*/
	wiringPiISR(Key1,INT_EDGE_FALLING,&KeyInterrupt1);
	wiringPiISR(Key2,INT_EDGE_FALLING,&KeyInterrupt2);
	wiringPiISR(Key3,INT_EDGE_FALLING,&KeyInterrupt3);
	wiringPiISR(Key4,INT_EDGE_FALLING,&KeyInterrupt4);
}


/*************************************************
Function:       delay_us
Description:    �ú�������΢����ʱ��
Calls:          unistd.h(
                            void usleep(int micro_seconds);
                        )
Called By:      main.c
                interrupt.c
                //
Input:          unsigned int useconds
Output:         NONE
Return:         NONE
Others:         NONE
*************************************************/
void delay_us(unsigned int useconds)
{
    usleep(useconds);
}

/*************************************************
Function:       delay_ms
Description:    �ú������ں�����ʱ��
Calls:          unistd.h(
                            void usleep(int micro_seconds);
                        )
Called By:      main.c
                interrupt.c
                //
Input:          unsigned int mseconds
Output:         NONE
Return:         NONE
Others:         NONE
*************************************************/
void delay_ms(unsigned int mseconds)
{
    sleep(mseconds*1000);
}

/*************************************************
Function:       delay_s
Description:    �ú������ں�����ʱ��
Calls:          unistd.h(
                             unsigned sleep(unsigned int seconds);
                        )
Called By:      main.c
                interrupt.c
                //
Input:          unsigned int seconds
Output:         NONE
Return:         NONE
Others:         NONE
*************************************************/
void delay_s(unsigned int seconds)
{
    sleep(seconds);
}
