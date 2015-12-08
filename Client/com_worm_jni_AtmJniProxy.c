#include <jni.h>
#include "com_worm_jni_AtmJniProxy.h"
#include "ATM.h"
#include <string.h>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
/*JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_isBlocked
(JNIEnv *, jobject)
{
	return ATM::getInstance("127.0.0.1", 9999).isBlocked();
}*/

JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_logIn
(JNIEnv *env, jobject, jstring cardN, jint PIN)
{
	jboolean isCopy = false;
	const char *cardN_char = (*env).GetStringUTFChars(cardN, &isCopy);
	string cardN_string (cardN_char);
	int PIN_int = (int) PIN;
	ATM &atm = ATM::getInstance("127.0.0.1", 9999); 
	return atm.logIn(cardN_string, PIN_int);
}

JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_logOut
  (JNIEnv *, jobject)
{
	ATM &atm = ATM::getInstance("127.0.0.1", 9999); 
	return atm.logOut();
}

JNIEXPORT jdouble JNICALL Java_com_worm_jni_AtmJniProxy_getBalance
  (JNIEnv *, jobject)
{
	ATM &atm = ATM::getInstance("127.0.0.1", 9999);
	return atm.getBalance();
}

JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_canWithdraw
  (JNIEnv *, jobject, jint sum)
{
	ATM &atm = ATM::getInstance("127.0.0.1", 9999);
	int sum_int = (int) sum;
	return atm.canWithdraw(sum_int);
}

#ifdef __cplusplus
}
#endif
