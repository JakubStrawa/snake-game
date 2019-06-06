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

/*!
 * \file
 * \brief Definitions of constants
 *
 * File contains constatns such as width, height
 * bool isRunning, playEndMusic and gameWin
 * int score and two clock floats
 */
/*!
 * \brief Directions enum
 */
enum directions {down, left, right, up};



// width and height, size of textures, score
int N=30,M=20;
int w = SIZE*N;
int h = SIZE*M;
bool isRunning=true;
bool gameWin=false;
int score = 0;

/*!
 * \brief Clock timer
 */
float timer=0;
/*!
 * \brief Clock delay between frames
 */
float delay=0.1;

/*!
 * \brief Bool to play exit music
 */
bool playEndMusic = false;


/*!
 * \brief Sets the Window
 */
sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

/*!
 * \brief Loading font
 */
sf::Font font;
/*!
 * \brief Loading game icon
 */
sf::Image icon;


/*!
 * \brief int to string converter
 */
std::string convert (int score){
    std::string s_score = std::to_string(score);
    return s_score;
}


#endif /* constants_h */
