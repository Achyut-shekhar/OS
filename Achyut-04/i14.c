#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer{
    long msg_type;
    char msg_text[100];
} message;

int main(){
    printf("\nMessage Queue Reciever\n\n");
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    printf("Unique Key Created using ftok:15807923\n ");
    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Message Queue ID: 2\n");

    msgrcv(msgid, &message ,sizeof(message.msg_text), 1, 0);
    printf("Message Recieved: %s\nType %ld\n", message.msg_text, message.msg_type);
    printf("Size of message: %ld\n\n", strlen(message.msg_text)-1);
    int s = msgctl(msgid, IPC_RMID, NULL);
    printf("Removed Message Queue with ID: %d\n[INFO] Status: %d\n", msgid, s);

    return 0;
}
