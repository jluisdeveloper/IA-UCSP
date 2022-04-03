#include <iostream>
#include <vector>
#include <list>
#include <tuple>

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

void printChevere(int tablero[8][8])
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

    bool isTerminalNode(Nodo* node){
        int AI = 0,Human = 0;
        int moves = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                AI += (node->Board[i][j] == -1);
                Human += (node->Board[i][j] == 1);

                if( node->Board[i][j] != 0){
                    vector<tuple<bool,int,int>> possibleMoves ;
                    checkPossibilities(node->Board[i][j] , i,j, possibleMoves ,node->Board);
                    moves += possibleMoves.size();
                }
            }
        }

        //tie case
        if(!moves) return 1;

        //win case
        if( AI * Human == 0) return 1;

        return  0;
    }

    bool isValidPosition(int i ,int j){
        return i >= 0 && i <=7 && j>=0 && j<=7;
    }

    void checkPossibilities(int player ,int ii , int jj , vector<tuple<bool,int,int>> & moves , int board [8][8]){
        //check 2 possible moves depending of the type of player
        // AI = -1 ; Human = 1
        int i = player * -1;
        for (int j = -1 ; j <=1 ; j+=2) {

            if(isValidPosition(ii+i,jj+j)){

                int _i = ii +i;
                int _j = jj +j;

                if( board[_i][_j] == 0){
                    //move to empty cell
                    moves.push_back(make_tuple(0,_i,_j));
                }
                else if( board[_i][_j] == player*-1 &&  isValidPosition(ii+2*i , jj+2*j) && !board[ii+2*i][jj+2*j]  )
                {
                    //eat opponent
                    moves.push_back(make_tuple(1,ii+2*i,jj+2*j));
                }

            }
        }
    }



    void makeGameTree(Nodo* _node,int _depth, int player){

        //no node exist
        if(!_node) return;

        cout<<"\nBoard: "<<depth<<"\n";
        printChevere(_node->Board);
        cout<<"\n-----------------------------------------------------------------------------------------";

        if( _depth == 0 || isTerminalNode(_node)){
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
                    vector<tuple<bool,int,int>> possibleMoves ;
                    checkPossibilities(player , i,j, possibleMoves,_node->Board);

                    //create possibilities childs
                    for (int k = 0 ; k < possibleMoves.size() ;k++) {
                        int newBoard[8][8];
                        copiar(newBoard, _node->Board);


                        bool eat = get<0>(possibleMoves[k]);
                        int new_i = get<1>(possibleMoves[k]);
                        int new_j = get<2>(possibleMoves[k]);

                        //move
                        newBoard[i][j] = 0;
                        newBoard[new_i][new_j] = player;


                        if(eat){
                            newBoard[i+((new_i-i)/2)][j+((new_j-j)/2)] = 0;
                        }


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





int main() {



    GameTree t(tablero,2,1);
    t.makeGameTree(t.root,2,-1);

//    bool Player;
//    cout << "Quien empieza el juego? \n 0 = computadora,  1 = Player: ";
//    cin >> Player;
//    cout << endl << "Ingrese Profundidad de arbol: ";
//    cin >> maxDepth;
//
//    while (true) {
//
//        if (Player) {//movimiento Player
//            int x_i, y_i, x_f, y_f;
//
//            //agregar if                    ######
//
//
//            printChevere(tablero);
//
//
//            break;
//        } //fin del while
//    }


}
