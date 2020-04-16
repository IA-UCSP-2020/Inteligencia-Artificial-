//#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <math.h>
#include <GL\freeglut.h>
#include <concurrent_priority_queue.h>
#include <Windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <queue>
#include <list>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define KEY_ESC 27
#define ii pair<int,int>
#define ll long long
#define INF 1e9
#define forall(it,v) for(auto it = v.begin(); it!=v.end(); ++it) 
#define MAX 250001
#define sze(x) (int)x.size()
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)


using namespace std;

class Node {
public:
    int id;
    int x;
    int y;
    vector<pair<int, Node*>> nei;
    vector<ii> neiS;
    map<int, bool> indices;
    void addneigh(int weitgh, Node* n2) {
        if (indices[n2->id]) return;
        nei.push_back({weitgh,n2 });
        neiS.push_back({ weitgh,n2->id });
        indices[n2->id] = true;
    }
};



double distance(Node* a, Node* b) {
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}


class Graph {
public:
    vector<Node*> m_nodes;
    Graph(int N) :m_nodes(N*N) {
        int Y = 0;
        int index = 0;
        for (short i = 0; i < N; ++i) {
            int X = 0;
            for (short j = 0; j < N; ++j) {
                m_nodes[index] = new Node();
                m_nodes[index]->x = X;
                m_nodes[index]->y = Y;
                m_nodes[index]->id = index;
                ++index;
                ++X;
            }
            ++Y;
        }

        index = 0;
        for (short i = N + 1; i <= ((N * N) - (N + 2)); i += N) {
            for (short j = 0; j < N - 2; ++j) {
                add_nodes(i + j, i + j - 1);
                add_nodes(i + j, i + j + 1);
                add_nodes(i + j, i + j + N);
                add_nodes(i + j, i + j + N - 1);
                add_nodes(i + j, i + j + N + 1);
                add_nodes(i + j, i + j - N);
                add_nodes(i + j, i + j - N - 1);
                add_nodes(i + j, i + j - N + 1);
            }
        }
        for (int i = 0; i < N - 1; ++i)
            add_nodes(i, i + 1);
   
        for (int i = (N * N) - N; i < (N * N) - 1; ++i) 
            add_nodes(i, i + 1);
        
        for (int i = 0; i <= (N * N) - 2 * N; i += N) 
            add_nodes(i, i + N);
        
        for (int i = N - 1; i < (N * N) - 1; i += N) 
            add_nodes(i, i + N);
    }

    double distance(Node* a, Node* b) {
        return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
    }

    void add_nodes(int n1, int n2) {
        m_nodes[n1]->addneigh(distance(m_nodes[n1], m_nodes[n2]), m_nodes[n2]);
        m_nodes[n2]->addneigh(distance(m_nodes[n2], m_nodes[n1]), m_nodes[n1]);
    }

    void show_nodes_graph() {
        for (short i = 0; i < m_nodes.size(); ++i) {
            if (i % 5 == 0 && i != 0)
                cout << endl;
            cout << m_nodes[i]->id << " ( " << m_nodes[i]->x << " " << m_nodes[i]->y << " ) ";

        }
    }

    void show_nodes_conection() {
        for (short i = 0; i < m_nodes.size(); ++i) {
            cout << "\n" << m_nodes[i]->id << " ( " << m_nodes[i]->x << ";" << m_nodes[i]->y << " ) " << " tiene conexiones con : ";
            for (short j = 0; j < m_nodes[i]->nei.size(); ++j) {
                cout << "\n\t" << m_nodes[i]->nei[j].second->id;
            }
        }
    }

    Node* operator[](int i) {
        return m_nodes[i];
    }

/*
    ll dijkstra(int being, int end) {
        map<int, bool> eliminated_node;
        vector<int> path(m_nodes.size(), -1);
        int finalpath;
        priority_queue<ii, vector<ii>, greater<ii> > A;
        vector<ll> dist(m_nodes.size() * m_nodes.size(), INF); vector<int> dad(m_nodes.size() * m_nodes.size(), -1);
    }
*/
};

