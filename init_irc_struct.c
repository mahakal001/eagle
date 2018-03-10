#include "main_hdr.h"

irc_t* init_irc_struct(void)
{
	irc_t* pIrc ;

	pIrc = (irc_t*) malloc(sizeof(irc_t)) ;

	pIrc -> server =  "chat.freenode.net" ;
	pIrc -> port = "6667" ;
	pIrc -> channel = "#chanName";
	pIrc -> nick = "eagle";
	pIrc -> user = "clzReal shul RyrverFoo wIzFVke" ;
	pIrc -> nick_ident_pass = "yourPass";

	strcpy(pIrc -> command,"PRIVMSG");

	pIrc -> chanNameLen = strlen(pIrc -> channel) ;
	pIrc -> nickNameLen = strlen(pIrc -> nick) ;
	pIrc -> userStrLen = strlen(pIrc -> user);

	
	memset(pIrc -> send_msg_buf,0,512); 
	memset(pIrc -> recv_msg_buf,0,512);

	return pIrc ;
}//init_irc_struct



