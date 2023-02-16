/**
 * This class handles only the encoding job. it does not touch the file-system. 
 * it takes an input_buffer and returns an output_buffer. all via pointers. 
 * Its the Worker class which touches the file-system. 
*/
#if !defined(LAMEENCODER_H)
#define LAMEENCODER_H

#include <lame/lame.h>
#include <string>
#include "constants.h"

class LameEncoder{

    public:
        LameEncoder();
        ~LameEncoder();
        int doEncode(
            int input_bytes, 
            short input_buffer[INBUFSIZE_MONO], 
            unsigned char output_buffer[OUTBUFSIZE_MONO]
            );
        void errored(std::string err);

    private:
        lame_global_flags* lgf;
        int m_bytesEncoded;

};

#endif // LAMEENCODER_H
