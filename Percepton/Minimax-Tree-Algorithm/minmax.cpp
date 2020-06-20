#include <bitset>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
// la clase para una jugada de 3 en raya
class tictactoe
{
public:
    // tb es el tablero de 9 casillas
    // conteniendo 3 estados en binario
    // vacío->00(0), x->01(1), o->10(2)
    vector<bitset<2>> tb;
    // el id de mi nodo
    int id;
    // los nodos hijos del nodo tictactoe
    vector<tictactoe *> nodes;
    // referencia al padre del nodo
    tictactoe *ancestor;
    // cada tablero tendrá su score con respecto a "x"
    short score = 0;

    // acepta el id del nodo tictactoe
    // la configuración del tablero y un nodo puntero al padre,
    // por defecto NULL
    tictactoe(int new_id, vector<bitset<2>> conf, tictactoe *parent = NULL)
    {
        id = new_id;
        for (int i = 0; i < conf.size(); i++)
            tb.push_back(conf[i]);
        // al momento de la construcción se autogenerará un score
        score = this->generate_score();
        ancestor = parent;
    }

    // this method simply sets a new configuration of my tictactoe board
    // conf must be of the same size of tb
    void set_configuration(vector<bitset<2>> conf)
    {
        for (int i = 0; i < conf.size(); i++)
            tb[i] = conf[i];
        this->score = this->generate_score();
        return;
    }

    // esta función simplemente cuenta cuántos espacios son no vacíos
    int count_symbols()
    {
        short symbols = 0;
        for (short i = 0; i < tb.size(); (tb[i++].to_string() != "00") ? symbols++ : symbols = symbols)
            ;
        return symbols;
    }

    // prints the tictactoe board on the screen
    void show()
    {
        string board[10];
        for (int i = 0; i < tb.size(); i++)
        {
            if (tb[i].to_string() == "00")
                board[i] = " ";
            else if (tb[i].to_string() == "01")
                board[i] = "x";
            else
                board[i] = "o";
        }
        cout << board[0] << " | " << board[1] << " | " << board[2] << "\n";
        cout << "---------\n";
        cout << board[3] << " | " << board[4] << " | " << board[5] << "\n";
        cout << "---------\n";
        cout << board[6] << " | " << board[7] << " | " << board[8] << "\n";
    }

    //esta función simplemente me indica si el tablero ya está lleno
    //true->si está lleno, false->todavía no está lleno
    bool table_full()
    {
        for (int i = 0; i < tb.size(); i++)
            if (tb[i].to_string() == "00")
                return false; // todavía no está lleno
        return true;          //está lleno
    }

