#include "main_hdr.h"


char* match_string(char* buff,char* str_to_match)
{
   char *p ;
   p = strstr(buff,str_to_match);
   return p ;
}//match_string

void 
search_token(int sfd,char* buff,irc_t* pIrc)
{
   char *p;

   //first searching for ping message 
   if( (p = match_string(buff,"PING ")) )
      pong(p,sfd);
   else if( (p = match_string(buff,",sh ")) )
		handle_shell(sfd,p+4,pIrc);
   else if( (match_string(buff,",help"))) 
	  send_help_msg(sfd,pIrc);
   else if((p = match_string(buff,",find "))) //find is there
   	  google_search(sfd,p+6,pIrc);
   else if((p = match_string(buff,",wiki "))) //wiki is there
   	  google_search(sfd,p+1,pIrc);
   else if((match_string(buff,",time"))) //tell me time
   	  ret_time(sfd,pIrc);
   else if( (p = match_string(buff,",resolve "))) //resolve host for me
   	  resolve_host(sfd,p+9,pIrc);
   else if((match_string(buff,",playgame") )) //play game
   	  playgame(sfd,pIrc);

  // printf("SEARCH END\n");
   return;

}//search_token
   
void send_help_msg(int sfd,irc_t* pIrc)
{
	  char helpBuf[HELP_MENU_BUF];
	  int hfd = open("helpMenu.txt",O_RDONLY);  //hfd for help file descriptor
	  
	  if ( hfd == -1) 
		 xexit("while opening Help Menu file\n");


	  if ( read(hfd,helpBuf,HELP_MENU_BUF) <= 0)
	  	 xexit("while reading from help menu\n");

	  frame_and_send(sfd,helpBuf,pIrc);

   	  return;
}
