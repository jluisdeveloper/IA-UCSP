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
Point fin(3, 5);


template <class N, class E>
struct Node
{
    int id = 0;
    E x = 0;
    E y = 0;
    N DtO = 0;
    list<Node<N, E>*> edges;

    Node(E x1, E y1, E _id, N _distance)
    {
        x = x1;
        y = y1;
        id = _id;
        DtO = _distance;
    }
    Node(E x1, E y1)
    {
        x = x1;
        y = y1;
        id = 0;
        DtO = 0;
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

    typedef vector<Node<float, int>*> Route;
    typedef pair<Node<float, int>*, Route> Node1;


    //DFS as the name says   ._.
    void dfs() {
        cout << "\nDFS\n" << endl;
        cout << "Route\n\n: ";
        Route r;
        Node<float, int>* temp;//Node1 inicio;
        for (typename::list<Node<N, E>*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it) {
            if ((*it)->x == inicio.x && (*it)->y == inicio.y) {
                temp = (*it);
                break;
            }
        }

        Node1 n(temp, r);
        stack<Node1> Stack1;
        Stack1.push(n);

        while (!Stack1.empty()) {
            Node1 temp;
            temp = Stack1.top();
            Stack1.pop();

            if (temp.first->x == fin.x && temp.first->y == fin.y) {
                for (auto i : temp.second) {
                    cout << "(" << i->x << "," << i->y << ") -> ";
                }
 
                return;
            }

            for (typename::list<Node<N, E>*>::iterator it2 = temp.first->edges.begin(); it2 != temp.first->edges.end(); ++it2) {
                bool encontrado = false;

                for (auto j : temp.second) {
                    if ((*it2) == j) {
                        encontrado = true;
                        break;
                    }
                }


                if (!encontrado) {
                    Node1 n2;
                    n2.second = temp.second;//Route actual
                    n2.second.push_back(temp.first);//agregit2 Node1 actual a la Route
                    n2.first = (*it2);//agregit2 el nuevo Node1
                    Stack1.push(n2);
                }
            }
        }

    }

};


void tester(Graph<float, int> graph)
{
    //Printer of Remaning Nodes             ########test########
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it) {
        cout << (*it)->x << "," << (*it)->y << endl;
    }
}

int random(int x)
{
    return rand() % x;
}

//Node Deleter
void Del_node(int x, int Rows, int Columns, Graph<float, int> graph)
{
    srand((unsigned)time(0));
    vector<Point> Delt;
    for (int k = 0; k < x; k++) {

        int v1 = random(Rows);
        int v2 = random(Columns);

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
    cout << endl;
    tester(graph);
}


//Node connector, Horizontal, Vertical and Diagonal
void Connector(Graph<float, int> graph)
{
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it)
    {
        Node<float, int>** p;

        if (graph.exist(((*it)->x) - 1, ((*it)->y) - 1, p))
            (*it)->edges.push_back(*p); // Dig I +
        if (graph.exist(((*it)->x) - 1, ((*it)->y), p))
            (*it)->edges.push_back(*p); 
        if (graph.exist(((*it)->x) - 1, ((*it)->y) + 1, p))
            (*it)->edges.push_back(*p); // Dig D +
        if (graph.exist(((*it)->x), ((*it)->y) - 1, p))
            (*it)->edges.push_back(*p); 
        if (graph.exist(((*it)->x), ((*it)->y) + 1, p))
            (*it)->edges.push_back(*p); 
        if (graph.exist(((*it)->x) + 1, ((*it)->y) - 1, p))
            (*it)->edges.push_back(*p); // Dig I -
        if (graph.exist(((*it)->x) + 1, ((*it)->y), p))
            (*it)->edges.push_back(*p); 
        if (graph.exist(((*it)->x) + 1, ((*it)->y) + 1, p))
            (*it)->edges.push_back(*p); // Dig D -
    }

}

int main() {

    Graph<float, int> graph;

    int Columns, Rows;
    cout << "Insert Rows: ";
    cin >> Rows;
    cout << endl << "Insert Columns: ";
    cin >> Columns;

    //Node Creator
    int i = 0;
    while (i < Rows)
    {
        int j = 0;
        while (j < Columns)
        {
            Node<float, int>* tmp = new Node<float, int>(i, j);
            graph.insertNode(tmp);
            j++;
        }
        i++;
    }

    //Printer on Nodes                      ########test########
    tester(graph);

    Connector(graph);
    

    int y;
    cout << "Insert % to Delete: ";
    cin >> y;

    //Percentage Calculator
    int x = (Rows * Columns);
    x = x * y;
    x = x / 100;


    //Eliminador
    Del_node(x, Rows, Columns, graph);


    cout << endl;
    cout << "----------------------------------------------------------" << endl;
    graph.dfs();
    cout << endl;

    return 0;
}
