// minmax_Tree_visual_studio.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "functions.cpp"
#include "minmax.cpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    // initiator es para el jugador que inicia el juego, el humano o la máquina
    // table positions es una lista que me indica que posiciones del tablero ya fueron llenadas,
    bool initiator = 0;
    short position_symbol = 255; // este valor es para asignar una posición del tablero
    showMenu();
    // 1 si inicia el humano
    // 0 si inicia la máquina
    cin >> initiator;
    vector<bitset<2>> conf;
    for (int i = 0; i < 10; i++)
    { // el tablero empieza vacío
        conf.push_back(bitset<2>(string("00")));
    }
    tictactoe tic(0, conf); // creo el tablero tic
    std::cin.clear();       // limpiamos el buffer, para que no haya ingún problema
    if (!initiator)
    {
        int rand_pos = rand() % 10;                 //la primera posición random que asigna la máquina
        tic.tb[rand_pos] = bitset<2>(string("01")); // una posición random del 0 al 9
        cout << "\n Movimiento de la maquina:\n";
        tic.show(); // y lo muestro
    }

    do
    {
        cout << "\ntu turno, ingresa un valor, que no este ocupado [0-8]: ";
        cin >> position_symbol;
    } while (position_symbol < 0 || position_symbol > 8 || tic.tb[position_symbol].to_string() != "00"); // mientras la posición no esté entre 0 y 8
    tic.tb[position_symbol] = bitset<2>(string("10"));                                                   // inserto el valor o->"10", en la posición indicada

    MinMax_Tree mytree(tic);     // creo el árbol
    mytree.build_min_max_tree(); // construyo el árbol minimax para elegir el siguiente mejor movimiento
    cout << "\n Movimiento de la maquina:\n";
    mytree.best_move->show();                    // muestro el movimiento de la máquina
    tic.set_configuration(mytree.best_move->tb); // a mi tablero, le asigno el tablero llenado por la máquina

    // hasta que no gane nadie, continúo el juego, o la tabla esté llena, lo que significa empate
    while (!tic.table_full() && tic.score != -1000 && tic.score != 1000)
    {
        do
        {
            cout << "\ntu turno, ingresa un valor, que no este ocupado [0-8]: ";
            cin >> position_symbol;
        } while (position_symbol < 0 || position_symbol > 8 || tic.tb[position_symbol].to_string() != "00"); // mientras la posición no esté entre 0 y 8
        tic.tb[position_symbol] = bitset<2>(string("10"));                                                   // inserto el valor o->"10", en la posición indicada
        tic.show();

        cout << "\n";
        mytree.set_new_root(tic);    // genero otro árbol basándome en el nuevo movimiento del oponente
        mytree.build_min_max_tree(); // construyo el arbol minmax
        cout << "\n Movimiento de la maquina:\n";
        mytree.best_move->show();                    // muestro el movimiento de la máquina
        tic.set_configuration(mytree.best_move->tb); // a mi tablero, le asigno el tablero llenado por la máquina
    }

    if (tic.score == -1000) // significa que ganó el humano
        cout << "felicidades ganaste\n";
    else if (tic.score == 1000) // gano la máquina
        cout << "lo siento perdiste, intentalo una vez mas\n";
    else
        cout << "empate, sigue jugando\n";
    system("PAUSE");
    return 0;
}
