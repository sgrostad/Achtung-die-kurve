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
#include "Enum.hpp"
#include "Line.hpp"
#include "LevelUp.hpp"

const int POS_SAVING_DISTANCE = 2;
const double ANGLE_PER_FRAME = 2*PI/FPS;
const double NORMAL_SPEED_PER_FRAME = 5.0;
const float SPEED_LEVEL_UP_INCREMENT = 3;
const float WIDTH_LEVEL_UP_INCREMENT = 5;

class Snake{
private:
    static std::list<Snake*> snakesInGame;

    sf::Vector2f pos;
    std::list<Line> lines;
    sf::CircleShape headCircle;
    sf::Color color;

    double angle;
    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;

    double speed;

    std::list<const LevelUp*> levelUps;
    bool openWalls;

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
    void draw(sf::RenderWindow& window) const;

    void turn(double timeElapsed);

    void updatePosition(double const& timeElapsed);
    void checkWhetherAddingPoint();
    void addPoint();
    bool DistanceEnoughToUpdate() const;

    void setCrashStatus();
    bool checkForEnemyCrash(sf::Vector2f const &headPosition, float const &headThickness)const;
    bool checkForSelfCrash(sf::Vector2f const &headPosition, float const &headThickness) const;
    bool checkForWallCrash();
    void goThroughWall();

    void addLevelUp(LevelUp const &levelUp);
    bool startLevelUp(LevelUpType levelUpType);
    void removeLevelUps();
    void stopLevelUp(LevelUpType levelUpType);
    void clearBoard();

    void updateInvisibleStatus();
    void setupNextInvisible();
    void becomeInvisible();
    void startNewLine(double thickness);

    sf::Vector2f getLastPoint(){return lines.front().getLastPointOnLine();}
    float getCurrentThickness(){return headCircle.getRadius();}
    bool setCurrentThickness(float thickness);
    sf::Keyboard::Key getRightKey(){return rightKey;}
    sf::Keyboard::Key getLeftKey(){return leftKey;}
    void setCrashed(bool crashed){this->crashed = crashed;}

};
#endif /* Kurve_hpp */

