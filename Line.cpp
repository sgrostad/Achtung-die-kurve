//
//  Line.cpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 04/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#include "Line.hpp"
#include "Utility.hpp"
#include <iostream>
Line::Line(){
    thickness = NORMAL_THICKNESS;
    vertexArray.setPrimitiveType(sf::TrianglesStrip);
    color = sf::Color::Blue;
}

Line::Line(double const& _thickness, sf::Color const& _color) : thickness(_thickness), color(_color) {
    vertexArray.setPrimitiveType(sf::TrianglesStrip);
}

void Line::addPoint(sf::Vector2f const& point){
    sf::Vector2f secondLast = line.front();
    line.push_front(point);
    sf::Vector2f last = line.front();
    if (line.size() > 1){
        sf::Vector2f unitVec = last-secondLast;
        unitVec = GetUnitVec(unitVec);
        sf::Vector2f u(unitVec.y, -unitVec.x);
        vertexArray.append( sf::Vertex(u*thickness+secondLast, color) );
        vertexArray.append( sf::Vertex(-u*thickness+secondLast, color) );
        vertexArray.append( sf::Vertex(u*thickness+last, color) );
        vertexArray.append( sf::Vertex(-u*thickness+last, color) );
    }
}

bool Line::crashedWithThisLine(sf::Vector2f const &headPosition, const float &headThickness, bool neckCheck) const{
    std::list< sf::Vector2f > tempLine = line;
    if (neckCheck){
        float delta = 1.0;
        for (auto it = tempLine.begin(); it != tempLine.end(); ){
            float maxThickness = Max(headThickness, thickness);
            if (Distance(*it, headPosition) < 2 * maxThickness + delta){
                it = tempLine.erase(it);
            }
            else{
                break;
            }
        }
    }
    return CircleCrashedWithLine(headPosition, headThickness, tempLine, thickness);
}

bool Line::headContainsWholeLine(sf::Vector2f const &headPosition, const float &headThickness) const {
    float delta = 1.0;
    for (auto it = line.begin(); it != line.end(); it++){
        if (Distance(*it, headPosition) > headThickness + thickness + delta){
            return false;
        }
    }
    return true;
}

void Line::clear(){
    vertexArray.clear();
    line.clear();
}

void Line::draw(sf::RenderWindow& window){
    sf::CircleShape endPoints(thickness);
    endPoints.setFillColor(color);
    endPoints.setOrigin(thickness, thickness);
    endPoints.setPosition(line.front());
    window.draw(endPoints);
    endPoints.setPosition(line.back());
    window.draw(endPoints);
    window.draw(vertexArray);
}


