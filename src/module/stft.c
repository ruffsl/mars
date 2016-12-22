
    #include "stft.h"

    stft_obj * stft_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics) {

    	stft_obj * obj;
    	unsigned int iMic;

    	obj = (stft_obj *) malloc(sizeof(stft_obj));

    	obj->hopSize = hopSize;
    	obj->frameSize = frameSize;
    	obj->halfFrameSize = frameSize/2 + 1;
    	obj->nMics = nMics;

        obj->hops = array_1d_malloc(obj->nMics);
        obj->analysis = array_1d_malloc(obj->nMics);
        obj->frames = array_1d_malloc(obj->nMics);
        obj->spectrum = array_1d_malloc(obj->nMics);
        obj->freqs = array_1d_malloc(obj->nMics);

        for (iMic = 0; iMic < nMics; iMic++) {
        	obj->hops->ptr[iMic] = (void *) vector_float_malloc(obj->hopSize);
        	obj->analysis->ptr[iMic] = (void *) analysis_construct(obj->hopSize, obj->frameSize);
        	obj->frames->ptr[iMic] = (void *) vector_float_malloc(obj->frameSize);
        	obj->spectrum->ptr[iMic] = (void *) spectrum_construct(obj->frameSize);
        	obj->freqs->ptr[iMic] = (void *) vector_float_malloc(obj->halfFrameSize*2);
        }
    	
    	obj->window = window_hann(obj->frameSize);

    	return obj;

    }

    void stft_destroy(stft_obj * obj) {

        unsigned int iMic;

        for (iMic = 0; iMic < obj->nMics; iMic++) {
        	vector_float_free(obj->hops->ptr[iMic]);
        	analysis_destroy(obj->analysis->ptr[iMic]);
        	vector_float_free(obj->frames->ptr[iMic]);
        	spectrum_destroy(obj->spectrum->ptr[iMic]);
        	vector_float_free(obj->freqs->ptr[iMic]);
        }

        array_1d_free(obj->hops);
        array_1d_free(obj->analysis);
        array_1d_free(obj->frames);
        array_1d_free(obj->spectrum);
        array_1d_free(obj->freqs);

        vector_float_free(obj->window);

    	free((void *) obj);

    }

    int stft_process(stft_obj * obj, const msg_hops_obj * hops, msg_spectra_obj * spectra) {

        unsigned int iMic;
        unsigned int iSample;

        for (iMic = 0; iMic < obj->nMics; iMic++) {
            for (iSample = 0; iSample < obj->hopSize; iSample++) {
                ((vector_float *) obj->hops->ptr[iMic])->array[iSample] = hops->samples[iMic][iSample];
            }
        }

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            analysis_process(obj->analysis->ptr[iMic], obj->hops->ptr[iMic], obj->frames->ptr[iMic]);
            spectrum_process(obj->spectrum->ptr[iMic], obj->frames->ptr[iMic], obj->window, obj->freqs->ptr[iMic]);

        }

        for (iMic = 0; iMic < obj->nMics; iMic++) {
            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            	spectra->samples[iMic][iSample*2+0] = ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+0];
                spectra->samples[iMic][iSample*2+1] = ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+1];

            }
        }

        spectra->timeStamp = hops->timeStamp;

    }
