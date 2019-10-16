#ifndef __THREAD_H
#define __THREAD_H

/*****************************************************************************
Copyright:     2016-2017, Firework.
File name:     thread.h
Description:   ���ļ���Ҫ��ɼ�ͥ����ϵͳ����¼���ϴ��ͽ������й��ܡ�
Author:        YU SHAO YANG
Version:       2.0
Date:          2016.05.15
History:       2016.04.30 �޸ĺ�����TESTΪVoice_Thread,����ͬǰ
               2016.05.15 �޸�Voice_Thread������ʵ�������ϴ�����
                          �޸�Emergency_Thread_Level������ʵ�ֽ������й���
*****************************************************************************/

void create_wav_thread(void);
void create_emergency_LV1(void);
void create_emergency_LV2(void);
void create_emergency_LV3(void);

int set_priority(const int pri);

#endif
