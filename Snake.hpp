//
//  Kurve.hpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#ifndef Kurve_hpp
#define Kurve_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <utility>
#include <vector>
#include <list>
#include "Enum.h"
#include "Line.hpp"
const int POS_SAVING_DISTANCE = 2;
const double ANGLE_PER_FRAME = 2*PI/FPS;
const int NORMAL_SPEED_PER_FRAME = 5;

class Snake{
private:
    static std::vector<Snake*> snakesInGame;

    sf::Vector2f pos;
    std::vector<Line> lines;
    sf::CircleShape headCircle;
    sf::Color color;

    double angle;
    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;

    sf::Clock invisibleTimer;
    bool invisible;
    int numFramesInvisible;
    int framesToNextInvisible;

    bool crashed;
public:
    Snake();
    Snake(sf::Vector2f startPos, sf::Color _color, sf::Keyboard::Key _leftKey, sf::Keyboard::Key _rightKey, double _angle);
    ~Snake();

    void update(double const& timeElapsed);
    void draw(sf::RenderWindow& window);

    void turn(double timeElapsed);

    void updatePosition(double const& timeElapsed);
    void checkWhetherAddingPoint();
    void addPoint();
    bool DistanceEnoughToUpdate();

    void setCrashStatus();
    bool checkForCrash(sf::Vector2f const &headPosition, float const &headThickness, int const &numNeckPointsToIgnore)const;

    void updateInvisibleStatus();

    int setupNextInvisible();
    void startNewLine();

    sf::Vector2f getLastPoint(){return lines.back().getLastPointOnLine();}
    sf::Keyboard::Key getRightKey(){return rightKey;}
    sf::Keyboard::Key getLeftKey(){return leftKey;}
};
#endif /* Kurve_hpp */

