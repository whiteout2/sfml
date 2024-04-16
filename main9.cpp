#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>
#include <chrono>





struct perf {
    std::chrono::steady_clock::time_point start_;
    perf() : start_(std::chrono::steady_clock::now()) {}
    double elapsed() const {
        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = stop - start_;
        return elapsed_seconds.count();
    }
};



// executes in-place bogo sort on a given array
static void bogo_sort(int* a, int size);
// returns 1 if given array is sorted and 0 otherwise
static int is_sorted(int* a, int size);
// shuffles the given array into a random order
static void shuffle(int* a, int size);


void printArrayBar(int A[], int size, int r);

int vsize = 1024;
std::vector<int> v(vsize);

std::string strName = "Merge Sort";
int comp = 0;

#include "WikiSort.h"

//sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

float x = window.getSize().x;
float y = window.getSize().y;

sf::RectangleShape rect;

// sound
sf::SoundBuffer buffer;
sf::Sound sound;

// text
sf::Font font;
sf::Text text;

void udelay (long usec) {
    perf p3;
    while (p3.elapsed() < usec/1000000.0f && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                //sound.stop();
                //window.close();
                exit(0);
            }
        }
    }
}


///////////////////////////////////////
void bogo_sort(int* a, int size) {
    while (!is_sorted(a, size) && window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                //sound.stop();
                //window.close();
                exit(0);
            }
        }
        
        shuffle(a, size);

        printArrayBar(a, size, 0);
    }
}

int is_sorted(int* a, int size) {
    for (int i = 0; i < size-1; i++) {
        if (a[i] > a[i+1]) {
            return 0;
        }
    }
    return 1;
}

void shuffle(int* a, int size) {
    int temp, random;
    for (int i = 0; i < size; i++) {
        random = (int) ((double) rand() / ((double) RAND_MAX + 1) * size);
        temp = a[random];
        a[random] = a[i];
        a[i] = temp;
    }
}



///////////////////////////////////////
// See: https://www.geeksforgeeks.org/cocktail-sort/
void CocktailSort(int a[], int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;
 
    // NOTE: need window.isOpen() check here because this has become our game loop
    while (swapped && window.isOpen()) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                //sound.stop();
                //window.close();
                exit(0);
            }
        }
 
        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                printArrayBar(a, n, i+1);
                swapped = true;
                comp++;
            }
        }
 
        // if nothing moved, then array is sorted.
        if (!swapped)
            break;
 
        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;
 
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
 
        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                printArrayBar(a, n, i+1);
                swapped = true;
                comp++;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}

///////////////////////////////////////
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            //sound.stop();
            //window.close();
            exit(0);
        }
    }

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            //printArray(arr, arr_size);
        }
        else {
            arr[k] = R[j];
            j++;
            //printArray(arr, arr_size);
        }
        k++;
        //printArray(arr, arr_size);
        printArrayBar(arr, vsize, k);
        comp++;
    }
    //printArray(arr, arr_size);

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        //printArray(arr, arr_size);
        printArrayBar(arr, vsize, k);
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        //printArray(arr, arr_size);
        printArrayBar(arr, vsize, k);
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r && window.isOpen()) {
        int m = l + (r - l) / 2;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                //sound.stop();
                //window.close();
                exit(0);
            }
        }

        // int arr_size = 6;//= sizeof(arr) / sizeof(arr[0]);
        //printArray(arr, 6);

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

///////////////////////////////////////
// See: https://www.geeksforgeeks.org/quick-sort/
// Lomuto partition scheme
/*
// Utility function to swap tp integers
void swap(int* p1, int* p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int low, int high)
{
    // choose the pivot
    int pivot = arr[high];

    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        printArrayBar(arr, vsize, i);
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            // Increment index of smaller element
            i++;
            swap(&arr[i], &arr[j]);
            //printArray(arr, arr_size);
            //printArrayBar(arr, arr_size, i, j, high);
            comp++;
        }
    }
    i++;
    //swap(&arr[i + 1], &arr[high]);
    swap(&arr[i], &arr[high]); // swap pivot
    //printArray(arr, arr_size);
    printArrayBar(arr, vsize, i);
    
    //return (i + 1);
    return (i);
}

// The Quicksort function Implement
void quickSort(int arr[], int low, int high)
{
    // when low is less than high
    if (low < high) {
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion Call
        // smaller element than pivot goes left and
        // higher element goes right
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
*/

