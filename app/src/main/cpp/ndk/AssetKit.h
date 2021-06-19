//
// Created by sodino on 2021/6/19.
//
#ifndef ANDROIDOPENGL_ASSETKIT_H
#define ANDROIDOPENGL_ASSETKIT_H
#include <jni.h>
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"

void ndkAsset_initAssetManager(JNIEnv *env, jobject assetManager);
const char* ndkAsset_readText(const char* assetItemName, int* itemLength, int mode = AASSET_MODE_BUFFER);
void ndkAsset_destroyAssetManager();

#endif //ANDROIDOPENGL_ASSETKIT_H
