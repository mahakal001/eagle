#include "main_hdr.h"

void 
google_search(int sfd,char *arg,irc_t* pIrc)
{
   char 	search_str[512];
   char 	url[512] ;
   FILE* 	tmpFile ;
   FILE* 	link ;
   char* 	buf = (char *)malloc(sizeof(char)*1024);
   size_t 	nread = 0 ;
   int  	index=0 ;
   int 		arg_len = strlen(arg) ;

   if ( NULL == strcpy(search_str,arg) ) 
   	  xexit("error during copying of url in buffer for editing purpose \n");

   for(index = 0 ; index < arg_len ; index++)  // Adding '+' sighn replacing the ' ' of oriiginal received request string
   {
   	  if( search_str[index] == ' ') 
   	  	 search_str[index] = '+';
	  else if(search_str[index] == '\0') // arg has its end bytes \0 
	  	 break;
   }//for

  // search_str[index] = '\0'; //terminate the string with null
   
   printf("prepared search string : %s\n",search_str);

  //url_len = 1+strlen("http://www.google.co.in/search?q=&ie=UTF-8")+strlen(search_str);
   //snprintf(url,url_len,"http://www.google.co.in/search?q=%s&ie=UTF-8",search_str);
   sprintf(url,"http://www.google.co.in/search?q=%s&ie=UTF-8",search_str);
   printf("url:%s\n",url);

   /* prepare curl for automatic google search */
   curl_global_init( CURL_GLOBAL_ALL );
   CURL* myHandle;
   tmpFile = fopen("/tmp/tempfile","w+");   				 // open new file for read/write
   myHandle = curl_easy_init ( ) ;

   curl_easy_setopt(myHandle, CURLOPT_URL,url); 		  // initializing string to search
   curl_easy_setopt(myHandle,CURLOPT_WRITEDATA,tmpFile); // write received data to tmpFIle
   curl_easy_perform( myHandle );  // make search

   system("url_parser.sh /tmp/tempfile");   /* data in tempFile is parsed for url ,
   											   the new data is transfer to new file 'links' */
   
    link = fopen("/tmp/links","r");  	  // now open the file for read only

	// Now , read from file to buf
   nread = fread(buf,sizeof(char),1024,link);
   
   for(index = 0 ; index < nread ;index++)
   {
   	  if( buf[index] != '\n')
		 continue;
	  else
		 buf[index] = ' ' ; 
   } //for

   buf[index] = '\0'; 					// terminate with null byte

   fprintf(stdout,"\n===== %s ====\n",buf);

   frame_and_send(sfd,buf,pIrc); 		// Frame and send the string

   free(buf);  // free buf
   curl_easy_cleanup( myHandle ); 		// clean the handle 
   fclose(link); 						// close the link_file
   fclose(tmpFile);        				// close the tmpFile

   return;

} // google_search
