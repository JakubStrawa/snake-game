
// Snake game
// CC Jakub Strawa 2019


//  DIRECTIONS:
//  UP 3
//  DOWN 0
//  RIGTH 2
//  LEFT 1

#include <SFML/Graphics.hpp>
#include "functions.h"

using namespace sf;

/*!
 * \file
 * \brief Main file
 *
 * Main includes creating Game class instance, loading icon and font from files
 * and entering game loop
 */

 int main(){
     
 srand(time(0));
/*!
* \brief New Game class instance
*/
 Game* game = new Game();
 
/*!
* \brief Set the Icon
*/
 if (!icon.loadFromFile("Resources/snake.png")) {
 return EXIT_FAILURE;
 }
 window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
 
/*!
* \brief Loading Font
*/
 if (!font.loadFromFile("Resources/sansation.ttf")) {
 return EXIT_FAILURE;
 }
/*!
* \brief Main game loop
*/
 gameLoop(*game);
 
 delete game;
 
 return 0;
 }



