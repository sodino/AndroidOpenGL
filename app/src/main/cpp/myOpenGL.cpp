#include <jni.h>
#include <string>
#include "print/printOpenGL.h"
#include <GLES3/gl3.h>


void renderGLFrame() {
    static float rgb = 0.0f;
    static bool isAdd = true;
    rgb += (isAdd) ? 0.01f : -0.01f;
    if (rgb > 1.0f) {
        isAdd = false;
        rgb = 1.0f;
    } else if (rgb < 0.0f) {
        isAdd = true;
        rgb = 0.0f;
    }
    // 'glClearColor' a confusing function name. specify color value for 'glClear' action
    glClearColor(rgb, rgb, rgb, 1.0f);
    // write color specified by 'glClearColor'
    glClear(GL_COLOR_BUFFER_BIT);
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_printOpenGLInfos(JNIEnv *env, jobject thiz) {
    printOpenGLInfos();
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_resizeGL(JNIEnv *env, jobject thiz, jint width, jint height) {
    glViewport(0, 0, width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_renderGL(JNIEnv *env, jobject thiz) {
    renderGLFrame();
}