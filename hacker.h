#ifndef HACKER_H
#define HACKER_H

#include <QObject>

#include "config.h"

class QTcpSocket;
class FileSender;

#define COMMAND_LEN 4

class Hacker : public QObject
{
    Q_OBJECT
public:
    explicit Hacker(QObject *parent = 0);
    void sendFile(const QString& filePath);

signals:

public slots:

private:
    QString m_server_ip;
    quint16 m_port;

    QTcpSocket *m_socket;
    FileSender *m_file_sender;

    char command[COMMAND_LEN];

    void writeCommand(HackerCommand cmd);
};

#endif // HACKER_H
