#include <jni.h>
#include <iostream>
#include "StringIni.h"
#include <windows.h>
#include <fileapi.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

JNIEXPORT jstring JNICALL Java_StringIni_GetStringUTFCharsFunc(JNIEnv* env, jobject jobj, jstring prompt) {
    char buf[128];
    const char* str;
    str = (env)->GetStringUTFChars(prompt, NULL);
    if (str == NULL) {
        return NULL;
    }
    cout << str << endl;
    (env)->ReleaseStringUTFChars(prompt, str);
    cin >> buf;
    return (env)->NewStringUTF(buf);
}

JNIEXPORT jstring JNICALL Java_StringIni_GetStringLengthAndRegionFunc(JNIEnv* env, jobject jobj, jstring prompt) {
    char outbuf[128], inbuf[128];
    int len = (env)->GetStringLength(prompt);
    cout << len << endl;
    (env)->GetStringUTFRegion(prompt, 0, len, outbuf);
    cout << outbuf << endl;
    cin >> inbuf;
    return (env)->NewStringUTF(inbuf);
}


