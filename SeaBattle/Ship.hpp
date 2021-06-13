#ifndef SEABATTLE_SHIP_HPP
#define SEABATTLE_SHIP_HPP

#include "BoardCell.hpp"

enum class ShipState {
    Destroyed,
    DamagedShip,
    Safe
};

class Ship {
private:
    BoardCell *_decks = nullptr;
    ShipState _state = ShipState::Safe;
    size_t _size = 0;
public:
    Ship() = default;

    void Create(size_t size, size_t x, size_t y, bool horizontal);

    inline BoardCell GetDeck(int _deckNum) {
        return _decks[_deckNum];
    }

    ~Ship();

    ShipState GetState();

    [[nodiscard]] inline size_t GetSize() const {
        return _size;
    };

    void Shoot(size_t x, size_t y);

    bool TryHit(int x, int y);
};


#endif //SEABATTLE_SHIP_HPP
