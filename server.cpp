#include <bits/stdc++.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errproccess.h>


const int maxn = 10000;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    Err::errCheck(sock == -1, "create sock failed");
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8899);

    Err::errCheck(bind(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == -1, "bind failed");

    Err::errCheck(listen(sock, 5) == -1, "listen failed");
    while(1){
        int client;
        sockaddr_in clientAddr;
        socklen_t socklen = sizeof(clientAddr);
        client = accept(sock, (sockaddr *)&clientAddr, &socklen);

        Err::errCheck(client == -1, "accept failed");

        printf("new client sock:%d,which ip is %s,port is %d\n", client,
            inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        char data[maxn] = { 0 };
        // int ret = recv(client, data, 255, 0);
        int readSize = read(client, data, sizeof(data));
        Err::errCheck(readSize == -1, "read failed");
        printf("message from client:%s\n", data);
    }
    close(sock);
    return 0;
}