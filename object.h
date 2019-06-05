//
//  object.h
//  Snake
//
//  Created by Jakub Strawa on 19/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef object_h
#define object_h
#include <SFML/Graphics.hpp>
#include "functions.h"








class Object{
public:
    int x,y;
    sf::Sprite sprite;
    Object() : x(0), y(0) {};
    
    virtual void draw() = 0;
};

// Snake, d - direction
class Snake {
public:
    int x,y,d;
    
    Snake() : x(0), y(0), d(0) {};
    
    
};

// Candy
class Candy : public Object {
public:
    void draw(){
        sprite.setPosition(x*SIZE,  y*SIZE);
        window.draw(sprite);
    }
    void spawnFirst(){
        x=2;
        y=2;
    }
};

// Background
class Background : public Object {
public:
    void draw(){
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++){
                sprite.setPosition(i*SIZE,  j*SIZE);
                window.draw(sprite);
            }
    }
};

#endif /* object_h */
