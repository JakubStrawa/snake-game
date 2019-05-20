//
//  object.h
//  Snake
//
//  Created by Jakub Strawa on 19/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef object_h
#define object_h
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include "constants.h"






class Object{
public:
    int x,y;
    sf::Sprite sprite;
    
    virtual void draw() = 0;
};

// Snake, d - direction
class Snake : public Object {
public:
    int d;
    
    void draw(){
        sprite.setPosition(x*SIZE,  y*SIZE);
        window.draw(sprite);
    }
};

// Candy
class Candy : public Object {
public:
    void draw(){
        sprite.setPosition(x*SIZE,  y*SIZE);
        window.draw(sprite);
    }
};

#endif /* object_h */
