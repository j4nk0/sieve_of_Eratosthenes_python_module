#include <python3.4m/Python.h>

char *sieve (long size, long *primesCnt)
{
    long i, j;
    char *arr;

    *primesCnt = 1;

    /* The Sieve of Eratosthenes */
    arr = (char *) malloc (size);
    for (i = 0; i < size; ++i) { arr[i] = 1; }
    for (i = 1; i < size; ++i) {
        if (arr [i]) {
            *primesCnt += 1;
            j = 3 * i + 1;
            for ( ; j < size; j += 2*i +1)
                arr [j] = 0;
        }
    }
    /* Sieve complete for primes up to maxnr */
    /* prime numbers are 2*i+1 for every arr[i] == 1 */
    /* There is 1 marked as prime at i == 0 */
    /* 2 is missing as even numbers are left out */
    /* 1001st prime is still 1001st */
    return arr;
}

PyObject *sieveWrapper (PyObject *self, PyObject *args)
{
    long maxNr, size, primesCnt, inListCnt, i;
    char *sieveArr;
    PyObject *resList;

    if (!PyArg_ParseTuple (args, "l", &maxNr))
        return NULL;
    maxNr += 1;
    size = maxNr / 2;
    sieveArr = sieve (size, &primesCnt);
    resList = PyList_New (primesCnt);
    PyList_SetItem (resList, 0, PyLong_FromLong (2l));
    inListCnt = 1;
    for (i = 1; i < size; i++) {
        if (sieveArr [i])
            PyList_SetItem (resList, inListCnt++, PyLong_FromLong (2*i+1));
        if (inListCnt == primesCnt) break;
    }
    free (sieveArr);
    return resList;
}

static PyMethodDef sieveOfEratosthenesModule_methods[] = {
    {
        "primesUnder",
        (PyCFunction) sieveWrapper,
        METH_VARARGS,
        "Returns sorted list of all prime numbers not higher than given value"
    },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef sieveOfEratosthenesModule = {
    PyModuleDef_HEAD_INIT,
    "sieveOfEratosthenesModule",
    "This module implements the sieve of Eratosthenes",
    -1, /* size of per-interpreter state of the module,
           or -1 if the module keeps state in global variables. */
    sieveOfEratosthenesModule_methods
};

PyMODINIT_FUNC PyInit_sieveOfEratosthenesModule (void)
{
    return PyModule_Create (&sieveOfEratosthenesModule);
}

