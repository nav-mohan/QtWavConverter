#if !defined(WORKER_H)
#define WORKER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QBuffer>
#include "constants.h"

#include <QDebug>

class Worker : public QObject 
{
    Q_OBJECT

    public:
        Worker(QString input_file_name);
        ~Worker();

    public slots:
        void process();

    signals:
        void finished(QString input_file_name);
        void errored(QString err);

    private:
        QString m_inPath;
        QString m_outPath;
        FILE* m_inStream;
        FILE* m_outStream;
        short m_inBuffer[INBUFSIZE_MONO];
        unsigned char m_outBuffer[OUTBUFSIZE_MONO];
        int m_inBytes;
        int m_outBytes;
};

#endif // WORKER_H
