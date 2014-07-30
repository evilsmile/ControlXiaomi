#include "filesender.h"

#include <QFile>
#include <QMessageBox>
#include <QDebug>

FileSender::FileSender(QTcpSocket *sock, QObject *parent) :
    QObject(parent), m_socket(sock)
{
}

void FileSender::sendFile(const QString &filePath)
{
    QStringList splits = filePath.split("/");
    QString baseName(splits[splits.length() - 1]);

    char *p_src = baseName.toLatin1().data();
    strncpy(file_name, p_src, strlen(p_src));

    m_socket->write(file_name, FILE_NAME_MAX);

    QFile sourceFile(filePath);
    if(!sourceFile.open(QIODevice::ReadOnly)){
        QMessageBox::critical(NULL, "Send file", "file open failed", QMessageBox::Yes, QMessageBox::No);
        return ;
    }

    char readBuf[READ_BUFFER_SIZE];
    int numRead = 0;
    int numSend = 0;
    while((numRead = sourceFile.read(readBuf, READ_BUFFER_SIZE)) > 0){
        numSend = m_socket->write(readBuf, numRead);
        if(numSend < 0){
            qDebug() << "write error";
        }
    }

}
