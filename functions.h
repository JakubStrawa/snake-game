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
#include "constants.h"
#include "game.h"

using namespace sf;



void gameLoop(Game game){
    
    // Load music to play
    Music music;
    if (!music.openFromFile(resourcePath() + "Undertale - Megalovania.ogg")) {
        return EXIT_FAILURE;
    }
    Music exit_music;
    if (!exit_music.openFromFile(resourcePath() + "mario.ogg")) {
        return EXIT_FAILURE;
    }
    Music win_music;
    if (!win_music.openFromFile(resourcePath() + "Mario Win.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.play();
    
    // Set the Textures
    game.setTextures();
    
    // Set the sprites
    game.setSprites();
    
    // Spawning first candy
    game.c.spawnFirst();

    // Set the Clock
    Clock clock;
    
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
            game.checkKeyborad();
        }
        
        //  Drawing game
        window.clear();

        game.bg.draw();
        game.c.draw();
        game.drawSnake();

        
        Text text("Score: " + convert(score), font, 30);
        text.setFillColor(Color::Black);
        window.draw(text);
        
        if (score > 100 && isRunning) {
            music.pause();
            win_music.play();
            isRunning = false;
            gameWin = true;
        }
        
        if (!isRunning && gameWin) {
            Text exitText("You Win!", font, 50);
            exitText.setPosition(230, 214);
            exitText.setCharacterSize(128);
            exitText.setFillColor(Color::Blue);
            exitText.setStyle(Text::Style::Bold);
            exitText.setOutlineColor(Color::Green);
            exitText.setOutlineThickness(-2);
            window.draw(exitText);
        }
        
        if (!isRunning && !gameWin) {
            music.pause();
            if (playEndMusic == false) {
                playEndMusic = true;
                exit_music.play();
            }
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

}






#endif /* functions_h */
