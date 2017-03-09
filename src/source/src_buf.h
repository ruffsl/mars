#ifndef __MARS_SOURCE_BUF
#define __MARS_SOURCE_BUF

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    typedef struct src_buf_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        int * buf; // for now, assume the input is ints (i.e. 32 bit)

    } src_raw_file_obj;

    typedef struct src_buf_cfg {

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        int* buf;

    } src_buf_cfg;

    src_buf_obj * src_buf_construct(const src_buf_cfg * cfg);

    void src_buf_destroy(src_buf_obj * obj);

    int src_buf_process(src_buf_obj * obj, msg_hops_obj * msg_hops);

    src_buf_cfg * src_buf_cfg_construct(void);

    void src_buf_cfg_destroy(src_buf_cfg * cfg);

#endif
