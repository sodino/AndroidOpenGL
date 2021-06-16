//
// Created by sodino on 2021/6/16.
//

#ifndef ANDROIDOPENGL_PRINTOPENGL_H
#define ANDROIDOPENGL_PRINTOPENGL_H

#include <android/log.h>


#define LOG_TAG "c++GL"
#define logD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)


void printOpenGLInfos();
#endif //ANDROIDOPENGL_PRINTOPENGL_H
