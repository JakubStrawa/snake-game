
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//
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
//      shared pointer to sprites snake body
//      one class Game with all objects and functions
//  Add project objectives:
//      Funkcje wirtualne - klasa obiekt dla płytek z funk draw
//     + Dziedziczenie - klasa główna obiekt, dziedziczące- tło, snake, candy
//     + Wyjątki - może przechodzenie przez ściany, albo candy w snake'u, throw klase specjalną, może być pusta
//      Testy jednostkowe
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

#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include "object.h"
#include "constants.h"
#include "functions.h"
using namespace sf;

class Game{
    Snake s[600];
    Texture t1,t22,t3,t21,t23,t24,t4;
};

int main()
{
    srand(time(0));
    
    // Set the Icon
    if (!icon.loadFromFile(resourcePath() + "snake.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Load music to play
    Music music;
    if (!music.openFromFile(resourcePath() + "Undertale - Megalovania.ogg")) {
        return EXIT_FAILURE;
    }
    Music exit_music;
    if (!exit_music.openFromFile(resourcePath() + "mario.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.play();
    
    
    // Set the Textures
    Texture t1,t22,t3,t21,t23,t24,t4;
    t1.loadFromFile(resourcePath() + "white_clean.png");
    t21.loadFromFile(resourcePath() + "green.png");
    t23.loadFromFile(resourcePath() + "snake_head.png");
    t24.loadFromFile(resourcePath() + "snake_tail.png");
    t3.loadFromFile(resourcePath() + "candy.png");
    t4.loadFromFile(resourcePath() + "snake_corner.png");
    
    bg.sprite = Sprite (t1);
    Sprite snake_body(t21);
    Sprite snake_head(t23);
    Sprite snake_tail(t24);
    c.sprite = Sprite (t3);
    Sprite snake_corner(t4);
    
    // Set the Clock
    Clock clock;
    float timer=0, delay=0.1;
    
    // Spawning first candy
    c.spawnFirst();
    
    isRunning=true;
    
    while (window.isOpen())
    {
        
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        Event e;
        while (window.pollEvent(e))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape)){
                isRunning=false;
                window.close();
            }
            if (e.type == Event::Closed){
                isRunning=false;
                window.close();
            }
        }
        if (isRunning) {
            int tempdir;
            if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && dir!=right)
                tempdir=left;
            if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && dir!=left)
                tempdir=right;
            if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && dir!=down)
                tempdir=up;
            if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && dir!=up)
                tempdir=down;
        
            if (timer>delay) {
                timer=0;
                dir=tempdir;
                Move(s, c);
            }
        }
        
        //  Drawing snake
        window.clear();
        
        bg.draw();
        
        for (int i=0;i<num;i++){

            //      Head drawing
            if (i==0) {
                if (s[i].d==left) {
                    snake_head.setRotation(90);
                    snake_head.setPosition((s[i].x+1)*SIZE, s[i].y*SIZE);
                } else if (s[i].d==right) {
                    snake_head.setRotation(270);
                    snake_head.setPosition(s[i].x*SIZE, (s[i].y+1)*SIZE);
                } else if (s[i].d==up) {
                    snake_head.setRotation(180);
                    snake_head.setPosition((s[i].x+1)*SIZE, (s[i].y+1)*SIZE);
                } else if (s[i].d==down) {
                    snake_head.setPosition(s[i].x*SIZE, s[i].y*SIZE);
                }
                window.draw(snake_head);
                snake_head.setRotation(0);
            }
            
            //      Tail drawing
            else if (i == num-1){
                s[i].d = s[i-1].d;
                if (s[i].d==left) {
                    snake_tail.setRotation(90);
                    snake_tail.setPosition((s[i].x+1)*SIZE, s[i].y*SIZE);
                } else if (s[i].d==right) {
                    snake_tail.setRotation(270);
                    snake_tail.setPosition(s[i].x*SIZE, (s[i].y+1)*SIZE);
                } else if (s[i].d==up) {
                    snake_tail.setRotation(180);
                    snake_tail.setPosition((s[i].x+1)*SIZE, (s[i].y+1)*SIZE);
                } else if (s[i].d==down) {
                    snake_tail.setPosition(s[i].x*SIZE, s[i].y*SIZE);
                }
                window.draw(snake_tail);
                snake_tail.setRotation(0);
            }
            
            //      Left/right drawing
            else if (s[i].d == left || s[i].d == right) {
                if (s[i].d == left && s[i-1].d == down) {
                    snake_corner.setRotation(270);
                    snake_corner.setPosition(s[i].x*SIZE, (s[i].y+1)*SIZE);
                    window.draw(snake_corner);

                } else if (s[i].d == left && s[i-1].d == up) {
                    snake_corner.setRotation(180);
                    snake_corner.setPosition((s[i].x+1)*SIZE, (s[i].y+1)*SIZE);
                    window.draw(snake_corner);
                } else if (s[i].d == right && s[i-1].d == down) {
                    snake_corner.setPosition((s[i].x)*SIZE, (s[i].y)*SIZE);
                    window.draw(snake_corner);

                } else if (s[i].d == right && s[i-1].d == up) {
                    snake_corner.setRotation(90);
                    snake_corner.setPosition((s[i].x+1)*SIZE, (s[i].y)*SIZE);
                    window.draw(snake_corner);

               } else {
                snake_body.setRotation(90);
                snake_body.setPosition((s[i].x+1)*SIZE, (s[i].y)*SIZE);
                window.draw(snake_body);
                snake_body.setRotation(0);
                }
                snake_corner.setRotation(0);
            }
            
            //      Up/down drawing
            else if (s[i].d == down || s[i].d == up) {
                if (s[i].d == down && s[i-1].d == left) {
                    snake_corner.setRotation(90);
                    snake_corner.setPosition((s[i].x+1)*SIZE, (s[i].y)*SIZE);
                    window.draw(snake_corner);

                } else if (s[i].d == down && s[i-1].d == right) {
                    snake_corner.setRotation(180);
                    snake_corner.setPosition((s[i].x+1)*SIZE, (s[i].y+1)*SIZE);
                    window.draw(snake_corner);
                } else if (s[i].d == up && s[i-1].d == left) {
                    snake_corner.setPosition((s[i].x)*SIZE, (s[i].y)*SIZE);
                    window.draw(snake_corner);

                } else if (s[i].d == up && s[i-1].d == right) {
                    snake_corner.setRotation(270);
                    snake_corner.setPosition(s[i].x*SIZE, (s[i].y+1)*SIZE);
                    window.draw(snake_corner);

                } else {
                snake_body.setPosition((s[i].x)*SIZE, s[i].y*SIZE);
                window.draw(snake_body);
                }
            }
            snake_corner.setRotation(0);
        }
        c.draw();
        //c.sprite.setPosition(c.x*SIZE,  c.y*SIZE);
        //window.draw(c.sprite);
        
        Text text("Score: " + convert(score), font, 30);
        text.setFillColor(Color::Black);
        //text.setPosition(420, 320); center
        
        window.draw(text);
        
        if (!isRunning) {
            music.pause();
            Text exitText("Game Over!", font, 50);
            exitText.setPosition(144, 214);
            exitText.setCharacterSize(128);
            exitText.setFillColor(Color::Red);
            exitText.setStyle(Text::Style::Bold);
            exitText.setOutlineColor(Color::Yellow);
            exitText.setOutlineThickness(-2);
            window.draw(exitText);
        }
        
        window.display();
        
    }
    return 0;
}
