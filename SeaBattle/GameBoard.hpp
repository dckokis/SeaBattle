#ifndef SEABATTLE_GAMEBOARD_HPP
#define SEABATTLE_GAMEBOARD_HPP


#include "Ship.hpp"
#include "BoardCell.hpp"

namespace {
    const size_t Size = 10;
    const size_t FourDeckShipCount = 1;
    const size_t ThreeDeckShipCount = 2;
    const size_t TwoDeckShipCount = 3;
    const size_t OneDeckShipCount = 4;
}

class GameBoard {
private:
    static const size_t _size = Size;
    static const size_t _4DeckShipCount = FourDeckShipCount;
    static const size_t _3DeckShipCount = ThreeDeckShipCount;
    static const size_t _2DeckShipCount = TwoDeckShipCount;
    static const size_t _1DeckShipCount = OneDeckShipCount;
    size_t _shipsAmount = 0;
    static const size_t _shipsCount =
            _4DeckShipCount + _3DeckShipCount + _2DeckShipCount + _1DeckShipCount;
    BoardCell _cells[_size][_size];
    Ship _ships[_shipsCount];

    void Generate();

public:
    GameBoard() {
        Generate();
    }

    ~GameBoard() = default;

    bool AddShip(size_t x, size_t y, size_t size, bool horizontal);

    inline void SetState(size_t x, size_t y, CellState state) {
        _cells[y][x].SetState(state);
    }

    [[nodiscard]] CellState GetState(size_t x, size_t y) const;

    void Print();

    static inline int GetCount() {
        return _size * _size;
    }

    static inline int GetSize() {
        return _size;
    }

    void Shoot(int x, int y);

    bool AllShipsDestroyed();
};


#endif //SEABATTLE_GAMEBOARD_HPP
