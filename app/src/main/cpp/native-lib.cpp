#include <jni.h>
#include <vector>
#include <stdlib.h>

class Prime {

    public:
        jintArray getPrime(JNIEnv* env, int from, int to);
        Prime();
};

/**
     * Rearrange array by random
     *
     * @param *v
     * @param n
     * @return  pointer to rearranged array
     *
    */

int* RandomElements(int* v, int n)
{
    int temp = 0;
    int ridx = n-1;

    for(int j=(n-1); j>1; j--)// one pass through array
    {
        ridx = rand()%(j+1);// index = 0 to j
        temp = v[ridx];// value will be moved to end element
        v[ridx] = v[j];// end element value in random spot
        v[j] = temp;// selected element moved to end. This value is final
    }
    return v;
}

Prime::Prime() { }

jintArray Prime::getPrime(JNIEnv* env, int from, int to){

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

    env->SetIntArrayRegion(jint_primes, 0, size, RandomElements(temp, size));

    return jint_primes;
}

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
    Prime mPrime;
    return mPrime.getPrime(env, from, to);
}

