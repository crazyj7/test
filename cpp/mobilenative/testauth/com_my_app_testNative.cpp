#include <cstring>
#include <iostream>
#include "com_my_app_testNative.h"


using namespace std ;
/*
 * Method:    hello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_my_app_testNative_hello
  (JNIEnv *, jclass) {
  	cout << "faceNative:Hello" << endl ;
  }

/*
 * Method:    greeting
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_my_app_testNative_greeting
  (JNIEnv *env, jobject obj, jstring jstr) {
	const char *name = env->GetStringUTFChars(jstr, NULL) ;
	char msg[100]="hello " ;
	jstring result ;
	strcat(msg, name) ;
	env->ReleaseStringUTFChars(jstr, name) ;
	result  = env->NewStringUTF(msg) ;
	return result ;  	
  }

