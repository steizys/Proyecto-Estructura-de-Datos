#include<Magbase.h>

bool BuscarCarta(Jugador *p, string nombre, string pinta){
    Carta *cartas = p->lista_cartas;
    while (cartas && cartas->next){
        if (cartas->nombre==nombre && cartas->pinta==pinta) return true;
    }
    return false;
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

void LlenarJerarquia(CartaSimple **p){
    string nombre="";
    CartaSimple *joker = new CartaSimple;
    joker->nombre= "Joker";
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
        nuevo->nombre= "Joker";
        nuevo->next=NULL;
        nuevo->next=*p
        *p= nuevo;
    }
    
}
void MostrarJerarquia(CartaSimple *p){ 
    while (p){
        cout << p->nombre<< " ";
        p = p->next;
    }
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
    LlenarJerarquia(&Jerarquia)
    MostrarJerarquia(Jerarquia);


    system("pause");

    return 0;
}