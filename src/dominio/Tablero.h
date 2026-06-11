#ifndef TABLERO_H
#define TABLERO_H

#include "Simbolo.h"
#include <set>
#include <vector>
using namespace std;

class Tablero{
private:
    Simbolo datos[3][3];
    set<int> ocupado;

public:
    Tablero(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                datos[i][j]=Simbolo::VACIO;
            }
        }
    }

    Simbolo get(int i, int j) const{
        return datos[i][j];
    }

    bool colocar(int i, int j, Simbolo v){
        if(i<0||i>2||j<0||j>2){
            return false;
        }
        int idx=i*3+j;
        if(ocupado.count(idx)>0){
            return false;
        }
        datos[i][j]=v;
        ocupado.insert(idx);
        return true;
    }

    void deshacer(int i, int j){
        int idx=i*3+j;
        datos[i][j]=Simbolo::VACIO;
        ocupado.erase(idx);
    }

    void restaurar(int i, int j, Simbolo s){
        datos[i][j]=s;
        ocupado.insert(i*3+j);
    }

    bool estaOcupada(int i, int j) const{
        return ocupado.count(i*3+j)>0;
    }

    bool estaLleno() const{
        return (int)ocupado.size()==9;
    }

    vector<int> celdasLibres() const{
        vector<int> libres;
        for(int i=0;i<9;i++){
            if(ocupado.count(i)==0){
                libres.push_back(i);
            }
        }
        return libres;
    }

    void limpiar(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                datos[i][j]=Simbolo::VACIO;
            }
        }
        ocupado.clear();
    }
};

#endif