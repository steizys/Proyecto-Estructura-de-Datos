#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm> //Para transform
#include <string>   // Para string
#include <windows.h> // Necesario para las funciones de consola de Windows
using namespace std;

// Función para habilitar los colores
void enableAnsiColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 
    if (hOut == INVALID_HANDLE_VALUE) return; 

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return; 
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return; 
}

// Colores
const string RESET = "\x1b[0m";      
const string NEGRITA = "\x1b[1m";    
const string SUBRAYADO = "\x1b[4m";  

// Colores
const string NEGRO = "\x1b[30m";
const string ROJO = "\x1b[31m";
const string VERDE = "\x1b[32m";
const string AMARILLO = "\x1b[33m";
const string AZUL = "\x1b[34m";
const string MAGENTA = "\x1b[35m";
const string CIAN = "\x1b[36m";
const string BLANCO = "\x1b[37m";

// Colores
const string FONDO_NEGRO = "\x1b[40m";
const string FONDO_ROJO = "\x1b[41m";
const string FONDO_VERDE = "\x1b[42m";
const string FONDO_AMARILLO = "\x1b[43m";
const string FONDO_AZUL = "\x1b[44m";
const string FONDO_MAGENTA = "\x1b[45m";
const string FONDO_CIAN = "\x1b[46m";
const string FONDO_BLANCO = "\x1b[47m";

struct Carta { // Nodos de cartas 
    string nombre;
    string pinta;
    Carta *next;
};

struct CartaSimple {
    string nombre;
    CartaSimple *next;
};

struct Jugador { // Nodos de Jugador
    int nombre;
    int puntos;
    Jugador *next;
    Carta *lista_cartas; // Multilista que une a cada jugador con sus cartas
};

struct Turnos {
    int nombre;
    Turnos *next;
};

void InsercionCabeza(Carta** p, Carta *q) {
    q->next = *p;
    *p = q;
}

Carta *CrearCarta(string nombre, string pinta) { // Procedimiento para Crear las cartas del mazo
    Carta* nuevo_carta = new Carta;
    nuevo_carta->nombre = nombre;
    nuevo_carta->pinta = pinta;
    nuevo_carta->next = NULL;
    return nuevo_carta;
}

void CrearMazo(Carta **p) { // Llenar el mazo
    string nombre = "";
    string pinta = "";
    for (int i = 1; i <= 13; i++) {
        if (i == 1) {
            nombre = "A";
        } else if (i == 2) {
            nombre = "2";
        } else if (i == 3) {
            nombre = "3";
        } else if (i == 4) {
            nombre = "4";
        } else if (i == 5) {
            nombre = "5";
        } else if (i == 6) {
            nombre = "6";
        } else if (i == 7) {
            nombre = "7";
        } else if (i == 8) {
            nombre = "8";
        } else if (i == 9) {
            nombre = "9";
        } else if (i == 10) {
            nombre = "10";
        } else if (i == 11) {
            nombre = "J";
        } else if (i == 12) {
            nombre = "Q";
        } else if (i == 13) {
            nombre = "K";
        }
        for (int j = 0; j < 4; j++) {
            Carta *carta = nullptr;
            if (j == 0) {
                pinta = "Corazon";
            } else if (j == 1) {
                pinta = "Diamante";
            } else if (j == 2) {
                pinta = "Trebol";
            } else if (j == 3) {
                pinta = "Pica";
            }

            carta = CrearCarta(nombre, pinta);
            InsercionCabeza(p, carta); // Inserta directamente al inicio
        }
    }
    // Agregar dos Jokers
    InsercionCabeza(p, CrearCarta("JOKER", ""));
    InsercionCabeza(p, CrearCarta("JOKER", ""));
}

void MostrarCarta(Carta *p) {
    while (p) {
        cout << p->nombre << " " << p->pinta << endl;
        p = p->next;
    }
}

void MostrarTurno(Turnos *p) {
    while (p) {
        cout << p->nombre << endl;
        p = p->next;
    }
}

void InsertarJugador(Jugador **p, int valor) { // Llenar jugadores por cola
    Jugador* nuevoJugador = new Jugador;
    nuevoJugador->nombre = valor;
    nuevoJugador->puntos = 0;
    nuevoJugador->next = NULL;
    nuevoJugador->lista_cartas = NULL;
    if (!(*p)) { // Si la lista está vacía
        *p = nuevoJugador; // Inserta directamente
    } else {
        Jugador *aux = *p;
        while (aux->next) { // Itera hasta el último nodo
            aux = aux->next;
        }
        aux->next = nuevoJugador; // Inserta al final
    }
}

Jugador *BuscarJugador(Jugador *malla, int i) { // Busca el nodo del jugador por su nombre
    while (malla) {
        if (malla->nombre == i) {
            return malla;
        }
        malla = malla->next;
    }
    return NULL;
}

int ContarCartas(Carta* cartas) { // Contar las cartas que tiene cada jugador
    int ncartas = 0;
    while (cartas) {
        ncartas++;
        cartas = cartas->next;
    }
    return ncartas;
}


