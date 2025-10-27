///////////////////////////////////////
// Insertion sort
// See: http://www.cs.brynmawr.edu/Courses/cs330/spring2016/CodeFromPearls.pdf

namespace isort
{ 

//#define MAXN 10000000


// Safe isort1 that works with std::vector
void swapVec(std::vector<int>& v, int i, int j)
{
    std::swap(v[i], v[j]); // safe swap
    comp++;
    printArrayBar(v.data(), v.size(), j); // pass raw pointer if visualization needs it
}

void isort1(std::vector<int>& v)
{
    int n = v.size();
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && v[j-1] > v[j]; j--)
            swapVec(v, j-1, j);
}



typedef int DType;

//DType realx[MAXN];
//int *x = realx; /* allow x to shift for heaps */
//int n;

// NOTE: we are getting an exception:
// x points directly into v.
// If v is resized, reassigned, or passed to a function that reallocates,
// x becomes dangling.
// Any subsequent access via x[i] is undefined behavior → can corrupt memory
// → malloc error.
int *x = &v[0];
int n = v.size();

void swap(int i, int j)
{   
    // TEST: bounds check OK
    if (i < 0 || j < 0 || i >= n || j >= n) {
        printf("swap index out of bounds: i=%d j=%d n=%d\n", i, j, n);
        exit(1);
    }

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
            comp++;
            printArrayBar(&v[0], vsize, j);
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