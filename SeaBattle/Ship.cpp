#include "Ship.hpp"

Ship::~Ship() {
    if (_size)
        delete _decks;
}

void
Ship::Create(size_t size, size_t x, size_t y, bool horizontal) {/////////////////нужна проверка что корабль не выходит за границы
    _size = size;
    _decks = new BoardCell[size];
    // заполняем клетки в зависимости от начала координат корябля и его направления
    for (int i = 0; i < size; i++) {
        if (horizontal) {
            _decks[i].SetX(x + i);
            _decks[i].SetY(y);
        } else {
            _decks[i].SetX(x);
            _decks[i].SetY(y + i);
        }
    }
}

ShipState Ship::GetState() {
    int hitCount = 0;
    for (int i = 0; i < _size; i++)
        if (_decks[i].GetState() == CellState::DamagedDeck)
            hitCount++;

    if (hitCount == 0)
        _state = ShipState::Safe;
    else if (hitCount < _size)
        _state = ShipState::DamagedShip;
    else
        _state = ShipState::Destroyed;

    return _state;
}

void Ship::Shoot(size_t x, size_t y) {
    for (int i = 0; i < _size; i++)
        if (_decks[i].TryHit(x, y)) {
            _decks[i].SetState(CellState::DamagedDeck);
            break;
        }
}

bool Ship::TryHit(int x, int y) {
    for (int i = 0; i < _size; i++)
        if (_decks[i].TryHit(x, y))
            return true;
    return false;
}