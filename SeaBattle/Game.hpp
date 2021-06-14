#ifndef SEABATTLE_GAME_HPP
#define SEABATTLE_GAME_HPP

#include "GameBoard.hpp"
#include <iostream>
#include "Game.hpp"
#include "console.h"
#include "Random.hpp"

const int FIELD_SHIFT_X = 0;
const int FIELD_SHIFT_Y = 12;

bool gamerShoot(GameBoard &gamerBoard, GameBoard &botBoard);

bool botShoot(GameBoard &gamerBoard, GameBoard &botBoard);

void startGame();

bool gameProcess(GameBoard &gamerBoard, GameBoard &botBoard);

void finishGame(bool win);

#endif //SEABATTLE_GAME_HPP
