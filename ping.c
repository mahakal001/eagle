/* pong reply */
#include "main_hdr.h"

//******************************************************************************************************
void 
pong(char *p,int sfd)
{
   char  pong_buf[256];
   int   index;

   for(index =0;*p !='\0';p++,index++)	// copying received ping message
     pong_buf[index] = *p;
 
   pong_buf[1] = 'O';// replace '1th' char of ping to 'O' of pong
   pong_buf[index] =  '\r';     // 
   pong_buf[index+1] = '\n' ;
   //   printf("pong_buf: %s\n",pong_buf);
 
   send(sfd,pong_buf,index+2,0);   // we are not allowed to send null byte over irc,so msg length is l not l+1

   return;
}//pong