    // esta función obtendrá el score para la máquina, primero sumando
    // los posibles tres en raya para el símbolo que esté usando la máquina
    // restándolos de los posibles tres en raya del humano
    // primero por defecto el símbolo para la máquina será la "x"
    // y si encuentra algún movimiento ganador, devolverá un valor muy grande
    // representando infinito por ejemplo 1000
    int generate_score()
    {
        int score_x = 0, score_o = 0;
        // evaluaremos los posibles 3 en raya de x y de o
        // a medida que pasamos por el tablero
        for (int i = 0; i < 9; i++)
        {
            if (tb[i].to_string() == "01") // si es x->01(1)
            {
                score_x += this->evaluate_tic_tac_toe_for_x(i);
                // encontró una jugada ganadora para x, así que devuelve 1000
                if (score_x >= 1000)
                    return 1000;
            }
            else if (tb[i].to_string() == "10") // si es o->10(2)
            {
                score_o += this->evaluate_tic_tac_toe_for_o(i);
                // encontró una jugada ganadora para o, así que devuelve -1000
                if (score_o <= -1000)
                    return -1000;
            }
        }
        // restamos las posibilidades de tres en raya de "x", con las de "o"
        return score_x - score_o;
    }
    // esta función evalúa si en esa posición se puede lograr
    // un tres en raya, para "x", tambipen devolver 1000 si
    // el movimiento es ganador para x
    int evaluate_tic_tac_toe_for_x(int i)
    {
        int result = 0;
        // primero evaluaré las esquinas de mi tablero
        // revisando la esquina superior izquierda
        if (i == 0)
        {
            if (tb[1].to_string() != "10" && tb[2].to_string() != "10")
                result++; //horizontal
            if (tb[3].to_string() != "10" && tb[6].to_string() != "10")
                result++; //vertical
            if (tb[4].to_string() != "10" && tb[8].to_string() != "10")
                result++; //diagonal
            // evalúo si el movimiento es ganador para x
            if (tb[1].to_string() == "01" && tb[2].to_string() == "01" ||
                tb[3].to_string() == "01" && tb[6].to_string() == "01" ||
                tb[4].to_string() == "01" && tb[8].to_string() == "01")
                return 1000;
        }
        // revisando la esquina superior derecha
        else if (i == 2)
        {
            if (tb[1].to_string() != "10" && tb[0].to_string() != "10")
                result++; //horizontal
            if (tb[5].to_string() != "10" && tb[8].to_string() != "10")
                result++; //vertical
            if (tb[4].to_string() != "10" && tb[6].to_string() != "10")
                result++; //diagonal
            // evalúo si el movimiento es ganador para x
            if (tb[1].to_string() == "01" && tb[0].to_string() == "01" ||
                tb[5].to_string() == "01" && tb[8].to_string() == "01" ||
                tb[4].to_string() == "01" && tb[6].to_string() == "01")
                return 1000;
        }
        // revisando la esquina inferior izquierda
        else if (i == 6)
        {
            if (tb[7].to_string() != "10" && tb[8].to_string() != "10")
                result++; //horizontal
            if (tb[3].to_string() != "10" && tb[0].to_string() != "10")
                result++; //vertical
            if (tb[4].to_string() != "10" && tb[2].to_string() != "10")
                result++; //diagonal
            // evalúo si el movimiento es ganador para x
            if (tb[7].to_string() == "01" && tb[8].to_string() == "01" ||
                tb[3].to_string() == "01" && tb[0].to_string() == "01" ||
                tb[4].to_string() == "01" && tb[2].to_string() == "01")
                return 1000;
        }
        // revisando la esquina inferior derecha
        else if (i == 8)
        {
            if (tb[7].to_string() != "10" && tb[6].to_string() != "10")
                result++; //horizontal
            if (tb[5].to_string() != "10" && tb[2].to_string() != "10")
                result++; //vertical
            if (tb[4].to_string() != "10" && tb[0].to_string() != "10")
                result++; //diagonal
            // evalúo si el movimiento es ganador para x
            if (tb[7].to_string() == "01" && tb[6].to_string() == "01" ||
                tb[5].to_string() == "01" && tb[2].to_string() == "01" ||
                tb[4].to_string() == "01" && tb[0].to_string() == "01")
                return 1000;
        }
        //luego evalúo las posiciones laterales
        else if (i == 1)
        {
            if (tb[0].to_string() != "10" && tb[2].to_string() != "10")
                result++; //horizontal
            if (tb[4].to_string() != "10" && tb[7].to_string() != "10")
                result++; //vertical
            // evalúo si el movimiento es ganador para x
            if (tb[0].to_string() == "01" && tb[2].to_string() == "01" ||
                tb[4].to_string() == "01" && tb[7].to_string() == "01")
                return 1000;
        }
        else if (i == 3)
        {
            if (tb[4].to_string() != "10" && tb[5].to_string() != "10")
                result++; //horizontal
            if (tb[0].to_string() != "10" && tb[6].to_string() != "10")
                result++; //vertical
            // evalúo si el movimiento es ganador para x
            if (tb[4].to_string() == "01" && tb[5].to_string() == "01" ||
                tb[0].to_string() == "01" && tb[6].to_string() == "01")
                return 1000;
        }
        else if (i == 5)
        {
            if (tb[3].to_string() != "10" && tb[4].to_string() != "10")
                result++; //horizontal
            if (tb[2].to_string() != "10" && tb[8].to_string() != "10")
                result++; //vertical
            // evalúo si el movimiento es ganador para x
            if (tb[3].to_string() == "01" && tb[4].to_string() == "01" ||
                tb[2].to_string() == "01" && tb[8].to_string() == "01")
                return 1000;
        }
        else if (i == 7)
        {
            if (tb[6].to_string() != "10" && tb[8].to_string() != "10")
                result++; //horizontal
            if (tb[4].to_string() != "10" && tb[1].to_string() != "10")
                result++; //vertical
            // evalúo si el movimiento es ganador para x
            if (tb[6].to_string() == "01" && tb[8].to_string() == "01" ||
                tb[4].to_string() == "01" && tb[1].to_string() == "01")
                return 1000;
        }
        // el que sobra es el casillero del centro i = 4
        else
        {
            if (tb[3].to_string() != "10" && tb[5].to_string() != "10")
                result++; //horizontal
            if (tb[1].to_string() != "10" && tb[7].to_string() != "10")
                result++; //vertical
            if (tb[0].to_string() != "10" && tb[8].to_string() != "10")
                result++; //diagonal
            if (tb[2].to_string() != "10" && tb[6].to_string() != "10")
                result++; //diagonal
            // evalúo si el movimiento es ganador para x
            if (tb[3].to_string() == "01" && tb[5].to_string() == "01" ||
                tb[1].to_string() == "01" && tb[7].to_string() == "01" ||
                tb[0].to_string() == "01" && tb[8].to_string() == "01" ||
                tb[2].to_string() == "01" && tb[6].to_string() == "01")
                return 1000;
        }
        return result;
    }