void Reparticion(Carta **mazo, Jugador **malla) {
    srand(time(NULL));
    int cartas_repartidas = 0;
    int jugadores_con_14 = 0;

    while (*mazo) {
        // Seleccionar jugador aleatorio (1-4)
        int i = rand() % 4 + 1;//AQUI
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
            InsercionCabeza(&(jugador->lista_cartas), carta);

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

Carta* BuscarCartaNode(Carta *cartas, string nombre, string pinta) {
    while (cartas) {
        if (cartas->nombre == nombre && cartas->pinta == pinta) return cartas;
        cartas = cartas->next;
    }
    return NULL;
}
Turnos* BuscarTurnoNode(Turnos *podio, int nombre) {
    while (podio) {
        if (podio->nombre == nombre) return podio;
        podio = podio->next;
    }
    return NULL;
}

void MostrarJugador(Jugador *p) {
    cout << "P->";
    while (p) {
        cout << "[" << p->nombre << "]-> ";
        p = p->next;
    }
    cout << "NULL" << endl;
}

bool BuscarTurno(Turnos *cartas, int jugador) {
    while (cartas) {
        if (cartas->nombre == jugador) return true;
        cartas = cartas->next;
    }
    return false;
}

bool BuscarCarta(Carta *cartas, string nombre, string pinta) {
    while (cartas) {
        if (cartas->nombre == nombre && cartas->pinta == pinta) return true;
        cartas = cartas->next;
    }
    return false;
}
void Insertar_ColaPodio(Turnos** p, int nombreJ) {
    // Verificar si el jugador ya está en el podio
    if (BuscarTurno(*p, nombreJ)) {
        return;
    }
    
    Turnos *nuevo = new Turnos;
    nuevo->nombre = nombreJ;
    nuevo->next = NULL;
    
    if (!(*p)) {
        *p = nuevo;
    } else {
        Turnos *aux = *p;
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = nuevo;
    }
}
void InsertarCola(Turnos**p, Turnos*nodo){
    Turnos *aux=*p;
    while (aux && aux->next){
        aux=aux->next;
    }
    aux->next=nodo;

};
void CompletarPodio(Turnos** podio, Jugador* malla) {
    // Primero, agregar los jugadores que aún tienen cartas al final del podio
    for (int i = 1; i <= 4; i++) {
        Jugador* jugador = BuscarJugador(malla, i);
        if (ContarCartas(jugador->lista_cartas) > 0) {
            Insertar_ColaPodio(podio, i);
        }
    }
}


void LlenarJerarquia(CartaSimple **p) {
    string nombre = "";
    CartaSimple *joker = new CartaSimple;
    joker->nombre = "JOKER";
    joker->next = NULL;
    *p = joker;

    for (int i = 1; i <= 13; i++) {
        if (i == 1) {
            nombre = "2";
        } else if (i == 2) {
            nombre = "A";
        } else if (i == 3) {
            nombre = "K";
        } else if (i == 4) {
            nombre = "Q";
        } else if (i == 5) {
            nombre = "J";
        } else if (i == 6) {
            nombre = "10";
        } else if (i == 7) {
            nombre = "9";
        } else if (i == 8) {
            nombre = "8";
        } else if (i == 9) {
            nombre = "7";
        } else if (i == 10) {
            nombre = "6";
        } else if (i == 11) {
            nombre = "5";
        } else if (i == 12) {
            nombre = "4";
        } else if (i == 13) {
            nombre = "3";
        }
        CartaSimple *nuevo = new CartaSimple;
        nuevo->nombre = nombre;
        nuevo->next = *p;
        *p = nuevo;
    }
}

void MostrarJerarquia(CartaSimple *p) {
    while (p) {
        cout << p->nombre << " ";
        p = p->next;
    }
}

int PosJerarquia(CartaSimple *Jerarquia, string nombre) {
    CartaSimple *aux = Jerarquia;
    int cont = 1;
    while (aux) {
        if (aux->nombre == nombre) {
            return cont;
        }
        aux = aux->next;
        cont += 1;
    }
    return 0;
}

// Funcion para la Revolución (invierte la jerarquía)

void InvertirJerarquia(CartaSimple** Jerarquia) {
    if (*Jerarquia == NULL || (*Jerarquia)->next == NULL) {
        return; // Lista vacía o con un solo elemento
    }
    
    CartaSimple *prev = NULL;
    CartaSimple *actual = *Jerarquia;
    CartaSimple *sig = NULL;
    
    // Avanzar hasta el penúltimo nodo
    while (actual->next != NULL) {
        sig = actual->next;
        actual->next = prev;
        prev = actual;
        actual = sig;
    }
    
    // El último nodo no se invierte, se conecta al nuevo inicio
    *Jerarquia = prev;
    // Buscar el nuevo último nodo (que era el primero)
    CartaSimple* temp = prev;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = actual; // Conectar al último nodo original
}
int VecesAparicionValor(Carta *p, string value) { // Contar cuántas veces aparece una carta del mismo nombre
    int cont = 0;
    Carta *aux = p;
    while (aux) {
        if (aux->nombre == value) cont++;
        aux = aux->next;
    }
    return cont;
}

void EliminarTodosEncuentros(Carta **p, string nombre) { // Eliminar los encuentros en donde aparece ese nombre
    if (!p) return;
    Carta *auxnum = *p;
    Carta *todelete; // nodo a eliminar
    Carta *auxprev = NULL; // nodo antes del número a eliminar
    while (auxnum) {
        if (auxnum->nombre == nombre) {
            todelete = auxnum;
            auxnum = auxnum->next;
            if (!auxprev) {
                // nodo a eliminar es la cabeza
                *p = auxnum;
            } else {
                // nodo a eliminar no es la cabeza
                auxprev->next = auxnum;
            }
            delete todelete;
        } else {
            auxprev = auxnum;
            auxnum = auxnum->next;
        }
    }
}

// Función para verificar si un jugador se quedó sin cartas
bool JugadorSinCartas(Jugador* malla) {
    for (int i = 1; i <= 4; i++) {
        Jugador* jugador = BuscarJugador(malla, i);
        if (ContarCartas(jugador->lista_cartas) == 0) {
            return true;
        }
    }
    return false;
}

// Función para contar cuántos jugadores se quedaron sin cartas
int JugadoresSinCartas(Jugador* malla) {
    int count = 0;
    for (int i = 1; i <= 4; i++) {
        Jugador* jugador = BuscarJugador(malla, i);
        if (ContarCartas(jugador->lista_cartas) == 0) {
            count++;
        }
    }
    return count;
}

void MostrarSi(Carta *p, string value) { // Mostrar las cartas que se quieren de un valor en específico
    Carta *aux = p;
    while (aux) {
        if (aux->nombre == value) {
            cout << aux->nombre << " " << aux->pinta << endl;
        }
        aux = aux->next;
    }
}

int CartasPermitidasPatronVali(Carta *p, int value) { // Cantidad de Cartas con el patrón
    Carta *aux = p;
    int cant = 0;
    Carta *mostradas = nullptr;
    while (aux) {
        if (VecesAparicionValor(p, aux->nombre) >= value) {
            // Verificamos si ya hemos mostrado cartas con este nombre
            Carta *temp_mostradas = mostradas;
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
                cant++; // indica la cantidad que hay en base al value
                // Agregamos el nombre a la lista de mostradas
                Carta *nueva_mostrada = new Carta; // No necesitamos la pinta aquí
                nueva_mostrada->nombre = aux->nombre;
                nueva_mostrada->pinta = "";
                nueva_mostrada->next = mostradas;
                mostradas = nueva_mostrada;
            }
        }
        aux = aux->next;
    }
    // Liberamos la memoria de la lista 'mostradas'
    Carta *temp;
    while (mostradas) {
        temp = mostradas;
        mostradas = mostradas->next;
        delete temp;
    }
    cant += VecesAparicionValor(p, "JOKER");

    return cant;
}

int CartasPermitidasJerarquia(Carta *CartasJ, int jerarquiaMesa, CartaSimple *Jerarquia, int value) { // Me indica si en las cartas del jugador existen cartas con jerarquía mayor a la de la mesa
    Carta *aux = CartasJ;
    int cant = 0;
    Carta *mostradas = nullptr;
    while (aux) {
        if (VecesAparicionValor(CartasJ, aux->nombre) >= value) {
            // Verificamos si ya hemos mostrado cartas con este nombre
            Carta *temp_mostradas = mostradas;
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
                if (PosJerarquia(Jerarquia, aux->nombre) > jerarquiaMesa) {
                    cant++; // indica la cantidad que hay en base al value Y LA JERARQUIA
                }

                // Agregamos el nombre a la lista de mostradas
                Carta *nueva_mostrada = new Carta; // No necesitamos la pinta aquí
                nueva_mostrada->nombre = aux->nombre;
                nueva_mostrada->pinta = "";
                nueva_mostrada->next = mostradas;
                mostradas = nueva_mostrada;
            }
        }
        aux = aux->next;
    }
    // Liberamos la memoria de la lista 'mostradas'
    Carta *temp;
    while (mostradas) {
        temp = mostradas;
        mostradas = mostradas->next;
        delete temp;
    }
    return cant;
}

