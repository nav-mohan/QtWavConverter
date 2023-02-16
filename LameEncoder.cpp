#include <QDebug>

#include "LameEncoder.h"

LameEncoder::LameEncoder()
{
    qDebug("LameEncoder initialized");
    lgf = lame_init();
    lame_set_mode(lgf,MONO);
    lame_set_in_samplerate(lgf, SAMPLE_RATE_HZ_MONO);
    lame_set_VBR_mean_bitrate_kbps(lgf, 128);
    lame_set_num_channels(lgf, 1);
    lame_init_params(lgf);

}

LameEncoder::~LameEncoder()
{
    qDebug("LameEncoder destroyed");
    lame_close(lgf);
}

int LameEncoder::doEncode(
    int input_bytes, 
    short input_buffer[INBUFSIZE_MONO], 
    unsigned char output_buffer[OUTBUFSIZE_MONO]
    )
{
    qDebug() << "Encoding" << input_bytes;
    m_bytesEncoded = lame_encode_buffer(
                            lgf,
                            input_buffer,
                            NULL,
                            input_bytes,
                            output_buffer,
                            OUTBUFSIZE_MONO
                        );
    return m_bytesEncoded;
}
