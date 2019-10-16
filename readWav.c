/*****************************************************************************
Copyright:     2015-2016, FireWork.
File name:     read_wav.c
Description:   ��ȡ��Ƶ�ļ����洢���ַ�����
Author:        YuZhou Guo
Version:       v3.0
Date:          2016-05-15
History:       2016-05-06 v1.0ʹ��LINUXϵͳ����ʵ�ֶ��ı�
               2016-05-14 v2.0ʵ������������䶯̬�ڴ棬��СΪ�ļ��ֽ���
               2016-05-15 v3.0���getFileLength(bfile)���޸Ķ����ƶ��ļ��������ַ����ص�bug
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "readWav.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX 1024

/*************************************************
Function:       char *read_wav(char *bfile)
Description:    ��ȡ��Ƶ�ļ����洢���ַ�ָ����
Calls:          NONE
Called By:      thread.c(
                         void Voice_Thread()
                        )
Table Accessed: NONE
Table Updated:  NONE
Input:          bfile-��Ƶ�ļ�����ָ��
Output:         ��Ƶ�ļ����ݣ�������ַ�����
Return:         ��Output��ͬ
Others:         NONE
*************************************************/
char *read_wav(char *bfile)
{

    int i, p = 0, fd, SIZE;

    if((fd = open(bfile, O_RDONLY)) < 0){
        perror("File open error");
        exit(1);
    }
    SIZE = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    //printf("File size: %d\n", SIZE);

    char *buf = (char *)malloc(MAX + 1); /*��Ŷ�ȡ�Ķ������ļ�����*/
    char *out = (char *)malloc(SIZE);
    /*ѭ����ȡ��Ƶ�ļ���ÿ�ζ�ȡ1024���ֽڣ������Ƶ�outָ����ڴ�ռ䣬ֱ���ļ�ĩβ*/
    while((i = read(fd, buf, MAX)) > 0){
        memcpy(out + p, buf, i);
        p+=i;
    }

    close(fd);

    /*�ͷŶ��ڴ棬��ֹ�ڴ�й©*/
    free(buf);
    buf = NULL;

    return out;
}

/*************************************************
Function:       int get_file_length(char *bfile)
Description:    ��ȡ��Ƶ����ַ����ĳ��ȣ�����������ַ����еĿ��ַ�
Calls:          NONE
Called By:      thread.c(
                         void Voice_Thread()
                        )
Table Accessed: NONE
Table Updated:  NONE
Input:          bfile-��Ƶ�ļ�����ָ��
Output:         ��Ƶ�ļ�����ַ�������
Return:         ��Output��ͬ
Others:         NONE
*************************************************/
int get_file_length(char *bfile)
{

    /*fd���ļ���������SIZE:�ļ��ֽ�����Ҳ������ַ����ĳ���*/
    int fd, SIZE;

    if((fd = open(bfile, O_RDONLY)) < 0){
        perror("File open error");
        exit(1);
    }
    SIZE = lseek(fd, 0, SEEK_END);
    close(fd);

    return SIZE;
}
