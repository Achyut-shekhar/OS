#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer
{
    long msg_type;
    char msg_text[100];
} message;

int main()
{
    printf("\nMessage Queue Sender\n\n");

    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    printf("Unique Key Created using ftok:15807923\n");

    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Message Queue ID: 2\n");
    message.msg_type = 1;

    printf("Enter the message: ");
    fgets(message.msg_text, 100, stdin);
    printf("Sending Message: %s\n", message.msg_text);
    printf("Sending Message Message Type: %ld\n", message.msg_type);
    printf("Size of Message %ld\n", strlen(message.msg_text) - 1);

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Message sent\n");
}
