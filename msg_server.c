/************
 * server
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
    struct mymesg mesg = {0, 0 , ""};
    mesg.type = 15;
    if( (msgid =  msgget(ftok("./", 0), IPC_CREAT | 0644)) == -1)
    {
        perror("msgget");
        return 0;
    }
    printf("msgid=%d\n", msgid);
    while(1)
    {
        n = msgrcv(msgid, &(mesg.type), sizeof(mesg)-2*sizeof(long), mesg.type, 0);
    
        printf("recv client n=%d, type=%ld, buf=%s\n", n, mesg.type, mesg.buf);

    }
}
