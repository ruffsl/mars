    
    #include "xcorr2xcorr.h"

    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize) {

        xcorr2xcorr_obj * obj;

        obj = (xcorr2xcorr_obj *) malloc(sizeof(xcorr2xcorr_obj));

        obj->frameSize = frameSize;

        return obj;

    }

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj) {

        free((void *) obj);

    }

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const unsigned int delta, xcorrs_obj * xcorrsMax) {

        unsigned int iSignal;
        unsigned int iSampleMax;
        unsigned int iSample;
        float maxValue;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            for (iSampleMax = tdoas->arrayMin[iSignal]; iSampleMax <= tdoas->arrayMax[iSignal]; iSampleMax++) {

                maxValue = xcorrs->array[iSignal * obj->frameSize + iSampleMax];

                for (iSample = (iSampleMax-delta); iSample <= (iSampleMax+delta); iSample++) {

                    if (xcorrs->array[iSignal * obj->frameSize + iSample] > maxValue) {

                        maxValue = xcorrs->array[iSignal * obj->frameSize + iSample];

                    }

                }

                xcorrsMax->array[iSignal * obj->frameSize + iSampleMax] = maxValue;

            }

        }

    }

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const unsigned int delta, const unsigned int iPoint, xcorrs_obj * xcorrsReset) {

        unsigned int iSignal;
        unsigned int iSample;
        unsigned int nSamples;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            iSample = iSignal * obj->frameSize + tdoas->arrayMin[iSignal];
            nSamples = (tdoas->arrayMax[iSignal] - tdoas->arrayMin[iSignal] + 1);

            memcpy(&(xcorrsReset->array[iSample]), &(xcorrs->array[iSample]), sizeof(float) * nSamples);

            iSample = iSignal * obj->frameSize + tdoas->array[iPoint * tdoas->nPairs + iSignal] - delta;
            nSamples = 2 * delta + 1;

            memset(&(xcorrsReset->array[iSample]), 0x00, sizeof(float) * nSamples);

        }

    }
