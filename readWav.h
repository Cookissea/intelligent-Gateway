/*****************************************************************************
Copyright:     2015-2016, FireWork.
File name:     readWav.h
Description:   readWav.c��ͷ�ļ�
Author:        YuZhou Guo
Version:       v3.0
Date:          2016-05-15
History:       2016-05-06 v1.0ʹ��LINUXϵͳ����ʵ�ֶ��ı�
               2016-05-14 v2.0ʵ������������䶯̬�ڴ棬��СΪ�ļ��ֽ���
               2016-05-15 v3.0���getFileLength(bfile)���޸Ķ����ƶ��ļ��������ַ����ص�bug
*****************************************************************************/
#ifndef READWAV_H_INCLUDED
#define READWAV_H_INCLUDED

char *read_wav(char *bfile);
int get_file_length(char *bfile);

#endif // READWAV_H_INCLUDED
