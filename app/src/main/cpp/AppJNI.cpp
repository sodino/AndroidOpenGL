#include <jni.h>
#include <string>
#include "print/printOpenGL.h"
#include "ndk/AssetKit.h"
#include "AppOpenGL.h"
extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_printOpenGLInfos(JNIEnv *env, jobject thiz) {
    printOpenGLInfos();
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_resizeGL(JNIEnv *env, jobject thiz, jint width, jint height) {
    app_resizeGL(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_renderGL(JNIEnv *env, jobject thiz) {
    app_renderGLFrame();
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_initGL(
        JNIEnv *env,
        jobject thiz,
        jobject assetManager,

        jint width, jint height) {
    ndkAsset_initAssetManager(env, assetManager);
    app_initGL(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_destroyGL(JNIEnv *env, jobject thiz) {
    app_destroyGL();
    ndkAsset_destroyAssetManager();
}


extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_onlyDrawLine(JNIEnv *env, jobject thiz, jboolean onlyLine) {
    app_onlyDrawLine(onlyLine);
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_setYawAngle(JNIEnv *env, jobject thiz, jint angle) {
    if (angle < 0) {
        angle = 0;
    } else if (angle >= 360) {
        angle = 360;
    }
    app_setYawAngle(angle);
}

extern "C"
JNIEXPORT void JNICALL
Java_sodino_open_gl_JniHandler_setPitchAngle(JNIEnv *env, jobject thiz, jint angle) {
    if (angle < 0) {
        angle = 0;
    } else if (angle >= 360) {
        angle = 360;
    }
    app_setPitchAngle(angle);
}