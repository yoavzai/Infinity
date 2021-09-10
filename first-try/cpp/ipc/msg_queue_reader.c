#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

#define KEY 1029384756
#define TYPE 4

int main()
{
    struct msgbuf
    {
        long m_type;
        char m_text[6];
    } reader;
    
    int msg_id = msgget(KEY, 0666 | IPC_CREAT);

    msgrcv(msg_id, &reader, sizeof(reader.m_text), TYPE , 0);
    printf("%s\n", reader.m_text);
    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}