///////////////////////////////////////
// See: https://web.archive.org/web/20120219000149/http://www.sorting-algorithms.com/static/QuicksortIsOptimal.pdf
// Quicksort with 2-way partitioning
// Hoare partition scheme but uses last value as pivot
// NOTE: nasty recursion prob. After one run sweep() takes over.
// Well, Sedgewick, is this code correct?
// Of course it is but we introduced errors with comp++ without using {} causing a break;
// immediately. Always use {} after if and while!!!
// Use: -Wmisleading-indentation
// And never try to write such terse code...
void quicksort(int a[], int l, int r) 
{
    if (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                //sound.stop();
                //window.close();
                exit(0);
            }
        }

        int i = l-1, j = r; 
        int v = a[r]; // last value is pivot
        if (r <= l) { comp++; return; }
        for (;;) {
            while (a[++i] < v) { comp++; }
            while (v < a[--j]) { comp++; if (j == l) break; } // comp++ introduced error: use {}
            if (i >= j) { comp++; break; }
            std::swap(a[i], a[j]);
            //printArray(a, arr_size);
            printArrayBar(a, vsize, i);
        }
        std::swap(a[i], a[r]); // swap pivot
        //printArray(a, arr_size);
        printArrayBar(a, vsize, i);
        quicksort(a, l, i-1);
        quicksort(a, i+1, r);
        printArrayBar(a, vsize, i); // one final print for correct comp
    }
}


//input: ratio is between 0.0 to 1.0
//output: rgb color
uint32_t rgb(double ratio)
{
    //we want to normalize ratio so that it fits in to 6 regions
    //where each region is 256 units long
    int normalized = int(ratio * 256 * 6); // use only 5 regions for ROGGBIV

    //find the region for this position
    int region = normalized / 256;

    //find the distance to the start of the closest region
    int x = normalized % 256;

    uint8_t r = 0, g = 0, b = 0;
    switch (region)
    {
    case 0: r = 255; g = 0;   b = 0;   g += x; break;
    case 1: r = 255; g = 255; b = 0;   r -= x; break;
    case 2: r = 0;   g = 255; b = 0;   b += x; break;
    case 3: r = 0;   g = 255; b = 255; g -= x; break;
    case 4: r = 0;   g = 0;   b = 255; r += x; break;
    case 5: r = 255; g = 0;   b = 255; b -= x; break;
    }
    //return r + (g << 8) + (b << 16);
    return 255 + (b << 8) + (g << 16) + (r << 24);
}

void printArrayBar(int A[], int size, int r)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            //sound.stop();
            //window.close();
            exit(0);
        }
    }

    window.clear();
    for (int i = 0; i < size; i++)
    {
        //sf::RectangleShape rect;
        //rect.setFillColor(sf::Color::White);
        rect.setFillColor(sf::Color(rgb(double(A[i])/size)));		


        //rect.setSize(sf::Vector2f(1.0f, A[i] * 0.75f));
        //rect.setPosition(i, 768 - A[i]*0.75f);

        //rect.setSize(sf::Vector2f(1024.0f/size, A[i] * 768.0f/size));
        //rect.setPosition(i*(1024.0f/size), 768 - A[i] * 768.0f/size);

        rect.setSize(sf::Vector2f(x/size, A[i] * y/size));
        rect.setPosition(i*(x/size), y - A[i] * y/size);

        // static int r = 0;
        // r++;
        // if (r>1023) r=0; 

        if (i == r)
        {
            //rect.setFillColor(sf::Color::Red);
            rect.setFillColor(sf::Color::White);

            sound.setPitch(A[i] * 0.003f);
            sound.play();
        }
        window.draw(rect);
    }

    // text
    //std::string str1 = "Merge Sort\n";
    std::string str1 = strName + "\n";
    std::string str2 = "Numbers: " + std::to_string(vsize) + "\n\n";
    std::string str3 = "Comparisons: " + std::to_string(comp);
    std::string str = str1 + str2 + str3;;
    text.setString(str);
    window.draw(text);

    window.display();

    // NOTE: we get stuck in the loop/recursion for high usleep
    // Check if window open
    if (window.isOpen()) {
        usleep(20);
    }
}

// Sweeps the array after sort is finished
void sweep(int A[], int size)
{
    for (int j = 0; j < size; j++)
    {
        // Below is similar to printArrayBar but with green color
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                //sound.stop();
                //window.close();
                exit(0);
            }
        }

        window.clear();
        for (int i = 0; i < size; i++)
        {
            rect.setFillColor(sf::Color::White);

            rect.setSize(sf::Vector2f(x / size, A[i] * y / size));
            rect.setPosition(i * (x / size), y - A[i] * y / size);

            if (i < j)
            {
                rect.setFillColor(sf::Color::Green);
            }

            if (i == j)
            {
                rect.setFillColor(sf::Color::Red);

                sound.setPitch(A[i] * 0.003f);
                sound.play();
            }
            window.draw(rect);
        }
        window.draw(text);
        window.display();

        if (window.isOpen())
        {
            usleep(1000 * 1024.0f/vsize);
        }
    }
}


