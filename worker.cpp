#include "worker.h"
#include "LameEncoder.h"
#include <QDebug>

Worker::Worker(QString input_file_name){
    qDebug() << "Worker Spawned";
    m_inPath    = input_file_name;
    m_outPath   = input_file_name.replace("wav","mp3");
    m_inStream  = fopen(m_inPath.toLocal8Bit().data(),"rb");
    m_outStream = fopen(m_outPath.toLocal8Bit().data(),"wb");
    m_inBytes = 0;
    m_outBytes = 0;
    qDebug() << m_inPath << " --> " << m_outPath;
}

Worker::~Worker(){
    qDebug() << "Worker Destroyed" << m_inPath;
    fclose(m_inStream);
    fclose(m_outStream);
}

void Worker::process(){
    qDebug() << "processing | " << m_inPath;
    LameEncoder* lame_encoder = new LameEncoder();
    do
    {
        m_inBytes = fread(m_inBuffer,2,INBUFSIZE_MONO,m_inStream);
        m_outBytes = lame_encoder->doEncode(m_inBytes,m_inBuffer,m_outBuffer);
        fwrite(m_outBuffer,1,m_outBytes,m_outStream);
        qDebug() << "Encoded" << m_outBytes;
    } 
    while (m_inBytes > 0);
        
    emit finished(m_inPath);
}