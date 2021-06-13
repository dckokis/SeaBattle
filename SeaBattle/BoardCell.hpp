#ifndef SEABATTLE_BOARDCELL_HPP
#define SEABATTLE_BOARDCELL_HPP


// множество состояний одной клетки
enum class CellState {
    Empty,
    Deck,
    Miss,
    DamagedDeck
};

class BoardCell {
private:
    int _x, _y;         // координаты клетки
    CellState _state;   // состояние клетки
public:
    explicit BoardCell(int x = 0, int y = 0, CellState state = CellState::Empty) : _x(x), _y(y), _state(state) {};

    inline void SetX(int x) {
        _x = x;
    }

    inline void SetY(int y) {
        _y = y;
    }

    inline void SetState(CellState state) {
        _state = state;
    }

    inline CellState GetState() {
        return _state;
    }

    [[nodiscard]] inline int GetX() const {
        return _x;
    }

    [[nodiscard]] inline int GetY() const {
        return _y;
    }

    inline bool TryHit(int x, int y) const {
        return x == _x and y == _y;
    }

    // функция печати одной клетки, в зависимости от ее состояния
    void Print();
};


#endif //SEABATTLE_BOARDCELL_HPP