    // esta función evalúa si en esa posición se puede lograr
    // un tres en raya, para "o", tambipen devolver -1000 si
    // el movimiento es ganador para o
    int evaluate_tic_tac_toe_for_o(int i)
    {
        int result = 0;
        // primero evaluaré las esquinas de mi tablero
        // revisando la esquina superior izquierda
        if (i == 0)
        {
            if (tb[1].to_string() != "01" && tb[2].to_string() != "01")
                result++; //horizontal
            if (tb[3].to_string() != "01" && tb[6].to_string() != "01")
                result++; //vertical
            if (tb[4].to_string() != "01" && tb[8].to_string() != "01")
                result++; //diagonal
            // evalúo si el movimiento es ganador para o
            if (tb[1].to_string() == "10" && tb[2].to_string() == "10" ||
                tb[3].to_string() == "10" && tb[6].to_string() == "10" ||
                tb[4].to_string() == "10" && tb[8].to_string() == "10")
                return -1000;
        }
        // revisando la esquina superior derecha
        else if (i == 2)
        {
            if (tb[1].to_string() != "01" && tb[0].to_string() != "01")
                result++; //horizontal
            if (tb[5].to_string() != "01" && tb[8].to_string() != "01")
                result++; //vertical
            if (tb[4].to_string() != "01" && tb[6].to_string() != "01")
                result++; //diagonal
            // evalúo si el movimiento es ganador para o
            if (tb[1].to_string() == "10" && tb[0].to_string() == "10" ||
                tb[5].to_string() == "10" && tb[8].to_string() == "10" ||
                tb[4].to_string() == "10" && tb[6].to_string() == "10")
                return -1000;
        }
        // revisando la esquina inferior izquierda
        else if (i == 6)
        {
            if (tb[7].to_string() != "01" && tb[8].to_string() != "01")
                result++; //horizontal
            if (tb[3].to_string() != "01" && tb[0].to_string() != "01")
                result++; //vertical
            if (tb[4].to_string() != "01" && tb[2].to_string() != "01")
                result++; //diagonal
            // evalúo si el movimiento es ganador para o
            if (tb[7].to_string() == "10" && tb[8].to_string() == "10" ||
                tb[3].to_string() == "10" && tb[0].to_string() == "10" ||
                tb[4].to_string() == "10" && tb[2].to_string() == "10")
                return -1000;
        }
        // revisando la esquina inferior derecha
        else if (i == 8)
        {
            if (tb[7].to_string() != "01" && tb[6].to_string() != "01")
                result++; //horizontal
            if (tb[5].to_string() != "01" && tb[2].to_string() != "01")
                result++; //vertical
            if (tb[4].to_string() != "01" && tb[0].to_string() != "01")
                result++; //diagonal
            // evalúo si el movimiento es ganador para o
            if (tb[7].to_string() == "10" && tb[6].to_string() == "10" ||
                tb[5].to_string() == "10" && tb[2].to_string() == "10" ||
                tb[4].to_string() == "10" && tb[0].to_string() == "10")
                return -1000;
        }
        //luego evalúo las posiciones laterales
        else if (i == 1)
        {
            if (tb[0].to_string() != "01" && tb[2].to_string() != "01")
                result++; //horizontal
            if (tb[4].to_string() != "01" && tb[7].to_string() != "01")
                result++; //vertical
            // evalúo si el movimiento es ganador para o
            if (tb[0].to_string() == "10" && tb[2].to_string() == "10" ||
                tb[4].to_string() == "10" && tb[7].to_string() == "10")
                return -1000;
        }
        else if (i == 3)
        {
            if (tb[4].to_string() != "01" && tb[5].to_string() != "01")
                result++; //horizontal
            if (tb[0].to_string() != "01" && tb[6].to_string() != "01")
                result++; //vertical
            // evalúo si el movimiento es ganador para o
            if (tb[4].to_string() == "10" && tb[5].to_string() == "10" ||
                tb[0].to_string() == "10" && tb[6].to_string() == "10")
                return -1000;
        }
        else if (i == 5)
        {
            if (tb[3].to_string() != "01" && tb[4].to_string() != "01")
                result++; //horizontal
            if (tb[2].to_string() != "01" && tb[8].to_string() != "01")
                result++; //vertical
            // evalúo si el movimiento es ganador para o
            if (tb[3].to_string() == "10" && tb[4].to_string() == "10" ||
                tb[2].to_string() == "10" && tb[8].to_string() == "10")
                return -1000;
        }
        else if (i == 7)
        {
            if (tb[6].to_string() != "01" && tb[8].to_string() != "01")
                result++; //horizontal
            if (tb[4].to_string() != "01" && tb[1].to_string() != "01")
                result++; //vertical
            // evalúo si el movimiento es ganador para o
            if (tb[6].to_string() == "10" && tb[8].to_string() == "10" ||
                tb[4].to_string() == "10" && tb[1].to_string() == "10")
                return -1000;
        }
        // el que sobra es el casillero del centro i = 4
        else
        {
            if (tb[3].to_string() != "01" && tb[5].to_string() != "01")
                result++; //horizontal
            if (tb[1].to_string() != "01" && tb[7].to_string() != "01")
                result++; //vertical
            if (tb[0].to_string() != "01" && tb[8].to_string() != "01")
                result++; //diagonal
            if (tb[2].to_string() != "01" && tb[6].to_string() != "01")
                result++; //diagonal
            // evalúo si el movimiento es ganador para o
            if (tb[3].to_string() == "10" && tb[5].to_string() == "10" ||
                tb[1].to_string() == "10" && tb[7].to_string() == "10" ||
                tb[0].to_string() == "10" && tb[8].to_string() == "10" ||
                tb[2].to_string() == "10" && tb[6].to_string() == "10")
                return -1000;
        }
        return result;
    }

