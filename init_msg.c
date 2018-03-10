#include "main_hdr.h"

void irc_reg_join(int sfd,irc_t* pIrc)
{
   sleep(2);
   register_wid_nw(sfd,pIrc);   // send NICK and USER command for registration purpose

   sleep(6);

   join_channel(sfd,pIrc);      // send JOIN command
   
   sleep(5);                    // sleeping to wait for server's response

	return;

}//sockRDWR

/**************************************************************************************/

/**************************************************************************************/
void 
register_wid_nw(int sfd,irc_t* pIrc)
{
   sprintf(pIrc ->send_msg_buf,"USER %s\r\n",pIrc ->user);   //build the string
   send(sfd,pIrc->send_msg_buf,strlen(pIrc ->send_msg_buf),0);     // send the cmd to server
   printf("%s\n",pIrc->send_msg_buf);

   sleep(3);
   
   sprintf(pIrc ->send_msg_buf,"NICK %s\r\n",pIrc ->nick);   //build the string
   send(sfd,pIrc->send_msg_buf,strlen(pIrc ->send_msg_buf),0);     // send the cmd to server 
   printf("%s\n",pIrc->send_msg_buf);

return;

}//register_bro


/**************************************************************************************/
 

void 
join_channel(int sfd,irc_t* pIrc)
{
   sprintf(pIrc ->send_msg_buf,"JOIN %s\r\n",pIrc ->channel);   //build the string
   
   send(sfd,pIrc->send_msg_buf,strlen(pIrc->send_msg_buf),0);     // send the cmd to server
   printf("%s\n",pIrc->send_msg_buf);
   

return;

}//join_channel
