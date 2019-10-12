/**
  * This a dummy server to feed data like a real Dirt Rally game,
  * so that i do not have to start a real Dirt game which is time consuming
  */
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
//input port as the second arg
{
  int i, sock, conn;
  short port;
  float telemetry[64]; //4*64=256
  int broadcastPermission = 1;
  //load port
  //sgetchar();
  sscanf(argv[1], "%d", &port);
  printf("port==%d\n", port);
  //initialize Diry Dally fake telemetries
  telemetry[33]=10.f;  // gear was set to Reverse
  telemetry[7]=20.f;   // volacity 20 mps should be 72kph
  telemetry[63]=100.f; // max RPM is 1000
  telemetry[37]=70.f;  // current rpm is 700, yield a 70% engine

  struct sockaddr_in saddr, baddr;

  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
            sizeof(broadcastPermission));

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  saddr.sin_port = htons(port);

  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  //bind(sock, &saddr, sizeof(saddr));

  printf("listening\n");
  while(1)
  {
    printf("sended\n");
    sendto(sock, telemetry, 256, 0, &saddr, sizeof(saddr));
    sleep(1);
  }

  return 0;
}
