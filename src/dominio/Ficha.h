#ifndef FICHA_H
#define FICHA_H

#include "Simbolo.h"
#include <string>

using namespace std;

class Ficha{
public:
  virtual Simbolo getSimbolo() const=0;
 virtual string getRep() const=0;
    virtual string getColor() const=0;
    virtual ~Ficha()=default;
};

class FichaX : public Ficha{
public:
    Simbolo getSimbolo() const override{
    	 return Simbolo::X;
     }
  string getRep() const override{
    	 return "X";
    	  }
    string getColor() const override{
    return "Rojo";
    	  }
};

class FichaO : public Ficha{
public:
    Simbolo getSimbolo() const override{
    return Simbolo::O;
    }
  string getRep() const override{
    return "O";
   }
    string getColor() const override{
      return "Azul";
     }
};

#endif
