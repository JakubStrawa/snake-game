
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
//  Add project objectives:
//      Funkcje wirtualne - klasa obiekt dla płytek z funk draw
//      Dziedziczenie - klasa główna obiekt, dziedziczące- tło, snake, candy
//     + Wyjątki - może przechodzenie przez ściany, albo candy w snake'u
//
//BUGS/GLITCHES:
//     + candy can spawn in snake
//     + candy won't spawn at all (with small maps)
//     ? snake can move inside itself




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
using namespace sf;

enum directions {down, left, right, up};

// width and height, size of textures
int N=30,M=20;
int size=32;
int w = size*N;
int h = size*M;
bool isRunning=false;
int score = 0;

// Direction and snake starting lenght
int dir,num=4;

//  Initializing snake and candy
Snake s[600];
Candy c;



// Create a graphical text to display
Font font;

// Set the Window
RenderWindow window(VideoMode(w, h), "Snake Game");

//  checks if candy spawn position is outside snake
bool checkCandyPos(){
    for (int i=num;i>-1;--i){
        if (s[i].x == c.x && s[i].y == c.y) {
            return false;
        }
    }
    return true;
}

void Move()
{
    if (num == N*M) {
        isRunning = false;
    }
    
    for (int i=num;i>0;--i){
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        s[i].d=s[i-1].d;
    }
    
    try {
        if (dir==down){
            s[0].y+=1;
            s[0].d = down;
            if (s[0].y==M) {
                throw 10;
            }
        }
        if (dir==left) {
            s[0].x-=1;
            s[0].d = left;
            if (s[0].x<0) {
                throw 10;
            }
        }
        if (dir==right) {
            s[0].x+=1;
            s[0].d = right;
            if (s[0].x==N) {
                throw 10;
            }
        }
        if (dir==up) {
            s[0].y-=1;
            s[0].d = up;
            if (s[0].y<0) {
                throw 10;
            }
        }
    } catch (int n) {
        //  Movement through walls
        if (s[0].x==N) s[0].x=0;
        if (s[0].x<0) s[0].x=N-1;
        if (s[0].y==M) s[0].y=0;
        if (s[0].y<0) s[0].y=M-1;
    }
    
    
    // Eating and spawning candy
    if ((s[0].x==c.x) && (s[0].y==c.y)){
        num++;
        score+=10;
        c.x=rand() % N;
        c.y=rand() % M;
        while (!checkCandyPos()) {
            c.x=rand() % N;
            c.y=rand() % M;
        }
    }
    

    
    //  Snake eating itself
    for (int i=1;i<num;i++){
        if (s[0].x==s[i].x && s[0].y==s[i].y){
            isRunning=false;
        }
    }
            
}


//  int to string converter
std::string convert (int score){
    std::string s_score = std::to_string(score);
    return s_score;
}

