/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_worm_jni_AtmJniProxy */

#ifndef _Included_com_worm_jni_AtmJniProxy
#define _Included_com_worm_jni_AtmJniProxy
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    isBlocked
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_isBlocked
  (JNIEnv *, jobject);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    logIn
 * Signature: (Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_logIn
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    logOut
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_logOut
  (JNIEnv *, jobject);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    changePIN
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_changePIN
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    getAdvert
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_worm_jni_AtmJniProxy_getAdvert
  (JNIEnv *, jobject);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    getBalance
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_worm_jni_AtmJniProxy_getBalance
  (JNIEnv *, jobject);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    canWithdraw
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_canWithdraw
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    withdraw
 * Signature: (JZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_withdraw
  (JNIEnv *, jobject, jlong, jboolean);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    getDataAbout
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_worm_jni_AtmJniProxy_getDataAbout
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_worm_jni_AtmJniProxy
 * Method:    sendMoneyTo
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_sendMoneyTo
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
