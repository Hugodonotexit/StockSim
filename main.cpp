#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>

using namespace sf;

int main() {
    //Window
    RenderWindow window(VideoMode(1920,1080), "Stock Sim", Style::Fullscreen);
    Event ev;

    //Game loop
    while (window.isOpen())
    {
        srand(time(nullptr));

        //Event polling
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case Event::Closed:
                window.close();
                break;
            
            case Event::KeyPressed:
                switch (ev.key.code)
                {
                case Keyboard::Escape:
                    window.close();
                    break;
                }
            }
        }

        //Update

        //Render
        window.clear(Color(125,192,45)); //Clear old frame (start drawing)

        window.display(); //Display frame (done drawing)
    }
    

    return 0;
}