    // este método generará las posibles jugadas para mi tablero
    // de acuerdo al turno del jugador "x"->"01" o "o"->"10"
    void generate_children_plays(string turn)
    {
        if (this->score != -1000 && this->score != 1000)
        {
            for (int i = 0, id = 0; i < tb.size(); i++)
            {
                // si el espacio está vacío, podemos asignar el símbolo
                if (tb[i].to_string() == "00")
                {
                    vector<bitset<2>> conf = tb;
                    conf[i] = bitset<2>(turn);
                    tictactoe *child = new tictactoe(id++, conf, this);
                    nodes.push_back(child);
                }
            }
        }
    }

    ~tictactoe()
    {
        if (!this->nodes.empty())
        {
            for (int i = 0; i < this->nodes.size(); i++)
                delete nodes[i];
        }
        tb.clear();
        nodes.clear();
        ancestor = NULL;
    };
};

// esta clase ya está considerada como el árbol para distintos
// tableros de 3 en raya
class MinMax_Tree
{
private:
    // p es la profundidad a la que se creará el árbol
    // se cuentan a partir de 0, es decir si p es 2, entonces
    // habrá el piso 0, 1, 2, en cuentas normales 3 pisos o p+1 pisos
    int p = 3;

public:
    // best_move será el nodo raíz de mi árbol
    tictactoe *best_move = NULL;

    // como constructor recibiremos una jugada cualquiera, y la asignaremos
    // al nodo raíz
    MinMax_Tree(tictactoe move)
    {
        best_move = new tictactoe(move.id, move.tb); // se geenera el nodo raíz
        best_move->ancestor = NULL;                  // el nodo raíz no puede tener ancestro
    }

    //esta función eliminará nuestra raíz, y pondrá otra en su lugar
    void set_new_root(tictactoe move)
    {
        delete best_move;
        best_move = NULL;
        best_move = new tictactoe(move.id, move.tb); // se genera el nodo raíz
    }