void CartasPermitidas(Carta *p, int value) {
    Carta *aux = p;
    Carta *mostradas = nullptr;
    while (aux) {
        if (VecesAparicionValor(p, aux->nombre) >= value) {
            // Verificamos si ya hemos mostrado cartas con este nombre
            Carta *temp_mostradas = mostradas;
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
                Carta *nueva_mostrada = new Carta; // No necesitamos la pinta aquí
                nueva_mostrada->nombre = aux->nombre;
                nueva_mostrada->pinta = "";
                nueva_mostrada->next = mostradas;
                mostradas = nueva_mostrada;
            }
        }
        aux = aux->next;
    }
    // Liberamos la memoria de la lista 'mostradas'
    Carta *temp;
    while (mostradas) {
        temp = mostradas;
        mostradas = mostradas->next;
        delete temp;
    }
}

void DevolverCartasMazo(Carta **Mazo, Carta **CartaJ, Carta **CartaM) {
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
            *CartaJ = aux->next;
        } else {
            // Si *CartaM no es la cabeza
            prev->next = aux->next;
        }
        // Asegurarse de que la carta devuelta no esté enlazada a nada
        aux->next = nullptr;
        // Devolver *CartaM al Mazo
        InsercionCabeza(Mazo, *CartaM);
    }
}
void MoverMendigo(Turnos **Podio, Turnos **Mendigo) {
    Turnos *aux = *Podio;
    Turnos *prev = nullptr;
    bool encontrado = false;
    // Buscar la carta *CartaM en la lista *CartaJ y mantener el nodo anterior
    while (aux) {
        if (aux == *Mendigo) {
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
            *Podio = aux->next;
        } else {
            // Si *CartaM no es la cabeza
            prev->next = aux->next;
        }
        // Asegurarse de que la carta devuelta no esté enlazada a nada
        (*Mendigo)->next = nullptr;
        // Devolver *CartaM al Mazo
        InsertarCola(Podio, *Mendigo);
    }
}

void DevolverCartasJugadasMazo(Carta **Mazo, Carta **CartasJugadas) {
    if (!*CartasJugadas) return; // Si no hay cartas jugadas, no hacer nada

    // Conectar las cartas jugadas al mazo
    Carta *aux = *CartasJugadas;
    while (aux->next) {
        aux = aux->next;
    }
    aux->next = *Mazo;
    *Mazo = *CartasJugadas;
    *CartasJugadas = NULL; // Limpiar la lista de cartas jugadas
}

// Función para verificar si hay revolucion (4 cartas iguales jugadas)
bool VerificarRevolucion(Carta* cartasJugadas) {
    if (!cartasJugadas) return false;
    
    string nombre = cartasJugadas->nombre;
    int cont = 0;
    Carta* actual = cartasJugadas;
    
    while (actual) {
        if (actual->nombre == nombre || actual->nombre == "JOKER") {
            cont++;
        }
        actual = actual->next;
    }
    
    return (cont == 4);
}

bool CartasPermitidasCarta(string name, int patron, Carta*CartasJ){
    Carta *aux=CartasJ;
    int cont1=0;
    while(aux){
        if (aux->nombre==name || aux->nombre=="JOKER"){
            cont1++;
        }
        aux=aux->next;
    }
    if (cont1>=patron){
        return true;//tiene cartas suficientes para jugar ese patron sin necesidad los joker
    }
   return false;
}
bool VerificarComplemento(Carta*cartasjugadas){
    Carta *aux=cartasjugadas;
    int joker=0; int cartasdiferentes=0;
    while(aux){
        if(aux->nombre=="JOKER"){
            joker++;
        }else{
            cartasdiferentes++;
        }
        aux=aux->next;
    }
    if (cartasdiferentes>0 && joker>0){
        return true;
    }
    return false;
}
void CartasJugadasMixtas(Carta**cartasjugadas){
    Carta *aux=*cartasjugadas;
    bool encontrado;
    Carta *prev=NULL;
    while (aux) {
        if (aux->nombre!="JOKER") {
            encontrado = true;
            break;
        }
        prev = aux;
        aux = aux->next;
    }
    if (encontrado) {
        // Desconectar *CartaM de la lista *CartaJ
        if (prev != NULL) {
            prev->next = aux->next;
        }
        // Asegurarse de que la carta devuelta no esté enlazada a nada
        aux->next = NULL;
        // Devolver *CartaM al Mazo
        InsercionCabeza(cartasjugadas, aux);
    }

}
// Función para mover las 2 cartas de mayor jerarquía de un jugador a otro
void MoverDosMayores(Jugador* origen, Jugador* destino, CartaSimple* Jerarquia) {
    if (!origen || !destino || !origen->lista_cartas) return;

    Carta* mayor1 = NULL;
    Carta* mayor2 = NULL;
    Carta* actual = origen->lista_cartas;
    Carta* prevMayor1 = NULL;
    Carta* prevMayor2 = NULL;
    Carta* prev = NULL;

    // Encontrar las dos cartas de mayor jerarquía
    while (actual) {
        if (!mayor1 || PosJerarquia(Jerarquia, actual->nombre) > PosJerarquia(Jerarquia, mayor1->nombre)) {
            mayor2 = mayor1;
            prevMayor2 = prevMayor1;
            mayor1 = actual;
            prevMayor1 = prev;
        } 
        else if (!mayor2 || PosJerarquia(Jerarquia, actual->nombre) > PosJerarquia(Jerarquia, mayor2->nombre)) {
            mayor2 = actual;
            prevMayor2 = prev;
        }
        prev = actual;
        actual = actual->next;
    }

    // Mover la primera carta mayor
    if (mayor1) {
        // Desconectar de origen
        if (prevMayor1) {
            prevMayor1->next = mayor1->next;
        } else {
            origen->lista_cartas = mayor1->next;
        }
        // Conectar a destino
        mayor1->next = destino->lista_cartas;
        destino->lista_cartas = mayor1;
    }

    // Mover la segunda carta mayor
    if (mayor2) {
        // Desconectar de origen (teniendo en cuenta que pudo cambiar la lista)
        actual = origen->lista_cartas;
        prev = NULL;
        while (actual && actual != mayor2) {
            prev = actual;
            actual = actual->next;
        }
        if (actual == mayor2) {
            if (prev) {
                prev->next = mayor2->next;
            } else {
                origen->lista_cartas = mayor2->next;
            }
            // Conectar a destino
            mayor2->next = destino->lista_cartas;
            destino->lista_cartas = mayor2;
        }
    }
    if (!origen->lista_cartas || !origen->lista_cartas->next) {
        cout << NEGRITA << ROJO << "El jugador no tiene suficientes cartas."<<RESET<<endl;
        return;
    }
}