int main()
{
    
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    // define a 120x50 rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(1.0f, 200.0f));
    //rectangle.setFillColor(sf::Color::White);

    //std::vector<int> v(vsize); // vector with 100 ints.
    std::iota(std::begin(v), std::end(v), 0); // Fill with 0, 1, ..., 99.

    //v[0] = 1023;
    //v[66] = 1023;
    // for (int i = 0; i < v.size(); i++) {
    //     if (i<100) v[i] = 66;
    // }

    //shuffle(&v[0], v.size());


    auto rng = std::default_random_engine {};
    std::shuffle(v.begin(), v.end(), rng);

    //std::reverse(v.begin(), v.end());

    


    // std::vector<sf::RectangleShape> vrect;
    // for (int i=0; i<1024; i++) {
    //     //int i = 100;
    //     sf::RectangleShape rectangle(sf::Vector2f(1.0f, i*0.75f));
    //     rectangle.setFillColor(sf::Color::White);
    //     //rectangle.setPosition(i*(1024.0f/768.0f), 768-i);
    //     vrect.push_back(rectangle);
    // }

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

    // shuffle
    //auto rng = std::default_random_engine {};
    //std::shuffle(vrect.begin(), vrect.end(), rng);

    //std::random_device rd;
    //std::mt19937 g(rd());
    //std::shuffle(vrect.begin(), vrect.end(), g);

    // sound
    //sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav"))
        return -1;
    //sf::Sound sound;
    sound.setBuffer(buffer);

    // text
    if (!font.loadFromFile("Menlo.ttc"))
        return -1;
    text.setFont(font);
    text.setString("Merge Sort");
    //text.setFillColor(sf::Color::Green);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(18);
    text.setPosition(sf::Vector2f(20.0f, 10.0f));


    // TODO: Even though we catch all Closed events in all the sort loops and recursions
    // the app does not close immediately. Fix it.
    // It is probably caused by the sound playing on for 5 secs but sound.stop(); does
    // not solve it.
    // Hoewel, main4 sluit wel OK en ook daar hebben we sound. CocktailSort draait daar in
    // een while loop. Het is pas fout gegaan bij MergeSort met recursion.
    // NONO: het komt door usleep(2000000); tijdens de Transition.
    // Sowieso maakt dat de boel unresponsive tijdens de sleep maar ook na het sluiten
    // loopen we nog eenmaal door 3x usleep(2000000);
    // Snelle fix is om alleen usleep te doen als window open is, maar nog beter is een 
    // aparte delay functie te maken waarbij er constant wordt gecheckt naar verlopen tijd
    // en window close event.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                sound.stop();
                window.close();
                return 0;
            }
        }

        //window.clear();
        

        // NOTE: problem is we are in the game loop and have to do the sort loop as well.
        // So sort loop becomes game loop and we draw from the sort loop.
        // But now the window no longer closes correctly.
        // TODO: make window close correctly
        // DONE: put window.isOpen() check in CocktailSort() while loop

        // NOTE: usleep(2000000); during transition makes interface unresponsive.
        // TODO: do in a loop that checks time passed and does window.pollEvent(event)

        // NOTE: whenever we close the window we still fall through to the other sorts
        // and functions one more time.
        // Those will then immediately return because they check for window close but
        // the program will still take a longer time to respond to close.
        // TODO: exit program immediately upon close.
        // DONE: use exit(0);

        //bogo_sort(&v[0], v.size());
        //CocktailSort(&v[0], v.size());
goto start;
        // Prep
        v.resize(vsize = 1024);
        std::iota(std::begin(v), std::end(v), 0);
        std::shuffle(v.begin(), v.end(), rng); 
        strName = "Merge Sort";
        comp = 0;

        mergeSort(&v[0], 0, v.size()-1);

        // Transition
        sweep(&v[0], v.size());
        printArrayBar(&v[0], v.size(), -1);
        sound.stop();
        //usleep(2000000);
        udelay(2000000);

        // Prep
        v.resize(vsize = 111);
        std::shuffle(v.begin(), v.end(), rng); 
        strName = "Cocktail Sort";
        comp = 0;

        CocktailSort(&v[0], v.size());

        // Transition
        sweep(&v[0], v.size());
        printArrayBar(&v[0], v.size(), -1);
        sound.stop();
        //usleep(2000000);
        udelay(2000000);
//start:
        // Prep
        v.resize(vsize = 2048);
        std::iota(std::begin(v), std::end(v), 0);
        std::shuffle(v.begin(), v.end(), rng); 
        strName = "Quick Sort";
        comp = 0;

        quicksort(&v[0], 0, v.size()-1);

        // Transition
        sweep(&v[0], v.size());
        printArrayBar(&v[0], v.size(), -1);
        sound.stop();
        //usleep(2000000);
        udelay(2000000);
start:
        // Prep
        v.resize(vsize = 1024);
        std::iota(std::begin(v), std::end(v), 0);
        std::shuffle(v.begin(), v.end(), rng); 
        strName = "Wiki Sort";
        //printArrayBar(&v[0], v.size(), -1);
        //udelay(2000000);
        comp = 0;

        Comparison compare = TestCompare;
        WikiSort(&v[0], v.size(), compare);

        // Transition
        sweep(&v[0], v.size());
        printArrayBar(&v[0], v.size(), -1);
        sound.stop();
        //usleep(2000000);
        udelay(2000000);

        // and again
        // NOTE: keypress only works when running from terminal, not from debug
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        // {
        //     std::shuffle(v.begin(), v.end(), rng);            
        // }

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        // {
        //     std::reverse(v.begin(), v.end());
        // } else
        //     std::shuffle(v.begin(), v.end(), rng);  
        
        

        //window.display();
    }

    return 0;
}