#include "BoardCell.hpp"
#include "console.h"
using namespace std;


void BoardCell::Print() {
    short color = 1;
    con_initPair(color, CON_COLOR_WHITE, CON_COLOR_BLACK);

    if (_state == CellState::Empty)
        con_charAt('~', color, _x, _y);
    else if (_state == CellState::DamagedDeck)
        con_charAt('x', color, _x, _y);
    else if (_state == CellState::Fire)
        con_charAt('!', color, _x, _y);
    else if (_state == CellState::Deck)
        con_charAt('#', color, _x, _y);
    else
        con_charAt('*', color, _x, _y);
}

