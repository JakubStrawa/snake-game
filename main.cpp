
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


 int main(){
     
 srand(time(0));
 
 Game* game = new Game();
 
 // Set the Icon
 if (!icon.loadFromFile("Resources/snake.png")) {
 return EXIT_FAILURE;
 }
 window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
 
 if (!font.loadFromFile("Resources/sansation.ttf")) {
 return EXIT_FAILURE;
 }
 
 gameLoop(*game);
 
 delete game;
 
 return 0;
 }



