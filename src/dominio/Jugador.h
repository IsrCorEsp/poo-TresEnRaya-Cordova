#ifndef JUGADOR_H
#define JUGADOR_H

#include "Ficha.h"
#include <string>
#include <memory>
using namespace std;

class Jugador{
private:
    string nombre;
    Simbolo simbolo;
    unique_ptr<Ficha> ficha;
    int victorias;
    int derrotas;
    int empates;
    int puntos;

public:
Jugador(string nom, Simbolo sim){
    nombre=nom;
    simbolo=sim;
    victorias=0;
    derrotas=0;
    empates=0;
    puntos=0;
    if(simbolo==Simbolo::X){
       ficha=unique_ptr<Ficha>(new FichaX());
    }else{
       ficha=unique_ptr<Ficha>(new FichaO());
    }
}

    string getNombre() const{ 
    return nombre; 
    }
    Simbolo getSimbolo() const{ 
    return simbolo;
     }
    const Ficha* getFicha() const{ 
    return ficha.get();
     }
    int getVictorias() const{
    	return victorias;
    }
    int getDerrotas() const{ 
    return derrotas;
     }
    int getEmpates() const{
    	return empates;
    	 }
    int getPuntos() const{ 
    return puntos; 
    }
    int getPartidasJugadas()const{ 
    return victorias+derrotas+empates; 
    }

    void setVictorias(int v){ 
    victorias=v; 
    }
    void setDerrotas(int d){
    	derrotas=d;
    	  }
    void setEmpates(int e){
    empates=e; 
    }
    void setPuntos(int p){
    	 puntos=p;
    	 }

    void sumarVictoria(){
        victorias++;
        puntos+=3;
    }

    void sumarDerrota(){
        derrotas++;
    }

    void sumarEmpate(){
        empates++;
        puntos++;
    }

    void resetEstadisticas(){
        victorias=0;
        derrotas=0;
        empates=0;
        puntos=0;
    }
};

#endif
