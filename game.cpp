//
//  game.cpp
//  Snake
//
//  Created by Jakub Strawa on 05/06/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//
//#include "game.h"

#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "object.h"
#include "constants.h"
#include "exception.h"
#include "functions.h"

void Game::setTextures(){
    t_bg.loadFromFile(resourcePath() + "white_clean.png");
    t_s_body.loadFromFile(resourcePath() + "green.png");
    t_s_head.loadFromFile(resourcePath() + "snake_head.png");
    t_s_tail.loadFromFile(resourcePath() + "snake_tail.png");
    t_candy.loadFromFile(resourcePath() + "candy.png");
    t_s_corner.loadFromFile(resourcePath() + "snake_corner.png");
}

void Game::setSprites(){
    bg.sprite.setTexture(t_bg);
    c.sprite.setTexture(t_candy);
    snake_head.setTexture(t_s_head);
    snake_body.setTexture(t_s_body);
    snake_tail.setTexture(t_s_tail);
    snake_corner.setTexture(t_s_corner);
    }

bool Game::checkCandyPos(){
    for (int i=num;i>-1;--i){
        if (s[i].x == c.x && s[i].y == c.y) {
            return false;
        }
    }
    return true;
}

void Game::Move(){
    if (num == N*M) {
        isRunning = false;
    }
    
    for (int i=num;i>0;--i){
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        s[i].d=s[i-1].d;
        //s[i].sprite=s[i-1].sprite;
    }
    
    try {
        Exception e(10);
        if (dir==down){
            s[0].y+=1;
            s[0].d = down;
            if (s[0].y==M) {
                throw e;
            }
        }
        if (dir==left) {
            s[0].x-=1;
            s[0].d = left;
            if (s[0].x<0) {
                throw e;
            }
        }
        if (dir==right) {
            s[0].x+=1;
            s[0].d = right;
            if (s[0].x==N) {
                throw e;
            }
        }
        if (dir==up) {
            s[0].y-=1;
            s[0].d = up;
            if (s[0].y<0) {
                throw e;
            }
        }
    } catch (Exception n) {
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
            //music.pause();
            //exit_music.play();
        }
    }
    
}

void Game::checkKeyborad(){
    int tempdir=dir;
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
        Move();
    }
}


void Game::drawSnake(){
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
    
    }