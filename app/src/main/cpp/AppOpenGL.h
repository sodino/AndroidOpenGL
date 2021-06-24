//
// Created by sodino on 2021/6/17.
//

#ifndef ANDROIDOPENGL_APPOPENGL_H
#define ANDROIDOPENGL_APPOPENGL_H
#include "jni.h"
#include "print/printOpenGL.h"

void app_resizeGL(jint width, jint height);
void app_renderGLFrame();
void app_initGL(jint width, jint height);
void app_destroyGL();
void app_onlyDrawLine(jboolean);


void app_setPitchAngle(jint angle);
void app_setYawAngle(jint angle);

#endif //ANDROIDOPENGL_APPOPENGL_H
