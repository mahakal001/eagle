main: irc_struct.h main_hdr.h host_resolver.c  handle_shell.c playgame.c main.c time.c send_msg.c init_msg.c init_irc_struct.c resolve_server.c google_search.c ping.c msg_recv.c search_token.c 
	gcc -Wall -g -o main main.c host_resolver.c playgame.c time.c handle_shell.c init_irc_struct.c send_msg.c init_msg.c resolve_server.c google_search.c ping.c msg_recv.c search_token.c -lcurl -lsqlite3

