#include <sys/msg.h>

#define KEY 1029384756
#define TYPE 4

int main()
{
    struct msgbuf
    {
        long m_type;
        char m_text[6];
    } writer = {TYPE, "Hello"};
    
    int msg_id = msgget(KEY, 0666 | IPC_CREAT);

    msgsnd(msg_id, &writer, sizeof(writer.m_text), 0);
    msgsnd(msg_id, &writer, sizeof(writer.m_text), 0);
    msgsnd(msg_id, &writer, sizeof(writer.m_text), 0);
    msgsnd(msg_id, &writer, sizeof(writer.m_text), 0);

    return 0;
}