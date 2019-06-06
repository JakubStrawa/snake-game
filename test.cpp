//
//  test.cpp
//  Snake
//
//  Created by Jakub Strawa on 05/06/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//
//  Unit Tests

#include <iostream>
#include <string>
#include "functions.h"
#include "constants.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*!
 * \file
 * \brief Unit Tests file
 *
 * File contains unit tests for different classes and functions
 * of Snake game.
 */

/*!
 * \brief Testing unit tests
 */
TEST_CASE("Sum"){
    int a=4;
    int b=1;
    REQUIRE(a+b == 5);
}
/*!
 * \brief Testing Candy class
 */
TEST_CASE("Objects class - Candy"){
    Candy obj;
    REQUIRE(obj.x == 0);
    REQUIRE(obj.y == 0);
    obj.spawnFirst();
    REQUIRE(obj.x == 2);
    REQUIRE(obj.y == 2);
}
/*!
 * \brief Testing Snake class
 */
TEST_CASE("Objects class - Snake"){
    Snake s;
    REQUIRE(s.x == 0);
    REQUIRE(s.y == 0);
    REQUIRE(s.d == 0);
}
/*!
 * \brief Testing Game class
 */
TEST_CASE("Game class"){
    Game obj;
    REQUIRE(obj.getDir() == 0);
    REQUIRE(obj.getNum() == 4);
    obj.c.spawnFirst();
    REQUIRE(obj.checkCandyPos() == true);
    obj.setDir(4);
    obj.setNum(20);
    REQUIRE(obj.getDir() == 4);
    REQUIRE(obj.getNum() == 20);
    obj.increaseNum();
    obj.increaseNum();
    REQUIRE(obj.getNum() == 22);
}
/*!
 * \brief Testing Exception class
 */
TEST_CASE("Exception class"){
    Exception obj;
    Exception obj2(40);
    REQUIRE(obj.get() == 20);
    REQUIRE(obj2.get() == 40);
}
/*!
 * \brief Testing Int to String converter
 */
TEST_CASE("Int to String converter"){
    int x = 123;
    std::string s = convert(x);
    std::string a = "123";
    REQUIRE(s == a);
    
}

