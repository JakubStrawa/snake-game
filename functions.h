//
//  functions.h
//  Snake
//
//  Created by Jakub Strawa on 21/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef functions_h
#define functions_h
#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "object.h"
#include "constants.h"
#include "exception.h"


//  checks if candy spawn position is outside snake
bool checkCandyPos(Snake (&s)[600], Candy &c){
    for (int i=num;i>-1;--i){
        if (s[i].x == c.x && s[i].y == c.y) {
            return false;
        }
    }
    return true;
}


void Move(Snake (&s)[600], Candy &c)
{
    if (num == N*M) {
        isRunning = false;
    }
    
    for (int i=num;i>0;--i){
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        s[i].d=s[i-1].d;
        s[i].sprite=s[i-1].sprite;
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
        while (!checkCandyPos(s, c)) {
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



#endif /* functions_h */
