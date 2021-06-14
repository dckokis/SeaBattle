#include "GameBoard.hpp"
#include "Random.hpp"
#include "console.h"

using namespace std;

namespace {

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
            _cells[i][j].SetX(j + FIELD_SHIFT_X);
            _cells[i][j].SetY(i + FIELD_SHIFT_Y);
            if (_isGamerField)
                _cells[i][j].SetVisibility(true);
            else
                _cells[i][j].SetVisibility(false);
        }
    }
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
    for (auto &_cell : _cells) {
        for (auto &j : _cell) {
            j.Print();
        }
    }
}

bool GameBoard::Shoot(size_t x, size_t y) {
    bool hit = false;
    for (auto &ship : _ships) {
        if (ship.TryHit(x, y)) {
            ship.Shoot(x, y);
            hit = true;
            SetState(x, y, CellState::DamagedDeck);
            if (ship.GetState() == ShipState::Destroyed) {
                for (int i = 0; i < ship.GetSize(); i++) {
                    size_t localX = ship.GetDeck(i).GetX();
                    size_t localY = ship.GetDeck(i).GetY();
                    SetState(localX, localY, CellState::Fire);
                }
            }
            break;
        } else{
            _cells[y][x].SetState(CellState::Miss);
            return false;
        }
    }
    return hit;
}

bool GameBoard::AllShipsDestroyed() {
    int destroyed = 0;
    for (auto &ship : _ships) {
        if (ship.GetState() == ShipState::Destroyed)
            destroyed++;
    }
    if (destroyed == _shipsAmount)
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

CellState GameBoard::GetState(size_t x, size_t y) const {
    if (x < 0 or y < 0 or x >= _size or y >= _size)
        return CellState::Empty;
    return _cells[y][x].GetState();
}

