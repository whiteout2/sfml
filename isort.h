///////////////////////////////////////
// Insertion sort
// See: http://www.cs.brynmawr.edu/Courses/cs330/spring2016/CodeFromPearls.pdf

namespace isort
{ 

#define MAXN 10000000

typedef int DType;

DType realx[MAXN];
//int *x = realx; /* allow x to shift for heaps */
//int n;
int *x = &v[0];
int n = v.size();

void swap(int i, int j)
{       
    DType t = x[i];
    x[i] = x[j];
    x[j] = t;
    comp++;
    printArrayBar(&v[0], vsize, j);
}

/* Simplest insertion sort */
void isort1()
{       
    int i, j;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j-1] > x[j]; j--)
            swap(j-1, j);
}

/* Write swap function inline */
void isort2()
{       
    int i, j;
    DType t;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j-1] > x[j]; j--) {
            t = x[j];
            x[j] = x[j-1];
            x[j-1] = t;
        }
}

/* Move assignments to and from t out of loop */
void isort3()
{
    int i, j;
    DType t;
    for (i = 1; i < n; i++) {
        t = x[i];
        for (j = i; j > 0 && x[j - 1] > t; j--) {
            x[j] = x[j - 1];
            comp++;
            printArrayBar(&v[0], vsize, j);
        }
        x[j] = t;
    }
}

} // namespace isort