    // cada vez que el jugador enemigo realice un movimiento,
    // se creará un árbol a minmax cierta profundidad, para escoger
    // nuestra mejor jugada es decir la de la máquina
    // como parámetro de construcción recibiremos una posición de juego
    // en el tablero, es el turno de la máquina, también debemos verificar
    // si el jugador ya ganó, el árbol decidirá el mejor movimiento, luego
    // lo guardará en el atributo best_move.
    // "position", será la ´que me indicará ´la posición en donde fué colocada la "x"
    void build_min_max_tree(tictactoe *node = NULL, int level = 0) // la función será recursiva
    {
        // primero generamos los hijos del nodo raíz, revisamos is no tuviese hijos
        // esto se verifica con que el parámetro node, si es NULL entonces estamos en la raíz
        // generamos las posibles jugadas para x, el símbolo de la máquina
        if (!node && level < p)
        {
            best_move->generate_children_plays("01"); // x->"01", porque es el turno de la máquina
            for (int i = 0; i < best_move->nodes.size(); i++)
                build_min_max_tree(best_move->nodes[i], level + 1); // llamo nuevamente a mi función para cada nuevo hijo del árbol

            // sumo 1 al nivel, porque se generó un nivel para la raíz
            // este for es para recorrer todos los posibles nodos, y extraer el de mejor
            // ya que al principio la raíz es max
            int max_score = -1000; //el peor valor que le asignaré será -1000
            short index = 0;
            for (int i = 0; i < best_move->nodes.size(); i++)
            {
                // si el score de mi hijo es el mayor de todos, lo escojo
                if (best_move->nodes[i]->score > max_score)
                {
                    index = i;
                    max_score = best_move->nodes[i]->score; // colocamos el máximo valor al nodo
                }
            }
            // si tengo hijos
            if (!best_move->nodes.empty())                                 // precaución para que no exista desbordamiento si no se posee nodos hijos
                best_move->set_configuration(best_move->nodes[index]->tb); // le colocamos la mejor configuración
        }
        else if (node && level < p) // si level todavía no ha llegado al nivel p máximo, sigo generando pisos
        {
            node->generate_children_plays(level % 2 ? "10" : "01"); // si level es par x->"01", si no, o->"10"
            for (int i = 0; i < node->nodes.size(); i++)
                build_min_max_tree(node->nodes[i], level + 1); // llamo nuevamente a mi función para cada nuevo hijo del árbol
            // este for es para recorrer todos los posibles nodos, y extraer el que tenga
            // el máximo valor, o el mínimo, esto lo sabré por el nivel en que esté
            if (level % 2)
            {                         // si el nivel en el que estoy es impar entonces debe ser el mínimo, ya que es el turno de "o", mi oponente
                int min_score = 1000; //le asignaré un valor grande para que escoja de mejor forma el menor
                short index = 0;
                for (int i = 0; i < node->nodes.size(); i++)
                {
                    // si el score de mi hijo es el menor de todos lo escojo
                    if (node->nodes[i]->score < min_score)
                    {
                        index = i;
                        min_score = node->nodes[i]->score;
                    }
                }
                if (!node->nodes.empty())                    // precaución para que no exista desbordamiento si no se posee nodos hijos
                    node->score = node->nodes[index]->score; // le colocamos la configuración de menor valor
            }
            else
            { // si no, el máximo pues es el turno de la máquina, "x"
                int max_score = -1000;
                short index = 0;
                for (int i = 0; i < node->nodes.size(); i++)
                {
                    // si el score de mi hijo es el mayor de todos, lo escojo
                    if (node->nodes[i]->score > max_score)
                    {
                        index = i;
                        max_score = node->nodes[i]->score;
                    }
                }
                if (!node->nodes.empty())                    // precaución para que no exista desbordamiento si no se posee nodos hijos
                    node->score = node->nodes[index]->score; // le colocamos la mejor configuración
            }
        }
        return;
    }

    // función para recorrer todo el árbol
    void bfs(tictactoe *node = NULL)
    {
        if (!node) // node es el padre, porque es vacío
        {
            best_move->show();
            cout << endl;
            for (int i = 0; i < best_move->nodes.size(); i++)
                bfs(best_move->nodes[i]);
        }
        else if (!node->nodes.empty()) // si el nodo tiene hijos
        {
            node->show();
            cout << endl;
            for (int i = 0; i < node->nodes.size(); i++)
                bfs(node->nodes[i]);
        }
        else
        { //solo muestro el nodo
            node->show();
        }
        return;
    }

    ~MinMax_Tree()
    {
        if (best_move)
        {
            delete best_move;
        }
    }
};
