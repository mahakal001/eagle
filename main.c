#include "main_hdr.h"

int main (int argc,char* argv[])
{
//   if ( daemon(0,0) < 0 )
  // 	  exit(EXIT_FAILURE) ;

   irc_t* pIrc ;
   struct addrinfo  *result ;    // for holding pointer to addrinfo structure
   int    sfd;                   // will have socket file descriptor

   pIrc = init_irc_struct();


   result = x_getaddrinfo(pIrc->server,pIrc->port,build_hint_addr()); //getting address of entered domain

   sfd = x_connect(result);               //connecting with the domain

   free(result);

   irc_reg_join(sfd,pIrc);           // register and join 
   
   sock_recv(sfd,pIrc);				//  receive ,analyze and response

   exit(EXIT_SUCCESS);

   return 0;
}
