/*****************************************************************************
Copyright:     2015-2016, FireWork.
File name:     makeJson.h
Description:   makeJson.c��ͷ�ļ�
Author:        YuZhou Guo,ShaoYang Yu
Version:       v3.0
Date:          2016-05-11
History:       2016-04-26 v1.0ʵ��make_json_raw����
               2016-05-8  v2.0�������ԣ�����JSON���ݰ������ֶ�Ϊbyte����
               2016-05-11 v3.0�ع��ļ������ĺ��������resolveJson.c������
*****************************************************************************/
#ifndef __MAKEJSON_H
#define __MAKEJSON_H

/*C���Ե����������⣬���ڴ���JSON���ݸ�ʽ*/
#include "cJSON.h"

char *create_json_packet(char *code, char *msg, char *serial, cJSON *data);
cJSON *generate_data(char *keyA, char *valueA, char *keyB, char *valueB);

unsigned char *pack_json_packet(char *item);
void int_to_byte(int i,  unsigned char *bytes);
void set_json_body(unsigned char *msg, char *item, int len);

#endif
