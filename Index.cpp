#include <string>
#include <iostream>

using namespace std;

struct Carta{ //Nodos de cartas 
    string nombre;
    int valor;
    string pinta;
    Carta *next;
};

struct Jugador{// Nodos de Jugador
    int nombre;
    Jugador *next;
    Carta *lista_cartas; //Multilista que une a cada jugador con sus cartas
};

void InsertarJugador(Jugador **p, int valor){ //Llenar jugadores por cola
    Jugador* nuevoJugador = new Jugador;
    nuevoJugador->nombre= valor;
    nuevoJugador->next= NULL;
    nuevoJugador->lista_cartas= NULL;
    if (!(*p)){ // Si la lista está vacía
        *p = nuevoJugador; // Inserta directamente
    }else{
        Jugador *aux = *p;
        while (aux->next){ // Itera hasta el último nodo
            aux = aux->next;
        }
        aux->next = nuevoJugador; // Inserta al final
    }

};
void CrearCarta(Carta **p, string nombre, int valor, string pinta ){ //Procedimiento para Crear las cartas del mazo
    Carta* nuevo_carta = new Carta;
    nuevo_carta->nombre= nombre;
    nuevo_carta->valor= valor;
    nuevo_carta->pinta= pinta;
    nuevo_carta->next= NULL;
    if (!(*p)){ // Si la lista está vacía
        *p = nuevo_carta; // Inserta directamente
    }else{
        Carta *aux = *p;
        while (aux->next){ // Itera hasta el último nodo
            aux = aux->next;
        }
        aux->next = nuevo_carta; // Inserta al final
    }

};

void MostrarJugador(Jugador *p){
    cout << "P->";
    while (p){
        cout << "[" << p->nombre<< "]-> ";
        p = p->next;
    }
    cout <<"NULL"<<endl;
};

void MostrarCarta(Carta *p){
    while (p){
        cout << p->nombre<< " | "<< p->pinta<< " | "<< p->valor<<endl;
        p = p->next;
    }
};

int main(){
    cout<<"Proyecto 1"<<endl;
    cout<<"Autoras: Amelie Moreno"<<endl;
    cout<<"         Gabriela Cantos"<<endl;
    cout<<"         Steizy Fornica"<<endl;

    Jugador *Malla = NULL;
    Carta *Mazo = NULL;

    InsertarJugador(&Malla,1);
    InsertarJugador(&Malla,2);
    InsertarJugador(&Malla,3);
    InsertarJugador(&Malla,4);
    MostrarJugador(Malla);
    CrearCarta(&Mazo,"3",1, "diamante");
    CrearCarta(&Mazo,"3",1, "picas");
    CrearCarta(&Mazo,"3",1, "trebol");
    MostrarCarta(Mazo);


    system("pause");

    return 0;
}