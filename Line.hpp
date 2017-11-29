//
//  Line.hpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 04/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
const int NORMAL_THICKNESS = 4;
class Line{
private:
    float thickness;
    std::vector< sf::Vector2f > line;
    sf::VertexArray vertexArray;
    sf::Color color;
public:
    Line();
    Line(double const& _thickness, sf::Color const& _color);

    void addPoint(sf::Vector2f const& point);

    bool crashedWithThisLine(sf::Vector2f const &headPosition, const float &headThickness, int const &numNeckPointsToIgnore)const;

    sf::Vector2f getLastPointOnLine() const {return line.back();}
    int getSize() const {return line.size();}
    void setThickness(double const _thickness){thickness = _thickness;}
    float getThickness() const {return thickness;}
    void clear();
    void draw(sf::RenderWindow& window);
};
#endif /* Line_hpp */

