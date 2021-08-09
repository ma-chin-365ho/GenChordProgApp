#include <jni.h>
#include <string>

extern "C" {
#include "GenChordProgCommon.h"
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_genchordprogapp_MainActivity_genChordProgFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    char cChordProg[16*(40+1)] = {0};
    c_GenChordProg(cChordProg, 0, 4);
    std::string strChordProg(cChordProg);
    return env->NewStringUTF(strChordProg.c_str());
}