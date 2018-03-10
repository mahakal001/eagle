#include "main_hdr.h"

#define TOTAL_QUESTIONS 19

int callback(void *data, int argc, char **argv, char **azColName)
{
   fprintf(stderr, "%s: ", (const char*)data);
  
   strcpy((char*)data,argv[0]);

   printf("\n");
   
   return 0;
}

 void playgame(int sfd,irc_t* pIrc)
{

   sqlite3 *db;
   int rc;
   char* question = malloc(512) ;
   char* answer  = malloc(128) ;
   int randomNo = 0;
   /***********  Open database *************/
   rc = sqlite3_open("progQuestions.sqlite", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return ;
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }


	int Break = 0 ;
   
while ( !Break )
{
	 randomNo = get_random ( TOTAL_QUESTIONS );
	 
	 get_question( randomNo,(void*)question,db);
	 
	 get_answer( randomNo,(void*)answer,db);
	 
	 frame_and_send(sfd,question,pIrc);

     Break = handle_answer(sfd,answer,pIrc);
}//while

   sqlite3_close(db);
   free(answer);
   free(question);

   return ;
}

int get_random(int maxLimit)
{

	srand(time(NULL));   // should only be called once
	return (rand() % maxLimit);      // returns a pseudo-random integer between 0 and maxLimit
} //get_random

void get_question(int randomNo,void* question,sqlite3 *db)
{
   printf("In get question \n");

   char sql[256];
   int rc ;
   char *zErrMsg = 0;

   /*********** Get question ******************/
   sprintf(sql,"SELECT que from play_linux where SNo=%d",randomNo);   
   
   rc = sqlite3_exec(db, sql, callback,(void*)question, &zErrMsg);
   if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
   } else {
	  fprintf(stdout, "Operation done successfully\n");
   }

   return;

}

void get_answer(int randomNo,void* answer,sqlite3 *db)
{
   printf("In get answer\n");
   char sql[256];
   char *zErrMsg = 0;
   int rc ;
   /*********** Get question ******************/
   sprintf(sql,"SELECT ans from play_linux where SNo=%d",randomNo);

   
   rc = sqlite3_exec(db, sql, callback,(void*)answer, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }

   return ;
}

int handle_answer(int sfd,char* answer,irc_t*  pIrc)
{
   char* p ;
   int remainingAttempt = 5 ;
while( 1 )
{
   ssize_t nread = recv(sfd,pIrc->recv_msg_buf,512,0);

   if( nread <= 0 )	//chk if we are really connected
   	  xexit("some error occured so ,Disconnected");

      pIrc->recv_msg_buf[nread-2] = '\0' ;
	 
   
   if (( p = match_string(pIrc->recv_msg_buf,",w ") ) )
	 {

		if( strncmp(answer,p+3,strlen(answer) ) == 0)
		{
	 	   frame_and_send(sfd,"Ahh ,Was a correct Answer",pIrc);
		   return 0 ;
		}
		else if (remainingAttempt-- != 0) 
		{
		   frame_and_send(sfd,"Incorrect,Try Again",pIrc);
		   continue;
		}
		else 
		   break;
	 }
	 
	 else if( match_string (pIrc->recv_msg_buf,",q") )
		{
		   frame_and_send(sfd,"Quitting Game ,The answer is :",pIrc);
		   frame_and_send(sfd,answer,pIrc);
		   return 1;
		}
   
  	 else if( (p = match_string(pIrc->recv_msg_buf,"PING ")))
	    	pong(p,sfd); 
}//while

frame_and_send(sfd,"You have lost your attempts,The answer to the question is: ",pIrc);
frame_and_send(sfd,answer,pIrc);
frame_and_send(sfd,"Here is your next question",pIrc);

return 0;

}// Handle answer