// Función para que un jugador elija 2 cartas y las mueva a otro jugador
void MoverCartasElegidas(Jugador* origen, Jugador* destino) {
    if (!origen || !destino || !origen->lista_cartas) return;

    cout << NEGRITA << VERDE << "Cartas del jugador " << origen->nombre << ":\n"<< RESET;
    MostrarCarta(origen->lista_cartas);

    int cartasSeleccionadas = 0;

    while (cartasSeleccionadas < 2) {
        string nombre, pinta;
            cout << NEGRITA << CIAN; 
            cout << "==========================================\n";
            cout << "          SELECCION DE CARTA            \n";
            cout << "------------------------------------------\n";
            cout << RESET << NEGRITA << BLANCO; 
            cout << "Opciones validas: 3 4 5 6 7 8 9 10 J Q K A 2 JOKER\n";
            cout << "Ingrese el nombre de la carta: ";
            cout << RESET<< "\n";
            cin >> nombre;
            transform(nombre.begin(), nombre.end(), nombre.begin(), ::toupper);

        if (nombre != "JOKER") {
            cout << RESET << NEGRITA << AZUL; 
            cout << "Ingrese la pinta de la carta: "<<endl;
            cout << RESET << NEGRITA << BLANCO; 
            cout << "   1 = Diamante"<<endl;
            cout << "   2 = Corazon"<<endl;
            cout << "   3 = Trebol"<<endl;
            cout << "   4 = Pica"<<endl;
            cin >> pinta;
            cout << RESET;
            if (pinta == "1") pinta = "Diamante";
            else if (pinta == "2") pinta = "Corazon";
            else if (pinta == "3") pinta = "Trebol";
            else if (pinta == "4") pinta = "Pica";
        } else {
            pinta = "";
        }

        // Buscar la carta en la lista del jugador
        Carta* actual = origen->lista_cartas;
        Carta* prev = NULL;
        while (actual) {
            if (actual->nombre == nombre && (nombre == "JOKER" || actual->pinta == pinta)) {
                // Desconectar de origen
                if (prev) {
                    prev->next = actual->next;
                } else {
                    origen->lista_cartas = actual->next;
                }
                
                // Conectar a destino
                actual->next = destino->lista_cartas;
                destino->lista_cartas = actual;
                
                cartasSeleccionadas++;
                break;
            }
            prev = actual;
            actual = actual->next;
        }

        if (!actual) {
            cout << NEGRITA << MAGENTA<< "Carta no encontrada. Intente nuevamente.\n" <<RESET<<endl;
        }
    }
}


void MoverMayorCarta(Jugador* origen, Jugador* destino, CartaSimple* Jerarquia) {
    if (!origen || !destino || !origen->lista_cartas) return;

    Carta* mayor = NULL;
    Carta* prevMayor = NULL;
    Carta* actual = origen->lista_cartas;
    Carta* prev = NULL;

    // Encontrar la carta de mayor jerarquía
    while (actual) {
        if (!mayor || PosJerarquia(Jerarquia, actual->nombre) > PosJerarquia(Jerarquia, mayor->nombre)) {
            mayor = actual;
            prevMayor = prev;
        }
        prev = actual;
        actual = actual->next;
    }

    // Mover la carta mayor
    if (mayor) {
        // Desconectar de origen
        if (prevMayor) {
            prevMayor->next = mayor->next;
        } else {
            origen->lista_cartas = mayor->next;
        }
        // Conectar a destino
        mayor->next = destino->lista_cartas;
        destino->lista_cartas = mayor;
    }
}

void MoverCartaElegida(Jugador* origen, Jugador* destino) {
    if (!origen || !destino || !origen->lista_cartas) return;

    cout <<NEGRITA<<VERDE<<"Cartas del jugador " << origen->nombre << ":\n" <<RESET;
    MostrarCarta(origen->lista_cartas);

    while (true) {
        string nombre, pinta;
        cout << NEGRITA << CIAN; 
        cout << "==========================================\n";
        cout << "          SELECCIONE UNA CARTA            \n";
        cout << "------------------------------------------\n";
        cout << RESET << NEGRITA << BLANCO; 
        cout << "Nombre: 3 4 5 6 7 8 9 10 J Q K A 2 JOKER\n";
        cout << "Ingrese el nombre de la carta: ";
        cout << RESET<< "\n";
        cin >> nombre;
        cout << RESET << NEGRITA << AZUL; 
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::toupper);

        if (nombre != "JOKER") {
            cout << RESET << NEGRITA << BLANCO; 
            cout << "Ingrese la pinta de la carta: "<<endl;
            cout << "   1 = Diamante"<<endl;
            cout << "   2 = Corazon"<<endl;
            cout << "   3 = Trebol"<<endl;
            cout << "   4 = Pica"<<endl;
            cin >> pinta;
            cout << RESET;
            if (pinta == "1") pinta = "Diamante";
            else if (pinta == "2") pinta = "Corazon";
            else if (pinta == "3") pinta = "Trebol";
            else if (pinta == "4") pinta = "Pica";
        } else {
            pinta = "";
        }

        // Buscar la carta en la lista del jugador
        Carta* actual = origen->lista_cartas;
        Carta* prev = NULL;
        while (actual) {
            if (actual->nombre == nombre && (nombre == "JOKER" || actual->pinta == pinta)) {
                // Desconectar de origen
                if (prev) {
                    prev->next = actual->next;
                } else {
                    origen->lista_cartas = actual->next;
                }
                
                // Conectar a destino
                actual->next = destino->lista_cartas;
                destino->lista_cartas = actual;
                
                cout << NEGRITA <<VERDE << "Carta movida exitosamente.\n"<<RESET<<endl;
                return; // Terminar después de mover una carta
            }
            prev = actual;
            actual = actual->next;
        }

        cout << NEGRITA << ROJO << "Carta no encontrada. Intente nuevamente.\n"<<RESET;
    }
}

