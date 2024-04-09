#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>


// executes in-place bogo sort on a given array
static void bogo_sort(int* a, int size);
// returns 1 if given array is sorted and 0 otherwise
static int is_sorted(int* a, int size);
// shuffles the given array into a random order
static void shuffle(int* a, int size);


void printArrayBar(int A[], int size, int r);

int vsize = 1024;

int comp = 0;

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


///////////////////////////////////////
void bogo_sort(int* a, int size) {
    while (!is_sorted(a, size) && window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                printArrayBar(a, n, i+1);
                swapped = true;
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
            window.close();
            //return;
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
                window.close();
                //return;
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


void printArrayBar(int A[], int size, int r)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
            //return;
        }
    }

    window.clear();
    for (int i = 0; i < size; i++)
    {
        //sf::RectangleShape rect;
        rect.setFillColor(sf::Color::White);

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
            rect.setFillColor(sf::Color::Red);

            sound.setPitch(A[i] * 0.01f);
            sound.play();
        }
        window.draw(rect);
    }

    // text
    std::string str1 = "Merge Sort\n";
    std::string str2 = "Numbers: " + std::to_string(vsize) + "\n\n";
    std::string str3 = "Comparisons: " + std::to_string(comp);
    std::string str = str1 + str2 + str3;;
    text.setString(str);
    window.draw(text);

    window.display();

    // NOTE: we get stuck in the loop/recursion for high usleep
    // Check if window open
    if (window.isOpen()) {
        usleep(2000);
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
            if (event.type == sf::Event::Closed)
            {
                window.close();
                // return;
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

                sound.setPitch(A[i] * 0.01f);
                sound.play();
            }
            window.draw(rect);
        }
        window.draw(text);
        window.display();

        if (window.isOpen())
        {
            usleep(1000);
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

    std::vector<int> v(vsize); // vector with 100 ints.
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
    text.setFillColor(sf::Color::Green);
    text.setCharacterSize(18);
    text.setPosition(sf::Vector2f(20.0f, 10.0f));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
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

        //bogo_sort(&v[0], v.size());
        //CocktailSort(&v[0], v.size());
        mergeSort(&v[0], 0, v.size()-1);

        sweep(&v[0], v.size());
        
        printArrayBar(&v[0], v.size(), -1);
        sound.stop();
        //usleep(2000000);

    
        comp = 0;

        // and again
        // NOTE: keypress only works when running from terminal, not from debug
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            std::shuffle(v.begin(), v.end(), rng);            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            std::reverse(v.begin(), v.end());
        } else
            std::shuffle(v.begin(), v.end(), rng);  
        
        

        //window.display();
    }

    return 0;
}