inline double h(Node* a, Node* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}


int n_nodes = 5;
map<int, bool> eliminated_node;
Graph G(n_nodes);
vector<int> pat(n_nodes * n_nodes, -1);
int finalpath;
ll dijkstra(int being, int end) {   
    priority_queue<ii, vector<ii>, greater<ii> > A;
    vector<ll> dist(n_nodes * n_nodes, INF); 
    vector<int> dad(n_nodes * n_nodes, -1);
    A.push(make_pair(0, being));
    dist[being] = 0;

    while (sze(A)) {
        ii p = A.top(); A.pop();
        if (p.second == end) break;
 //       cout << "\n p First : " << p.first << " p Second : " << p.second;
 //       cout << "\n size of A : " << sze(A);
        forall(it, G[p.second]->nei) 
            if (dist[p.second] + it->first < dist[it->second->id] && eliminated_node[p.second] != true) {

  /*              cout << "\n" << dist[p.second] << " + " <<it->second->id<<" -> " <<it->first << " < " << dist[it->second->id] << " and "<< eliminated_node[p.second] <<"\n";*/
                dist[it->second->id] = dist[p.second] + it->first + h(G[p.second], it->second);
 //               cout << "\n" << dist[it->second->id] << " = " << dist[p.second] << "+" << it->first <<"+" << h(G[p.second], it->second);
                dad[it->second->id] = p.second;
 //               cout << "\n change  dad " << dad[it->second->id] << " = " << p.second;
 //               cout << "\n it->id  " << it->second->id;
                A.push(make_pair(dist[it->second->id], it->second->id));
 //               cout << "\n A push --->   first : " << A.top().first << " second  : " << A.top().second;
 //               cout << "\n---------------------------------------------------\n";
            }
    }
    /*
    cout << "\n Dad : ";
    for (short i = 0; i < dad.size(); ++i) {
        cout << "\n" << dad[i];
    }
    */
    pat = dad;


    finalpath = end;
    if (dist[end] < INF) {
        for (short i = end; i != -1; i = dad[i]) {
            printf("%d%c", i, (i == end ? '\n' : ' '));
        }
    }
    return dist[end];
}

vector<int> v(n_nodes* n_nodes);
bool dfs(int being, int end) {
    finalpath = end;
    if (being == end) {return 1; }
    forall(it, G[being]->nei) {
        if (!v[it->second->id] && eliminated_node[it->second->id] != true) {
            v[it->second->id] = 1;
            pat[it->second->id] = being;
            int d = dfs(it->second->id, end);
            if (d)return 1;
        }
    }
    return 0;
}


