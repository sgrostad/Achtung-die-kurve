//
//  Window.hpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;
class WindowSpec {
private:
    sf::VideoMode videoMode;
    string windowName;
public:
    int static windowWidth;
    int static windowHeight;
    WindowSpec();
    sf::VideoMode getVideoMode(){return videoMode;}
    string getWindowName(){return windowName;}
};
#endif /* Window_hpp */

