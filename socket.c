/*****************************************************************************
Copyright:     2015-2016, FireWork.
File name:     socket.c
Description:   ���ļ�������JSON���ݰ��������йصĺ��������ڹ��ߺ����ļ�
Author:        ShaoYang Yu
Version:       v3.0
Date:          2016-05-15
History:       2016-04-26 v1.0
               2016-05-8  v2.0
               2016-05-11 v3.0
*****************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<pthread.h>
#include"makeJson.h"
#include"resolveJson.h"
#include"socket.h"

/*����������ַ�����*/
#define MAX 65535

/*������IP��ַ���˿ں�����*/
const char* IP = "121.42.196.94";
const int SERVERPORT = 10101;

unsigned char * raw_send_buffer_tick;   /*ԭ��tick���ݰ�Ԥ���ͻ�����*/
unsigned char * send_buffer_tick;   /*tick���ݰ����ͻ�����*/

unsigned char * raw_send_buffer = NULL;    /*ԭ�������ͻ�����*/
unsigned char raw_recv_buffer[MAX];    /*����Ԥ���ջ�����*/

unsigned char * send_buffer;    /*���ݷ��ͻ�����*/

/*************************************************
Function:       int create_socket()
Description:    ��ʼ��socket�����������������ͨ�����ͻ����JSON���ݰ�
Calls:          socket.c(
                        void send_tick(void*arg)
                        void send_json_packet(void *arg)
                        void recv_json_packet(void *arg)
                        )
Called By:      main.c(
                      int main()
                    )
Table Accessed: NONE
Table Updated:  NONE
Input:          NONE
Output:         �����׽��֣����Ͳ�����JSON���ݰ�
Return:         0
Others:         NONE
*************************************************/
int create_socket()
{
    int ser_socketfd;   /*�����׽��ֱ�Ƿ�*/
    struct sockaddr_in remote_addr;     /*����socket�ṹ��*/
    pthread_t send_socket_tick; /*��������tick�߳�������*/
    pthread_t send_socket;  /*���������߳�������*/
    pthread_t recv_socket;  /*���������߳�������*/

    memset(&remote_addr, 0, sizeof(struct sockaddr_in));    /*��ʼ���ṹ��*/
    remote_addr.sin_family = AF_INET;   /*����ʹ������IPv4Э��*/
    remote_addr.sin_addr.s_addr = inet_addr(IP);    /*����IP��ַ*/
    remote_addr.sin_port = htons(SERVERPORT);   /*���÷������˿�*/

    /*�����׽���*/
    if((ser_socketfd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("socket failed.");
        return 1;
    }

    /*���׽�����ṹ��������ӣ���������˷������������ź�*/
    if((connect(ser_socketfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))) < 0)
    {
        perror("connect failed.");
        return 1;
    }

    /*�����׽���tick���ݷ����߳�*/
    if((pthread_create(&send_socket_tick, NULL, send_tick,(void*)ser_socketfd)) != 0)
    {
        perror("send thread create failed.");
        return 1;
    }

    /*�����׽������ݷ����߳�*/
    if((pthread_create(&send_socket, NULL, send_json_packet,(void*)ser_socketfd)) != 0)
    {
        perror("send thread create failed.");
        return 1;
    }

    /*�����׽������ݽ����߳�*/
    if((pthread_create(&recv_socket, NULL, recv_json_packet,(void*)ser_socketfd)) != 0)
    {
        perror("recv thread create failed.");
        return 1;
    }

    while(1);/*������ѭ������ִ�йر��׽�������*/
    close(ser_socketfd);
    return 0;
}


/*************************************************
Function:       void send_tick(void*arg)
Description:    ����������
Calls:          makeJson.c(
                        char* create_json_packet(char* code, char* msg, char* serial, cJSON *data)
                        unsigned char *pack_json_packet(char *item)
                        )
Called By:      socket.c(
                      int create_socket()
                    )
Table Accessed: NONE
Table Updated:  NONE
Input:          arg-�׽��ֱ�Ƿ�����Ϊ�߳���ں�����������void *���ʹ��Σ�
Output:         ��������������ͨ���׽��ַ���
Return:         void
Others:         NONE
*************************************************/
void send_tick(void*arg)
{
    int fd = (int)arg;
    int len;
    raw_send_buffer_tick = create_json_packet("1100","tick","20160001",NULL);
    len = strlen(raw_send_buffer_tick) + 4;
    send_buffer_tick = pack_json_packet(raw_send_buffer_tick);
    while(1)
    {
        if((send(fd,send_buffer_tick,len,0))<0)
        {
            perror("send failed.");
            return 1;
        }
        sleep(10);
    }
}

