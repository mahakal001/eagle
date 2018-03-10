#include "main_hdr.h"

/************************************************************************************/
struct addrinfo* build_hint_addr(void)
{ 
   struct addrinfo* hints;
   hints = malloc(sizeof(struct addrinfo));

   memset(hints,0,sizeof(struct addrinfo));
   hints->ai_family   = AF_UNSPEC ;   //allow ipv4 or ipv6   
   hints->ai_socktype = SOCK_STREAM ; //stream socket only
   hints->ai_flags    = AI_CANONNAME;     //all type of addresses
   hints->ai_protocol =  0 ;

   return hints;
}

/**************************************************************************************/
void xexit(char* msg)
{
   fprintf(stderr,"%s\n",msg);
   exit(EXIT_FAILURE);
}//xexit

/**************************************************************************************/
struct addrinfo* x_getaddrinfo(char* arg1,char* arg2,struct addrinfo* hint)
{
   int s=0;
   struct addrinfo* res = (struct addrinfo*) malloc(sizeof(struct addrinfo)) ;

   if ((s = getaddrinfo(arg1,arg2,hint,&res)) != 0){
	  fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(s));
	  exit(EXIT_FAILURE);
   } //if

   free(hint); // hint to free here
   return res;
}//x_getaddrinfo
/**************************************************************************************/
int x_connect(struct addrinfo* result)
{
   int sfd,count=0;
   struct addrinfo* rp;
   char buff[512];
   void* addr;

   	for(count=1,rp=result ; rp != NULL ; rp = rp->ai_next,count++) 
   	{
      if (rp->ai_family == AF_INET) {  // IPv4
          struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
          addr = &(ipv4->sin_addr);
        }//if
      else { // IPv6
          struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
          addr = &(ipv6->sin6_addr);
       }//else

      inet_ntop(rp->ai_family,addr,buff, 512); //network to presentation form
	  printf("%d) IP : [%s] \n",count,buff);        //print ip of given domain

	  if( (sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol )) == -1)
		 continue;

	  if(connect(sfd,rp->ai_addr,rp->ai_addrlen) != -1) { 
//		 fprintf(stdout,"connected...");
		 break;
	  }//if
 }
return sfd;
}

/**************************************************************************************/

