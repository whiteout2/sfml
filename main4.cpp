#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");


// sound
sf::SoundBuffer buffer;
sf::Sound sound;


void bogo_sort(int* a, int size) {
    while (!is_sorted(a, size)) {
        
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


// See: https://www.geeksforgeeks.org/cocktail-sort/
void CocktailSort(int a[], int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;
 
    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;
 
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


void printArrayBar(int A[], int size, int r)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();
    for (int i = 0; i < 1024; i++)
    {
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::White);

        rect.setSize(sf::Vector2f(1.0f, A[i] * 0.75f));
        //rect.setPosition(i * (1024.0f / 768.0f) * 0.75f, 0);
        rect.setPosition(i * (1024.0f / 768.0f) * 0.75f, 768 - A[i]*0.75f);
        //rect.setFillColor(sf::Color::White);

        // static int r = 0;
        // r++;
        // if (r>1023) r=0; 

        if (i == r)
        {
            rect.setFillColor(sf::Color::Red);
            //rect.setSize(sf::Vector2f(33.0f, A[i] * 0.75f));

            // sound.setPitch(vrect[i].getSize().y*0.001f);
            sound.setPitch(rect.getSize().y * 0.1f);
            sound.play();
        }
        window.draw(rect);
    }
    window.display();
    //usleep(2000);
}

int main()
{
    
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    // define a 120x50 rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(1.0f, 200.0f));
    //rectangle.setFillColor(sf::Color::White);

    std::vector<int> v(1024) ; // vector with 100 ints.
    std::iota(std::begin(v), std::end(v), 0); // Fill with 0, 1, ..., 99.
    //v[0] = 1023;
    //v[666] = 1023;

    shuffle(&v[0], 1024);


    //auto rng = std::default_random_engine {};
    //std::shuffle(v.begin(), v.end(), rng); // buggy!!!
    


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

    

    


    while (window.isOpen())
    {
        // sf::Event event;
        // while (window.pollEvent(event))
        // {
        //     if (event.type == sf::Event::Closed)
        //         window.close();
        // }

        //window.clear();

        // NOTE: problem is we are in the game loop and have to do the sort loop as well
        //bogo_sort(&v[0], 1024);
        CocktailSort(&v[0], 1024);

        //window.display();
    }

    return 0;
}