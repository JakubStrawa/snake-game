//
//  functions.h
//  Snake
//
//  Created by Jakub Strawa on 21/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef functions_h
#define functions_h
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "game.h"

using namespace sf;

/*!
 * \file
 * \brief Game loop function file
 *
 * Definition of entire gameLoop function
 */

/*!
 * \brief Main game loop
 */
int gameLoop(Game game){
    
    /*!
     * \brief Load music to play - main theme, loss and win sounds
     */
    Music music;
    if (!music.openFromFile("Resources/Undertale - Megalovania.ogg")) {
        return EXIT_FAILURE;
    }
    /*!
     * \brief Load music to play - main theme, loss and win sounds
     */
    Music exit_music;
    if (!exit_music.openFromFile("Resources/mario.ogg")) {
        return EXIT_FAILURE;
    }
    /*!
     * \brief Load music to play - main theme, loss and win sounds
     */
    Music win_music;
    if (!win_music.openFromFile("Resources/Mario Win.ogg")) {
        return EXIT_FAILURE;
    }
    
    /*!
     * \brief Play the music
     */
    music.play();
    
    /*!
     * \brief Set the Textures
     */
    game.setTextures();
    
    /*!
     * \brief Set the sprites
     */
    game.setSprites();
    
    /*!
     * \brief Spawning first candy
     */
    game.c.spawnFirst();

    /*!
     * \brief Creating clock
     */
    Clock clock;
    
    /*!
     * \brief MAIN loop
     */
    while (window.isOpen())
    {
        /*!
         * \brief counting elapsed time
         */
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        /*!
         * \brief event to check if user wants to quit
         */
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
        /*!
         * \brief checking if keys are pressed
         */
        if (isRunning) {
            game.checkKeyborad();
        }
        
        /*!
         * \brief Drawing background, candy and snake
         */
        window.clear();
        game.bg.draw();
        game.c.draw();
        game.drawSnake();

        /*!
         * \brief displaying score
         */
        Text text("Score: " + convert(score), font, 30);
        text.setFillColor(Color::Black);
        window.draw(text);
        
        /*!
         * \brief win conditions
         */
        if (score > 1000 && isRunning) {
            music.pause();
            win_music.play();
            isRunning = false;
            gameWin = true;
        }
        
        /*!
         * \brief win text display
         */
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
        
        /*!
         * \brief loss text display
         */
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

    return 0;
}






#endif /* functions_h */
