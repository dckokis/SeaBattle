#include "GameBoard.hpp"
#include <iostream>

using namespace std;

void GameBoard::Generate() {/////////////тут нужно чтобы пользователь сам расставил
    // заполняем игровое поле пустыми клетками
    for (auto &_cell : _cells)
        for (auto &j : _cell)
            j.SetState(CellState::Empty);
    int idx = 0;
    // расставяем 4-х палубные
    AddShip(0, 0, 4, true);
    // расставяем 3-х палубные
    AddShip(0, 2, 3, false);
    AddShip(8, 1, 3, false);
    // расставяем 2-х палубные
    AddShip(3, 9, 2, true);
    AddShip(2, 6, 2, true);
    AddShip(6, 5, 2, true);
    // расставяем 1-х палубные
    AddShip(4, 2, 1, true);
    AddShip(8, 8, 1, true);
    AddShip(0, 8, 1, true);
    AddShip(6, 0, 1, true);
}

void GameBoard::Print() {
    for (int i = 0; i < _size; i++)
    {
        cout << "|";
        for (int j = 0; j < _size; j++)
        {
            _cells[i][j].Print();
            cout << "|";
        }
        cout << endl;
    }
}

void GameBoard::Shoot(int x, int y) {
// просмотрим все корабли
    for (auto &ship : _ships) {
        // проверим попадание
        if (ship.TryHit(x, y)) {
            // если попадаем - стреляем по кораблю
            ship.Shoot(x, y);
            SetState(x, y, CellState::DamagedDeck);
            if (ship.GetState() == ShipState::Destroyed) {
                for (int i = 0; i < ship.GetSize(); i++) {
                    int localX = ship.GetDeck(i).GetX();
                    int localY = ship.GetDeck(i).GetY();
                    if (localX - 1 >= 0 && localY - 1 >= 0 && !IsDeck(localX - 1, localY - 1))
                        SetState(localX - 1, localY - 1, CellState::Miss);
                    if (localX - 1 >= 0 && !IsDeck(localX - 1, localY))
                        SetState(localX - 1, localY, CellState::Miss);
                    if (localX - 1 >= 0 && localY + 1 < GetSize() &&
                        !IsDeck(localX - 1, localY + 1))
                        SetState(localX - 1, localY + 1, CellState::Miss);

                    if (localY - 1 >= 0 && !IsDeck(localX, localY - 1))
                        SetState(localX, localY - 1, CellState::Miss);
                    if (localY + 1 < GetSize() && !IsDeck(localX, localY + 1))
                        SetState(localX, localY + 1, CellState::Miss);

                    if (localX + 1 < GetSize() && localY - 1 >= 0 &&
                        !IsDeck(localX + 1, localY - 1))
                        SetState(localX + 1, localY - 1, CellState::Miss);
                    if (localX + 1 < GetSize() && !IsDeck(localX + 1, localY))
                        SetState(localX + 1, localY, CellState::Miss);
                    if (localX + 1 < GetSize() && localY + 1 < GetSize() &&
                        !IsDeck(localX + 1, localY + 1))
                        SetState(localX + 1, localY + 1, CellState::Miss);
                }
            }
            break;
        } else
            _cells[y][x].SetState(CellState::Miss);

    }
}

bool GameBoard::AllShipsDestroyed() {
    // обход всех кораблей
    for (auto &_ship : _ships)
        // если хотя бы один не уничтожен, вернем false
        if (_ship.GetState() != ShipState::Destroyed)
            return false;
    return true;    // иначе true
}

void GameBoard::AddShip(int x, int y, int size, bool horizontal) {
    if (_shipsAmount != _shipsCount) {
        _ships[_shipsAmount].Create(size, x, y, horizontal);
        _shipsAmount++;
        for (int i = 0; i < size; i++) {
            if (horizontal) {
                this->SetState(x + i, y, CellState::Deck);
            } else {
                this->SetState(x, y + i, CellState::Deck);
            }
        }
    }

}
