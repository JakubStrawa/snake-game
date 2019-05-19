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


class Object{
public:
    int x,y;
    sf::Sprite sprite;
    
    virtual void draw() = 0;
};

// Snake, d - direction
class Snake {
public:
    int x,y,d;
};

// Candy
class Candy {
public:
    int x,y;
};

#endif /* object_h */
