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

/*!
 * \file
 * \brief Definitions of Object, Candy, Background and Snake classes
 *
 * Definitions of Object, Candy, Background and Snake classes
 * Inheritance between Object (virtual class) and Candy, Background
 */

/*!
 * \brief Definition of Object class
 *
 * Virtual class of Object with sprite and x,y coordinates
 */
class Object{
public:
    /*!
     * \brief X position of Object
     */
    int x;
    /*!
     * \brief Y position of Object
     */
    int y;
    /*!
     * \brief Object sprite
     */
    sf::Sprite sprite;
    /*!
     * \brief Object constructor
     */
    Object() : x(0), y(0) {};
    /*!
     * \brief Virtual draw function
     */
    virtual void draw() = 0;
};


/*!
 * \brief Candy class definition
 *
 * Candy class definition inheriting from Object publicly.
 */
class Candy : public Object {
public:
    /*!
     * \brief Candy draw function
     */
    void draw(){
        sprite.setPosition(x*SIZE,  y*SIZE);
        window.draw(sprite);
    }
    /*!
     * \brief Candy spawnFirst function
     *
     * Function used when spawning first candy,
     * automatically assigns 2 to x and y.
     */
    void spawnFirst(){
        x=2;
        y=2;
    }
};

/*!
 * \brief Background class definition
 *
 * Background class definition inheriting from Object publicly.
 */
class Background : public Object {
public:
    /*!
     * \brief Background draw function
     */
    void draw(){
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++){
                sprite.setPosition(i*SIZE,  j*SIZE);
                window.draw(sprite);
            }
    }
};


// Snake class, d - direction
/*!
 * \brief Snake class definition
 *
 * Snake class definition containing x and y coordinates and
 * d as direction described by directions enum.
 */
class Snake {
public:
    /*!
     * \brief X position of Snake
     */
    int x;
    /*!
     * \brief Y position of Snake
     */
    int y;
    /*!
     * \brief direction of Snake
     */
    int d;
    /*!
     * \brief Snake constructor
     */
    Snake() : x(0), y(0), d(0) {};
    
    
};

#endif /* object_h */
