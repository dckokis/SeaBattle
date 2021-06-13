#ifndef SEABATTLE_GAMEBOARD_HPP
#define SEABATTLE_GAMEBOARD_HPP


#include "Ship.hpp"
#include "BoardCell.hpp"

class GameBoard {
private:
    static const int _size = 10;            // размер игорового поля
    static const int _4DeckShipCount = 1;   // число 4-х палубных
    static const int _3DeckShipCount = 2;   // число 3-х палубных
    static const int _2DeckShipCount = 3;   // число 2-х палубных
    static const int _1DeckShipCount = 4;   // число 1-х палубных
    int _shipsAmount = 0;
    static const int _shipsCount = _4DeckShipCount + _3DeckShipCount + _2DeckShipCount + _1DeckShipCount;   // число кораблей
    BoardCell _cells[_size][_size]; // клетки игрового поля
    Ship _ships[_shipsCount];   // корабли
// функция создание игрового поля
    void Generate();

public:
    GameBoard() {
        Generate();
    }

    ~GameBoard() = default;

    void AddShip(int x, int y, int size, bool horizontal);
// функция установки статуса клетки игровго поля
    inline void SetState(int x, int y, CellState state) {
        _cells[y][x].SetState(state);
    }

// функция возвращает является ли клетка палубой
    inline bool IsDeck(int x, int y) {
        return _cells[y][x].GetState() == CellState::Deck or _cells[y][x].GetState() == CellState::DamagedDeck;
    }

// функция печати игрового поля
    void Print();

// функция возвращает число клеток игровой области
    static inline int GetCount() {
        return _size * _size;
    }

// функция возвращает размер игровой области
    static inline int GetSize() {
        return _size;
    }

// функция - выстрел в игрове поле
    void Shoot(int x, int y);

// функция провекри - уничтожены ли все корабли на поле
    bool AllShipsDestroyed();
};


#endif //SEABATTLE_GAMEBOARD_HPP
