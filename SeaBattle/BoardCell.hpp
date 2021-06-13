#ifndef SEABATTLE_BOARDCELL_HPP
#define SEABATTLE_BOARDCELL_HPP


// множество состояний одной клетки
enum class CellState {
    Empty,
    Deck,
    Miss,
    DamagedDeck,
    Fire
};

class BoardCell {
private:
    size_t _x, _y;         // координаты клетки
    CellState _state;   // состояние клетки
public:
    explicit BoardCell(int x = 0, int y = 0, CellState state = CellState::Empty) : _x(x), _y(y), _state(state) {};

    inline void SetX(size_t x) {
        _x = x;
    }

    inline void SetY(size_t y) {
        _y = y;
    }

    inline void SetState(CellState state) {
        _state = state;
    }

    [[nodiscard]] inline CellState GetState() const {
        return _state;
    }

    [[nodiscard]] inline size_t GetX() const {
        return _x;
    }

    [[nodiscard]] inline size_t GetY() const {
        return _y;
    }

    [[nodiscard]] inline bool TryHit(size_t x, size_t y) const {
        return x == _x and y == _y;
    }

    // функция печати одной клетки, в зависимости от ее состояния
    void Print();
};


#endif //SEABATTLE_BOARDCELL_HPP
