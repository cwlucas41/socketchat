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
   void* server_buf[256];
   char* write_string;
   
   char running = 1;
   while(1){
     size_t userin =  read(STDIN_FILENO, read_buf, 256 );
     if(!strncmp(read_buf,"quit",4)){
       break;
     }
     ssize_t w =  write(sockfd, write_string, userin);
     //size_t r  =  read(sockfd, server_buf, 256 ); //this blocks
     printf("The server told me:  \n'%s'\n",server_buf);
   }
   close(sockfd);
   return 0;
}
