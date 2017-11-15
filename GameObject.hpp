//  GameObject.h
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h
#include <SFML/Graphics.hpp>
#include "Enum.h"
class GameObject{
public:
    virtual void update(double timeElapsed) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

#endif /* GameObject_h */

