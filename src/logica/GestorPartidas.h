#ifndef GESTORPARTIDAS_H
#define GESTORPARTIDAS_H

#include "Partida.h"
#include "../../lib/nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;
using json=nlohmann::json;

struct DatosJugador{
    int victorias;
    int derrotas;
    int empates;
    int puntos;

    DatosJugador(){
        victorias=0;
        derrotas=0;
        empates=0;
        puntos=0;
    }
};

class GestorPartidas{
public:

    struct DatosGuardados{
        string nombre1;
        string nombre2;
        int victoriasX;
        int victoriasO;
        int empates;
        int puntos1;
        int puntos2;
        int tablero[3][3];
        int turno;
        vector<string> historial;
        vector<int> movimientos;
        bool valido;

        DatosGuardados(){
            nombre1="Jugador 1";
            nombre2="Jugador 2";
            victoriasX=0;
            victoriasO=0;
            empates=0;
            puntos1=0;
            puntos2=0;
            turno=1;
            valido=false;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    tablero[i][j]=0;
               }
            }
        }
    };

  static void guardar(const Partida& partida, const string& nombre1, const string& nombre2, const vector<string>& historial, const string& archivo="../data/partida.json"){
        json obj;
        obj["jugador1"]=nombre1;
        obj["jugador2"]=nombre2;
   obj["victoriasX"]=partida.getEstadisticas().at("victoriasX");
   obj["victoriasO"]=partida.getEstadisticas().at("victoriasO");
     obj["empates"]=partida.getEstadisticas().at("empates");
   obj["puntos1"]=partida.getJugador1()->getPuntos();
 obj["puntos2"]=partida.getJugador2()->getPuntos();

        int t;
 if(partida.getJugadorActual()==partida.getJugador1()){
            t=1;
        }else{
            t=2;
        }
        obj["turno"]=t;

        json tab=json::array();
        for(int i=0;i<3;i++){
            json fila=json::array();
            for(int k=0;k<3;k++){
fila.push_back((int)partida.getTablero().get(i,k));
            }
            tab.push_back(fila);
        }
        obj["tablero"]=tab;

        json hist=json::array();
        for(int i=0;i<(int)historial.size();i++){
            hist.push_back(historial[i]);
        }
        obj["historial"]=hist;

        json movs=json::array();
 for(int i=0;i<(int)partida.getHistorial().size();i++){
  movs.push_back(partida.getHistorial()[i]);
        }
        obj["movimientos"]=movs;

        ofstream file(archivo);
        file<<obj.dump(2);
        file.close();
    }

  static DatosGuardados cargar(const string& archivo="../data/partida.json"){
        DatosGuardados datos;
        ifstream file(archivo);
        if(!file){
            return datos;
        }
        json arr;
        file>>arr;
        file.close();

 datos.nombre1=arr.value("jugador1","Jugador 1");
   datos.nombre2=arr.value("jugador2","Jugador 2");
  datos.victoriasX=arr.value("victoriasX",0);
 datos.victoriasO=arr.value("victoriasO",0);
     datos.empates=arr.value("empates",0);
      datos.puntos1=arr.value("puntos1",0);
    datos.puntos2=arr.value("puntos2",0);
        datos.turno=arr.value("turno",1);

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
     datos.tablero[i][j]=arr["tablero"][i][j];
            }
        }

        if(arr.contains("historial")){
 for(int i=0;i<(int)arr["historial"].size();i++){
                string aux=arr["historial"][i];
                datos.historial.push_back(aux);
            }
        }

        if(arr.contains("movimientos")){
for(int i=0;i<(int)arr["movimientos"].size();i++){
            int aux=arr["movimientos"][i];
            datos.movimientos.push_back(aux);
            }
        }

        datos.valido=true;
        return datos;
    }

    static void guardarJugadores(const map<string,DatosJugador>& mapa, const string& archivo="../data/jugadores.json"){
        json arr=json::array();
        for(auto& p:mapa){
            json obj;
            obj["nombre"]=p.first;
            obj["victorias"]=p.second.victorias;
            obj["derrotas"]=p.second.derrotas;
            obj["empates"]=p.second.empates;
            obj["puntos"]=p.second.puntos;
            arr.push_back(obj);
        }
        ofstream file(archivo);
        file<<arr.dump(2);
        file.close();
    }

    static map<string,DatosJugador> cargarJugadores(const string& archivo="../data/jugadores.json"){
        map<string,DatosJugador> mapa;
        ifstream file(archivo);
        if(!file){
            return mapa;
        }
        json arr;
        file>>arr;
        file.close();
        for(int i=0;i<(int)arr.size();i++){
            DatosJugador datosJ;
      datosJ.victorias=arr[i].value("victorias",0);
     datosJ.derrotas=arr[i].value("derrotas",0);
       datosJ.empates=arr[i].value("empates",0);
       datosJ.puntos=arr[i].value("puntos",0);
     string nombre=arr[i].value("nombre","");
            mapa[nombre]=datosJ;
        }
        return mapa;
    }
};

#endif

