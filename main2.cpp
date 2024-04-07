#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    // define a 120x50 rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(1.0f, 200.0f));
    //rectangle.setFillColor(sf::Color::White);
    std::vector<sf::RectangleShape> vrect;
    for (int i=0; i<1024; i++) {
        //int i = 100;
        sf::RectangleShape rectangle(sf::Vector2f(1.0f, i*0.75f));
        rectangle.setFillColor(sf::Color::White);
        //rectangle.setPosition(i*(1024.0f/768.0f), 768-i);
        vrect.push_back(rectangle);
    }

    auto rng = std::default_random_engine {};
    std::shuffle(vrect.begin(), vrect.end(), rng);

    //std::random_device rd;
    //std::mt19937 g(rd());
    //std::shuffle(vrect.begin(), vrect.end(), g);


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
            vrect[i].setPosition(i*(1024.0f/768.0f), 768-vrect[i].getSize().y);
            if (i==r) {
                vrect[i].setFillColor(sf::Color::Red);
                vrect[i-1].setFillColor(sf::Color::White);
            }
            window.draw(vrect[i]);
        }
        //for (sf::RectangleShape n : vrect) {
        //    window.draw(n);
        //}

        window.display();
    }

    return 0;
}