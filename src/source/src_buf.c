
    #include "src_buf.h"

    src_buf_obj * src_buf_construct(const src_buf_cfg * cfg) {

        src_buf_obj * obj;

        obj = (src_buf_obj *) malloc(sizeof(src_buf_obj));

        obj->timeStamp = 0;

        obj->hopSize = cfg->hopSize;
        obj->nMics = cfg->nMics;
        obj->nBits = cfg->nBits;

        obj->buf = cfg->buf;

        if (obj->buf == NULL) {
            printf("Passed null buffer.\n");
            exit(EXIT_FAILURE);
        }

        if (!(/*(cfg->nBits == 16) |*/ (cfg->nBits == 32))) {
            printf("Invalid number of bits-- required 32.\n");
            exit(EXIT_FAILURE);
        }

        return obj;

    }

    void src_buf_destroy(src_buf_obj * obj) {
      // do nothing -- caller handles buffer lifetime
    }

    int src_buf_process(src_buf_obj * obj, msg_hops_obj * msg_hops) {

        unsigned int iSample;
        unsigned int iMic;
        signed char sampleChar;
        signed short sampleShort;
        signed int sampleInt;
        float sample;
        int rtnValue;
        int offset;
        int tmp;

        rtnValue = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iMic = 0; iMic < obj->nMics; iMic++) {


                switch (obj->nBits) {

                    // case 16:
                    //
                    //     tmp = fread(&sampleShort, sizeof(signed short), 1, obj->fp);
                    //     sample = pcm_signed16bits2normalized(sampleShort);
                    //
                    // break;

                    case 32:
                        offset = iSample * obj->nMics + iMic;
                        sampleInt = obj->buf[offset]; // fread(&sampleInt, sizeof(signed int), 1, obj->fp);
                        sample = pcm_signed32bits2normalized(sampleInt);

                    break;
                }


                msg_hops->hops->array[iMic][iSample] = sample;

            }

        }

        obj->timeStamp++;

        msg_hops->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    src_buf_cfg * src_buf_cfg_construct(void) {

        src_buf_cfg * cfg;

        cfg = (src_buf_cfg *) malloc(sizeof(src_buf_cfg));

        cfg->hopSize = 0;
        cfg->nMics = 0;
        cfg->nBits = 0;
        cfg->buf = (int *) NULL;

        return cfg;

    }

    void src_buf_cfg_destroy(src_buf_cfg * cfg) {

        // same stuff, caller must configure

    }
