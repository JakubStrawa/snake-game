
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//
// TODO:
//     + change textures - different cherry and snake, maybe background --- red is for candy
//     + make snake head texture, and snake body rotate
//     + make corners on snake body
//     ? can go through walls - should stay
//     + can be stuck in wall - seems it is drawing one row less
//     + can change direction by 180
//     + add score counter
//     + add possibilities to lose - eating itself, ? hitting wall
//     + add quiting by ESC
//     + check spawning cherry where snake is
//     + add music
//     + set game icon
//     + remake main to have bool isRunning
//     + one class Game with all objects and functions
//     + add winning possibility
//  Add project objectives:
//     + Funkcje wirtualne - klasa obiekt dla płytek z funk draw
//     + Dziedziczenie - klasa główna obiekt, dziedziczące- tło, snake, candy
//     + Wyjątki - może przechodzenie przez ściany, albo candy w snake'u, throw klase specjalną, może być pusta
//     + Testy jednostkowe - gettery, settery, przeliczanie pozycji
//
// BUGS/GLITCHES:
//     + candy can spawn in snake
//     + candy won't spawn at all (with small maps)
//     + snake can move inside itself




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



