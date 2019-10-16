#include "cJSON.h"
#include "resolveJson.h"
#include"wgetDownload.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int resolve_json(char* json){
    struct recv re;
    int num = 0;
    pthread_t download;
    clear_struct(re);

    re.code = get_json_stringValue(json, "code",NULL);
    if(strcmp(re.code,"2101")==0){  //get tick back noOrder
        printf("code:2101 received!\n");
        num = 13;
    }
    else if(strcmp(re.code,"2113")==0){
        re.type = get_json_stringValue(json, "data","type");
        num = 12;
    }
    else if(strcmp(re.code,"2100")==0){
        re.filePath = get_json_stringValue(json, "data","filePath");
        re.newVersion = get_json_stringValue(json, "data","newvision");
        re.hash = get_json_stringValue(json, "data","hash");
        //printf("%s\n",re.filePath);
        num = 11;
    }
    else if(strcmp(re.code,"2112")==0){
        printf("code:2112 received!\n");
        re.filePath = get_json_stringValue(json, "data","filePath");
        re.fileType = get_json_stringValue(json, "data", "fileType");
          if((pthread_create(&download, NULL, download_file, (void*)&re))!=0)
            {
            perror("recv thread create failed.");
            return 1;
            }
        //printf("%s\n",re.filePath);
        num = 10;
    }
    return num;
}

void download_file(void *arg){
    struct recv *re = (struct recv *)arg;
    char* filedir;
    char buffer[30] = {0};
    //printf("good\n");
    printf("filePath:%s\nfileType:%s\n",(*re).filePath,(*re).fileType);
    if(strstr((*re).filePath,".wav")!=NULL)
    {
    //free(filedir);
        filedir = wget_download((*re).filePath, 3, 5, (*re).fileType);
        strcpy(buffer,"omxplayer -o local ");
        strcat(buffer, filedir);
        system(buffer);

        strcpy(buffer, "sudo rm ");
        strcat(buffer, filedir);
        system(buffer);

    }
    printf("wrong filePath.\n");
    return ;
}

void clear_struct(struct recv re){
        re.code = NULL;
        re.filePath = NULL;
        re.fileType = NULL;
        re.hash = NULL;
        re.newVersion = NULL;
        re.type = NULL;
}

//获取JSON数据包中的数据，keyA表示你想要获得的值对应的键
//如果*keyA != "data"，那么将keyB设为NULL；否则，keyB设置为data对象中想要获取的字段
char *get_json_stringValue(char *string_from_server, char *keyA, char *keyB)
{
    cJSON *JsonFromServer = cJSON_Parse(string_from_server);
    cJSON *stringValue = cJSON_GetObjectItem(JsonFromServer, keyA);
    //printf("%s\n", cJSON_Print(stringValue));
    cJSON *dataValue;
    if(strcmp(keyA,"data")!=0){
        //printf("%s\n", cJSON_Print(stringValue));
        //实际上除了cJSON_String也没有其他类型
        if(stringValue->type == cJSON_String){
            //printf("%s\n", stringValue->valuestring);
            return stringValue->valuestring;
            }
    }else{
        dataValue = cJSON_GetObjectItem(stringValue, keyB);
        //printf("%s\n", cJSON_Print(dataValue));
        //printf("%d\n", dataValue->type);
        if(dataValue->type == cJSON_String){
            //printf("%s\n", dataValue->valuestring);
            return dataValue->valuestring;
            }
    }
    return NULL;
}

//对捕获内容进行拆包
char* unpack_json_packet(unsigned char* item)
{
    int i;
    int len;
    char* body;
    len = bytes_to_int(item);
    //printf("%d",len);
    body = (char *)malloc(len-4);//动态分配数组空间
    for(i=0;i<len-4;i++){
        body[i]=item[4+i];
    }
    return body;

}


//Bytes类型向Int类型转换函数
int bytes_to_int(unsigned char* bytes)
{
    int addr = bytes[0] & 0xFF;
    addr |= ((bytes[1] << 8) & 0xFF00);
    addr |= ((bytes[2] << 16) & 0xFF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
 }
