#include <jni.h>
#include <string>
#include "print/printOpenGL.h"

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_printOpenGLInfos(JNIEnv *env, jobject thiz) {
    printOpenGLInfos();
}