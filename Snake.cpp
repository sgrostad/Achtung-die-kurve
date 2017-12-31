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
#include "WindowSpec.hpp"
std::list<Snake*> Snake::snakesInGame;
Snake::Snake() : crashed(false), openWalls(false){
    color = sf::Color::Red;
    pos = sf::Vector2f(100,100);
    angle = 0;
    speed = NORMAL_SPEED_PER_FRAME;
    headCircle.setOrigin(NORMAL_THICKNESS,NORMAL_THICKNESS); headCircle.setRadius(NORMAL_THICKNESS); headCircle.setPosition(pos); headCircle.setFillColor(color);
    leftKey = sf::Keyboard::Left;
    rightKey = sf::Keyboard::Right;
    setupNextInvisible();
    startNewLine(NORMAL_THICKNESS);
    snakesInGame.push_back(this);
}

Snake::Snake(sf::Vector2f startPos, sf::Color _color, sf::Keyboard::Key _leftKey, sf::Keyboard::Key _rightKey, double _angle) :
        pos(startPos), color(_color), leftKey(_leftKey), rightKey(_rightKey), angle(_angle), crashed(false), speed(NORMAL_SPEED_PER_FRAME),
        openWalls(true) {
    headCircle.setOrigin(NORMAL_THICKNESS,NORMAL_THICKNESS); headCircle.setRadius(NORMAL_THICKNESS); headCircle.setPosition(pos); headCircle.setFillColor(color);
    setupNextInvisible();
    startNewLine(NORMAL_THICKNESS);
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
    //std::cout<< "x: " << pos.x << ", y: "<<pos.y<<std::endl;
    if (!crashed){
        this->turn(timeElapsed);
        this->updatePosition(timeElapsed);
        this->updateInvisibleStatus();
        this->removeLevelUps();
        if (!invisible){
            this->checkWhetherAddingPoint();
            this->setCrashStatus();
        }
    }
}

void Snake::draw(sf::RenderWindow &window) const {
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
    pos.x += speed * cos(angle) * timeElapsed;
    pos.y -= speed * sin(angle) * timeElapsed;
    headCircle.setPosition(pos);
}

void Snake::checkWhetherAddingPoint(){
    if (DistanceEnoughToUpdate()){
        this->addPoint();
    }
}

void Snake::addPoint(){
    lines.front().addPoint(pos);
    headCircle.setPosition(pos);
}

bool Snake::DistanceEnoughToUpdate() const {
    return Distance(pos, lines.front().getLastPointOnLine()) > POS_SAVING_DISTANCE;
}

void Snake::setCrashStatus(){
    sf::Vector2f headPosition = this->getLastPoint();
    if (this->checkForWallCrash()){
        this->setCrashed(true);
        this->addPoint();
    }
    for(auto it = snakesInGame.begin(); it != snakesInGame.end(); it++){
        if (this == *it){
            this->setCrashed( (*it)->checkForSelfCrash(headPosition, this->getCurrentThickness()) );
        } else {
            this->setCrashed( (*it)->checkForEnemyCrash(headPosition, this->getCurrentThickness()) );
        }
        if (crashed){
            this->addPoint();
            return;
        }
    }
}

bool Snake::checkForEnemyCrash(sf::Vector2f const &headPosition, float const &headThickness) const {//Called from another snake
    for(auto it = lines.begin(); it != lines.end(); it++){
        if(it->crashedWithThisLine(headPosition, headThickness, false)){
            return true;
        }
    }
    return false;
}

bool Snake::checkForSelfCrash(const sf::Vector2f &headPosition, const float &headThickness) const{
    bool neckCheck = true;
    for(auto it = lines.begin(); it != lines.end(); it++){
        if(it->crashedWithThisLine(headPosition, headThickness, neckCheck)){
            return true;
        }
        if (neckCheck && it->headContainsWholeLine(headPosition, headThickness)){
            neckCheck = true;
        } else {
            neckCheck = false;
        }
    }
    return false;
}

bool Snake::checkForWallCrash(){
    int boardWidth = WindowSpec::windowWidth;
    int boardHeight = WindowSpec::windowHeight;
    float headThickness = this->getCurrentThickness();
    if(pos.x - headThickness < 0 || pos.x + headThickness > boardWidth ||
       pos.y - headThickness < 0 || pos.y + headThickness > boardHeight){
        if(!openWalls){
            return true;
        } else {
            this->goThroughWall();
        }
    }
    return false;
}

