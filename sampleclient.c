#include <sys/types.h>          
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/un.h>

/*
 *struct sockaddr_un {
    sa_family_t sun_family;                AF_UNIX 
    char        sun_path[UNIX_PATH_MAX];   pathname 
};
*/


int main( int argc, char** argv){
 
  int sockfd;
  int c = -1;

  sockfd =  socket(AF_LOCAL, SOCK_STREAM, 0);
  if(sockfd == -1){
    perror("error creating socket");
    return -1;
  }
  
  struct sockaddr_un mysockaddr;
  mysockaddr.sun_family = AF_UNIX;
  char path[] = "./sockdescript";
  memcpy( mysockaddr.sun_path,path, 14);
  socklen_t socksize =(socklen_t) sizeof(struct sockaddr_un);

    c = connect(sockfd,&mysockaddr,socksize);
    //read and write stuff here
    void* read_buf[256];
    char* write_string;
    if(argc == 2){
    
     write_string = "quit\0";
    }
    else{
    
     write_string = "Writing from client\n\0";
    }
    ssize_t w =  write(sockfd, write_string, strlen(write_string));
    size_t r =  read(sockfd, read_buf, 21 );
    printf("The server told me:  \n'%s'\n",read_buf);
    close(sockfd);
 return 0;
}
 /* 
  struct sockaddr_un mysockaddr;
  mysockaddr.sun_family = AF_UNIX;
  char path[] = "./sockdescript";
  memset( mysockaddr.sun_path,path, 14);
  socklen_t socksize =(socklen_t) sizeof(struct sockaddr_un);

  int b= bind(sockfd,  &mysockaddr, socksize);

  if(b==-1){
    perror("error binding socket");
    return -1;
  }
  int l = listen(sockfd,10);
  
  if(l==-1){
    perror("error listening to  socket");
    return -1;
  }

  int a = accept(sockfd,&mysockaddr,&socksize);
  if(a==-1){
    perror("error accepting socket");
    return -1;
  }
  //read and write data here...
  unlink(sockfd);
  return 0;
}
*/
