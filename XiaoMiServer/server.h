#ifndef __SERVER_H
#define __SERVER_H
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <string.h>

#include "../config.h"

#define READ_BUFF_SIZE 4096
class VictimServer{
public:
	    VictimServer(int port);		
		void beginToListen();
		void getRemoteFile(int client_fd);
private:
		char readBuf[READ_BUFF_SIZE];
		struct sockaddr_in s_sa;
		struct sockaddr_in c_sa;
		int m_port;
		int command;
		int m_s_sock;
		int m_c_sock;

		void readCommand();
};

#endif
