//
//  Window.cpp
//  achtung die kurve
//
//  Created by Sindre Grøstad on 03/11/2017.
//  Copyright © 2017 Sindre Grøstad. All rights reserved.
//

#include "WindowSpec.hpp"
using namespace std;

WindowSpec::WindowSpec(){
    windowName = "Achtung die kurve";
    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    int windowWidth = modes[0].width; //2560 on Sindres Mac
    int windowHeight = modes[0].height; //1600 on Sindres Mac
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    videoMode = sf::VideoMode(windowWidth, windowHeight, desktopMode.bitsPerPixel);
}

