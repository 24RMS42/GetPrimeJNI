#include <jni.h>
#include <string>
#include <vector>

/**
     * Get array of prime between two numbers
     *
     * @param from
     * @param to
     * @return   array of prime numbers
     *
    */

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_matata_testprime_MainActivity_getPrime(
        JNIEnv* env,
        jobject,
        int from,
        int to)
{
    // get prime as vector
    if (from == 1) from = 2;
    std::vector<int> vector_primes;
    for(int i = from; i < to; i++)
    {
        bool prime = true;
        for (int j=2; j*j<=i; j++)
        {
            if(i % j == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime)
        {
            vector_primes.push_back(i);
        }
    }

    // convert vector into jint array
    int size = vector_primes.size();
    jint temp[size];
    for (int j = 0; j < size; j++) {
        temp[j] = vector_primes[j];
    }

    // move from the temp structure to the java structure
    jintArray jint_primes;
    jint_primes = env->NewIntArray(size);
    if (jint_primes == NULL) {
        return NULL; /* out of memory error thrown */
    }
    env->SetIntArrayRegion(jint_primes, 0, size, temp);

    return jint_primes;
}