#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm> // Para transform

using namespace std;

struct Carta{ //Nodos de cartas 
    string nombre;
    string pinta;
    Carta *next;
};

struct CartaSimple{
    string nombre;
    CartaSimple *next;
};

struct Jugador{// Nodos de Jugador
    int nombre;
    int puntos;
    Jugador *next;
    Carta *lista_cartas; //Multilista que une a cada jugador con sus cartas
};

void InsercionCabeza(Carta**p, Carta *q){
        q->next= *p;
        *p=q;
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
        }
        for (int j = 0; j < 4; j++){
            Carta *carta = nullptr; 
            if(j==0){
                pinta="Corazon";
            }else if(j==1){
                pinta="Diamante";
            }else if(j==2){
                pinta="Trebol";
            }else if(j==3){
                pinta="Pica";
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
    nombre="JOKER";
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

void MostrarCarta(Carta *p){ 
    while (p){
        cout << p->nombre<< " "<< p->pinta<< " "<<endl;
        p = p->next;
    }
};

void InsertarJugador(Jugador **p, int valor){ //Llenar jugadores por cola
    Jugador* nuevoJugador = new Jugador;
    nuevoJugador->nombre= valor;
    nuevoJugador->puntos= 0;
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

void Reparticion(Carta **mazo, Jugador **malla) {
    srand(time(NULL));
    int cartas_repartidas = 0;
    int jugadores_con_14 = 0;

    while (*mazo) {
        // Seleccionar jugador aleatorio (1-4)
        int i = rand() % 4 + 1;
        Jugador *jugador = BuscarJugador(*malla, i);
        
        // Contar cartas del jugador
        int cartas_jugador = ContarCartas(jugador->lista_cartas);
        
        // Verificar si puede recibir más cartas
        if ((cartas_jugador < 14 && jugadores_con_14 < 2) || 
            (cartas_jugador < 13 && jugadores_con_14 >= 2)) {
            
            // Sacar carta del mazo
            Carta *carta = *mazo;
            *mazo = (*mazo)->next;
            carta->next = NULL;
            
            // Insertar carta al jugador
            if (!jugador->lista_cartas) {
                jugador->lista_cartas = carta;
            } else {
                Carta *ultima = jugador->lista_cartas;
                while (ultima->next) {
                    ultima = ultima->next;
                }
                ultima->next = carta;
            }
            
            // Actualizar contadores
            cartas_repartidas++;
            if (ContarCartas(jugador->lista_cartas) == 14) {
                jugadores_con_14++;
            }
        }
        
        // Condición de salida cuando todas las cartas están repartidas
        if (cartas_repartidas == 54) break;
    }
}



Carta* BuscarCartaNode(Carta *cartas, string nombre, string pinta){
    //&& cartas->next
    while (cartas){
        if (cartas->nombre==nombre && cartas->pinta==pinta) return cartas;
        cartas = cartas->next;
    }
    return NULL;
};


void MostrarJugador(Jugador *p){
    cout << "P->";
    while (p){
        cout << "[" << p->nombre<< "]-> ";
        p = p->next;
    }
    cout <<"NULL"<<endl;
};

bool BuscarCarta(Carta *cartas, string nombre, string pinta){
    if (cartas->nombre==nombre && cartas->pinta==pinta) return true;
    while (cartas){
        if (cartas->nombre==nombre && cartas->pinta==pinta) return true;
        cartas = cartas->next;
    }
    return false;
};

void LlenarJerarquia(CartaSimple **p){
    string nombre="";
    CartaSimple *joker = new CartaSimple;
    joker->nombre= "JOKER";
    joker->next=NULL;
    *p= joker;
                            
    for (int i=1; i<=13; i++){
        if(i==1){
            nombre="2";
        }else if(i==2){
            nombre="A";
        }else if(i==3){
            nombre="K";
        }else if(i==4){
            nombre="Q";
        }else if(i==5){
            nombre="J";
        }else if(i==6){
            nombre="10";
        }else if(i==7){
            nombre="9";
        }else if(i==8){
            nombre="8";
        }else if(i==9){
            nombre="7";
        }else if(i==10){
            nombre="6";
        }else if(i==11){
            nombre="5";
        }else if(i==12){
            nombre="4";
        }else if(i==13){
            nombre="3";
        }
        CartaSimple *nuevo = new CartaSimple;
        nuevo->nombre= nombre;
        nuevo->next=NULL;
        nuevo->next=*p;
        *p= nuevo;
    }
};

void MostrarJerarquia(CartaSimple *p){ 
    while (p){
        cout << p->nombre<< " ";
        p = p->next;
    }
};

int PosJerarquia(CartaSimple *Jerarquia, string nombre){
    CartaSimple *aux = Jerarquia;
    int cont=1;
    while(aux){
        if (aux->nombre==nombre){
            return cont;
        }
        aux=aux->next;
        cont+=1;
    }
    return 0;
};

int VecesAparicionValor (Carta*p, string value){ //Contas cuantas veces aparece una carta del mismo nombre
    int cont=0;
    Carta *aux= p;
    if (!p){
        return 0;
    }else{
        while (aux){
            if (aux->nombre==value) cont++;
            aux=aux->next;
        }
    }
    return cont;
};

void EliminarTodosEncuentros(Carta**p, string nombre){ //Eliminar los encuentros en donde aparece ese nombre
    if(!p) return;
    Carta *auxnum= *p;
    Carta *todelete; //nodo a eliminar
    Carta *auxprev; //nodo antes del numero a eliminar
    while (auxnum){
        if (auxnum->nombre==nombre){
            todelete = auxnum;
            auxnum=auxnum->next;
            if (!auxprev) {
                //nodo a eliminar es la cabeza
                *p = auxnum;
            } else {
                //nodo a eliminar no es la cabeza
                auxprev->next = auxnum;
            }
            delete todelete;
        } else {
            auxprev = auxnum;
            auxnum = auxnum->next;
        }
    }
}

void MostrarSi(Carta*p, string value){ //Mostrar las cartas que se quieren de un valor en especifico
    Carta *aux= p;
    while(aux){
        if (aux->nombre==value){
            cout << aux->nombre<< " "<< aux->pinta<< " "<<endl;
        }
        aux=aux->next;
    }
};

int CartasPermitidasPatronVali(Carta*p, int value){ //Cantidad de Cartas con el patron
    Carta *aux= p;
    int cant=0;
    Carta* mostradas = nullptr;
    while (aux) {
        if (VecesAparicionValor(p, aux->nombre) >= value) {
            // Verificamos si ya hemos mostrado cartas con este nombre
            Carta* temp_mostradas = mostradas;
            bool ya_mostrada = false;
            while (temp_mostradas) {
                if (temp_mostradas->nombre == aux->nombre) {
                    ya_mostrada = true;
                    break;
                }
                temp_mostradas = temp_mostradas->next;
            }
            // Si no hemos mostrado esta carta, mostramos todas las ocurrencias
            if (!ya_mostrada) {
                cant++;//indica la cantidad que hay en base al value
                // Agregamos el nombre a la lista de mostradas
                Carta* nueva_mostrada = new Carta; // No necesitamos la pinta aquí
                nueva_mostrada->nombre=aux->nombre;
                nueva_mostrada->pinta="";
                nueva_mostrada->next = mostradas;
                mostradas = nueva_mostrada;
            }
        }
        aux = aux->next;
    }
    // Liberamos la memoria de la lista 'mostradas'
    Carta* temp;
    while (mostradas) {
        temp = mostradas;
        mostradas = mostradas->next;
        delete temp;
    }
    cant+=VecesAparicionValor(p, "JOKER");

    return cant;

};

int CartasPermitidasJerarquia(Carta *CartasJ, int jerarquiaMesa, CartaSimple *Jerarquia,int value){ //Me indica si en las cartas del jugador existen cartas con jerarquia mayor a la de la mesa
    Carta *aux= CartasJ;
    int cant=0;
    Carta* mostradas = nullptr;
    while (aux) {
        if (VecesAparicionValor(CartasJ, aux->nombre) >= value) {
            // Verificamos si ya hemos mostrado cartas con este nombre
            Carta* temp_mostradas = mostradas;
            bool ya_mostrada = false;
            while (temp_mostradas) {
                if (temp_mostradas->nombre == aux->nombre) {
                    ya_mostrada = true;
                    break;
                }
                temp_mostradas = temp_mostradas->next;
            }
            // Si no hemos mostrado esta carta, mostramos todas las ocurrencias
            if (!ya_mostrada) {
                if (PosJerarquia(Jerarquia,aux->nombre)>jerarquiaMesa){
                    cant++;//indica la cantidad que hay en base al value Y LA JERARQUIA
                }
                
                // Agregamos el nombre a la lista de mostradas
                Carta* nueva_mostrada = new Carta; // No necesitamos la pinta aquí
                nueva_mostrada->nombre=aux->nombre;
                nueva_mostrada->pinta="";
                nueva_mostrada->next = mostradas;
                mostradas = nueva_mostrada;
            }
        }
        aux = aux->next;
    }
    // Liberamos la memoria de la lista 'mostradas'
    Carta* temp;
    while (mostradas) {
        temp = mostradas;
        mostradas = mostradas->next;
        delete temp;
    }
    return cant;
        
       
};
void CartasPermitidas(Carta*p, int value){
    Carta *aux= p;
    Carta* mostradas = nullptr;
    while (aux) {
        if (VecesAparicionValor(p, aux->nombre) >= value) {
            // Verificamos si ya hemos mostrado cartas con este nombre
            Carta* temp_mostradas = mostradas;
            bool ya_mostrada = false;
            while (temp_mostradas) {
                if (temp_mostradas->nombre == aux->nombre) {
                    ya_mostrada = true;
                    break;
                }
                temp_mostradas = temp_mostradas->next;
            }

            // Si no hemos mostrado esta carta, mostramos todas las ocurrencias
            if (!ya_mostrada) {
                MostrarSi(p, aux->nombre);
                // Agregamos el nombre a la lista de mostradas
                Carta* nueva_mostrada = new Carta; // No necesitamos la pinta aquí
                nueva_mostrada->nombre=aux->nombre;
                nueva_mostrada->pinta="";
                nueva_mostrada->next = mostradas;
                mostradas = nueva_mostrada;
            }
        }
        aux = aux->next;
    }

    // Liberamos la memoria de la lista 'mostradas'
    Carta* temp;
    while (mostradas) {
        temp = mostradas;
        mostradas = mostradas->next;
        delete temp;
    }
};
void DevolverCartasMazo (Carta**Mazo, Carta**CartaJ, Carta**CartaM){
    Carta *aux = *CartaJ;
    Carta *prev = nullptr;
    bool encontrado = false;
    // Buscar la carta *CartaM en la lista *CartaJ y mantener el nodo anterior
    while (aux) {
        if (aux == *CartaM) {
            encontrado = true;
            break;
        }
        prev = aux;
        aux = aux->next;
    }
    if (encontrado) {
        // Desconectar *CartaM de la lista *CartaJ
        if (prev == nullptr) {
            // Si *CartaM es la cabeza de *CartaJ
            *CartaJ = (*CartaM)->next;
        } else {
            // Si *CartaM no es la cabeza
            prev->next = (*CartaM)->next;
        }
        // Asegurarse de que la carta devuelta no esté enlazada a nada
        (*CartaM)->next = nullptr;
        // Devolver *CartaM al Mazo
        InsercionCabeza(Mazo, *CartaM);
    }
};
void DevolverCartasJugadasMazo(Carta**Mazo, Carta**CartasJugadas){
    Carta *aux= *CartasJugadas;
    while (aux && aux->next) {
        aux=aux->next;
    };
    aux->next=*Mazo;
    *Mazo=*CartasJugadas;
    *CartasJugadas=NULL;

};
///Insertar Sublista (Para Probar)
void SubLista(Carta **sublist, string nombre,  string pinta)
{
    Carta *newcarta = new Carta;
    newcarta->nombre= nombre;
    newcarta->pinta= pinta;
    newcarta->next = *sublist;
    *sublist = newcarta;
};

void InsertarCarta(Jugador *malla , int nombrej, string nombre, string pinta){
    Jugador *jugador = BuscarJugador(malla, nombrej); ////Me da el nodo del jugador al que quiero insertar una carta 
    SubLista(&(jugador->lista_cartas),nombre, pinta);
};

///////////////////////////////////////////////////////////////////////////
int main() {
    cout << "Proyecto 1 - Juego de Cartas Magnate" << endl;
    cout << "Autoras: Amelie Moreno, Gabriela Cantos, Steizy Fornica" << endl << endl;

    // Inicialización de estructuras
    Jugador *Malla = NULL;
    Carta *Mazo = NULL;
    CartaSimple *Jerarquia = NULL;
    Carta *CartasEnMesa = NULL; // Nueva lista para cartas en mesa

    // Llenado inicial
    LlenarJerarquia(&Jerarquia);
    for (int i = 1; i <= 4; i++) {
        InsertarJugador(&Malla, i);
    }
    CrearMazo(&Mazo);
    Reparticion(&Mazo, &Malla);

    // Variables del juego
    int j = 0; // Turno actual
    int partidas = 0;
    int ronda = 0, pasesConsecutivos = 0, patron = 1;
    int jugada = 0;
    int jerarCMesa = 0;
    bool rondaTerminada = false;
    int ultimoJugadorQueJugo = 0;
    bool tresDePicasEnMesa = false;

    // Bucle principal del juego
    while (partidas < 3) {
        cout << "\n=== PARTIDA " << partidas + 1 << " ===" << endl;
        ronda = 0;

        // Bucle de rondas
        while (ContarCartas(BuscarJugador(Malla, 1)->lista_cartas) > 0 &&
               ContarCartas(BuscarJugador(Malla, 2)->lista_cartas) > 0 &&
               ContarCartas(BuscarJugador(Malla, 3)->lista_cartas) > 0 &&
               ContarCartas(BuscarJugador(Malla, 4)->lista_cartas) > 0) {

            ronda++;
            pasesConsecutivos = 0;
            rondaTerminada = false;
            tresDePicasEnMesa = false;
            cout << "\n--- RONDA " << ronda << " ---" << endl;
            cout << "Patron actual: " << patron << " carta(s)" << endl;

            // Primera jugada especial
            if (ronda == 1 && jugada == 0) {
                for (int i = 1; i <= 4; i++) {
                    Jugador *jugador = BuscarJugador(Malla, i);
                    Carta *cartasjugador = jugador->lista_cartas;
                    if (BuscarCarta(cartasjugador, "3", "Diamante")) {
                        j = i;
                        ultimoJugadorQueJugo = j;
                        cout << "\nJugador " << j << " inicia la partida con el 3 de diamantes." << endl;
                        Carta *CartaMesa = BuscarCartaNode(cartasjugador, "3", "Diamante");
                        // Mover a cartas en mesa en lugar del mazo
                        DevolverCartasMazo(&CartasEnMesa, &cartasjugador, &CartaMesa);
                        patron = 1;
                        j++;
                        break;
                    }
                }
            } else {
                // Iniciar ronda con el último jugador que jugó
                j = ultimoJugadorQueJugo;
                cout << "\nJugador " << j << " inicia la ronda por ser el último que jugó." << endl;
            }

            // Bucle de turnos en la ronda
            while (pasesConsecutivos < 3 && !rondaTerminada) {
                if (j > 4) j = 1;

                Jugador *jugador = BuscarJugador(Malla, j);
                cout << "\nTurno del Jugador " << j << endl;

                // Mostrar estado actual
                cout<<" Mazo "<<endl;
                MostrarCarta(Mazo);
                cout << "Carta en mesa: " << (CartasEnMesa ? CartasEnMesa->nombre + " " + CartasEnMesa->pinta : "Ninguna") << endl;
                jerarCMesa = CartasEnMesa ? PosJerarquia(Jerarquia, CartasEnMesa->nombre) : 0;

                // Mostrar cartas del jugador
                cout << "\nTus cartas:" << endl;
                MostrarCarta(jugador->lista_cartas);

                // Si hay 3 de picas en mesa, nadie puede jugar
                if (tresDePicasEnMesa) {
                    cout << "\nHay un 3 de picas en mesa. Nadie puede jugar hasta nueva ronda." << endl;
                    pasesConsecutivos++;
                    j++;
                    system("pause");
                    continue;
                }

                // Mostrar opciones válidas
                if (patron > 1) {
                    cout << "\nPuedes jugar:" << endl;
                    CartasPermitidas(jugador->lista_cartas, patron);
                }

                // Opciones del jugador
                int op = 0;
                while (op != 1 && op != 2) {
                    cout << "\nOpciones:\n1. Lanzar cartas\n2. Pasar\nSeleccione: ";
                    cin >> op;
                    if (op != 1 && op != 2) {
                        cout << "Opcion invalida!" << endl;
                    }
                }

                if (op == 2) { // Pasar turno
                    pasesConsecutivos++;
                    cout << "Jugador " << j << " pasa su turno." << endl;
                    j++;
                } else { // Intentar jugar cartas
                    Carta *cartasjugador = jugador->lista_cartas;
                    int cantidadCartas = ContarCartas(cartasjugador);
                    int cantidadPatron = CartasPermitidasPatronVali(cartasjugador, patron);
                    int cantidadJerarquia = CartasPermitidasJerarquia(cartasjugador, jerarCMesa, Jerarquia, patron);

                    // Verificar si tiene el 3 de picas en single
                    bool tiene3Picas = (patron == 1 && BuscarCarta(cartasjugador, "3", "Pica"));

                    // Validar si puede jugar
                    if (cantidadCartas == 0) {
                        cout << "No tienes cartas para jugar. Turno pasado." << endl;
                        pasesConsecutivos++;
                    } else if (cantidadPatron <= 0 && !tiene3Picas) {
                        cout << "No tienes cartas suficientes para el patron. Turno pasado." << endl;
                        pasesConsecutivos++;
                    } else if (cantidadJerarquia <= 0 && !tiene3Picas) {
                        cout << "No tienes cartas con mayor jerarquia. Turno pasado." << endl;
                        pasesConsecutivos++;
                    } else {
                        pasesConsecutivos = 0;
                        cout << "\nIngresa las cartas a jugar (" << patron << "):" << endl;

                        Carta *CartaJugadas = NULL;
                        string primerNombre = "";
                        bool errorIngreso = false;

                        for (int i = 0; i < patron; ) {
                            if (errorIngreso) {
                                cout << "\nIntenta nuevamente la carta " << (i + 1) << ":" << endl;
                                errorIngreso = false;
                            }

                            string nombrecarta, pintacarta;
                            cout << "Carta " << (i + 1) << ":" << endl;
                            cout << "Nombre [3,4,5,...,J,Q,K,A,2,JOKER]: ";
                            cin >> nombrecarta;
                            
                            transform(nombrecarta.begin(), nombrecarta.end(), nombrecarta.begin(), ::toupper);

                            if (nombrecarta != "JOKER") {
                                cout << "Pinta [1=Diamante, 2=Corazon, 3=Trebol, 4=Pica]: ";
                                cin >> pintacarta;
                                if (pintacarta == "1") pintacarta = "Diamante";
                                else if (pintacarta == "2") pintacarta = "Corazon";
                                else if (pintacarta == "3") pintacarta = "Trebol";
                                else if (pintacarta == "4") pintacarta = "Pica";
                                else {
                                    cout << "Pinta invalida! Por favor ingresa 1, 2, 3 o 4." << endl;
                                    errorIngreso = true;
                                    continue;
                                }
                            } else {
                                pintacarta = "";
                            }

                            // Validaciones
                            if (!BuscarCarta(cartasjugador, nombrecarta, pintacarta)) {
                                cout << "No tienes esa carta en tu mazo! Por favor elige otra." << endl;
                                errorIngreso = true;
                                continue;
                            }

                            if (i == 0) {
                                primerNombre = nombrecarta;
                                if (tiene3Picas && nombrecarta == "3" && pintacarta == "Pica") {
                                    // 3 de picas es la mayor jerarquía en single
                                } else if (!tiene3Picas && nombrecarta != "JOKER" && 
                                    PosJerarquia(Jerarquia, nombrecarta) <= jerarCMesa) {
                                    cout << "La carta no supera la jerarquia de la mesa (" 
                                         << CartasEnMesa->nombre << " " << CartasEnMesa->pinta << ")." << endl;
                                    errorIngreso = true;
                                    continue;
                                }
                            } else {
                                if (nombrecarta != primerNombre && nombrecarta != "JOKER") {
                                    cout << "Debe coincidir con la primera carta (" << primerNombre 
                                         << ") o ser JOKER!" << endl;
                                    errorIngreso = true;
                                    continue;
                                }
                            }

                            Carta *cartaJugada = BuscarCartaNode(cartasjugador, nombrecarta, pintacarta);
                            DevolverCartasMazo(&CartaJugadas, &cartasjugador, &cartaJugada);
                            i++;
                        }

                        // Actualizar último jugador que hizo una jugada válida
                        ultimoJugadorQueJugo = j;

                        // Verificar si se jugó un 8 o 3 de picas
                        if (CartaJugadas) {
                            if (CartaJugadas->nombre == "8") {
                                cout << "\n¡Se jugó un 8! Ronda terminada." << endl;
                                rondaTerminada = true;
                            } else if (patron == 1 && CartaJugadas->nombre == "3" && CartaJugadas->pinta == "Pica") {
                                cout << "\n¡Se jugó el 3 de picas! Nadie puede jugar hasta nueva ronda." << endl;
                                tresDePicasEnMesa = true;
                                rondaTerminada = true;
                            }
                        }

                        // Mover cartas jugadas a la mesa
                        if (CartaJugadas) {
                            // Limpiar mesa actual (sin eliminar las cartas)
                            if (CartasEnMesa) {
                                // Mover las cartas de la mesa al mazo
                                DevolverCartasJugadasMazo(&Mazo, &CartasEnMesa);
                            }
                            // Poner las nuevas cartas en la mesa
                            CartasEnMesa = CartaJugadas;
                        }
                    }
                    j++;
                    jugada++;
                }

                system("pause");
            }

            // Fin de ronda - Selección de nuevo patrón
            if (ultimoJugadorQueJugo > 0) {
                cout << "\n--- FIN DE RONDA " << ronda << " ---" << endl;
                
                if (tresDePicasEnMesa) {
                    cout << "El 3 de picas fue jugado. Patron reset a single para nueva ronda." << endl;
                    patron = 1;
                } else {
                    // El último jugador que jugó elige el nuevo patrón
                    cout << "Jugador " << ultimoJugadorQueJugo << " elige el nuevo patron." << endl;
                    
                    bool patronValido = false;
                    while (!patronValido) {
                        cout << "Seleccione el patron para la siguiente ronda:\n";
                        cout << "1. Single (1 carta)\n2. Doble (2 cartas)\n3. Triple (3 cartas)\n4. Poker (4 cartas)\n";
                        cout << "Opcion: ";
                        cin >> patron;
                        
                        if (patron >= 1 && patron <= 4) {
                            patronValido = true;
                        } else {
                            cout << "Opcion invalida. Por favor elige entre 1 y 4." << endl;
                        }
                    }
                }

                // Limpiar la mesa (moviendo las cartas al mazo)
                if (CartasEnMesa) {
                    DevolverCartasJugadasMazo(&Mazo, &CartasEnMesa);
                }
            }

            // Reiniciar variables para nueva ronda
            pasesConsecutivos = 0;
            rondaTerminada = false;
            tresDePicasEnMesa = false;
        }

        // Fin de partida
        cout << "\n=== FIN DE PARTIDA " << (partidas + 1) << " ===" << endl;
        partidas++;
    }

    cout << "\n=== JUEGO TERMINADO ===" << endl;
    system("pause");
    return 0;
}

