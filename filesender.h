#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>
#include <qtcpsocket.h>
#include "config.h"

#define READ_BUFFER_SIZE 4096

class FileSender : public QObject
{
    Q_OBJECT
public:
    explicit FileSender(QTcpSocket *sock, QObject *parent = 0);
    void sendFile(const QString& filePath);

private:
    QTcpSocket *m_socket;
    char file_name[FILE_NAME_MAX];

};

#endif // FILESENDER_H