int main()
{
    srand(time(0));
    
    // Set the Icon
    Image icon;
    if (!icon.loadFromFile(resourcePath() + "snake.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Load a music to play
    Music music;
    if (!music.openFromFile(resourcePath() + "Undertale - Megalovania.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.play();
    
    
    // Set the Textures
    Texture t1,t22,t3,t21,t23,t24,t4;
    t1.loadFromFile(resourcePath() + "white_clean.png");
    t21.loadFromFile(resourcePath() + "green.png");
    //t22.loadFromFile(resourcePath() + "green1.png");
    t23.loadFromFile(resourcePath() + "snake_head.png");
    t24.loadFromFile(resourcePath() + "snake_tail.png");
    t3.loadFromFile(resourcePath() + "candy.png");
    t4.loadFromFile(resourcePath() + "snake_corner.png");
    
    Sprite sprite1(t1);
    //Sprite sprite22(t22);
    Sprite sprite21(t21);
    Sprite sprite23(t23);
    Sprite sprite24(t24);
    Sprite sprite3(t3);
    Sprite sprite4(t4);
    
    // Set the Clock
    Clock clock;
    float timer=0, delay=0.1;
    
    // Spawning first candy
    c.x=2;
    c.y=2;
    
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
            
            if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && dir!=right)
                dir=left;
            if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && dir!=left)
                dir=right;
            if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && dir!=down)
                dir=up;
            if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && dir!=up)
                dir=down;
        
            if (timer>delay) {
                timer=0;
                Move();
            }
        }
        
        //  Drawing snake
        window.clear();
        
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++)
            { sprite1.setPosition(i*size,j*size);
                window.draw(sprite1); }
        
        for (int i=0;i<num;i++){

            //      Head drawing
            if (i==0) {
                if (s[i].d==left) {
                    sprite23.setRotation(90);
                    sprite23.setPosition((s[i].x+1)*size, s[i].y*size);
                } else if (s[i].d==right) {
                    sprite23.setRotation(270);
                    sprite23.setPosition(s[i].x*size, (s[i].y+1)*size);
                } else if (s[i].d==up) {
                    sprite23.setRotation(180);
                    sprite23.setPosition((s[i].x+1)*size, (s[i].y+1)*size);
                } else if (s[i].d==down) {
                    sprite23.setPosition(s[i].x*size, s[i].y*size);
                }
                window.draw(sprite23);
                sprite23.setRotation(0);
            }
            
            //      Tail drawing
            else if (i == num-1){
                s[i].d = s[i-1].d;
                if (s[i].d==left) {
                    sprite24.setRotation(90);
                    sprite24.setPosition((s[i].x+1)*size, s[i].y*size);
                } else if (s[i].d==right) {
                    sprite24.setRotation(270);
                    sprite24.setPosition(s[i].x*size, (s[i].y+1)*size);
                } else if (s[i].d==up) {
                    sprite24.setRotation(180);
                    sprite24.setPosition((s[i].x+1)*size, (s[i].y+1)*size);
                } else if (s[i].d==down) {
                    sprite24.setPosition(s[i].x*size, s[i].y*size);
                }
                window.draw(sprite24);
                sprite24.setRotation(0);
            }
            
            //      Left/right drawing
            else if (s[i].d == left || s[i].d == right) {
                if (s[i].d == left && s[i-1].d == down) {
                    sprite4.setRotation(270);
                    sprite4.setPosition(s[i].x*size, (s[i].y+1)*size);
                    window.draw(sprite4);

                } else if (s[i].d == left && s[i-1].d == up) {
                    sprite4.setRotation(180);
                    sprite4.setPosition((s[i].x+1)*size, (s[i].y+1)*size);
                    window.draw(sprite4);
                } else if (s[i].d == right && s[i-1].d == down) {
                    sprite4.setPosition((s[i].x)*size, (s[i].y)*size);
                    window.draw(sprite4);

                } else if (s[i].d == right && s[i-1].d == up) {
                    sprite4.setRotation(90);
                    sprite4.setPosition((s[i].x+1)*size, (s[i].y)*size);
                    window.draw(sprite4);

               } else {
                sprite21.setRotation(90);
                sprite21.setPosition((s[i].x+1)*size, (s[i].y)*size);
                window.draw(sprite21);
                sprite21.setRotation(0);
                }
                sprite4.setRotation(0);
            }
            
            //      Up/down drawing
            else if (s[i].d == down || s[i].d == up) {
                if (s[i].d == down && s[i-1].d == left) {
                    sprite4.setRotation(90);
                    sprite4.setPosition((s[i].x+1)*size, (s[i].y)*size);
                    window.draw(sprite4);

                } else if (s[i].d == down && s[i-1].d == right) {
                    sprite4.setRotation(180);
                    sprite4.setPosition((s[i].x+1)*size, (s[i].y+1)*size);
                    window.draw(sprite4);
                } else if (s[i].d == up && s[i-1].d == left) {
                    sprite4.setPosition((s[i].x)*size, (s[i].y)*size);
                    window.draw(sprite4);

                } else if (s[i].d == up && s[i-1].d == right) {
                    sprite4.setRotation(270);
                    sprite4.setPosition(s[i].x*size, (s[i].y+1)*size);
                    window.draw(sprite4);

                } else {
                sprite21.setPosition((s[i].x)*size, s[i].y*size);
                window.draw(sprite21);
                }
            }
            sprite4.setRotation(0);
        }
        
        sprite3.setPosition(c.x*size,  c.y*size);
        window.draw(sprite3);
        
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
