#include <cstdlib>
#include "GameBoard.hpp"
#include "console.h"

using namespace std;

namespace {
    size_t getRandom(size_t size) {
        return rand() % size;
    }

    bool isPossibleToPlace(const GameBoard &board, size_t x, size_t y, size_t size, bool horizontal) {
        bool isPossible = true;
        for (int i = 0; i < size; i++) {
            if (x < 0 or x >= GameBoard::GetSize() or y < 0 or y >= GameBoard::GetSize()) {
                isPossible = false;
                break;
            }
            if (board.GetState(x, y) != CellState::Empty or
                board.GetState(x, y + 1) != CellState::Empty or
                board.GetState(x, y - 1) != CellState::Empty or
                board.GetState(x + 1, y) != CellState::Empty or
                board.GetState(x + 1, y + 1) != CellState::Empty or
                board.GetState(x + 1, y - 1) != CellState::Empty or
                board.GetState(x - 1, y) != CellState::Empty or
                board.GetState(x - 1, y + 1) != CellState::Empty or
                board.GetState(x - 1, y - 1) != CellState::Empty) {
                isPossible = false;
                break;
            }
            if (horizontal) {
                x++;
            } else
                y++;
        }
        return isPossible;
    }
}

void GameBoard::Generate() {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            _cells[i][j].SetState(CellState::Empty);
            _cells[i][j].SetX(j);
            _cells[i][j].SetY(i);
        }
    }
//    // расставяем 4-х палубные
//    AddShip(0, 0, 4, true);
//    // расставяем 3-х палубные
//    AddShip(0, 2, 3, false);
//    AddShip(8, 1, 3, false);
//    // расставяем 2-х палубные
//    AddShip(3, 9, 2, true);
//    AddShip(2, 6, 2, true);
//    AddShip(6, 5, 2, true);
//    // расставяем 1-х палубные
//    AddShip(4, 2, 1, true);
//    AddShip(8, 8, 1, true);
//    AddShip(0, 8, 1, true);
//    AddShip(6, 0, 1, true);
    size_t x, y;

    int placedShips = 0;

    while (placedShips != _4DeckShipCount) {
        bool isPlaced = false;
        while (!isPlaced) {
            x = getRandom(_size);
            y = getRandom(_size);
            bool orient = getRandom(2);
            isPlaced = AddShip(x, y, 4, orient);
        }
        ++placedShips;
    }
    placedShips = 0;

    while (placedShips != _3DeckShipCount) {
        bool isPlaced = false;
        while (!isPlaced) {
            x = getRandom(_size);
            y = getRandom(_size);
            bool orient = getRandom(2);
            isPlaced = AddShip(x, y, 3, orient);
        }
        placedShips++;
    }
    placedShips = 0;

    while (placedShips != _2DeckShipCount) {
        bool isPlaced = false;
        while (!isPlaced) {
            x = getRandom(_size);
            y = getRandom(_size);
            bool orient = getRandom(2);
            isPlaced = AddShip(x, y, 2, orient);
        }
        placedShips++;
    }
    placedShips = 0;

    while (placedShips != _1DeckShipCount) {
        bool isPlaced = false;
        while (!isPlaced) {
            x = getRandom(_size);
            y = getRandom(_size);
            bool orient = getRandom(2);
            isPlaced = AddShip(x, y, 1, orient);
        }
        placedShips++;
    }
}

void GameBoard::Print() {
    con_clearScr();
    {
        for (auto &_cell : _cells) {
            for (auto &j : _cell) {
                j.Print();
            }
        }
    }
}

void GameBoard::Shoot(int x, int y) {
    for (auto &ship : _ships) {
        if (ship.TryHit(x, y)) {
            ship.Shoot(x, y);
            SetState(x, y, CellState::DamagedDeck);
            if (ship.GetState() == ShipState::Destroyed) {
                for (int i = 0; i < ship.GetSize(); i++) {
                    size_t localX = ship.GetDeck(i).GetX();
                    size_t localY = ship.GetDeck(i).GetY();
                    SetState(localX, localY, CellState::Fire);
                }
            }
            break;
        } else
            _cells[y][x].SetState(CellState::Miss);

    }
}

bool GameBoard::AllShipsDestroyed() {
    int destroyed = 0;
    for (auto &ship : _ships) {
        if (ship.GetState() == ShipState::Destroyed)
            destroyed++;
    }
    if (destroyed == _shipsCount)
        return true;
    else
        return false;
}

bool GameBoard::AddShip(size_t x, size_t y, size_t size, bool horizontal) {
    bool isPlaced = false;
    if (_shipsAmount != _shipsCount) {
        if (isPossibleToPlace(*this, x, y, size, horizontal)) {
            _ships[_shipsAmount].Create(size, x, y, horizontal);
            _shipsAmount++;
            isPlaced = true;
            for (int i = 0; i < size; i++) {
                if (horizontal) {
                    this->SetState(x + i, y, CellState::Deck);
                } else {
                    this->SetState(x, y + i, CellState::Deck);
                }
            }
        }
    }
    return isPlaced;
}

