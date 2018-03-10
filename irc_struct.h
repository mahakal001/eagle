/*here we have irc structure related to all in and out with irc */


typedef struct 
{
   char* server ;
   char* port  ;   
   char* channel ;
   char* nick ;
   char* user ;
   char* nick_ident_pass ;

   unsigned int chanNameLen ;
   unsigned int nickNameLen ;
   unsigned int userStrLen  ;

   char command[32];
   char send_msg_buf[512]  ; //buffer to hold  message to send
   char recv_msg_buf[512]  ; // buffer to hold received message

} irc_t ;