/*************************************************
Function:       void send_json_packet(void *arg)
Description:    ��������JSON���ݰ����ֽ׶ΰ����������а����ļ��ϴ���
Calls:          makeJson.c(
                        unsigned char *pack_json_packet(char *item)
                        )
Called By:      socket.c(
                      int create_socket()
                      )
Table Accessed: NONE
Table Updated:  NONE
Input:          arg-�׽��ֱ�Ƿ�����Ϊ�߳���ں�����������void *���ʹ��Σ�
Output:         ��������JSON���ݰ�����ͨ���׽��ַ���
Return:         void
Others:         NONE
*************************************************/
void send_json_packet(void *arg)
{
    int fd = (int)arg;
    int len;
    while(1)
    {
        if(raw_send_buffer!=NULL)
        {
            len = strlen(raw_send_buffer)+4;
            send_buffer = pack_json_packet(raw_send_buffer);
            if((send(fd,send_buffer,len,0))<0)
            {
                perror("send failed.");
                return 1;
            }
            send_buffer=NULL;
            raw_send_buffer=NULL;
        }
    }
}

/*************************************************
Function:       void recv_json_packet(void *arg)
Description:    ���շ��������͵�JSON���ݰ��������ļ�·���������������
Calls:          resolveJson.c(
                        char* unpack_json_packet(unsigned char* item)
                        )
Called By:      socket.c(
                      int create_socket()
                      )
Table Accessed: NONE
Table Updated:  NONE
Input:          arg-�׽��ֱ�Ƿ�����Ϊ�߳���ں�����������void *���ʹ��Σ�
Output:         ���շ��������͵�JSON���ݰ��������ļ�·���������������
Return:         void
Others:         NONE
*************************************************/
void recv_json_packet(void *arg)
{
    int fd = (int)arg;

    int wholelenth; /*��������JSON���ݰ�����*/
    int len;    /*��������JSON���ݰ�����*/

    pthread_t resolve_socket;
    char* recv_buffer;  /*�����ԭ��JSON���ݰ�*/
    char* recv_head;

    /*ѭ�����շ��������͵�����JSON���ݰ�*/
    while(1)
    {
        /*ÿ��������MAX���ֽ����ݣ����ؽ����ֽ���*/
        wholelenth = recv(fd,raw_recv_buffer,MAX,0);
        if(wholelenth<0)
        {
            perror("recv failed.");
            return 1;
        }
        else
        {
            /*���*/
            recv_buffer = unpack_json(raw_recv_buffer);
            len  = strlen(recv_buffer) + 4;

            /*������*/
            if((pthread_create(&resolve_socket, NULL, resolve_json_packet,(void*)recv_buffer))!=0)
            {
                perror("recv thread create failed.");
                return 1;
            }

            /*���һ���Խ��ն�����ݰ������ֱ��û�и���İ��ɲ𣬲��������а�*/
            while(len<wholelenth)
            {
                /*recv_head�����ݰ�ͷָ��*/
                recv_head = &raw_recv_buffer[len];
                recv_buffer = unpack_json_packet(recv_head);
                len += strlen(recv_buffer)+4;
                if((pthread_create(&resolve_socket, NULL, resolve_json_packet,(void*)recv_buffer))!=0)
                {
                    perror("recv thread create failed.");
                    return 1;
                }
            }
        }
    }
}

/*************************************************
Function:       void resolve_json_packet(void* arg)
Description:    ���շ��������͵�JSON���ݰ��������ļ�·���������������
Calls:          resolveJson.c(
                        int resolve_json(char* json);
                        )
Called By:      socket.c(
                      void recv_json_packet(void *arg)
                      )
Table Accessed: NONE
Table Updated:  NONE
Input:          arg-����JSON����Ӧ���ַ�������Ϊ�߳���ں�����������void *���ʹ��Σ�
Output:         ���շ��������͵�JSON���ݰ��������ļ�·���������������
Return:         void
Others:         NONE
*************************************************/
void resolve_json_packet(void* arg)
{
    char* recv_buffer = (char *)arg;
    resolve_json(recv_buffer);
}

