#include <jni.h>
#include <string>

extern "C" {
#include "GenChordProgCommon.h"
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_genchordprogapp_MainActivity_genChordProgFromJNI(
        JNIEnv* env, jobject, /* this */
        jint p_key_idx, jint p_chordChange_cnt
        ) {

    char cChordProg[16*(40+1)] = {0};
    unsigned char uc_key_idx = 0;
    unsigned char uc_chordChange_cnt = 0;

    uc_key_idx = (unsigned char)p_key_idx;
    uc_chordChange_cnt = (unsigned char)p_chordChange_cnt;

    c_GenChordProg(cChordProg, uc_key_idx, uc_chordChange_cnt);
    std::string strChordProg(cChordProg);
    return env->NewStringUTF(strChordProg.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_genchordprogapp_MainActivity_genTempoFromJNI(
        JNIEnv* env, jobject /* this */
) {
    char cTempo[3+1] = {0};
    c_GenTempo(cTempo);
    std::string strTempo(cTempo);
    return env->NewStringUTF(strTempo.c_str());
}