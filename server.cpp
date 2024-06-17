#include <bits/stdc++.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errproccess.h>
#include <sys/epoll.h>
#include <fcntl.h>



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

    int epfd = epoll_create1(0);
    epoll_event events[maxn], ev;

    epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
    // Err::errCheck(listen(sock, 5) == -1, "listen failed");
    while(1){
        int nfds = epoll_wait(epfd, events, maxn, -1);
        for(size_t i; i < nfds; i++){
            if(events[i].data.fd == sock){
                int client;
                sockaddr_in clientAddr;
                socklen_t socklen = sizeof(clientAddr);
                client = accept(sock, (sockaddr *)&clientAddr, &socklen);
                Err::errCheck(client == -1, "accept failed");

                printf("new client sock:%d,which ip is %s,port is %d\n", client,
                    inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                ev.data.fd = client;
                ev.events = EPOLLIN | EPOLLET;//et use with unblock io

                epoll_ctl(epfd, EPOLL_CTL_ADD, client, &ev);

            }
            else if(events[i].events & EPOLLIN){
                int client = events[i].data.fd;
                char data[maxn] = { 0 };
                fcntl(client, F_SETFL, fcntl(client, F_GETFL) | O_NONBLOCK);
                while(1){
                    memset(data, 0, sizeof(data));
                    int readSize = read(client, data, sizeof(data));

                    //unblock io will return < 0 and 
                    //errno == EAGAIN or EWOULDBLOCK while io finish.
                    if(readSize > 0){
                        printf("message from client %d:%s\n", client, data);
                    }
                    else if(readSize == -1 && errno == EINTR){
                        printf("continue reading\n");
                        continue;
                    }
                    else if(readSize == -1 && (errno == EAGAIN) || (errno == EWOULDBLOCK)){
                        printf("client %d read over.\n", client);
                        break;
                    }
                    else if(readSize == 0){
                        printf("%d disconnect\n", client);
                        close(client);
                        break;
                    }
                }
            }
            else{

            }
        }
    }
    close(sock);
    return 0;
}