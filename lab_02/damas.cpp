#include <iostream>
#include <vector>
#include <list>

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
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            t1[i][j] = t2[i][j];

        }
    }
}


struct Nodo {

    int Board[8][8];
    list<Nodo*> children;

    Nodo(int c[8][8]) {
        copiar(Board, c);
    }
};


struct GameTree{

    Nodo* root = 0;
    int depth;
    bool max;

    GameTree(int board[8][8] , int depth, bool max){
        root = new Nodo(board);
        this->depth = depth;
        this->max = depth & 1;
    }

    bool isTerminal(Nodo* node){

    }

    void checkPossibilities(int player ,int ii , int jj , vector<pair<int,int>> & moves){
        //check 2 possible moves depending of the type of player
        // AI = -1 ; Human = 1
        int i = player * -1;
        for (int j = -1 ; j <=1 ; j+=2) {
            if( ii+i >=0 && ii+i <= 7 && jj+j>=0 && jj+j<= 7){
                moves.push_back(make_pair(ii+i,jj+j));
            }
        }
    }

    void swap(int ){

    }

    void makeGameTree(Nodo* _node,int _depth, int player){
        if( _depth == 0 || isTerminal(_node)){
            return ;
        }

        // check possibilities for each piece
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                //find piece
                if(_node->Board[i][j] == player)
                {
                    vector<pair<int,int>> possibleMoves ;
                    checkPossibilities(player , i,j, possibleMoves);

                    //create possibilities childs
                    for (int k = 0 ; k < possibleMoves.size() ;k++) {
                        int newBoard[8][8];
                        copiar(newBoard, _node->Board);

                        int row = possibleMoves[i].first;
                        int col = possibleMoves[i].second;

                        //swap
                        int aux = newBoard[row][col];
                        newBoard[row][col] = newBoard[i][j];
                        newBoard[i][j] = aux;

                        //create child
                        Nodo* child = new Nodo(newBoard);
                        _node->children.push_back(child);

                        makeGameTree(child,_depth - 1 , player*-1);

                    }
                }


            }
        }





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
