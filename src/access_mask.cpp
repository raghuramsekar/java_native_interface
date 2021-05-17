#include <jni.h>
#include <iostream>
#include <windows.h>
#include <fileapi.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Caller.h"
#include <cstring>

using namespace std;

JNIEXPORT jobject JNICALL Java_Caller_accessSecFunc(JNIEnv* env, jobject jobj){

	//security descriptor
	DWORD length = 0;
	static char psd[64 * 1024];
	PSECURITY_DESCRIPTOR psdvar = (PSECURITY_DESCRIPTOR*)psd;

	if (!GetFileSecurity("E:\\file\\filechild.txt", DACL_SECURITY_INFORMATION, psdvar, sizeof(psd), &length)) {
		cout << "invalid" << endl;
		//return 1;
	}

	//get dacl from security descriptor
	PACL pacl;
	BOOL acl_present = FALSE;
	BOOL acl_defaulted = TRUE;

	if (!GetSecurityDescriptorDacl(psdvar, &acl_present, &pacl, &acl_defaulted)) {
		cout << "failed in pacl" << endl;
		//return 1;
	}

	//get acl overall info
	ACL_SIZE_INFORMATION acl_info;
	if (!GetAclInformation(pacl, &acl_info, sizeof(acl_info), AclSizeInformation)) {
		cout << "failed in length" << endl;
		//return 1;
	}

	//loo all acl and lists its props
	ACCESS_ALLOWED_ACE* pace = NULL;
	LPCWSTR wszComputerName = L"\0";
	WCHAR* wszAccName = new WCHAR[256 * sizeof(DWORD)];
	WCHAR* wszDomainName = new WCHAR[256 * sizeof(DWORD)];
	DWORD cchAccName = 256;
	DWORD cchDomainName = 256;
	SID_NAME_USE eSidType;
	jclass cls2 = env->FindClass("Caller");
	jobjectArray ACL_HEADER_AccName = env->NewObjectArray(acl_info.AceCount, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	jintArray ACL_HEADER_AceType = env->NewIntArray(acl_info.AceCount);
	jintArray ACE_Entries = env->NewIntArray(acl_info.AceCount);
	jint fill_acetype[acl_info.AceCount];
	jint fill_mask[acl_info.AceCount];


	for (int i = 0; i < acl_info.AceCount; i++)
	{

		if (GetAce(pacl, i, (LPVOID*)&pace) == FALSE)
		{
			cout << "get ace failed" << endl;
		}

		for (;;)
		{
			//lookup account name via sid
			if (LookupAccountSidW(wszComputerName, &pace->SidStart, wszAccName, &cchAccName, wszDomainName, &cchDomainName, &eSidType) == TRUE) {
				break;
			}
		}

		//acc name convert from wchar* to char*
		char ACL_HEADER_AccName_temp[30];
		sprintf(ACL_HEADER_AccName_temp, "%ls", wszAccName);
		jstring str = env->NewStringUTF(ACL_HEADER_AccName_temp);
		env->SetObjectArrayElement(ACL_HEADER_AccName, i, str);

		//acetype in byte datatype stored in fill type array
		fill_acetype[i] = (int)pace->Header.AceType;

		//mask in int stored in fill mask array
		fill_mask[i] = pace->Mask;
	}
	

	//acetype array in java assigned values
	env->SetIntArrayRegion(ACL_HEADER_AceType, 0, acl_info.AceCount, fill_acetype);

	//aceentries assigned 
	env->SetIntArrayRegion(ACE_Entries, 0, acl_info.AceCount, fill_mask);

	//hashmap class creation
	jclass mapClass = env->FindClass("java/util/HashMap");
	jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
	jobject hashMap = env->NewObject(mapClass, init);
	jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

	//acc name entered into hashmap
	jstring str3 = env->NewStringUTF("ACL_HEADER_AccName");
	env->CallObjectMethod(hashMap, put, str3, ACL_HEADER_AccName);

	//ace type entered into hashmap
	str3 = env->NewStringUTF("ACL_HEADER_AceType");
	env->CallObjectMethod(hashMap, put, str3, ACL_HEADER_AceType);

	//ace entries entered into hashmap
	str3 = env->NewStringUTF("ACE_Entries");
	env->CallObjectMethod(hashMap, put, str3, ACE_Entries);

	//create global references for returning
	jobject globalhashMap = static_cast<jobject>(env->NewGlobalRef(hashMap));



	return globalhashMap;
}