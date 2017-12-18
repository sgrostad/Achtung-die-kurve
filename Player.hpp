//
//  Player.hpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Enum.hpp"
class Player {
private:
    sf::Color playerColor;
    Snake snake;
public:
    Player(sf::Color playerColor);
    Player(sf::Vector2f startPos, sf::Color _color, sf::Keyboard::Key _leftKey, sf::Keyboard::Key _rightKey, double _angle);

    void update(double timeElapsed);
    void draw(sf::RenderWindow &window);

    void addLevelUp(LevelUp const &levelUp){ snake.addLevelUp(levelUp);}

    sf::Vector2f getPosition(){ return snake.getLastPoint();}
    float getCurrentThickness(){ return snake.getCurrentThickness();}
};
#endif /* Player_hpp */