void displayGizmo() {
    for (int i = 0; i < G.m_nodes.size(); ++i) {
        glColor3d(1, 1, 1);              //// refondo
        glBegin(GL_POLYGON);
        //cout << "coordenadas " << G[i]->x << ' ' << G[i]->y << endl;
        glVertex2d(G[i]->x + 0.5, G[i]->y + 0.5);
        glVertex2d(G[i]->x + 0.5, G[i]->y - 0.5);
        glVertex2d(G[i]->x - 0.5, G[i]->y - 0.5);
        glVertex2d(G[i]->x - 0.5, G[i]->y + 0.5);
        glEnd();
    }
    for (int i = finalpath; i != -1; i = pat[i]) {
        glColor3d(1, 1, 0);               //// camino extra 
        glBegin(GL_POLYGON);
        //cout << "coordenadas " << G[i]->x << ' ' << G[i]->y << endl;
        glVertex2d(G[i]->x + 0.5, G[i]->y + 0.5);
        glVertex2d(G[i]->x + 0.5, G[i]->y - 0.5);
        glVertex2d(G[i]->x - 0.5, G[i]->y - 0.5);
        glVertex2d(G[i]->x - 0.5, G[i]->y + 0.5);
        glEnd();
    }

    forall(it, eliminated_node) {
        if (it->second) {                 
            glColor3d(1, 0, 0);            //// nodos eliminados
            glBegin(GL_POLYGON);
            //cout << "coordenadas " << G[i]->x << ' ' << G[i]->y << endl;
            glVertex2d(G[it->first]->x + 0.5, G[it->first]->y + 0.5);
            glVertex2d(G[it->first]->x + 0.5, G[it->first]->y - 0.5);
            glVertex2d(G[it->first]->x - 0.5, G[it->first]->y - 0.5);
            glVertex2d(G[it->first]->x - 0.5, G[it->first]->y + 0.5);
            glEnd();
        }
    }

    for (int i = 0; i < G.m_nodes.size(); ++i) {
        glColor3d(0, 1, 0);             /// nodos del tablero 
        glBegin(GL_POLYGON);
        //cout << "coordenadas " << G[i]->x << ' ' << G[i]->y << endl;
        glVertex2d(G[i]->x + 0.3, G[i]->y + 0.3);
        glVertex2d(G[i]->x + 0.3, G[i]->y - 0.3);
        glVertex2d(G[i]->x - 0.3, G[i]->y - 0.3);
        glVertex2d(G[i]->x - 0.3, G[i]->y + 0.3);
        glEnd();
    }

    for (int i = finalpath; pat[i] != -1; i = pat[i]) {
        glColor3d(0, 0, 1);        /// camino inicio - fin
        glBegin(GL_LINES);
        glVertex2d(G[i]->x, G[i]->y);
        glVertex2d(G[pat[i]]->x, G[pat[i]]->y);
        glEnd();
    }
}



void idle() { 
    glutPostRedisplay();
}

void OnMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //convertir x,y 
        //insertar un nuevo punto en el quadtree
    }
}

void OnMouseMotion(int x, int y)
{
    //opcional 
    //hacer algo x,z cuando se mueve el mouse
}


void glPaint(void) {
    //El fondo de la escena al color initial
    glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
    glLoadIdentity();
    glPushMatrix(); // save the current matrix
    glScalef(30, 30, 30); // scale the matrix
    glOrtho(-300.0f, 300.0f, -300.0f, 300.0f, -1.0f, 1.0f);
    //dibujar quadTree (qt->draw())

    //dibuja el gizmo
    displayGizmo();
    glPopMatrix(); // load the unscaled matrix
    //doble buffer, mantener esta instruccion al fin de la funcion
    glutSwapBuffers();
}


void init_GL(void) {
    //Color del fondo de la escena
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

    //modo projeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


}

GLvoid window_key(unsigned char key, int x, int y) {
    switch (key) {
    case KEY_ESC:
        exit(0);
        break;

    default:
        break;
    }

}



int main(int argc, char** argv)
{
 //   Graph A1(5);
 //   A1.show_nodes_graph();
 //   A1.show_nodes_conection();
    int n1;
    cout << "\n Ingrese el nodo de inicio : ";
    cin >> n1;
    int n2;
    cout << "\n Ingrese el nodo final : ";
    cin >> n2;
    int block = n_nodes*0.20;
    cout << "\n block = " << block;
    int random = 0;
    srand(time(NULL));
    while (block) {
        random = rand() % (n2-1) + n1;
     //   cout << "\n r : " << random;
        eliminated_node[random] = true;
        --block;
    }

    cout << endl;
    for (int i = finalpath; i != -1; i = pat[i])
        printf("%d%c", i, (i == 2 ? '\n' : ' '));
    cout << "Se termino exitosamente\n";


    dijkstra(n1, n2);
 //   dfs(n1, n2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP2 bis OpenGL : Bresenham");
    init_GL();
    glutDisplayFunc(glPaint);
    glutReshapeFunc(&window_redraw);
    glutKeyboardFunc(&window_key);
    glutMouseFunc(&OnMouseClick);
    glutMotionFunc(&OnMouseMotion);
    glutIdleFunc(&idle);
    glutMainLoop();



    return 0;
}









