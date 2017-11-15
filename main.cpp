
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "WindowSpec.hpp"
#include "Player.hpp"

int main(int, char const**)
{
    srand(time(nullptr));
    WindowSpec windowSpec;
    sf::RenderWindow window(windowSpec.getVideoMode(),windowSpec.getWindowName(),sf::Style::Fullscreen);
    std::list<GameObject*> gameobjects;
    //gameobjects.push_back();
    gameobjects.push_back(new Player(sf::Vector2f(100,100), sf::Color::Red, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, 0));
    gameobjects.push_back(new Player(sf::Vector2f(100,400), sf::Color::Blue, sf::Keyboard::Key::A, sf::Keyboard::Key::D, 0));
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    double lastTime = time.asMicroseconds();//System.nanoTime();
    double delta = 0.0;
    const double MICRO_SECONDS_PER_PHOTO = 1000000.0 / FPS;
    double timer = time.asMilliseconds();//System.currentTimeMillis();
    int updates = 0;
    int frames = 0;
    // Start the game loop
    while (window.isOpen()) {
        time = clock.getElapsedTime();
        double timeNow = time.asMicroseconds();
        delta += (timeNow - lastTime) / MICRO_SECONDS_PER_PHOTO;
        double timeElapsed = (timeNow - lastTime) / MICRO_SECONDS_PER_PHOTO;
        lastTime = timeNow;
        for(auto gameobject : gameobjects){
            gameobject->update(timeElapsed);
        }
        updates++;
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }
        if (delta >= 1.0) {
            // Clear screen
            window.clear();
            for(auto gameobject : gameobjects){
                gameobject->draw(window);
            }
            // Update the window
            window.display();
            frames++;
            delta--;
        }
        time = clock.getElapsedTime();
        if (time.asMilliseconds() - timer > 1000) {
            timer += 1000;
            std::cout<< updates << " ups, " << frames << " fps"<<std::endl;
            updates = 0;
            frames = 0;
        }



    }

    return EXIT_SUCCESS;
}

/*
 // Set the Icon
 sf::Image icon;
 if (!icon.loadFromFile(resourcePath() + "icon.png")) {
 return EXIT_FAILURE;
 }
 window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
 
 // Load a sprite to display
 sf::Texture texture;
 if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
 return EXIT_FAILURE;
 }
 sf::Sprite sprite(texture);
 
 // Create a graphical text to display
 sf::Font font;
 if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
 return EXIT_FAILURE;
 }
 sf::Text text("Hello SFML", font, 50);
 text.setColor(sf::Color::Black);
 // Load a music to play
 sf::Music music;
 if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
 return EXIT_FAILURE;
 }
 
 // Play the music
 music.play();
 
 // Draw the sprite
 window.draw(sprite);
 
 // Draw the string
 window.draw(text);
 */

