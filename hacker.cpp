#include <QTcpSocket>
#include <filesender.h>
#include <QMessageBox>

#include "hacker.h"

Hacker::Hacker(QObject *parent) :
    QObject(parent),
    m_socket(NULL),
    m_file_sender(NULL),
    m_port(SERVER_PORT),
    m_server_ip(SERVER_NAME)
{
}

void Hacker::sendFile(const QString &filePath)
{
    if(m_socket == NULL){
        m_socket = new QTcpSocket(this);
        m_socket->connectToHost(m_server_ip, m_port);
    }
    if(m_file_sender == NULL){
        m_file_sender = new FileSender(m_socket, this);
    }

    writeCommand(SEND_FILE_CMD);
    //send file
    m_file_sender->sendFile(filePath);
    m_socket->close();
    QMessageBox::information(NULL, "Send file", "file send over", QMessageBox::No | QMessageBox::Yes ,
                             QMessageBox::Yes);
    m_socket = NULL;
}

void Hacker::writeCommand(HackerCommand cmd)
{
    for(int i = 0; i < COMMAND_LEN; i++){
        command[i] = (cmd >> i) & 0xFF;
    }
    //send file name
    m_socket->write(command, COMMAND_LEN);
}
