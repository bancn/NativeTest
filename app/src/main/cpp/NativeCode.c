//
// Created by Bancn on 2021/11/19.
//

#include "NativeCode.h"
JNIEXPORT jstring JNICALL Java_cn_axhl_util_NativeLib_GetNativeString
  (JNIEnv *env, jclass cls) {
    char *lpStr = "hello world";
    jstring jstr = (* env)->NewStringUTF(env, lpStr);
    return jstr;
}


JNIEXPORT jint JNICALL Java_cn_axhl_util_NativeLib_add
  (JNIEnv *env, jclass clzz, jint a, jint b) {
    return a + b;
}
