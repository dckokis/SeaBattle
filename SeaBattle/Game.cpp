#include "Game.hpp"

using namespace std;

bool gamerShoot(GameBoard &gamerBoard, GameBoard &botBoard) {
    bool miss = false;
    while (!miss) {
        gamerBoard.Print();
        con_gotoXY(FIELD_SHIFT_X, FIELD_SHIFT_Y);
        botBoard.Print();
        con_gotoXY(0, 0);
        con_outTxt("Enter the X coordinate: ");
        int x;
        cin >> x;
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        con_gotoXY(0, 1);
        con_outTxt("Enter the Y coordinate: ");
        int y;
        cin >> y;
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        con_clearScr();
        bool hit = botBoard.Shoot(x, y);
        if (botBoard.AllShipsDestroyed())
            miss = true;
        if (!hit)
            miss = !miss;
        con_gotoXY(FIELD_SHIFT_X, FIELD_SHIFT_Y);
        botBoard.Print();
    }
    return miss;
}

bool botShoot(GameBoard &gamerBoard, GameBoard &botBoard) {
    bool miss = false;
    size_t X = getRandom(GameBoard::GetSize());
    size_t Y = getRandom(GameBoard::GetSize());
    while (!miss) {
        gamerBoard.Print();
        con_gotoXY(FIELD_SHIFT_X, FIELD_SHIFT_Y);
        botBoard.Print();
        con_gotoXY(0, 0);
        con_outTxt("Now it's the bot's turn. Let him think a little.");
        _sleep(3000);
        con_clearScr();
        bool hit = gamerBoard.Shoot(X, Y);
        if (gamerBoard.AllShipsDestroyed())
            miss = true;
        if (!hit)
            miss = !miss;
        else {
            X = X + 1;
            Y = Y + 1;
        }
        con_gotoXY(0, 0);
        gamerBoard.Print();
    }
    return miss;
}

void startGame() {
    bool start = false;
    while (!start) {
        con_gotoXY(0, 0);
        con_outTxt(
                "Press ENTER to start or ESC to exit...\nMiss marks as *, damaged ship as x and destroyed ship as !\nCoordinates can only be numbers, other characters will be ignored!");
        int key;
        if (con_keyPressed()) {
            key = con_getKey();
            switch (key) {
                case CON_KEY_ESCAPE:
                    exit(0);

                case CON_KEY_ENTER:
                    con_clearScr();
                    start = true;
                    break;
                default:
                    continue;
            }
        }

    }
}

bool gameProcess(GameBoard &gamerBoard, GameBoard &botBoard) {
    bool gamerTurn = true;
    while (!botBoard.AllShipsDestroyed() and !gamerBoard.AllShipsDestroyed()) {
        con_gotoXY(15, 13);
        con_outTxt("Miss marks as *, damaged ship as x and destroyed ship as !");
        con_gotoXY(15, 14);
        con_outTxt("Upper field is yours, lower field belongs to bot.");
        con_gotoXY(0, 0);
        if (gamerTurn) {
            bool miss = false;
            while (!miss) {
                miss = gamerShoot(gamerBoard, botBoard);
            }
            gamerTurn = !gamerTurn;
            con_clearScr();
        } else {
            bool miss = false;
            while (!miss) {
                miss = botShoot(gamerBoard, botBoard);
            }
            gamerTurn = !gamerTurn;
            con_clearScr();
        }
    }
    bool win = false;
    if (botBoard.AllShipsDestroyed())
        win = true;
    return win;
}

void finishGame(bool win) {
    bool finish = false;
    con_clearScr();
    while (!finish) {
        if (win) {
            con_gotoXY(0, 0);
            con_outTxt("VICTORY!!!\nPress ESC to exit...");
        } else {
            con_gotoXY(0, 0);
            con_outTxt("Unfortunately you lost\nPress ESC to exit...");
        }
        int key;
        if (con_keyPressed()) {
            key = con_getKey();
            switch (key) {
                case CON_KEY_ESCAPE:
                    exit(0);

                case CON_KEY_ENTER:
                    con_clearScr();
                    finish = true;
                    break;
                default:
                    continue;
            }
        }
    }
}
