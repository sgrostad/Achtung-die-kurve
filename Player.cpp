//
//  Player.cpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#include "Player.hpp"
#include <utility>
Player::Player(sf::Color playerColor) : playerColor(playerColor){}

Player::Player(sf::Vector2f startPos, sf::Color _color, sf::Keyboard::Key _leftKey, sf::Keyboard::Key _rightKey, double _angle) :
        playerColor(_color), snake(Snake(startPos, _color, _leftKey, _rightKey, _angle)){}

void Player::update(double timeElapsed){
    snake.update(timeElapsed);
}

void Player::draw(sf::RenderWindow &window){
    snake.draw(window);
}


