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
  printf("receiver\n");
  key_t key;
  int msgid;
  key = ftok("progfile", 65);
  printf("unique key created using ftok:%d\n", key);
  msgid = msgget(key, 0666 | IPC_CREAT);
  printf("message queue id:%d\n", msgid);
  msg.msg_type = 1;
  msgrcv(msgid, &msg, sizeof(msg.msg_txt), 1, 0);
  printf("message recieved:%s\n", msg.msg_txt);
  printf("message type:%lld\n", msg.msg_type);
  printf("size of message:%ld\n", strlen(msg.msg_txt) - 1);
  int s = msgctl(msgid, IPC_RMID, NULL);
  printf("removed message queue with id:%d\n[INFO] status:%d\n", msgid, s);
  return 0;
}
