/* host resolver.c to resolve host addresss to ip */
#include "main_hdr.h"

void resolve_host(int sfd,char* domain_name,irc_t* pIrc)
{
   struct addrinfo* result = (struct addrinfo*) malloc(sizeof(struct addrinfo)) ;
   struct addrinfo* hint = build_hint_addr() ; //hints are initialized here
   int count = 0;
   struct addrinfo* rp;
   char buff[2048] = {0} ;
   void* addr;
   
   printf("host to resolve: %s \n",domain_name);


   if ( getaddrinfo(domain_name,NULL,hint,&result) != 0)
	{
	 frame_and_send(sfd,"Unknown host: may be you misspelled it",pIrc);
	 free(hint); // hint to free here
  	 free(result) ; // res to free here
   	 return ;
	}//if

  for(count=1,rp=result ; rp != NULL ; rp = rp->ai_next,count++) 
   	{
   	   char tmp_buf[128] = {0} ;

      if (rp->ai_family == AF_INET) {  // IPv4
          struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
          addr = &(ipv4->sin_addr);
        }//if
      else { // IPv6
          struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
          addr = &(ipv6->sin6_addr);
       }//else

      inet_ntop(rp->ai_family,addr,tmp_buf, 128);   //network to presentation form
	  printf("%d) IP : [%s] \n",count,buff);        //print ip of given domain
	  strcat(buff,tmp_buf);
	  strncat(buff,"],[",3);
	}//for
   
   ssize_t  buf_len = strlen(buff) ;
   if( buf_len > 2048 )
	  buff[2048] = '\0' ;
   else
   	  buff[buf_len] = '\0' ;

   frame_and_send(sfd,buff,pIrc);

	 free(hint); // hint to free here
  	 free(result) ; // res to free here
 
 	 return ;
}
	   
