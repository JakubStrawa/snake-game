//
//  constants.h
//  Snake
//
//  Created by Jakub Strawa on 20/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef constants_h
#define constants_h
#include <SFML/Graphics.hpp>
#define SIZE 32


enum directions {down, left, right, up};



// width and height, size of textures
int N=30,M=20;
int w = SIZE*N;
int h = SIZE*M;
bool isRunning=true;
bool gameWin=false;
int score = 0;

// Clock timer and delay between frames
float timer=0, delay=0.1;

// Bool to play exit music
bool playEndMusic = false;


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
