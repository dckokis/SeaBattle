#include "Ship.hpp"

Ship::~Ship() {
    // очистим память, если она была выделена.
    if (_size)
        delete _decks;
}

void
Ship::Create(int size, int x, int y, bool horizontal) {/////////////////нужна проверка что корабль не выходит за границы
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
    // считаем число попаданий
    int hitCount = 0;
    for (int i = 0; i < _size; i++)
        if (_decks[i].GetState() == CellState::DamagedDeck)
            hitCount++;

    // сверяем число попаданий с числом палуб
    if (hitCount == 0)  // если не попали - корабль цел
        _state = ShipState::Safe;
    else if (hitCount < _size)  // если попали но меньше раз, чем число палуб, то ранен
        _state = ShipState::DamagedShip;
    else
        _state = ShipState::Destroyed; // иначе уничтожен

    return _state;
}

void Ship::Shoot(int x, int y) {
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