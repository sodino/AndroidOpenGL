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


 const char* ndkAsset_readText(
        const char *assetItemName,
        int *itemLength,
        int mode) {
    if (gAAssetMgr == NULL) {
        return NULL;
    }
    AAsset* asset = AAssetManager_open(gAAssetMgr, assetItemName, mode);
    int assetLength = AAsset_getLength(asset);
    char* buffer = NULL;
    if (assetLength > 0) {
        *itemLength = assetLength + 1;
        buffer = (char*) malloc(assetLength);
        AAsset_read(asset, buffer, *itemLength);
        buffer[assetLength] = '\0';
    }
    AAsset_close(asset);

    return buffer;
}


const unsigned char* ndkAsset_readBytes(
        const char *assetItemName,
        int *itemLength,
        int mode) {
    if (gAAssetMgr == NULL) {
        return NULL;
    }
    AAsset* asset = AAssetManager_open(gAAssetMgr, assetItemName, mode);
    int assetLength = AAsset_getLength(asset);
    unsigned char* buffer = NULL;
    if (assetLength > 0) {
        *itemLength = assetLength;
        buffer = (unsigned char*) malloc(assetLength);
        AAsset_read(asset, buffer, *itemLength);
    }
    AAsset_close(asset);

    return buffer;
}