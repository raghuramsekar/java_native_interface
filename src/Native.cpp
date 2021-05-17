#include <jni.h>
#include <iostream>
#include "Caller.h"
#include <windows.h>
#include <fileapi.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>


using namespace std;

JNIEXPORT jobject JNICALL Java_Caller_nativeFunc(JNIEnv* env, jobject jobj,jstring filePath) {

	const char *path;
	path = (env)->GetStringUTFChars(filePath,NULL);

	//CreateFile for opening a file 
	HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 0, OPEN_EXISTING, 0, 0);

	if (hFile == INVALID_HANDLE_VALUE) {
		cout << "invalid";
	}

	//Class reference for HashMap
	jclass mapClass = env->FindClass("java/util/HashMap");
	jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
	jobject hashMap = env->NewObject(mapClass, init);
	jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");


	DWORD dwFileSize = GetFileSize(hFile, NULL);
	jclass intclass = env->FindClass("java/lang/Long");
	init = env->GetMethodID(intclass, "<init>", "(J)V");
	jobject intobj = env->NewObject(intclass, init, dwFileSize);
	jstring str3 = env->NewStringUTF("FileSizeInBytes");
	env->CallObjectMethod(hashMap, put, str3, intobj);



	//File create,modify,access 
	FILETIME flcreatetime, flmodifytime, flaccesstime;
	SYSTEMTIME stutc;
	FILETIME ltutc;
	tm t;
	unsigned long int timing;

	//Get file create,access,modify
	GetFileTime(hFile, &flcreatetime, &flaccesstime, &flmodifytime);

	FileTimeToLocalFileTime(&flcreatetime, &ltutc);
	FileTimeToSystemTime(&ltutc, &stutc);

	//File created to epoch time 
	t.tm_year = stutc.wYear-1900;
	t.tm_mon = stutc.wMonth-1;
	t.tm_mday = stutc.wDay;
	t.tm_hour = stutc.wHour;
	t.tm_min = stutc.wMinute;
	t.tm_sec = stutc.wSecond;
	timing = mktime(&t);
	//set epoch time to java field "FileCreated"
	intclass = env->FindClass("java/lang/Long");
	init = env->GetMethodID(intclass, "<init>", "(J)V");
	intobj = env->NewObject(intclass, init, timing);
	str3 = env->NewStringUTF("FileCreated");
	env->CallObjectMethod(hashMap, put, str3, intobj);


	FileTimeToLocalFileTime(&flaccesstime, &ltutc);
	FileTimeToSystemTime(&ltutc, &stutc);

	//File accessed to epoch time
	t.tm_year = stutc.wYear - 1900;
	t.tm_mon = stutc.wMonth - 1;
	t.tm_mday = stutc.wDay;
	t.tm_hour = stutc.wHour;
	t.tm_min = stutc.wMinute;
	t.tm_sec = stutc.wSecond;
	timing = mktime(&t);
	//set epoch time to java field "FileAccessed"
    intclass = env->FindClass("java/lang/Long");
	init = env->GetMethodID(intclass, "<init>", "(J)V");
    intobj = env->NewObject(intclass, init, timing);
	str3 = env->NewStringUTF("FileAccessed");
	env->CallObjectMethod(hashMap, put, str3, intobj);

	FileTimeToLocalFileTime(&flmodifytime, &ltutc);
	FileTimeToSystemTime(&ltutc, &stutc);

	//File Modified to epoch time
	t.tm_year = stutc.wYear - 1900;
	t.tm_mon = stutc.wMonth - 1;
	t.tm_mday = stutc.wDay;
	t.tm_hour = stutc.wHour;
	t.tm_min = stutc.wMinute;
	t.tm_sec = stutc.wSecond;
	timing = mktime(&t);
	//set epoch time to java field "FileModified"
	intclass = env->FindClass("java/lang/Long");
	init = env->GetMethodID(intclass, "<init>", "(J)V");
	intobj = env->NewObject(intclass, init, timing);
	str3 = env->NewStringUTF("FileModified");
	env->CallObjectMethod(hashMap, put, str3, intobj);

	ULONG attr;
	attr = GetFileAttributesA(path);

	//Check File is ReadOnly
	bool isReadOnly = attr & FILE_ATTRIBUTE_READONLY;
	intclass = env->FindClass("java/lang/Boolean");
	init = env->GetMethodID(intclass, "<init>", "(Z)V");
	intobj = env->NewObject(intclass, init, isReadOnly);
	str3 = env->NewStringUTF("ReadOnly");
	env->CallObjectMethod(hashMap, put, str3, intobj);

	//Check File is Hidden
	bool isHidden = attr & FILE_ATTRIBUTE_HIDDEN;
	intclass = env->FindClass("java/lang/Boolean");
	init = env->GetMethodID(intclass, "<init>", "(Z)V");
	intobj = env->NewObject(intclass, init, isHidden);
	str3 = env->NewStringUTF("Hidden");
	env->CallObjectMethod(hashMap, put, str3, intobj);

	//global ref for return
	jobject globalhashMap = static_cast<jobject>(env->NewGlobalRef(hashMap));

	return globalhashMap;
}