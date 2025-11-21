#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg
{
  long long msg_type;
  char msg_txt[100];
} msg;

int main()
{
  printf("sender\n");
  key_t key;
  int msgid;
  key = ftok("progfile", 65);
  printf("unique key created using ftok:%d\n", key);
  msgid = msgget(key, 0666 | IPC_CREAT);
  printf("message queue id:%d\n", msgid);
  msg.msg_type = 1;
  printf("enter the message:");
  fgets(msg.msg_txt, 100, stdin);
  printf("sending message:%s\n", msg.msg_txt);
  printf("sending message type:%lld\n", msg.msg_type);
  printf("size of message:%ld\n", strlen(msg.msg_txt) - 1);
  msgsnd(msgid, &msg, sizeof(msg.msg_txt), 0);
  printf("message sent\n");
}