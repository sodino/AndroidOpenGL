//
// Created by sodino on 2021/6/19.
//
#include "AssetKit.h"
#include "jni.h"
#include "malloc.h"
AAssetManager* gAAssetMgr = NULL;


void ndkAsset_initAssetManager(JNIEnv *env, jobject assetManager) {
    gAAssetMgr = AAssetManager_fromJava(env, assetManager);
}

void ndkAsset_destroyAssetManager() {
    if (gAAssetMgr == NULL) {
        return;
    }
    gAAssetMgr = NULL;
}


const char *ndkAsset_readText(
        const char *assetItemName,
        int *itemLength,
        int mode) {
    if (gAAssetMgr == NULL) {
        return NULL;
    }
    AAsset* asset = AAssetManager_open(gAAssetMgr, assetItemName, mode);
    (*itemLength) = AAsset_getLength(asset);
    char* buffer = NULL;
    if (*itemLength > 0) {
        buffer = (char*) malloc(*itemLength +1);
        AAsset_read(asset, buffer, *itemLength);
        buffer[*itemLength] = '\0';
    }
    AAsset_close(asset);

    return buffer;
}
