#include "main_hdr.h"

void frame_and_send(int sfd,char *msg,irc_t* pIrc)
{
fprintf(stdout,"In Func : frame_and_send\n");
   unsigned int curIndex = 0;
   unsigned int readByteCount=0 ;

   char tmpBuf[350];

   while(1)
   {
   	  if( msg[curIndex] != '\0'  && msg[curIndex] != '\r')
	  {
	  	 if( msg[curIndex] == '\n' )
		 {
		 if( 0 == readByteCount)  // nothing to send
		 {
		 	curIndex++;
		 	continue;
		 }
		 	tmpBuf[readByteCount]   = '\r';
		 	tmpBuf[readByteCount+1] = '\n';
		 	tmpBuf[readByteCount+2] = '\0';
		 	xsend(sfd,tmpBuf,readByteCount+3,pIrc);
		 	readByteCount = 0 ;
		 	curIndex++ ;
		 	continue ;
		 }

	  	 if (readByteCount != 347 )
		 {
		 	tmpBuf[readByteCount] = msg[curIndex];
		 	curIndex++;
		 	readByteCount++;
		 }//if
		 else
		 {
		 	tmpBuf[readByteCount]   = '\r';
		 	tmpBuf[readByteCount+1] = '\n';
		 	tmpBuf[readByteCount+2] = '\0';
		 	xsend(sfd,tmpBuf,readByteCount+3,pIrc);
		 	readByteCount = 0;
		 }//else
	  }//if
	  else
	  {
		 if( 0 == readByteCount)  // nothing to send
		 	break;
		 	tmpBuf[readByteCount]   = '\r';
		 	tmpBuf[readByteCount+1] = '\n';
		 	tmpBuf[readByteCount+2] = '\0';
		 	xsend(sfd,tmpBuf,readByteCount+3,pIrc);
		 	readByteCount = 0;
		 	break;
	  }//else
   }
   
  printf("Total Bytes send :%d\n",curIndex); 
   
  return ;
}

void xsend(int sfd,char* msg,unsigned int msgLen,irc_t* pIrc)
{
   unsigned int totMsgLen;
   unsigned int totByteLen ;

   memset(pIrc->send_msg_buf,0,512);

   totMsgLen = sprintf(pIrc->send_msg_buf,"%s %s :%s",pIrc->command, pIrc->channel ,msg);


  totByteLen = send(sfd,pIrc->send_msg_buf,totMsgLen,0);
  
  printf("xsend: %s , Bytes send :%d\n",pIrc -> send_msg_buf,totByteLen); 

  sleep(1);
  
  return ;
}//xsend

