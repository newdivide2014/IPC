/************
 * client
 *
 * ***************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymesg {
    long type;
    long len;
    char buf[1024];
};

int main(int argc, char** argv)
{
    int msgid;
    int n;
    struct mymesg mesg;
    mesg.type = 15;
    strcpy(mesg.buf, "ganlezhewanrexiang");
    mesg.len = sizeof(mesg.buf);
    if( (msgid =  msgget(ftok("./", 0), IPC_CREAT)) == -1)
    {
        perror("msgget");
        return 0;
    }
    printf("msgid=%d\n", msgid);
    while(1)
    {
        n = msgsnd(msgid, &(mesg.type), mesg.len, 0);
        printf("send server n=%d, type=%ld, buf=%s\n", n, mesg.type, mesg.buf);
        sleep(30);
    }
}
