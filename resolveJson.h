#ifndef __RESOLVEJSON_H
#define __RESOLVEJSON_H

#include"wgetDownload.h"
struct recv{
    //code:2112 2100
    char *filePath;
    char *fileType;
    //code:2100
    char *newVersion;
    char *hash ;
    //code:2113
    char *type;
    char *code;
};

int resolve_json(char* json);
char *get_json_stringValue(char *string_from_server, char *keyA, char *keyB);
int bytes_to_int(unsigned char* bytes);
char* unpack_json_packet(unsigned char* item);
void download_file(void* arg);
void clear_struct(struct recv re);
#endif
