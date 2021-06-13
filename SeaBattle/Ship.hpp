#ifndef SEABATTLE_SHIP_HPP
#define SEABATTLE_SHIP_HPP
#include "BoardCell.hpp"
// множество состояний корабля
enum class ShipState {
    Destroyed,
    DamagedShip,
    Safe
};

class Ship {
private:
    BoardCell *_decks;  // клетки корабля
    ShipState _state;   // состояние корабля
    int _size;
public:
    Ship() {
        _state = ShipState::Safe;
        _decks = nullptr;
        _size = 0;
    }

    void Create(int size, int x, int y, bool horizontal);

    inline BoardCell GetDeck(int _deckNum) {
        return _decks[_deckNum];
    }
    ~Ship();

    // функция вощвращает состояние корабля, выполнив проверку целостности всех палуб
    ShipState GetState();
    inline int GetSize() const {
        return _size;
    };

    // функция выстрела по корабрю, возвращает состояние корябля, после выстрела
    void Shoot(int x, int y);

    bool TryHit(int x, int y);
};


#endif //SEABATTLE_SHIP_HPP
