//
//  game.h
//  Snake
//
//  Created by Jakub Strawa on 05/06/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef game_h
#define game_h

#include <SFML/Graphics.hpp>
#include "object.h"
#include "exception.h"
using namespace sf;

/*!
 * \file
 * \brief Game class definition
 *
 * File contains definition of Game class and its methods.
 */

/*!
 * \brief Game class definition
 *
 * Definition of Game class and its methods.
 */
class Game{
private:
    /*!
     * \brief direction of Snake's head
     */
    int dir=0;
    /*!
     * \brief Snake length
     */
    int num;
public:
    /*!
     * \brief Snake table of objects
     */
    Snake s[600];
    /*!
     * \brief Texture of Background
     */
    Texture t_bg;
    /*!
     * \brief Texture of Candy
     */
    Texture t_candy;
    /*!
     * \brief Texture of Snake body
     */
    Texture t_s_body;
    /*!
     * \brief Texture of Snake head
     */
    Texture t_s_head;
    /*!
     * \brief Texture of Snake tail
     */
    Texture t_s_tail;
    /*!
     * \brief Texture of Snake corner
     */
    Texture t_s_corner;
    /*!
     * \brief Candy instance
     */
    Candy c;
    /*!
     * \brief Background instance
     */
    Background bg;
    /*!
     * \brief Snake body sprite
     */
    Sprite snake_body;
    /*!
     * \brief Snake corner sprite
     */
    Sprite snake_corner;
    /*!
     * \brief Snake head sprite
     */
    Sprite snake_head;
    /*!
     * \brief Snake tail sprite
     */
    Sprite snake_tail;
    /*!
     * \brief Game constructor
     */
    Game() : dir(0), num(4) {};
    /*!
     * \brief Game default destructor
     */
    ~Game()=default;
    
    /*!
     * \brief dir value getter
     */
    int getDir(){
        return dir;
    }
    /*!
     * \brief num value getter
     */
    int getNum(){
        return num;
    }
    /*!
     * \brief dir value setter
     */
    void setDir(int x){
        dir = x;
    }
    /*!
     * \brief num value setter
     */
    void setNum(int x){
        num = x;
    }
    /*!
     * \brief num value incrementator
     */
    void increaseNum(){
        ++num;
    }
    
    /*!
     * \brief Snake, Candy and Background texture loader
     */
    void setTextures(){
        t_bg.loadFromFile("Resources/white_clean.png");
        t_s_body.loadFromFile("Resources/green.png");
        t_s_head.loadFromFile("Resources/snake_head.png");
        t_s_tail.loadFromFile("Resources/snake_tail.png");
        t_candy.loadFromFile("Resources/candy.png");
        t_s_corner.loadFromFile("Resources/snake_corner.png");
    }
    
    /*!
     * \brief Snake, Candy and Background sprite loader
     */
    void setSprites(){
        bg.sprite.setTexture(t_bg);
        c.sprite.setTexture(t_candy);
        snake_head.setTexture(t_s_head);
        snake_body.setTexture(t_s_body);
        snake_tail.setTexture(t_s_tail);
        snake_corner.setTexture(t_s_corner);
    }
    
    /*!
     * \brief Function checks if candy spawn position is outside snake
     */
    bool checkCandyPos(){
        for (int i=num;i>-1;--i){
            if (s[i].x == c.x && s[i].y == c.y) {
                return false;
            }
        }
        return true;
    }
    
    /*!
     * \brief Move function
     */
    void Move(){
        if (num == N*M) {
            isRunning = false;
        }
        
        for (int i=num;i>0;--i){
            s[i].x=s[i-1].x;
            s[i].y=s[i-1].y;
            s[i].d=s[i-1].d;
        }
        /*!
         * \brief Exception use for out-of-bounds movement
         */
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
            /*!
             * \brief Movement through walls
             */
            if (s[0].x==N) s[0].x=0;
            if (s[0].x<0) s[0].x=N-1;
            if (s[0].y==M) s[0].y=0;
            if (s[0].y<0) s[0].y=M-1;
        }
        
        /*!
         * \brief Eating and spawning candy
         */
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
        
        /*!
         * \brief Snake eating itself
         */
        for (int i=1;i<num;i++){
            if (s[0].x==s[i].x && s[0].y==s[i].y){
                isRunning=false;
            }
        }
        
    }
    
    /*!
     * \brief Function checks if keys are pressed
     */
    void checkKeyborad(){
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
    
    /*!
     * \brief Function drawing Snake
     */
    void drawSnake(){
        for (int i=0;i<num;i++){
            
            /*!
             * \brief Snake head drawing
             */
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
            
            /*!
             * \brief Snake tail drawing
             */
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
            
            /*!
             * \brief Snake left/right drawing
             */
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
            
            /*!
             * \brief Snake up/down drawing
             */
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
    
};

#endif /* game_h */
