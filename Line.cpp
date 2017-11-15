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
    line.push_back(point);
    if (line.size() > 1){
        sf::Vector2f unitVec = line[line.size()-1]-line[line.size()-2];
        unitVec = GetUnitVec(unitVec);
        sf::Vector2f u(unitVec.y, -unitVec.x);
        // TODO: Check which order is correct
        vertexArray.append( sf::Vertex(u*thickness+line[line.size()-2], color) );
        vertexArray.append( sf::Vertex(-u*thickness+line[line.size()-2], color) );
        vertexArray.append( sf::Vertex(u*thickness+line[line.size()-1], color) );
        vertexArray.append( sf::Vertex(-u*thickness+line[line.size()-1], color) );
    }
}
/*
 bool Line::crashedWithThisLine(sf::Vector2f const &headPosition, const float &headThickness, int const &numNeckPointsToIgnore){
 for(int i = line.size() - 1 - numNeckPointsToIgnore; i >= 0; i--){
 if(Distance(headPosition, line[i]) <= headThickness + thickness){
 return true;
 }
 }
 return false;
 }*/

bool Line::crashedWithThisLine(sf::Vector2f const &headPosition, const float &headThickness, int const &numNeckPointsToIgnore) const{
    std::vector< sf::Vector2f > tempLine = line;
    if(numNeckPointsToIgnore > line.size()){
        return false;
    }
    tempLine.resize(line.size() - numNeckPointsToIgnore);
    return CircleCrashedWithLine(headPosition, headThickness, tempLine, thickness);
}

void Line::clear(){
    vertexArray.clear();
    line.clear();
}

void Line::draw(sf::RenderWindow& window){
    window.draw(vertexArray);
}


