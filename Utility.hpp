//
//  Utility.hpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 04/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <list>

double Norm2(sf::Vector2f const& vec);
sf::Vector2f GetUnitVec(sf::Vector2f vec);
double Distance(sf::Vector2f vec1, sf::Vector2f vec2);
int RandomInt(int min, int max);
sf::Vector2f RandomVec(sf::Vector2f min, sf::Vector2f max);
double Average(double val1, double val2);
bool CircleCrashedWithLine(sf::Vector2f const &position, float const &circleRadius, std::list< sf::Vector2f > const &line, int const &lineThickness);
float Max(float const &val1, float const &val2);
#endif /* Utility_hpp */

