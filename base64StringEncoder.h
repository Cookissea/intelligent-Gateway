/*****************************************************************************
Copyright:     2015-2016, FireWork.
File name:     base64StringEncoder.h
Description:   base64StringEncoder.c��ͷ�ļ�
Author:        YuZhou Guo
Version:       v3.0
Date:          2016-05-15
History:       2016-04-25 v1.0ʵ��base64�����߼�
               2016-05-14 v2.0�޸�ָ��bug��ʵ�ֱ�������
               2016-05-15 v3.0���е�Ԫ���ԣ�ʵ�������ļ��ϴ�
*****************************************************************************/
#ifndef BASE64STRINGENCODER_H_INCLUDED
#define BASE64STRINGENCODER_H_INCLUDED

/*base64�ַ�ӳ�伯���ض�ָ��ƫ�������ض��ַ��γ�һ��ӳ��*/
static const char *codes;

unsigned char* encode_base64(const unsigned char *in,  unsigned long len);

#endif // BASE64STRINGENCODER_H_INCLUDED
