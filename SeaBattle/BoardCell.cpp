#include <iostream>
#include "BoardCell.hpp"

using namespace std;
void BoardCell::Print() {
    if (_state == CellState::Empty)
        cout << ' ';
    else if (_state == CellState::DamagedDeck)
        cout << 'x';
    else if (_state == CellState::Deck)
        cout << 'd';
    else
        cout << '*';
}

