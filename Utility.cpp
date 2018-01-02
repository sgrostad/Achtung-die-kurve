//
//  Utility.cpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 04/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#include "Utility.hpp"
#include <math.h>
#include <iostream>
#include <list>

#include "Enum.hpp"

double Norm2(sf::Vector2f const& vec){
    return sqrt( pow(vec.x,2) + pow(vec.y, 2) );
}

sf::Vector2f GetUnitVec(sf::Vector2f vec){
    double norm = Norm2(vec);
    return sf::Vector2f(vec.x/norm, vec.y/norm);
}

double Distance(sf::Vector2f vec1, sf::Vector2f vec2){
    return sqrt(pow(vec1.x-vec2.x, 2) + pow(vec1.y-vec2.y, 2));
}

int RandomInt(int min, int max){ //including min and max
    return rand() % (max-min+1) + min;
}

sf::Vector2f RandomVec(sf::Vector2f min, sf::Vector2f max){
    return sf::Vector2f(RandomInt(min.x, max.x), RandomInt(min.y, max.y));
}

double Average(double val1, double val2){
    return (val1 + val2) / 2;
}

bool CircleCrashedWithLine(sf::Vector2f const &position, float const &circleRadius, std::list< sf::Vector2f > const &line, int const &lineThickness){
    for(auto it = line.begin(); it != line.end(); it++){
        if( Distance(position, *it) <= circleRadius + lineThickness){
            return true;
        }
    }
    return false;
}

float Max(float const &val1, float const &val2){
    if (val1 > val2){
        return val1;
    }
    return val2;
}
