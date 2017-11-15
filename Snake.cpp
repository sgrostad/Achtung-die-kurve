//
//  Kurve.cpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#include "Snake.hpp"
#include <math.h>
#include <iostream>
#include "Utility.hpp"
std::vector<Snake*> Snake::snakesInGame;
Snake::Snake() : crashed(false){
    color = sf::Color::Red;
    pos = sf::Vector2f(100,100);
    angle = 0;
    tailCircle.setFillColor(color); tailCircle.setOrigin(NORMAL_THICKNESS,NORMAL_THICKNESS); tailCircle.setRadius(NORMAL_THICKNESS); tailCircle.setPosition(pos);
    headCircle.setOrigin(NORMAL_THICKNESS,NORMAL_THICKNESS); headCircle.setRadius(NORMAL_THICKNESS); headCircle.setPosition(pos); headCircle.setFillColor(color);
    leftKey = sf::Keyboard::Left;
    rightKey = sf::Keyboard::Right;
    setupNextInvisible();
    startNewLine();
    snakesInGame.push_back(this);
}

Snake::Snake(sf::Vector2f startPos, sf::Color _color, sf::Keyboard::Key _leftKey, sf::Keyboard::Key _rightKey, double _angle) : pos(startPos), color(_color), leftKey(_leftKey), rightKey(_rightKey), angle(_angle), crashed(false){
    tailCircle.setFillColor(color); tailCircle.setOrigin(NORMAL_THICKNESS,NORMAL_THICKNESS); tailCircle.setRadius(NORMAL_THICKNESS); tailCircle.setPosition(pos);
    headCircle.setOrigin(NORMAL_THICKNESS,NORMAL_THICKNESS); headCircle.setRadius(NORMAL_THICKNESS); headCircle.setPosition(pos); headCircle.setFillColor(color);
    setupNextInvisible();
    startNewLine();
    snakesInGame.push_back(this);
}

Snake::~Snake(){
    for (auto it = snakesInGame.begin(); it != snakesInGame.end(); it++){
        if (*it == this){
            snakesInGame.erase(it);
        }
    }
}

void Snake::update(double const& timeElapsed){
    if (!crashed){
        turn(timeElapsed);
        updatePosition(timeElapsed);
        updateInvisibleStatus();
        if (!invisible){
            checkWhetherAddingPoint();
            setCrashStatus();
        }
    }
}

void Snake::draw(sf::RenderWindow &window){
    window.draw(tailCircle);
    window.draw(headCircle);
    for(auto line : lines){
        line.draw(window);
    }
}

void Snake::turn(double timeElapsed){
    if (sf::Keyboard::isKeyPressed(leftKey)){
        angle += ANGLE_PER_FRAME * timeElapsed;
    }
    if (sf::Keyboard::isKeyPressed(rightKey)){
        angle -= ANGLE_PER_FRAME * timeElapsed;
    }
}

void Snake::updatePosition(double const& timeElapsed){
    pos.x += NORMAL_SPEED_PER_FRAME * cos(angle) * timeElapsed;
    pos.y -= NORMAL_SPEED_PER_FRAME * sin(angle) * timeElapsed;
    headCircle.setPosition(pos);
}

void Snake::checkWhetherAddingPoint(){
    if (DistanceEnoughToUpdate()){
        this->addPoint();
    }
}

void Snake::addPoint(){
    lines.back().addPoint(pos);
    headCircle.setPosition(pos);
}

bool Snake::DistanceEnoughToUpdate(){
    return Distance(pos, lines.back().getLastPointOnLine()) > POS_SAVING_DISTANCE;
}

void Snake::setCrashStatus(){
    sf::Vector2f headPosition = this->getLastPoint();
    int numNeckPointsToIgnore;
    for(auto it = snakesInGame.begin(); it != snakesInGame.end(); it++){
        if (this == *it && headPosition == (*it)->getLastPoint()){
            //Calculated number to avoid false self crash:
            numNeckPointsToIgnore =  PI * NORMAL_SPEED_PER_FRAME / (ANGLE_PER_FRAME * POS_SAVING_DISTANCE * 4);
        }
        else{
            numNeckPointsToIgnore = 0;
        }
        if ((*it)->checkForCrash(headPosition, lines.back().getThickness()/*Make member variable in snake*/, numNeckPointsToIgnore)){
            crashed = true;
            this->addPoint();
            return;
        }
    }
}

bool Snake::checkForCrash(const sf::Vector2f &headPosition, const float &headThickness, int const &numNeckPointsToIgnore) const{ //Called from another snake
    for(auto it = lines.begin(); it != lines.end(); it++){
        if(it->crashedWithThisLine(headPosition, headThickness, numNeckPointsToIgnore)){
            return true;
        }
    }
    return false;
}

void Snake::updateInvisibleStatus(){
    sf::Time time = invisibleTimer.getElapsedTime();
    int FramesSinceRestart = time.asSeconds() * FPS;
    if (FramesSinceRestart < (framesToNextInvisible) ){
        invisible = false;
    }
    else if (FramesSinceRestart < (framesToNextInvisible + numFramesInvisible) ){
        invisible = true;
    }
    else{ //Not invisible more
        setupNextInvisible();
        startNewLine();
    }
}


int Snake::setupNextInvisible(){
    invisibleTimer.restart();
    invisible = false;
    int minNumFramesInvisible = 4;
    int maxNumFramesInvisible = 12;
    int reduceChanceForLongInvisible = RandomInt(1, 3);
    numFramesInvisible = RandomInt(minNumFramesInvisible, maxNumFramesInvisible);
    if (numFramesInvisible > Average(minNumFramesInvisible,maxNumFramesInvisible)){
        numFramesInvisible /= reduceChanceForLongInvisible;
    }
    int minFramesToInvisible = 10;
    int maxFramesToInvisible = 160;
    framesToNextInvisible = RandomInt(minFramesToInvisible, maxFramesToInvisible);
}

void Snake::startNewLine(){
    lines.push_back(Line(NORMAL_THICKNESS,color));
    lines.back().addPoint(pos);
}