void Snake::goThroughWall() {
    int boardWidth = WindowSpec::windowWidth;
    int boardHeight = WindowSpec::windowHeight;
    float headThickness = this->getCurrentThickness();
    bool positionChanged = false;
    if (pos.x < 0){
        pos.x += boardWidth;
        positionChanged = true;
    } else if (pos.x > boardWidth){
        pos.x -= boardWidth;
        positionChanged = true;
    }
    if (pos.y < 0){
        pos.y += boardHeight;
        positionChanged = true;
    } else if (pos.y > boardHeight) {
        pos.y -= boardHeight;
        positionChanged = true;
    }
    if (positionChanged){
        this->startNewLine(headThickness);
    }
}

void Snake::addLevelUp(LevelUp const &levelUp) {
    if(levelUp.isEnemiesLevelUp()){ //TODO check if it everything works when enemies get level up
        for(auto it = this->snakesInGame.begin(); it != this->snakesInGame.end(); it++){
            if( (*it) != this ){
                (*it)->levelUps.push_back(&levelUp);
                (*it)->startLevelUp(levelUp.getLevelUpType());
            }
        }
    }
    else {
        levelUps.push_back(&levelUp);
        this->startLevelUp(levelUp.getLevelUpType());
    }
}

void Snake::startLevelUp(LevelUpType levelUpType) { //TODO add all cases
    sf::Keyboard::Key tempKey;
    switch(levelUpType){
        case SPEED_FAST:
            speed = speed + SPEED_LEVEL_UP_INCREMENT;
            break;
        case SPEED_SLOW:
            speed = speed - SPEED_LEVEL_UP_INCREMENT;
            break;
        case FAT:
            this->setCurrentThickness(this->getCurrentThickness() + WIDTH_LEVEL_UP_INCREMENT);
            break;
        case THIN:
            this->setCurrentThickness(this->getCurrentThickness() - WIDTH_LEVEL_UP_INCREMENT);
            break;
        case REVERSE_CONTROLS:
            tempKey = this->rightKey;
            this->rightKey = this->leftKey;
            this->leftKey = tempKey;
            break;
        case OPEN_WALLS:
            this->openWalls = true;
            break;
        case INVISIBLE:
            std::cout << "INVISIBLE" << std::endl;
            break;
        default:
            std::cout<<"Should not end up here when starting LevelUp "<< levelUpType << std::endl;
            //exit(1);
    }
}

void Snake::removeLevelUps() {
    for(auto it = levelUps.begin(); it != levelUps.end();){
        if((*it)->timeToDeactivate()){
            stopLevelUp((*it)->getLevelUpType());
            it = levelUps.erase(it);
        } else{
            it++;
        }
    }
}

void Snake::stopLevelUp(LevelUpType levelUpType) { //TODO add all cases
    sf::Keyboard::Key tempKey;
    switch(levelUpType){
        case SPEED_FAST:
            speed = speed - SPEED_LEVEL_UP_INCREMENT;
            break;
        case SPEED_SLOW:
            speed = speed + SPEED_LEVEL_UP_INCREMENT;
            break;
        case FAT:
            this->setCurrentThickness(this->getCurrentThickness() - WIDTH_LEVEL_UP_INCREMENT);
            break;
        case THIN:
            this->setCurrentThickness(this->getCurrentThickness() + WIDTH_LEVEL_UP_INCREMENT);
            break;
        case REVERSE_CONTROLS:
            tempKey = this->rightKey;
            this->rightKey = this->leftKey;
            this->leftKey = tempKey;
            break;
        case OPEN_WALLS:
            this->openWalls = false;
            break;
        case INVISIBLE:
            std::cout << "INVISIBLE" << std::endl;
            break;
        default:
            std::cout<<"Should not end up here when stopping LevelUp"<<std::endl;
            //exit(1);
    }
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
        startNewLine(this->getCurrentThickness());
    }
}

void Snake::setupNextInvisible(){
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

void Snake::startNewLine(double thickness){
    lines.push_front(Line(thickness,color));
    lines.front().addPoint(pos);
}

void Snake::setCurrentThickness(float thickness) {
    this->startNewLine(thickness);
    headCircle.setRadius(thickness);
    headCircle.setOrigin(thickness,thickness);
}
void Snake::printLines() {
    for (auto line : lines){
        std::cout<<line.printLine()<<std::endl;
    }
}
