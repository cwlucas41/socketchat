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
 
  int sockfd =  socket(AF_LOCAL, SOCK_STREAM, 0);
  if(sockfd == -1){
    perror("error creating socket");
    return -1;
  }
  
  struct sockaddr_un mysockaddr;
  mysockaddr.sun_family = AF_UNIX;
  char path[] = "./sockdescript";
  memcpy(mysockaddr.sun_path,path, 14);
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

  int a;
  int connections =0;
 
  void* read_buf[256];
  while(1){
    a = accept(sockfd,&mysockaddr,&socksize);
    if(a==-1){
      perror("error accepting socket");
      return -1;
    }

    char* write_string = malloc(100*sizeof(char));
    sprintf(write_string,
        "Writing from client #%d\n\0",connections);
    connections++;
    size_t r =  read(a, read_buf,  20);
    printf("The client told me:  \n'%s'\n",read_buf);
    if(!strncmp(read_buf,"quit",4)) break;
    ssize_t w =  write(a, write_string, strlen(write_string));
    printf("writing to client:  \n'%s'\n",write_string);
    free(write_string);
    sleep(1);

  }

  unlink(sockfd);
  close(sockfd);
  return 0;
}
