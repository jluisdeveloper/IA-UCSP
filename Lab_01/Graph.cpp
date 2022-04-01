//#include <GL/glut.h>  OPEN GL WITH GLUT
#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
#include <vector>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <queue>
#include <unordered_set>

using namespace std;

struct Point
{
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point() { x = y = 0; }
};

long long steps;
Point inicio(0, 0);
Point fin(3, 7);

// heuristic euclidian distance
inline float heuristic(int x, int y) { return sqrt(pow(fin.x - x, 2) + pow(fin.y - y, 2)); }

template <class N, class E>
struct Node
{
    int id = 0;
    E x = 0;
    E y = 0;
    N DtO = 0;
    N Fn = 0;
    N Gn = 0;
    Node<N, E>* cameFrom = 0;
    list<Node<N, E>*> edges;

    void getEdgeValue()
    {
    }

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
        id = Fn = 0;
        Gn = 9999999999;
        DtO = heuristic(x1, y1);
        cameFrom = 0;
    }
};

// compare functor to priority queue
struct CmpNodePtrs
{
    bool operator()(const Node<float, int>* a, const Node<float, int>* b) const
    {
        return a->Fn > b->Fn;
    }
};

template <class N, class E>
struct Graph
{
    list<Node<N, E>*> Nodes;
    Node<N, E>* inicio_ptr;

