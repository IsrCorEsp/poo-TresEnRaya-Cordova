#ifndef PARTIDA_H
#define PARTIDA_H

#include "../dominio/Jugador.h"
#include "../dominio/Tablero.h"
#include "EstadoJuego.h"
#include <vector>
#include <map>
#include <array>
#include <string>
using namespace std;

class Partida{
private:
    Tablero tablero;
    Jugador* jugador1;
    Jugador* jugador2;
    Jugador* jugadorActual;
    EstadoJuego estado;
    vector<int> historial;
    map<string,int> estadisticas;
    array<int,3> lineaGanadora;

    void verificarEstado(){
 const int lineas[8][3]={ {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}
        };
        for(int i=0;i<8;i++){
 int a=lineas[i][0],b=lineas[i][1],c=lineas[i][2];
            Simbolo sa=tablero.get(a/3,a%3);
            Simbolo sb=tablero.get(b/3,b%3);
            Simbolo sc=tablero.get(c/3,c%3);
 
if(sa!=Simbolo::VACIO&&sa==sb&&sb==sc){
                lineaGanadora={a,b,c};
                if(sa==Simbolo::X){
          estado=EstadoJuego::GANADOR_X;
                    estadisticas["victorias_X"]++;
                    jugador1->sumarVictoria();
                    jugador2->sumarDerrota();
                }else{
       estado=EstadoJuego::GANADOR_O;
                    estadisticas["victorias_O"]++;
                    jugador2->sumarVictoria();
                    jugador1->sumarDerrota();
                }
                return;
            }
        }
        if(tablero.estaLleno()){
            estado=EstadoJuego::EMPATE;
            estadisticas["empates"]++;
            jugador1->sumarEmpate();
            jugador2->sumarEmpate();
        }
    }

public:
    Partida(Jugador* j1, Jugador* j2){
        jugador1=j1;
        jugador2=j2;
        jugadorActual=j1;
        estado=EstadoJuego::EN_CURSO;
        lineaGanadora[0]=-1;
        lineaGanadora[1]=-1;
        lineaGanadora[2]=-1;
        estadisticas["victoriasX"]=0;
        estadisticas["victoriasO"]=0;
        estadisticas["empates"]=0;
    }

    bool hacerMovimiento(int fila, int col){
        if(estado!=EstadoJuego::EN_CURSO){
            return false;
        }
   if(!tablero.colocar(fila,col,jugadorActual->getSimbolo())){
            return false;
        }
        historial.push_back(fila*3+col);
        verificarEstado();
        if(estado==EstadoJuego::EN_CURSO){
            if(jugadorActual==jugador1){
                jugadorActual=jugador2;
            }else{
                jugadorActual=jugador1;
            }
        }
        return true;
    }

    bool deshacerMovimiento(){
      if(estado!=EstadoJuego::EN_CURSO){
            return false;
        }
        if(historial.empty()){
            return false;
        }
        int idx=historial.back();
        historial.pop_back();
        int fila=idx/3;
        int col=idx%3;
        tablero.deshacer(fila,col);
        if(jugadorActual==jugador1){
            jugadorActual=jugador2;
        }else{
            jugadorActual=jugador1;
        }
        lineaGanadora[0]=-1;
        lineaGanadora[1]=-1;
        lineaGanadora[2]=-1;
        return true;
    }

void restaurarTablero(int tab[3][3], int turno){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(tab[i][j]!=0){
     tablero.restaurar(i,j,(Simbolo)tab[i][j]);
                }
            }
        }
        if(turno==2){
            jugadorActual=jugador2;
        }else{
            jugadorActual=jugador1;
        }
    }

    void setHistorial(const vector<int>& h){
        historial=h;
    }

    void nuevaRonda(){
        tablero.limpiar();
        historial.clear();
        lineaGanadora[0]=-1;
        lineaGanadora[1]=-1;
        lineaGanadora[2]=-1;
        jugadorActual=jugador1;
        estado=EstadoJuego::EN_CURSO;
    }

    void reiniciarCompleto(){
        nuevaRonda();
        estadisticas["victorias_X"]=0;
        estadisticas["victorias_O"]=0;
        estadisticas["empates"]=0;
        jugador1->resetEstadisticas();
        jugador2->resetEstadisticas();
    }

    void setEstadisticas(int vx, int vo, int emp){
        estadisticas["victorias_X"]=vx;
        estadisticas["victorias_O"]=vo;
        estadisticas["empates"]=emp;
        jugador1->setVictorias(vx);
        jugador2->setVictorias(vo);
    }

    EstadoJuego getEstado() const{
    	return estado;
    }
    Jugador* getJugadorActual() const{
    	return jugadorActual;
    }
    Jugador* getJugador1() const{
    	return jugador1;
    	}
    Jugador* getJugador2() const{
    	return jugador2;
    	}
  const Tablero& getTablero() const{
    return tablero;
    }
    const vector<int>& getHistorial() const{
    	return historial;
    	}
 const map<string,int>& getEstadisticas()  const{
    	return estadisticas;
    	}
    array<int,3> getLineaGanadora() const{
    	return lineaGanadora;
    	}
};

#endif