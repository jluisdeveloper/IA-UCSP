#include <iostream>
#include <vector>

using namespace std;
#define INF 12345
int maxDepth;


int tablero[8][8] = {
{0, -1, 0, -1, 0, -1, 0, -1},
{-1, 0, -1, 0, -1, 0, -1, 0},
{0, -1, 0, -1, 0, -1, 0, -1},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 1, 0, 1, 0, 1, 0},
{0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 0}
};



void copiar(int t1[8][8], int t2[8][8]) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            t1[i][j] = t2[i][j];
}


struct Nodo {
    int BestBoard[8][8];
    int CurBoard[8][8];
    int depth;

    bool minimize;
    Nodo(int c[8][8], int d) {
        depth = d;
        copiar(CurBoard, c);
        minimize = depth & 1;
    }

};


/*void PrintTablero() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j)
            cout << tablero[i][j] << "\t";

        cout << endl;
    }
}*/

void printChevere()
{
    int rr, cc, pp;

    cout<<("  +---.---.---.---.---.---.---.---+\n");

    for (rr = 0; rr < 8; ++rr)
    {
        cout<<("%d |", rr);
        for (cc = 0; cc < 8; ++cc)
        {
            if (tablero[rr][cc] == 1) 
                cout << " # |";
            
            if (tablero[rr][cc] == -1) 
                cout << " $ |";
            
            if (tablero[rr][cc] == 0) 
                cout << "   |";
            

        }
        cout<<("\n");
        cout<<("  +---.---.---.---.---.---.---.---+\n");
    }

    cout<<("    0   1   2   3   4   5   6   7\n");
}




int main() {


    bool Player;
    cout << "Quien empieza el juego? \n 0 = computadora,  1 = Player: ";
    cin >> Player;
    cout << endl << "Ingrese Profundidad de arbol: ";
    cin >> maxDepth;

    while (true) {

        if (Player) {//movimiento Player
            int x_i, y_i, x_f, y_f;

            //agregar if                    ######


            printChevere();


            break;
        } //fin del while
    }


}
