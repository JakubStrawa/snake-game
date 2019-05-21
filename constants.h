//
//  constants.h
//  Snake
//
//  Created by Jakub Strawa on 20/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef constants_h
#define constants_h
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include "object.h"
#define SIZE 32


enum directions {down, left, right, up};



// width and height, size of textures
int N=30,M=20;
int w = SIZE*N;
int h = SIZE*M;
bool isRunning=false;
int score = 0;

// Direction
int dir, num=4;

// Set the Window
sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

// Create a graphical text to display
sf::Font font;

sf::Image icon;


//  int to string converter
std::string convert (int score){
    std::string s_score = std::to_string(score);
    return s_score;
}



#endif /* constants_h */
