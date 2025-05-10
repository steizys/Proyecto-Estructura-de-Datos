#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Carta{ //Nodos de cartas 
    string nombre;

    string pinta;
    Carta *next;
};
struct Jugador{// Nodos de Jugador
    int nombre;
    Jugador *next;
    Carta *lista_cartas; //Multilista que une a cada jugador con sus cartas
};
Carta *CrearCarta( string nombre, string pinta){ //Procedimiento para Crear las cartas del mazo
    Carta* nuevo_carta = new Carta;
    nuevo_carta->nombre= nombre;
    nuevo_carta->pinta= pinta;
    nuevo_carta->next= NULL;
    return nuevo_carta;


};
void CrearMazo(Carta **p){ //Llenar jugadores por cola
    string nombre="";
    string pinta="";
    for (int i = 1; i <= 13; i++){
        if(i==1){
            nombre="A";
        }else if(i==2){
            nombre="2";
        }else if(i==3){
            nombre="3";
        }else if(i==4){
            nombre="4";
        }else if(i==5){
            nombre="5";
        }else if(i==6){
            nombre="6";
        }else if(i==7){
            nombre="7";
        }else if(i==8){
            nombre="8";
        }else if(i==9){
            nombre="9";
        }else if(i==10){
            nombre="10";
        }else if(i==11){
            nombre="J";
        }else if(i==12){
            nombre="Q";
        }else if(i==13){
            nombre="K";
        }else{
        }
        for (int j = 0; j < 4; j++){
            Carta *carta = nullptr; 
            if(j==0){
                pinta="corazon";
            }else if(j==1){
                pinta="diamante";
            }else if(j==2){
                pinta="trebol";
            }else if(j==3){
                pinta="picas";
            }
           
            carta=CrearCarta(nombre, pinta);
            if (!(*p)){ // Si la lista está vacía
                *p = carta; // Inserta directamente
            }else{
                Carta *aux = *p;
                while (aux->next){ // Itera hasta el último nodo
                    aux = aux->next;
                }
                aux->next = carta; // Inserta al final
            }

        }

    }
    nombre="Joker";
    pinta="";
    Carta *carta=CrearCarta(nombre, pinta);
    Carta *aux = *p;
    while (aux->next){ // Itera hasta el último nodo
        aux = aux->next;
    }
    aux->next = carta; // Inserta al final
    Carta *carta2=CrearCarta(nombre, pinta);
    carta->next=carta2;
    
    

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

Jugador *BuscarJugador (Jugador *malla, int i){ //Busca el nodo del jugador por su nombre
    while (malla){
        if (malla->nombre==i){
            return malla;
        }
        malla=malla->next;
    }
    return NULL;
};

int ContarCartas(Carta* cartas){//Contar las cartas que tiene cada jugador
    int ncartas=0;
    while(cartas){
        ncartas++;
        cartas=cartas->next;
    }
    return ncartas;
};


void Reparticion(Carta **mazo, Jugador **malla) {  //Reparte de forma aleatoria las cartas del mazo a los jugadores
    srand(time(NULL)); // Inicializar la i una vez
    while (*mazo) { 
        Carta *carta = *mazo;
        *mazo = (*mazo)->next; // Sacamos carta de la cabeza del mazo
        carta->next = NULL; // Aseguramos que la carta a insertar no apunte a nada
        int i = rand() % 4 + 1;
        Jugador *jugador = BuscarJugador(*malla, i);
        if (ContarCartas(jugador->lista_cartas) <= 14) {
            Carta *aux=jugador->lista_cartas;
            if (!jugador->lista_cartas){
                jugador->lista_cartas=carta;
            }
            else{
                while (aux && aux->next){
                    aux=aux->next; //Ultima posicion de las cartas del jugador
                }
                aux->next=carta;
            }
        }
        
    }
}

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
        cout << p->nombre<< " | "<< p->pinta<< " "<<endl;
        p = p->next;
    }
};


///////////////////////////////////////////////////
///Insertar Sublista (Para Probar)
void SubLista(Carta **sublist, string nombre,  string pinta)
{
    Carta *newcarta = new Carta;
    newcarta->nombre= nombre;
    newcarta->pinta= pinta;
    newcarta->next = *sublist;
    *sublist = newcarta;
}
void InsertarCarta(Jugador *malla , int nombrej, string nombre, string pinta){
    Jugador *jugador = BuscarJugador(malla, nombrej); ////Me da el nodo del jugador al que quiero insertar una carta 
    SubLista(&(jugador->lista_cartas),nombre, pinta);
};
////////////////////////////////////////////////////
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
    InsertarCarta(Malla , 1, "3", "diamante");
    InsertarCarta(Malla , 1, "3","picas");
    CrearMazo(&Mazo);
    //CrearCarta(&Mazo,"3", "picas");
    //CrearCarta(&Mazo,"3", "trebol");
    MostrarCarta(Mazo);
    Reparticion(&Mazo, &Malla);
    cout<<"//// Jugador 1 ////"<<endl;
    Jugador *jugador = BuscarJugador(Malla, 1);
    MostrarCarta(jugador->lista_cartas);
    cout<<"//// Jugador 2 ////"<<endl;
    Jugador *jugador2 = BuscarJugador(Malla, 2);
    MostrarCarta(jugador2->lista_cartas);
    cout<<"//// Jugador 3 ////"<<endl;
    Jugador *jugador3 = BuscarJugador(Malla, 3);
    MostrarCarta(jugador3->lista_cartas);
    cout<<"//// Jugador 4 ////"<<endl;
    Jugador *jugador4 = BuscarJugador(Malla, 4);
    MostrarCarta(jugador4->lista_cartas);
    cout<<"----- Mazo -----"<<endl;
    MostrarCarta(Mazo);

    system("pause");

    return 0;
}