    bool insertNode(Node<N, E>* newNode)
    {
        Nodes.push_back(newNode);
        if (newNode->x == inicio.x && newNode->y == inicio.y) {
            inicio_ptr = newNode;
        }
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

    // DFS as the name says   ._.
    void dfs()
    {
        int counter = 0;
        cout << "\nDFS\n"
            << endl;
        cout << "Route\n\n: ";
        Route r;
        Node<float, int>* temp = inicio_ptr; // Node1 inicio;

        Node1 n(temp, r);
        stack<Node1> Stack1;
        Stack1.push(n);

        while (!Stack1.empty())
        {
            Node1 temp;
            temp = Stack1.top();
            Stack1.pop();

            if (temp.first->x == fin.x && temp.first->y == fin.y)
            {
                for (auto i : temp.second)
                    cout << "(" << i->x << "," << i->y << ") -> ";
                cout << "(" << fin.x << "," << fin.y << ")  ";
                cout << "\nPasos: " << counter << "\n";
                return;
            }

            for (typename ::list<Node<N, E>*>::iterator it2 = temp.first->edges.begin(); it2 != temp.first->edges.end(); ++it2)
            {
                bool encontrado = false;

                for (auto j : temp.second)
                {
                    counter++;
                    if ((*it2) == j)
                    {
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado)
                {
                    Node1 n2;
                    n2.second = temp.second;         // Route actual
                    n2.second.push_back(temp.first); // agregit2 Node1 actual a la Route
                    n2.first = (*it2);               // agregit2 el nuevo Node1
                    Stack1.push(n2);
                }
            }
        }
    }

    void bfs() {
        cout << "\nBFS\n\n";
        cout << "Route\n\n";
        Route r;
        Node<float, int>* tem;
        for (typename ::list<Node<N, E>*>::iterator it = Nodes.begin(); it != Nodes.end(); ++it) {
            if ((*it)->x == inicio.x && (*it)->y == inicio.y) {
                tem = (*it);
                break;
            }
        }
        Node1 n(tem, r);
        queue<Node1> myqueue;
        myqueue.push(n);

        while (!myqueue.empty()) {
            Node1 temp;
            temp = myqueue.front();
            myqueue.pop();
            if (temp.first->x == fin.x && temp.first->y == fin.y) {
                for (auto i : temp.second)
                    cout << "(" << i->x << "," << i->y << ") -> ";
                cout << "(" << fin.x << "," << fin.y << ")  ";
                return;
            }
            for (typename ::list<Node<N, E>*>::iterator it = temp.first->edges.begin(); it != temp.first->edges.end(); ++it) {
                bool aux = false;
                for (auto j : temp.second) {
                    if ((*it) == j) {
                        aux = true;
                        break;
                    }
                }
                if (!aux) {
                    Node1 tem;
                    tem.second = temp.second;
                    tem.second.push_back(temp.first);
                    tem.first = (*it);
                    myqueue.push(tem);
                }
            }
        }
    }

    float weightEdge(Node<N, E>* a, Node<N, E>* b)
    {
        return ((a->x - b->x) * (a->y - b->y) != 0) ? sqrt(2) : 1;
    }

    bool existNodeInQueue(priority_queue<Node<N, E>*, vector<Node<N, E>*>, CmpNodePtrs> temp, Node<N, E>* node)
    {
        while (!temp.empty())
        {
            if (temp.top() == node)
            {
                steps++;
                return 1;
            }
            temp.pop();
            steps++;
        }
        return 0;
    }

    void A_Start()
    {
        steps = 0;

        priority_queue<Node<N, E>*, vector<Node<N, E>*>, CmpNodePtrs> openList;
        unordered_set<Node<N, E>*> aux;

        Node<float, int>* temp = inicio_ptr; // Node1 inicio;

        // put the first node in the open list
        openList.push(temp);
        aux.insert(temp);


        // calculate the cost function
        // F(n) = g(n) + h(n)
        (*Nodes.begin())->Gn = 0;
        (*Nodes.begin())->Fn = (*Nodes.begin())->Gn + (*Nodes.begin())->DtO;

        steps += 7;
        while (!openList.empty())
        {

            // take the node with the smallest value of F(n)
            Node<N, E>* current = openList.top();
            steps++;

            if (current->x == fin.x && current->y == fin.y)
            {
                steps++;
                cout << "\nA* \n Route: \n";
                stack<Node<N, E>*> path;
                for (; current; current = current->cameFrom)
                    path.push(current);
                for (; !path.empty(); path.pop())
                    cout << "-> (" << path.top()->x << "," << path.top()->y << ")  ";
                cout << "\nPasos: " << steps;
                break;
            }

            openList.pop();
            steps++;

            // get children of n
            for (auto it = current->edges.begin(); it != current->edges.end(); it++)
            {

                auto itt = *it;
                int xx = (*it)->x;
                int yy = (*it)->y;
                float tentative_Gn = current->Gn + weightEdge(current, *it);
                steps += 4;

                if (tentative_Gn < (*it)->Gn)
                {
                    (*it)->cameFrom = current;
                    (*it)->Gn = tentative_Gn;
                    (*it)->Fn = tentative_Gn + (*it)->DtO;
                    steps += 3;

                    if (!existNodeInQueue(openList, *it))
                    {
                        openList.push(*it);
                        steps++;
                    }
                }

            }

        }

    }

    void BestFirst()
    {

        cout << endl;
        cout << "BEST FIRST " << endl;
        cout << endl;
        cout << "Route: " << endl
            << endl;
        Route r;
        Node<float, int>* temp = inicio_ptr; // Node1 inicio;

        Node1 n(temp, r);
        stack<Node1> _stack;
        _stack.push(n);

        while (!_stack.empty())
        {
            Node1 aux;
            aux = _stack.top();
            _stack.pop();

            if (aux.first->x == fin.x && aux.first->y == fin.y)
            {
                for (auto i : aux.second)
                {
                    cout << "(" << i->x << "," << i->y << ") -> ";
                }
                cout << "(" << fin.x << "," << fin.y << ")  ";
                return;
            }

            vector<pair<float, Node1>> distancias;

            for (typename ::list<Node<N, E>*>::iterator ar = aux.first->edges.begin(); ar != aux.first->edges.end(); ++ar)
            {
                bool encontrado = false;

                for (auto j : aux.second)
                {
                    if ((*ar) == j)
                    {
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado)
                {
                    pair<float, Node1> x;
                    x.first = heuristic(fin.x - (*ar)->x, fin.y - (*ar)->y);

                    Node1 n2;
                    n2.second = aux.second;
                    n2.second.push_back(aux.first);
                    n2.first = (*ar);

                    x.second = n2;
                    distancias.push_back(x);
                }
            }

            sort(distancias.begin(), distancias.end());
            reverse(distancias.begin(), distancias.end());

            for (int i = 0; i < distancias.size(); i++)
            {
                _stack.push(distancias[i].second);
            }
        }
    }
};

void tester(Graph<float, int> graph)
{
    // Printer of Remaning Nodes             ########test########
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it)
    {
        cout << (*it)->x << "," << (*it)->y << endl;
    }
}

int random(int x)
{
    return rand() % x;
}

// Node Deleter
void Del_node(int x, int Rows, int Columns, Graph<float, int> graph)
{
    srand((unsigned)time(0));
    vector<Point> Delt;
    for (int k = 0; k < x; k++)
    {

        int v1 = random(Rows);
        int v2 = random(Columns);

        if (v1 != inicio.x || v2 != inicio.y)
        {
            if (v1 != fin.x || v2 != fin.y)
                Delt.push_back(Point(v1, v2));
        }
    }

    cout << endl;
    cout << "Nodes Deleted " << endl
        << endl;
    for (list<Node<float, int>*>::iterator it = graph.Nodes.begin(); it != graph.Nodes.end(); ++it)
    {
        for (int i = 0; i < Delt.size(); i++)
        {
            if ((*it)->x == Delt[i].x && (*it)->y == Delt[i].y)
            {
                cout << "(" << (*it)->x << "," << (*it)->y << ")"
                    << " ";
                for (list<Node<float, int>*>::iterator et = (*it)->edges.begin(); et != (*it)->edges.end(); ++et)
                {
                    for (list<Node<float, int>*>::iterator at = (*et)->edges.begin(); at != (*et)->edges.end(); ++at)
                    {
                        if ((*at)->x == Delt[i].x && (*at)->y == Delt[i].y)
                        {
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

// Node connector, Horizontal, Vertical and Diagonal
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

void PrintExecutionTime(time_t start, time_t end)
{
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nTime taken by program is : " << fixed
        << time_taken;
    cout << " milisec ";
}

int main()
{

    Graph<float, int> graph;

    int Columns, Rows;
    cout << "Insert Rows: ";
    cin >> Rows;
    cout << endl
        << "Insert Columns: ";
    cin >> Columns;

    // Node Creator
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

    // Printer on Nodes                      ########test########
    tester(graph);

    Connector(graph);

    int y;
    cout << "Insert % to Delete: ";
    cin >> y;

    // Percentage Calculator
    int x = (Rows * Columns);
    x = x * y;
    x = x / 100;

    // Eliminador
    Del_node(x, Rows, Columns, graph);

    // measure execution Time
    time_t start, end;

    cout << "\n----------------------------------------------------------\n";
    time(&start);
    graph.dfs();
    time(&end);
    PrintExecutionTime(start, end);

    cout << "\n----------------------------------------------------------\n";
    time(&start);
    graph.bfs();
    time(&end);
    PrintExecutionTime(start, end);

    cout << "\n----------------------------------------------------------\n";
    time(&start);
    graph.BestFirst();
    time(&end);
    PrintExecutionTime(start, end);


    cout << "\n----------------------------------------------------------\n";
    time(&start);
    graph.A_Start();
    time(&end);
    PrintExecutionTime(start, end);

    cout << "\n----------------------------------------------------------\n";
    cout << endl;

    return 0;
}
