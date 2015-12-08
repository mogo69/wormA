#include <jni.h>
#include "atmjniproxy.h"
#include "ATM.h"

JNIEXPORT jboolean JNICALL Java_com_worm_jni_AtmJniProxy_isBlocked
(JNIEnv *, jobject)
{
	return ATM::getInstance("127.0.0.1", 9999).isBlocked();
}
