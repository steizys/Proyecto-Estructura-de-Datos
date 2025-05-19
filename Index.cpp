#include <iostream>
#include <stdlib.h>
#include <time.h>
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
////////////////////////////////////////////////////
int main(){
    cout<<"Proyecto 1"<<endl;
    cout<<"Autoras: Amelie Moreno"<<endl;
    cout<<"         Gabriela Cantos"<<endl;
    cout<<"         Steizy Fornica"<<endl;
    Jugador *Malla = NULL;
    Carta *Mazo = NULL;
    CartaSimple *Jerarquia = NULL;
    Carta *CartaMesa;
    /////// Llenado principal ///////
    LlenarJerarquia(&Jerarquia);
    InsertarJugador(&Malla,1);
    InsertarJugador(&Malla,2);
    InsertarJugador(&Malla,3);
    InsertarJugador(&Malla,4);
    CrearMazo(&Mazo);
    Reparticion(&Mazo, &Malla);
    /////////// Empieza el juego ///////////
    int j=0; //LLeva los turnos
    int partidas=0;
    int ronda=0, pases =0, patron=1;
    int jugada=0;
    //while(partidas<3){
        cout<<"Partida "<< partidas+1<<endl;
        //Asigan puntos dependiendo de como ganaron en la partida
        //Partida que finaliza cuando 3 se queden sin carta 
        //while (ContarCartas(BuscarJugador(Malla, 1)->lista_cartas)>0 && ContarCartas(BuscarJugador(Malla, 2)->lista_cartas)>0 && ContarCartas(BuscarJugador(Malla, 3)->lista_cartas)>0 && ContarCartas(BuscarJugador(Malla, 4)->lista_cartas)>0){
            ronda++;
            while(pases<3){ /// Cada ronda, se sale despues de tres pases
                cout<<"RONDA "<<ronda<<endl;
                if (ronda==1 && jugada==0){
                    for (int i = 1; i <= 4; i++) {
                        Jugador *jugador = BuscarJugador(Malla, i);
                        Carta *cartasjugador=jugador->lista_cartas;
                        bool buscar=BuscarCarta(cartasjugador, "3", "Diamante");
                        if (buscar==true) {
                            j = i;
                            cout<<"\n --- JUGADOR "<<j<<" --- "<<endl;
                            cout << "El jugador " << j << " comienza la partida con el 3 de diamantes." << endl;
                            CartaMesa=BuscarCartaNode(cartasjugador, "3", "Diamante");
                            DevolverCartasMazo (&Mazo, &cartasjugador,&CartaMesa);
                            j++;
                            break;
                        }
                    }       
                }
                if (j>4) j=1;
                Jugador *jugador=BuscarJugador (Malla, j);
                cout<<"\n---------- MESA ----------"<<endl;
                cout<<Mazo->nombre <<  " "<<Mazo->pinta<<endl;
                int jerarCMesa=PosJerarquia(Jerarquia, Mazo->nombre); //Me indica la jerarquia que tiene la ultima carta de la mesa/mazo
                int jerarCCarta; //Jerarquia de la carta que lance
                cout<<"\n --- JUGADOR "<<j<<" --- "<<endl;
                Carta *cartasjugador=jugador->lista_cartas;
                MostrarCarta(cartasjugador);
                cout<<"Esta ronda se rige por ";
                if (patron==1) cout<<"single (1 carta). "<<endl;
                if (patron>1){
                    if (patron==2){
                        cout<<"pares (2 cartas). "<<endl;
                        cout<<"\n Estas son tus pares disponibes"<<endl;
                    }else if (patron==3){
                        cout<<"trios (3 cartas). "<<endl;
                        cout<<"\nEstas son tus trios disponibes"<<endl;
                    }else{
                        cout<<"póker (4 cartas). "<<endl;
                        cout<<"\n Estas son tus póker disponibes"<<endl;

                    }
                    CartasPermitidas(cartasjugador, patron);
                }
                int op=0;
                while(op!=1 && op!=2){
                    cout<<"Seleccione su jugada: "<<endl;
                    cout<<"\t1. Lanzar Cartas"<<endl; ///Validar que tenga cartas, validar que tenga para lanzar esa cantidad de patron
                    cout<<"\t2. Pasar"<<endl;
                    cin>>op;
                    if (op!=1 && op!=2){
                        cout<<"Opcion Invalida"<<endl;
                    }
                } 
                if (op==2){ //Eligio la opcion 2, es decir, pasar
                    pases++;
                    j++;
                }else{///Lanzar Carta
                    int cantidadcartas=ContarCartas(cartasjugador);//Me dice si tiene cartas suficientes para jugar
                    int cantidadpatron=CartasPermitidasPatronVali(cartasjugador, patron); //Me dice si tiene suficientes cartas para jugar con cierto patron
                    int cantidadjerarquia= CartasPermitidasJerarquia(cartasjugador,jerarCMesa, Jerarquia, patron); //Me dice si dependiendo del patron, el jugador tiene cartas de mayor jerarquia que la mesa
                    cout<<" Cantidad de Cartas "<<cantidadcartas<<endl;
                    cout<<" Cantidad de Cartas por patron "<<cantidadpatron<<endl;
                    cout<<" Cantidad de Cartas por jerarquia "<<cantidadjerarquia<<endl;
                    //pases=0;
                    //Condiciones paar que pueda lanzar cartas
                    if (cantidadcartas==0){
                        cout<<"\nNo puedes jugar ya que no tienes cartas"<<endl;
                        cout<<"Tu turno pasa"<<endl;
                        pases++;
                    } else if (cantidadpatron<=0){
                        cout<<"\nNo tienes cartas suficientes para jugar segun el patron"<<endl;
                        cout<<"Tu turno pasa"<<endl;
                        pases++;
                    }else if(cantidadjerarquia<=0){
                        cout<<"\nNo tienes cartas con mayor jerarquia que la mesa"<<endl;
                        cout<<"Tu turno pasa"<<endl;
                        pases++;
                    }else{
                        cout<<"\nIngresa tus cartas a jugar "<<endl;
                        cout<<"Recuerda la cantidad de cartas permitidas para jugar y su jerarquia "<<endl;
                        cout<<"---------- MESA ----------"<<endl;
                        cout<<Mazo->nombre <<  " "<<Mazo->pinta<<endl;
                        int cont_cartasingresadas=patron;
                        int i=1;
                        string nombrecarta, pintacarta, primeracarta;
                        Carta *CartaJugadas=NULL;

                        /******** Ciclo ingreso de cartas  **********/
                        while(cont_cartasingresadas>0){
                            cout<<"Carta "<<i<<endl;
                            cout<<"Ingresa el nombre de la carta: "<<endl;
                            cout<<"[3][4][5][6][7][8][9][10][J][Q][K][A][2][JOKER]"<<endl;
                            cin>>nombrecarta;
                            pintacarta="";
                            
                            if (nombrecarta!="JOKER"){
                                while(pintacarta!="1" && pintacarta!="2" && pintacarta!="3" && pintacarta!="4" && pintacarta!="5"){
                                    cout<<"Ingrese la pinta"<<endl;
                                    cout<<"\t1. Diamante "<<endl;
                                    cout<<"\t2. Corazon "<<endl;
                                    cout<<"\t3. Trebol "<<endl;
                                    cout<<"\t4. Pica "<<endl;
                                    cin>>pintacarta;
                                }
                                if(pintacarta=="1"){
                                    pintacarta="Diamante";
                                }else if(pintacarta=="2"){
                                    pintacarta="Corazon";
                                }else if(pintacarta=="3"){
                                    pintacarta="Trebol";
                                }else if(pintacarta=="4"){
                                    pintacarta="Pica";
                                }
                            }else{
                                pintacarta="";
                            }
                            
                            if (BuscarCarta(cartasjugador, nombrecarta, pintacarta)){
                                if ((VecesAparicionValor(cartasjugador,nombrecarta)+VecesAparicionValor(cartasjugador,"JOKER"))>=patron){
                                    jerarCCarta=PosJerarquia(Jerarquia, nombrecarta);
                                    if (jerarCCarta>jerarCMesa){
                                        if (i==1){
                                            pases=0;
                                            primeracarta=nombrecarta;
                                            Carta *cartaBuscada=BuscarCartaNode(cartasjugador, nombrecarta, pintacarta);
                                            DevolverCartasMazo(&CartaJugadas,&cartasjugador ,&cartaBuscada);
                                            cout<<"--- CARTAS JUGADAS  ---"<<endl;
                                            MostrarCarta(CartaJugadas);
                                            i++;
                                            cont_cartasingresadas--;
                                        }else{
                                            if (nombrecarta==primeracarta || nombrecarta=="JOKER"){
                                                pases=0;
                                                primeracarta=nombrecarta;
                                                Carta *cartaBuscada=BuscarCartaNode(cartasjugador, nombrecarta, pintacarta);
                                                DevolverCartasMazo(&CartaJugadas,&cartasjugador ,&cartaBuscada);
                                                cout<<"--- CARTAS JUGADAS  ---"<<endl;
                                                MostrarCarta(CartaJugadas);
                                                i++;
                                                cont_cartasingresadas--;
                                            }else{
                                                cout<<"La carta ingresada no es del mismo tipo de tu primera carta o un JOKER que complete tu patron"<<endl;
                                                cout<<"La primera carta que ingresaste fue: "<<primeracarta<<endl;
                                            }      
                                        }
                                    }else{
                                        cout<<"La carta ingresada es de una jerarquia menor a la que se encuentra en mesa"<<endl;
                                    }
                                }else{
                                    cout<<"\nNo tienes suficientes cartas con ese nombre, para cumplir con el patron"<<endl;
                                }
                            }else{
                                cout<<"\nLa carta ingresada no existe en tu mazo de cartas"<<endl;
                            }
                            /*Carta *cartaBuscada=BuscarCartaNode(cartasjugador, nombrecarta, pintacarta);
                            cout<<"Nodo buscado "<<cartaBuscada->nombre<<endl;
                            
                            cout<<"--- CARTAS JUGADAS ---"<<endl;
                            MostrarCarta(CartaJugadas);
                            cout<<"--- CARTAS DEL JUGADOR  ---"<<endl;
                            MostrarCarta(cartasjugador);
                            DevolverCartasMazo(&CartaJugadas,&cartasjugador ,&cartaBuscada);
                            cout<<"--- CARTAS JUGADAS  ---"<<endl;
                            MostrarCarta(CartaJugadas);
                            cout<<"--- CARTAS DEL JUGADOR  ---"<<endl;
                            MostrarCarta(cartasjugador);
                            i++;
                            cont_cartasingresadas--;*/
                        }
                        DevolverCartasJugadasMazo(&Mazo, &CartaJugadas);
                        cout<<"--- MAZO  ---"<<endl;
                        MostrarCarta(Mazo);
                        cout<<"--- CARTAS JUGADAS ---"<<endl;
                        MostrarCarta(CartaJugadas);
                    }
                    
                }
                
                j++;
                jugada++;
                system("pause");
            }
            cout<<" 3 pases";
       //} 
   // }    

    system("pause");

    return 0;
}