void SubLista(Carta **sublist, string nombre, string pinta) {
    Carta *newcarta = new Carta;
    newcarta->nombre = nombre;
    newcarta->pinta = pinta;
    newcarta->next = *sublist;
    *sublist = newcarta;
}

void InsertarCarta(Jugador *malla, int nombrej, string nombre, string pinta) {
    Jugador *jugador = BuscarJugador(malla, nombrej); // Me da el nodo del jugador al que quiero insertar una carta 
    SubLista(&(jugador->lista_cartas), nombre, pinta);
}


// Función principal del juego
int main() {
    enableAnsiColors();
    cout <<AMARILLO<< "  __  __       _____ _  _        _______ ______ \n";
    cout <<AMARILLO<< " |  \\/  |  /\\  / ____| \\ | |  /\\|__  __| ____| \n";
    cout <<AMARILLO<< " | |\\  / | /  \\| |  __|  \\| | /  \\  | |  | |__   \n";
    cout <<AMARILLO<<" | |\\/| | / /\\ \\ | |_ | . ` | / /\\ \\ | |  |  __|  \n";
    cout <<AMARILLO<<" | |  | |/ ____ \\ |__| | |\\  |/ ____ \\| |  | |____ \n";
    cout <<AMARILLO<< " |_|  |_/_/    \\_\\_____|_| \\_/_/    \\_\\_|  |______| \n";
    cout << "                                                    \n"; 
    cout << NEGRITA << CIAN  << "AUTORAS: Amelie Moreno, Gabriela Cantos, Steizy Fornica" << endl;
    cout << RESET << endl; 

    // Inicialización de estructuras
    Jugador *Malla = NULL;
    Carta *Mazo = NULL;
    CartaSimple *Jerarquia = NULL;
    Carta *CartasEnMesa = NULL;
    Turnos *Podio=NULL;

    // Llenado inicial
    LlenarJerarquia(&Jerarquia);
    for (int i = 1; i <= 4; i++) {
        InsertarJugador(&Malla, i);
    }
    
    //CrearMazo(&Mazo);
    InsercionCabeza(&Mazo, CrearCarta("8", "Pica"));
    InsercionCabeza(&Mazo, CrearCarta("K", "Pica"));

    // Variables del juego
    int j = 0; // Turno actual
    int partidas = 1;
    int ronda = 0, pasesConsecutivos = 0, patron = 1;
    int jugada = 0;
    int jerarCMesa = 0;
    int terminarRonda = 0;
    bool rondaTerminada = false;
    int ultimoJugadorQueJugo = 0;
    bool tresDePicasEnMesa = false;
    bool revolucion = false;
    bool CambioMagnate=false;
    
    //// PODIO ////
    int Magnate; int Rico; int Pobre; int Mendigo;

    //Reparticion(&Mazo, &Malla);

    //JUGADOR 1
    Jugador *jugador = BuscarJugador(Malla,1);
    InsertarCarta(jugador, 1, "2","Corazon");
    InsertarCarta(jugador, 1, "2","Diamante");

    //JUGADOR 2
    Jugador *jugador2 = BuscarJugador(Malla,2);
    InsertarCarta(jugador2, 2, "3","Pica");
    InsertarCarta(jugador2, 2, "3","Diamante");

    //JUGADOR 3
    Jugador *jugador3 = BuscarJugador(Malla,3);
    InsertarCarta(jugador3, 3, "7","Corazon");
    InsertarCarta(jugador3, 3, "5","Corazon");

    //JUGADOR 4
    Jugador *jugador4 = BuscarJugador(Malla,4);
    InsertarCarta(jugador4, 4, "5","Corazon");
    InsertarCarta(jugador4, 4, "8","Corazon");

    // Bucle principal del juego
    while (partidas < 3 ) {
        cout << MAGENTA << NEGRITA <<"* * * * * *    P A R T I D A   " << partidas << "   * * * * * *"<< endl;
        cout<< RESET <<endl;
        ronda = 0;
        Podio=NULL;
        CambioMagnate=false;
        
        // Bucle de rondas
        while (JugadoresSinCartas(Malla) < 3 && !terminarRonda) {
            ronda++;
            pasesConsecutivos = 0;
            rondaTerminada = false;
            tresDePicasEnMesa = false;
            if (JugadoresSinCartas(Malla)>=3){
                terminarRonda=true;
                continue;
            }
            cout << NEGRITA << VERDE; 
            cout << "=============== R O N D A   " << ronda << " ===============\n";
            cout << RESET; 
            cout << BLANCO << "        Patron actual: " << CIAN << patron << " carta(s)\n"; 
            cout << RESET; 
            cout << "\n"; 
            
            // Primera jugada especial
            if (partidas == 1 && jugada == 0) {
                Jugador* temp = Malla;
                while (temp) {
                    if (BuscarCarta(temp->lista_cartas, "3", "Diamante")) {
                        j = temp->nombre;
                        ultimoJugadorQueJugo = j;
                        cout << NEGRITA << AZUL<<"\nJugador " << j << " inicia la partida con el 3 de diamantes." << RESET<<endl;
                        Carta *CartaMesa = BuscarCartaNode(temp->lista_cartas, "3", "Diamante");
                        DevolverCartasMazo(&CartasEnMesa, &temp->lista_cartas, &CartaMesa);
                        patron = 1;
                        j++;
                        jugada++;
                        break;
                    }
                    temp = temp->next;
                }
            } else {
                
               // Iniciar ronda con el último jugador que jugó
                j = ultimoJugadorQueJugo;
                cout << NEGRITA << AZUL<<"\nJugador " << j << " inicia la ronda por ser el último que jugó." << RESET<< endl;
            }
            //if (JugadoresSinCartas(Malla) >= 3) continue;
            // Bucle de turnos en la ronda
            while (pasesConsecutivos < 3 && !rondaTerminada) {
                if (j > 4) j = 1;


                Jugador *jugador = BuscarJugador(Malla, j);
              
                if (JugadoresSinCartas(Malla) >= 3){
                    rondaTerminada=true;
                    continue;
                } 
                //cout<< partidas<<" Partidas"<<endl;
                //cout<<JugadoresSinCartas(Malla)<<" jugadores"<<endl;
                if (Podio){
                    cout<<AMARILLO<<NEGRITA<< Podio->nombre <<" PODIO"<<endl<<RESET;
                }
                if(Podio && partidas>1 && JugadoresSinCartas(Malla)==1){
                    if(Podio->nombre!=Magnate){
                        CambioMagnate=true;
                        Jugador *CartasMagnateViejo= BuscarJugador(Malla, Magnate);
                        DevolverCartasJugadasMazo(&Mazo, &CartasMagnateViejo->lista_cartas);

                    }
                }
                cout<< NEGRO<<"\nJugadores sin carta dentro ronda: "<<JugadoresSinCartas(Malla)<<endl;
                cout << "Turno del Jugador " << j << endl<<RESET;

                // Mostrar estado actual
                cout << NEGRO << "Carta en mesa: "<<endl;
                if (CartasEnMesa) {
                    cout << CartasEnMesa->nombre << " " << CartasEnMesa->pinta << RESET<<endl;
                    jerarCMesa = PosJerarquia(Jerarquia, CartasEnMesa->nombre);
                } else {
                    cout << "Ninguna" << endl;
                    jerarCMesa = 0;
                }

                cout << NEGRITA<< AZUL<<endl;
                cout << "---------------------------";
                cout << RESET<< NEGRITA<< AZUL<<endl;
                cout<<"         TUS CARTAS     \n" << RESET;
                cout << RESET<< BLANCO;
                MostrarCarta(jugador->lista_cartas);
                cout << RESET<< NEGRITA<< AZUL;
                cout << "---------------------------";
                cout << RESET<< endl;

                // Si hay 3 de picas en mesa, nadie puede jugar
                if (tresDePicasEnMesa) {
                    cout << ROJO << "\nHay un 3 de picas en mesa. Nadie puede jugar hasta nueva ronda." << endl;
                    cout << RESET;
                    rondaTerminada=true;
                    pasesConsecutivos++;
                    j++;
                    system("pause");
                    continue;
                }

                // Mostrar opciones válidas
                if (patron > 1) {
                    cout << CIAN << "\nCartas que cumplen con el patron de " << patron << ":" << endl;
                    cout << RESET;
                    CartasPermitidas(jugador->lista_cartas, patron);
                }

                // Opciones del jugador
                int op = 0;
                while (op != 1 && op != 2) {
                    cout<< NEGRITA<<AMARILLO;
                    cout << "\n";
                    cout << "---------------------------\n";
                    cout<< RESET<< NEGRITA<<AMARILLO;
                    cout << " OPCIONES DEL TURNO\n";
                    cout<< RESET << NEGRITA << BLANCO;
                    cout << " [1] Lanzar cartas\n";
                    cout << " [2] Pasar turno\n";
                    cout<< RESET<< NEGRITA<<AMARILLO;
                    cout << "---------------------------\n";
                    cout<< RESET << NEGRITA << BLANCO;
                    cout << "-> Ingrese su eleccion: ";
                    cout << RESET;
                    cin >> op;
                    if (op != 1 && op != 2) {
                        cout << ROJO << NEGRITA << "Opcion invalida!" << RESET << endl;
                    }
                }

                if (op == 2) { // Pasar turno
                    pasesConsecutivos++;
                    cout << NEGRITA<<VERDE << "Jugador " << j << " pasa su turno." << RESET<< endl;
                    j++;
                } else { // Intentar jugar cartas
                    int cantidadCartas = ContarCartas(jugador->lista_cartas);
                    int cantidadPatron = CartasPermitidasPatronVali(jugador->lista_cartas, patron);
                    int cantidadJerarquia = CartasPermitidasJerarquia(jugador->lista_cartas, jerarCMesa, Jerarquia, patron);
                    bool tiene3Picas = (patron == 1 && BuscarCarta(jugador->lista_cartas, "3", "Pica"));

                    // Validar si puede jugar
                    if (cantidadCartas == 0) {
                        //terminarRonda++;
                        cout << NEGRITA << MAGENTA<< "No tienes cartas para jugar. Turno pasado." << RESET << endl;
                        //Insertar_ColaPodio(&Podio,(jugador->nombre));
                        pasesConsecutivos++;
                    } else if (cantidadPatron <= 0 && !tiene3Picas) {
                        cout << NEGRITA << MAGENTA<< "No tienes cartas suficientes para el patron. Turno pasado." << RESET << endl;
                        pasesConsecutivos++;
                    } else if (cantidadJerarquia <= 0 && !tiene3Picas && !BuscarCarta(jugador->lista_cartas, "JOKER", "")) {
                        cout << NEGRITA << MAGENTA<< "No tienes cartas con mayor jerarquia. Turno pasado." << RESET << endl;
                        pasesConsecutivos++;
                    } else {
                        pasesConsecutivos = 0;
                        
                        cout << NEGRITA<<CIAN << "\nIngresa las cartas a jugar (" << patron << "):" << RESET<<endl;

                        Carta *CartaJugadas = NULL;
                        string primerNombre = "";
                        bool errorIngreso = false;

                        for (int i = 0; i < patron; ) {
                            if (errorIngreso) {
                                cout << AMARILLO << NEGRITA << "\nIntenta nuevamente la carta " << (i + 1) << ":" << endl<< RESET;
                                errorIngreso = false;
                            }

                            string nombrecarta, pintacarta;
                            cout<< NEGRO<< NEGRITA<<"   NOTA: Si deseas  completar tus cartas con JOKER, debes escribir primero tus cartas a completar y despues el JOKER"<<RESET<<endl;
                            cout << NEGRO<< NEGRITA<<"   CARTA " << (i + 1) << ":" << RESET<< endl;
                            cout << NEGRITA << CIAN; 
                            cout << "==========================================\n";
                            cout << "          SELECCIONE LA CARTA " <<(i + 1)<<"\n";
                            cout << "------------------------------------------\n";
                            cout << RESET << NEGRITA << BLANCO; 
                            cout << "Nombre: 3 4 5 6 7 8 9 10 J Q K A 2 JOKER\n";
                            cout << "Ingrese el nombre de la carta: ";
                            cout << RESET<< "\n";
                            cin >> nombrecarta;
                            transform(nombrecarta.begin(), nombrecarta.end(), nombrecarta.begin(), ::toupper);

                            if (nombrecarta != "JOKER") {
                                cout << RESET << NEGRITA << AZUL; 
                                cout << "Ingrese la pinta de la carta: "<<endl;
                                cout << RESET << NEGRITA << BLANCO; 
                                cout << "   1 = Diamante"<<endl;
                                cout << "   2 = Corazon"<<endl;
                                cout << "   3 = Trebol"<<endl;
                                cout << "   4 = Pica"<<endl;
                                cin >> pintacarta;
                                if (pintacarta == "1") pintacarta = "Diamante";
                                else if (pintacarta == "2") pintacarta = "Corazon";
                                else if (pintacarta == "3") pintacarta = "Trebol";
                                else if (pintacarta == "4") pintacarta = "Pica";
                                else {
                                    cout << NEGRITA<<AMARILLO <<"Pinta invalida! Por favor ingresa 1, 2, 3 o 4." << RESET << endl;
                                    errorIngreso = true;
                                    continue;
                                }
                            } else {
                                pintacarta = "";
                            }

                            // Validaciones
                            if (!BuscarCarta(jugador->lista_cartas, nombrecarta, pintacarta)) {
                                cout << NEGRITA << MAGENTA<< "No tienes esa carta en tu mazo! Por favor elige otra." << RESET << endl;
                                errorIngreso = true;
                                continue;
                            }
                            if (i == 0) {
                                primerNombre = nombrecarta;
                                if (!tiene3Picas && nombrecarta != "JOKER" && PosJerarquia(Jerarquia, nombrecarta) <= jerarCMesa) {
                                    cout << NEGRITA << MAGENTA<< "La carta no supera la jerarquia de la mesa (" 
                                         << CartasEnMesa->nombre << " " << CartasEnMesa->pinta << ")." << RESET << endl;
                                    errorIngreso = true;
                                    continue;
                                }else if (primerNombre!="JOKER" && !CartasPermitidasCarta(nombrecarta, patron,jugador->lista_cartas)){
                                    cout << NEGRITA << MAGENTA<< "La carta no tiene suficientes complementos para jugar este patron, ni siquiera completando con JOKER "<< RESET << endl;
                                    errorIngreso = true;
                                    continue;
                                }else if (tiene3Picas && nombrecarta!="3" && pintacarta!="Pica" && PosJerarquia(Jerarquia, nombrecarta) <= jerarCMesa){
                                    cout << NEGRITA << MAGENTA<< "La carta no supera la jerarquia de la mesa (" 
                                         << CartasEnMesa->nombre << " " << CartasEnMesa->pinta << ")." << RESET << endl;
                                    errorIngreso = true;
                                    continue;
                                }else if (tiene3Picas && pintacarta!="Pica" && PosJerarquia(Jerarquia, nombrecarta) <= jerarCMesa){
                                    cout << NEGRITA << MAGENTA<< "La carta no supera la jerarquia de la mesa (" 
                                         << CartasEnMesa->nombre << " " << CartasEnMesa->pinta << ")." << RESET << endl;
                                    errorIngreso = true;
                                    continue;
                                }
                            } else {
                                if (nombrecarta != primerNombre && nombrecarta != "JOKER") {
                                    cout << NEGRITA << MAGENTA<< "Debe coincidir con la primera carta (" << primerNombre 
                                         << ") o ser JOKER!" << RESET << endl;
                                    errorIngreso = true;
                                    continue;
                                }
                            }

                            Carta *cartaJugada = BuscarCartaNode(jugador->lista_cartas, nombrecarta, pintacarta);
                            DevolverCartasMazo(&CartaJugadas, &jugador->lista_cartas, &cartaJugada);
                            i++;
                        }

                        
                        ultimoJugadorQueJugo = j;

                        // Verificar si se jugó un 8
                        if (CartaJugadas && CartaJugadas->nombre == "8") {
                            cout << NEGRO << NEGRITA << "\n8 STOP! Se limpia la mesa y el jugador puede jugar cualquier combinacion.\n" << RESET<<endl;
                            DevolverCartasJugadasMazo(&Mazo, &CartasEnMesa);
                            patron = 0; // Permite que el jugador elija cualquier patrón
                            rondaTerminada = true;
                        }
                        if (VerificarComplemento(CartaJugadas)){
                            cout<<"Complemento "<<endl;
                            MostrarCarta(CartaJugadas);
                            CartasJugadasMixtas(&CartaJugadas);
                            cout<<"Complemento "<<endl;
                            MostrarCarta(CartaJugadas);
                        }
                        // Verificar si hay revolución
                        if (VerificarRevolucion(CartaJugadas) ) {
                            if (!revolucion){
                                cout << NEGRO << NEGRITA << "\n¡REVOLUCION! La jerarquia se invierte.\n"<< RESET<<endl;
                            }else{
                                cout << NEGRO << NEGRITA << "\n¡CONTRAREVOLUCION! La jerarquia a su estado original.\n"<< RESET<<endl;
                            }
                            
                            InvertirJerarquia(&Jerarquia);
                            revolucion = !revolucion;
                            cout << AMARILLO << NEGRITA<< "Nueva jerarquia:\n"<<RESET<<endl;
                            MostrarJerarquia(Jerarquia);
                        }

                        // Verificar si se jugó 3 de picas
                        if (BuscarCartaNode(CartaJugadas, "3", "Pica") && patron==1) {
                            tresDePicasEnMesa = true;
                            rondaTerminada = true;
                        }

                        // Mover cartas jugadas a la mesa
                        if (CartaJugadas) {
                            if (CartasEnMesa) {
                                DevolverCartasJugadasMazo(&Mazo, &CartasEnMesa);
                            }
                            CartasEnMesa = CartaJugadas;
                        }
                    // Fin de ronda - Selección de nuevo patrón
                
                        int conturnos=0;
                        if (ultimoJugadorQueJugo > 4) ultimoJugadorQueJugo = 1;
                        while(conturnos<3){
                            Jugador *jugador = BuscarJugador(Malla, ultimoJugadorQueJugo);
                            if ((ContarCartas(jugador->lista_cartas) == 0)) {
                                Insertar_ColaPodio(&Podio,ultimoJugadorQueJugo);
                                ultimoJugadorQueJugo++; 
                                if (ultimoJugadorQueJugo > 4) ultimoJugadorQueJugo = 1;
                            }else{
                                break;
                            }
                            conturnos++;
                        }
                    

              
                    }
                    j++;
                    jugada++;
                }

                system("pause");
            }
              
            if (JugadoresSinCartas(Malla)>=3) continue;
            if (ultimoJugadorQueJugo > 0) {
                cout << NEGRITA << VERDE; 
                cout << "============ F I N R O N D A   " << ronda << " ============\n";
                cout << RESET; 
                
                Jugador *jugador = BuscarJugador(Malla, ultimoJugadorQueJugo);
                cout << NEGRO<< "\nJugador " << ultimoJugadorQueJugo << " elige el nuevo patron." << endl;
                cout << NEGRO << "\nTus cartas:" << endl;
                MostrarCarta(jugador->lista_cartas);
                
                bool patronValido = false;
                while (!patronValido) {
                    cout << "-----------------------------------\n";
                    cout<< RESET<< NEGRITA<<NEGRO;
                    cout << " PATRON PARA LA SIGUIENTE RONDA\n";
                    cout<< RESET << NEGRITA << BLANCO;
                    cout << " [1] Single (1 carta)\n";
                    cout << " [2] Doble (2 cartas)\n";
                    cout << " [3] Triple (3 cartas)\n";
                    cout << " [4] Poker (4 cartas)\n";
                    cout<< RESET<< NEGRITA<<NEGRO;
                    cout << "------------------------------------\n";
                    cout<< RESET << NEGRITA << BLANCO;
                    cout << "-> Ingrese su eleccion: ";
                    cout << RESET;
                    cin >> patron;
                    
                    if (patron >= 1 && patron <= 4) {
                        if (CartasPermitidasPatronVali(jugador->lista_cartas, patron)>0){
                            patronValido = true;
                        }else{
                            cout << NEGRITA<<MAGENTA <<"Opcion invalida. No tienes cartas suficientes para este patron." << RESET<< endl;
                        }
                    } else {
                        cout << NEGRITA<<MAGENTA <<"Opcion invalida. Por favor elige entre 1 y 4." << RESET<<endl;
                    }
                    
                }
                
                // Limpiar la mesa
                if (CartasEnMesa) {
                    DevolverCartasJugadasMazo(&Mazo, &CartasEnMesa);
                }
            }

            // Reiniciar variables para nueva ronda
            pasesConsecutivos = 0;
            rondaTerminada = false;
            tresDePicasEnMesa = false;
        }

        // Fin de partida - Asignar puntos y rangos
        cout << MAGENTA << NEGRITA <<"* * * *    F I N  P A R T I D A    * * * *"<< endl;
        cout<< RESET <<endl;
        
        //Insertar_ColaPodio(&Podio,j);
        //cout<<"Orden en el que se quedan sin cartas "<<endl;
        //MostrarTurno(Podio);
        CompletarPodio(&Podio,Malla);
        if(CambioMagnate==true){
            //cout<<"Entra a la condicion FIN DE PARTIDA"<<endl;
            Turnos *Mendigo= BuscarTurnoNode(Podio, Magnate);
            MoverMendigo(&Podio, &Mendigo);
        }
        MostrarTurno(Podio);
        // Reiniciar para nueva partida
        partidas++;
        terminarRonda = 0;
        
        // Revertir revolución si estaba activa
        if (revolucion) {
            InvertirJerarquia(&Jerarquia);
            revolucion = false;
        }

        if (CartasEnMesa) {
            DevolverCartasJugadasMazo(&Mazo, &CartasEnMesa);
        }
        // Repartir cartas para nueva partida
        Jugador* temp = Malla;
        while (temp) {//Devolver todas las cartas restantes de los jugadores al mazo otra vez
            DevolverCartasJugadasMazo(&Mazo, &temp->lista_cartas);
            temp = temp->next;
        }
        Reparticion(&Mazo, &Malla);
        temp = Malla;
        while (temp) {//Devolver todas las cartas restantes de los jugadores al mazo otra vez
            cout<<"\n\nLas cartas de los jugadores es "<<temp->nombre<<endl;
            MostrarCarta(temp->lista_cartas);
            temp = temp->next;
        }



        cout<< NEGRITA<< VERDE<< " --- ASIGNACION DE RANGOS --- "<<RESET<<endl;

        Magnate=Podio->nombre; cout<<"MAGNATE "<<Magnate<<endl;
        Rico=Podio->next->nombre; cout<<"RICO "<<Rico<<endl;
        Pobre=Podio->next->next->nombre; cout<<"POBRE "<<Pobre<<endl;
        Mendigo=Podio->next->next->next->nombre; cout<<"MENDIGO "<<Mendigo<<endl;
         
        cout << NEGRITA<< VERDE<< "----- MAGNATE - MENDIGO -----\n";
        Jugador* Mag = BuscarJugador(Malla, Magnate); 
        Mag->puntos+=30;
        Jugador* Men = BuscarJugador(Malla, Mendigo); 
        Men->puntos+=0;
        cout<<"MAGNATE -- Jugador "<<Mag->nombre<<endl;
        MostrarCarta(Mag->lista_cartas);
        cout<<"MENDIGO -- Jugador "<<Men->nombre<<endl;
        MostrarCarta(Men->lista_cartas);
        cout << "\nMoviendo las 2 cartas de mayor jerarquia del MENDIGO al MAGNATE ...\n";
        MoverDosMayores(Men,Mag,Jerarquia);
        cout << "\nAhora el MAGNATE seleccionará 2 cartas para mover al MENDIGO...\n";
        MoverCartasElegidas(Mag, Men);
        
        cout<<" \n\nSUS CARTAS ACTUALIZADAS "<<endl;
        cout<<"MAGNATE -- Jugador "<<Mag->nombre<<" Sus puntos son "<<Mag->puntos<<endl;
        MostrarCarta(Mag->lista_cartas);
        cout<<"MENDIGO -- Jugador "<<Men->nombre<<" Sus puntos son "<<Men->puntos<<endl;
        MostrarCarta(Men->lista_cartas);
        
        cout << "----- RICO - POBRE -----\n";
        Jugador* Ric = BuscarJugador(Malla, Rico); 
        Ric->puntos+=20;
        Jugador* Pob = BuscarJugador(Malla, Pobre); 
        Pob->puntos+=10;
        cout<<"RICO -- Jugador "<<Ric->nombre<<endl;
        MostrarCarta(Ric->lista_cartas);
        cout<<"POBRE -- Jugador "<<Pob->nombre<<endl;
        MostrarCarta(Pob->lista_cartas);
        cout << "\nMoviendo la carta de mayor jerarquia del POBRE al RICO ...\n";
        MoverMayorCarta(Pob, Ric, Jerarquia);
        cout << "\nAhora el RICO seleccionará una carta para mover al POBRE...\n";
        MoverCartaElegida(Ric, Pob);
        cout<<" \n\nSUS CARTAS ACTUALIZADAS "<<endl;
        cout<<"RICO -- Jugador "<<Ric->nombre<<" Sus puntos son "<<Ric->puntos<<endl;
        MostrarCarta(Ric->lista_cartas);
        cout<<"POBRE -- Jugador "<<Pob->nombre<<" Sus puntos son "<<Pob->puntos<<endl;
        MostrarCarta(Pob->lista_cartas);
        
        system("pause");
    }

    cout << NEGRITA<<MAGENTA<< "\n=== JUEGO TERMINADO ===" << RESET<<endl;
    system("pause");
    return 0;
}
