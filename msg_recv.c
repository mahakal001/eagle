#include "main_hdr.h"

void sock_recv(int sfd,irc_t* pIrc)
{
   size_t readCount = 0;
   while(1)
   {
		 if ( (readCount = recv(sfd, pIrc->recv_msg_buf, 510, 0))  > 0  )
		 {
			   //printf("bytes Read: %d\n",readCount);
			   pIrc->recv_msg_buf[readCount - 2] = '\0';
			   //printf("############### read buffer START ##################\n");
			   printf(ANSI_COLOR_YELLOW);
			   printf("\n[%s]\n",pIrc->recv_msg_buf);
			   printf(ANSI_COLOR_RESET);
			   //printf("############## read buffer ENDED ###############\n");

			    search_token(sfd,pIrc->recv_msg_buf,pIrc);
		  } //if
		 else
		 	xexit("Error While Receiving Message From Buffer\n");
   } // while

   return;

} //sock_recv


