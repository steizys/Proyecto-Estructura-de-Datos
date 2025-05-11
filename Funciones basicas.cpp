#include<Magbase.h>

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