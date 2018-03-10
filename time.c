#include "main_hdr.h"

void ret_time(int sfd,irc_t* pIrc)
{
   time_t second_since_epoch  = time(NULL) ;
   char time_buf[256];
   char* str = ctime(&second_since_epoch);
   sprintf(time_buf,"Time: %s",str) ;

   frame_and_send(sfd,time_buf,pIrc) ;

   return ;
}//return
   


