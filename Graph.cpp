#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
#include <vector>
#include <ctime>
#include <math.h>

using namespace std;


struct Point {
    int x, y;
    Point(int _x, int _y) :x(_x), y(_y) {}
    Point() { x = y = 0; }
};

Point inicio(0, 0);
Point fin(9,9 );


template <class N, class E>
struct Node
{
    int id = 0;
    E x = 0;
    E y = 0;
    N distanceToObjective = 0;
    list<Node<N, E>*> edges;

    Node(E x1, E y1, E _id, N _distance)
    {
        x = x1;
        y = y1;
        id = _id;
        distanceToObjective = _distance;
    }
    Node(E x1, E y1)
    {
        x = x1;
        y = y1;
        id = 0;
        distanceToObjective = 0;
    }
};

template <class N, class E>
struct Graph
{
    list<Node<N, E>*> Nodes;

    bool insertNode(Node<N, E>* newNode)
    {
        Nodes.push_back(newNode);
        return 1;
    }

    bool exist(E _x, E _y, Node<float, int>**& p)
    {
        for (list<Node<float, int>*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it)
        {
            if ((*it)->x == _x && (*it)->y == _y)
            {
                p = &(*it);
                return true;
            }
        }
        return false;
    }

};


//Node Deleter
void Del_node(int x, int filas, int columnas, Graph<float, int> graph)
{
    srand((unsigned)time(0));
    vector<Point> Delt;
    for (int k = 0; k < x; k++) {
        int v1 = rand() % filas;
        int v2 = rand() % columnas;

        if (v1 != inicio.x || v2 != inicio.y) 
        {
            if (v1 != fin.x || v2 != fin.y) 
                Delt.push_back(Point(v1, v2));
        }

    }

    cout << endl;
    cout << "Nodes Deleted " << endl << endl;
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it) {
        for (int i = 0; i < Delt.size(); i++) {
            if ((*it)->x == Delt[i].x && (*it)->y == Delt[i].y) 
            {

                cout << "(" << (*it)->x << "," << (*it)->y << ")" << " ";
                for (list<Node<float, int>*>::iterator et = (*it)->edges.begin(); et != (*it)->edges.end(); ++et) {
                    for (list<Node<float, int>*>::iterator at = (*et)->edges.begin(); at != (*et)->edges.end(); ++at) {
                        if ((*at)->x == Delt[i].x && (*at)->y == Delt[i].y) {
                            (*et)->edges.erase(at);
                            break;
                        }
                    }
                }
                graph.Nodes.erase(it--);
            }
        }
    }
}
int main() {

    Graph<float, int> graph;

    int columnas, filas;
    cout << "Ingresar F: ";
    cin >> filas;
    cout << endl << "Ingresar C: ";
    cin >> columnas;

    //Node Creator
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            Node<float, int>* tmp = new Node<float, int>(i, j);
            graph.insertNode(tmp);
        }
    }



    //Printer on Nodes
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it) {
        cout << (*it)->x << "," << (*it)->y << endl;
    }


    int y;
    cout << "Ingresar el porcentaje de nodos que desea Delt: ";
    cin >> y;

    //Percentage Calculator
    int x = (filas * columnas);
    x = x * y;
    x = x / 100;

    Del_node(x, filas, columnas, graph);


    cout << endl;
    //Printer of Remaning Nodes
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it) {
        cout << (*it)->x << "," << (*it)->y << endl;
    }

    return 0;
}