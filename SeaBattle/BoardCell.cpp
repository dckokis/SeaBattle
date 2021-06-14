#include "BoardCell.hpp"
#include "console.h"

namespace {
    short const WHITE = 1;
    short const RED = 2;
}

void BoardCell::Print() {
    con_initPair(WHITE, CON_COLOR_WHITE, CON_COLOR_BLACK);
    con_initPair(RED, CON_COLOR_RED, CON_COLOR_BLACK);
    switch (_state) {
        case CellState::Empty:
            con_charAt('~', WHITE, _x, _y);
            break;
        case CellState::DamagedDeck:
            con_charAt('x', RED, _x, _y);
            break;
        case CellState::Fire:
            con_charAt('!', RED, _x, _y);
            break;
        case CellState::Deck:
            if (_isVisible) {
                con_charAt('#', WHITE, _x, _y);
                break;
            } else {
                con_charAt('~', WHITE, _x, _y);
                break;
            }
        case CellState::Miss:
            con_charAt('*', WHITE, _x, _y);
            break;
    }
}

