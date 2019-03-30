#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/msg.h>

struct mess
{
    long int type;
    char buff[32];
};

int main()
{
   int msgid = msgget((key_t)1234,IPC_CREAT|0600);
   assert(msgid != -1);

   struct mess dt;
   dt.type = 2;
   strcpy(dt.buff,"hello");

   msgsnd(msgid,(void*)&dt,32,0);

   exit(0);

}
