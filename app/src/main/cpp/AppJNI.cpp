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
Java_sodino_open_gl_JniHandler_initGL(JNIEnv *env, jobject thiz, jobject assetManager) {
    ndkAsset_initAssetManager(env, assetManager);
    app_initGL();
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