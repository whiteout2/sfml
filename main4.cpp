#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <random>


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
                //printArrayBar(a, arr_size, 0, 0, i);
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
                //printArrayBar(a, arr_size, 0, 0, i);
                swapped = true;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    // define a 120x50 rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(1.0f, 200.0f));
    //rectangle.setFillColor(sf::Color::White);

    std::vector<int> v(1024) ; // vector with 100 ints.
    std::iota(std::begin(v), std::end(v), 0); // Fill with 0, 1, ..., 99.

    //auto rng = std::default_random_engine {};
    //std::shuffle(v.begin(), v.end(), rng); // buggy!!!


    std::vector<sf::RectangleShape> vrect;
    for (int i=0; i<1024; i++) {
        //int i = 100;
        sf::RectangleShape rectangle(sf::Vector2f(1.0f, i*0.75f));
        rectangle.setFillColor(sf::Color::White);
        //rectangle.setPosition(i*(1024.0f/768.0f), 768-i);
        vrect.push_back(rectangle);
    }

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

    // shuffle
    //auto rng = std::default_random_engine {};
    //std::shuffle(vrect.begin(), vrect.end(), rng);

    //std::random_device rd;
    //std::mt19937 g(rd());
    //std::shuffle(vrect.begin(), vrect.end(), g);

    

    // sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav"))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //sf::View view = window.getDefaultView();
        //view.setSize(1024, -1024); 
        //window.setView(view);

        static int r = 0;
        r++;
        if (r>1023) r=0; 

        //window.draw(rectangle);
        for (int i=0; i<1024; i++) {
            //vrect[i].setPosition(i*(1024.0f/768.0f), 768-i);
            //vrect[i].setPosition(i*(1024.0f/768.0f), 0);
            //vrect[i].setPosition(i*(1024.0f/768.0f)*0.75f, 768-vrect[i].getSize().y);
            vrect[i].setSize(sf::Vector2f(1.0f, v[666]*0.75f)); // leaks mem???
            vrect[i].setPosition(v[666]*(1024.0f/768.0f)*0.75f, 0);

            rect.setSize(sf::Vector2f(1.0f, v[i]*0.75f)); // leaks mem???
            rect.setPosition(v[i]*(1024.0f/768.0f)*0.75f, 0);
            rect.setFillColor(sf::Color::White);
            if (i==r) {
                vrect[i].setFillColor(sf::Color::Red);
                if(i==0) vrect[1023].setFillColor(sf::Color::White);
                else vrect[i-1].setFillColor(sf::Color::White);

                rect.setFillColor(sf::Color::Red);
                
                sound.setPitch(vrect[i].getSize().y*0.001f);
                //sound.play();
            }
            //window.draw(vrect[i]);
            window.draw(rect);
        }
        //for (sf::RectangleShape n : vrect) {
        //    window.draw(n);
        //}

        CocktailSort(&v[0], 1024);

        window.display();
    }

    return 0;
}