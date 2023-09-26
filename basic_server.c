#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <unistd.h>
#include<sys/types.h>
#include <arpa/inet.h>


//MACROS
#define IP_v4 AF_INET
#define PORT 8081
#define BACKLOG 10
#define MAXLINE 4096
#define SA struct sockaddr_in




//Server Process
int main(int argc, char const* argv[]){

    //var decleration
    int sockfd,bindfd,new_socket,read_val;
    SA servaddr;
    uint8_t buff[MAXLINE+1];
    uint8_t recvline[MAXLINE+1];

    //socket creation
    if((sockfd = socket(IP_v4,SOCK_STREAM,0)) == -1)
        perror("[-] Socket not made");
        exit(1); //File descriptor of socket
    
    //Create IPv4 Address structure
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    //bind()

    bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));  //Learn how bind takes in the fd for socket, then its other parameters.
    if(bindfd==-1)
        perror("[-] Bind Failed");
        exit(1);
    
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR, &servaddr,sizeof(servaddr))==-1)
        perror("[-] Set Socket failed");
        exit(1);

    //listen()
    if(listen(sockfd, BACKLOG)== -1)
        perror("[-] Sockaddr Error");
        exit(1);
    //when all networks are connected create read - request then write-repsonse

    printf("[+] Server is listening to port 8081\n");

    
    while(1){
        int sin_size = sizeof(SA);
        if((new_socket=accept(sockfd,(struct sockaddr *)&servaddr, &sin_size))==-1){
        perror("[+] Connection Accepted:: Relay message");
        continue;
        }
        printf("[+] Server connected from: %s\n", inet_ntoa(servaddr.sin_addr));

        //read - the request


        //write - to response
        
        close(new_socket);

    }




    close(sockfd);
    return 0;
}


//close
