#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "Render.h"
#include "../logica/GestorPartidas.h"
#include "../logica/EstadoJuego.h"
using namespace std;

class Interfaz{
private:
    sf::RenderWindow ventana;
    sf::Font fuente;
    unique_ptr<Render> render;
    unique_ptr<Jugador> jugador1;
    unique_ptr<Jugador> jugador2;
    unique_ptr<Partida> partida;
    Pantalla pantalla;
    string inputN1;
    string inputN2;
    int campo;
    bool mostrarStats;
    vector<string> historialRondas;
map<string,DatosJugador> mapaJugadores;
    string mensajeError;
    GestorPartidas::DatosGuardados guardado;

    sf::FloatRect rJugar(){
    	float W=ventana.getSize().x;
    	return{W/2-100,330,200,50};
    	}
    sf::FloatRect rCargar(){
    	float W=ventana.getSize().x;
    	return{W/2-210,395,420,50};
    	}
    sf::FloatRect rSalir(){
    	float W=ventana.getSize().x;
    	return{W/2-100,465,200,50};
    	}
    sf::FloatRect rCampo1(){
  float W=ventana.getSize().x;
  return{W/2-150,155,300,44};
  }
    sf::FloatRect rCampo2(){
    	float W=ventana.getSize().x;
    	return{W/2-150,245,300,44};
    	}
    sf::FloatRect rNuevaRonda(){
    	float W=ventana.getSize().x;
    	float H=ventana.getSize().y;
    	return{W/2-185,H/2+20,170,50};
    	}
    sf::FloatRect rMenuBtn(){
    	float W=ventana.getSize().x;
    	float H=ventana.getSize().y;
    	return{W/2+15,H/2+20,170,50};
    	}

 bool dentro(sf::FloatRect r, float x, float y){
        return r.contains(x,y);
    }

   sf::Vector2f mouse(){
sf::Vector2i m=sf::Mouse::getPosition(ventana);
    return{(float)m.x,(float)m.y};
    }

    void guardarTodo(){
GestorPartidas::guardar(*partida,jugador1->getNombre(),jugador2->getNombre(),historialRondas);

GestorPartidas::guardarJugadores(mapaJugadores);
    guardado=GestorPartidas::cargar();
    }

    void actualizarMapa(){
  mapaJugadores[jugador1->getNombre()].victorias=jugador1->getVictorias();
   mapaJugadores[jugador1->getNombre()].derrotas=jugador1->getDerrotas();
    mapaJugadores[jugador1->getNombre()].empates=jugador1->getEmpates();
    mapaJugadores[jugador1->getNombre()].puntos=jugador1->getPuntos();
    mapaJugadores[jugador2->getNombre()].victorias=jugador2->getVictorias();
    mapaJugadores[jugador2->getNombre()].derrotas=jugador2->getDerrotas();
   mapaJugadores[jugador2->getNombre()].empates=jugador2->getEmpates();
   mapaJugadores[jugador2->getNombre()].puntos=jugador2->getPuntos();
    }

 void iniciar(string n1, string n2){
    string a,b;
    if(n1.empty()){
        a="Jugador 1";
    }else{
        a=n1;
    }
    if(n2.empty()){
        b="Jugador 2";
    }else{
        b=n2;
    }

    jugador1=unique_ptr<Jugador>(new Jugador(a,Simbolo::X));
    jugador2=unique_ptr<Jugador>(new Jugador(b,Simbolo::O));

    if(mapaJugadores.count(a) > 0){
 jugador1->setVictorias(mapaJugadores[a].victorias);
 jugador1->setDerrotas(mapaJugadores[a].derrotas);
  jugador1->setEmpates(mapaJugadores[a].empates);
  jugador1->setPuntos(mapaJugadores[a].puntos);
    }
    if(mapaJugadores.count(b) > 0){
    jugador2->setVictorias(mapaJugadores[b].victorias);
   jugador2->setDerrotas(mapaJugadores[b].derrotas);
  jugador2->setEmpates(mapaJugadores[b].empates);
   jugador2->setPuntos(mapaJugadores[b].puntos);
    }

    partida=unique_ptr<Partida>(new Partida(jugador1.get(),jugador2.get()));
    historialRondas.clear();
    mensajeError="";
    pantalla=Pantalla::JUGANDO;
}


    void iniciarDesdeGuardado(){
iniciar(guardado.nombre1,guardado.nombre2);
       historialRondas=guardado.historial;
partida->setEstadisticas(guardado.victoriasX,guardado.victoriasO,guardado.empates);
     jugador1->setPuntos(guardado.puntos1);
  jugador2->setPuntos(guardado.puntos2);
     partida->restaurarTablero(guardado.tablero,guardado.turno);
 partida->setHistorial(guardado.movimientos);
    }

void eventoMenu(sf::Event ev){
       sf::Vector2f m=mouse();

  if(ev.type==sf::Event::MouseButtonPressed &&ev.mouseButton.button==sf::Mouse::Left){
       if(dentro(rCampo1(),m.x,m.y)){
               campo=0;
      }else if(dentro(rCampo2(),m.x,m.y)){
               campo=1;
         }else{
               campo=-1;
            }

      if(dentro(rJugar(),m.x,m.y)){
             string a,b;
            if(inputN1.empty()){
          a="Jugador 1";
             }else{
            a=inputN1;
      }
                if(inputN2.empty()){
              b="Jugador 2";
               }else{
             b=inputN2;
                }
                if(a==b){
   mensajeError="Los jugadores no pueden tener el mismo nombre";
                }else{
            mensajeError="";
         iniciar(inputN1,inputN2);
             }
            }else if(guardado.valido&&dentro(rCargar(),m.x,m.y)){
       iniciarDesdeGuardado();
            }else if(dentro(rSalir(),m.x,m.y)){
        ventana.close();
            }
        }

     if(ev.type==sf::Event::TextEntered &&campo>=0){
        uint32_t c=ev.text.unicode;
        if(campo==0){
          if(c==8&&!inputN1.empty()){
              inputN1.pop_back();
}else if(c>=32&&c<128&&inputN1.size()<14){
            inputN1+=(char)c;
                }
            }else{
              if(c==8&&!inputN2.empty()){
                 inputN2.pop_back();
 }else if(c>=32&&c<128&&inputN2.size()<14){
                inputN2+=(char)c;
                }
            }
        }

        if(ev.type==sf::Event::KeyPressed){
          if(ev.key.code==sf::Keyboard::Tab){
                campo=(campo+1)%2;
            }
      if(ev.key.code==sf::Keyboard::Return){
                string a,b;
      if(inputN1.empty()){
             a="Jugador 1";
  }else{
                    a=inputN1;
                }
           if(inputN2.empty()){
                 b="Jugador 2";
         }else{
                   b=inputN2;
                }
                if(a==b){
         mensajeError="Los jugadores no pueden tener el mismo nombre";
                }else{
           mensajeError="";
          iniciar(inputN1,inputN2);
                }
      }
        }
    }

    void eventoJuego(sf::Event ev){
        sf::Vector2f m=mouse();

if(ev.type==sf::Event::MouseButtonPressed && ev.mouseButton.button==sf::Mouse::Left&&partida->getEstado()== EstadoJuego::EN_CURSO){
        float cell=200,oy=120;
            if(m.y>=oy&&m.x<600){
                int col=(int)(m.x/cell);
                int fila=(int)((m.y-oy)/cell);
           partida->hacerMovimiento(fila,col);
        if(partida->getEstado()!=EstadoJuego::EN_CURSO){
                    string res;
    int nRonda=(int)historialRondas.size()+1;
    if(partida->getEstado()==EstadoJuego::GANADOR_X){
        res="R"+to_string(nRonda)+": Gana "+jugador1->getNombre();
                    }else if(partida->getEstado()==EstadoJuego::GANADOR_O){
        res="R"+to_string(nRonda)+": Gana "+jugador2->getNombre();
                    }else{
    res="R"+to_string(nRonda)+": Empate";
                    }
              historialRondas.push_back(res);
                    actualizarMapa();
               pantalla=Pantalla::RESULTADO;
            }
            }
        }

     if(ev.type==sf::Event::KeyPressed){
         if(ev.key.code==sf::Keyboard::Z){
      partida->deshacerMovimiento();
            }
  if(ev.key.code==sf::Keyboard::S){
               guardarTodo();
           }
  if(ev.key.code==sf::Keyboard::Escape){
                guardarTodo();
       pantalla=Pantalla::MENU;
            }
        }
  }

  void eventoResultado(sf::Event ev){
        sf::Vector2f m=mouse();

  if(ev.type==sf::Event::MouseButtonPressed &&ev.mouseButton.button==sf::Mouse::Left){
       if(dentro(rNuevaRonda(),m.x,m.y)){
          partida->nuevaRonda();
                pantalla=Pantalla::JUGANDO;
        }else if(dentro(rMenuBtn(),m.x,m.y)){
                partida->nuevaRonda();
                guardarTodo();
           pantalla=Pantalla::MENU;
            }
        }
    }

public:
    Interfaz(){
     ventana.create(sf::VideoMode(920,720),"Tres en Raya",sf::Style::Default);
        pantalla=Pantalla::MENU;
        campo=-1;
        mostrarStats=false;
        mensajeError="";
        ventana.setFramerateLimit(60);
   fuente.loadFromFile("../assets/fuente.ttf");
        render=unique_ptr<Render>(new Render(ventana,fuente));

mapaJugadores=GestorPartidas::cargarJugadores();
     guardado=GestorPartidas::cargar();
        if(guardado.valido){
        inputN1=guardado.nombre1;
           inputN2=guardado.nombre2;
        }
    }

    void ejecutar(){
     while(ventana.isOpen()){
           sf::Event ev;
         while(ventana.pollEvent(ev)){
          if(ev.type==sf::Event::Closed){
                    ventana.close();
                }
          if(ev.type==sf::Event::Resized){
  sf::FloatRect vista(0,0,ev.size.width,ev.size.height);
         ventana.setView(sf::View(vista));
                }
   if(ev.type==sf::Event::KeyPressed&&ev.key.code==sf::Keyboard::H){
      mostrarStats=!mostrarStats;
   }else if(mostrarStats&&ev.type==sf::Event::MouseButtonPressed){
            mostrarStats=false;
     }else if(!mostrarStats){
              if(pantalla==Pantalla::MENU){
       eventoMenu(ev);
  }else if(pantalla==Pantalla::JUGANDO){
             eventoJuego(ev);
   }else if(pantalla==Pantalla::RESULTADO){
               eventoResultado(ev);
         }
               }
         }
           int celdaHover=-1;
           if(pantalla==Pantalla::JUGANDO&& partida&&partida->getEstado()==EstadoJuego::EN_CURSO){
           sf::Vector2f m=mouse();
            float cell=200,oy=120;
 if(m.y>=oy&&m.x>=0&&m.x<600&&m.y<720){
             int col=(int)(m.x/cell);
               int fila=(int)((m.y-oy)/cell);
     if(col>=0&&col<3&&fila>=0&&fila<3){
             int idx=fila*3+col;
 vector<int> libres=partida->getTablero().celdasLibres();
        for(int i=0;i<(int)libres.size();i++){
              if(libres[i]==idx){
                   celdaHover=idx;
                  break;
                }
                       }
                    }
           }
            }

            ventana.clear(sf::Color(20,20,40));

    if(pantalla==Pantalla::MENU){
 render->dibujarMenu(inputN1,inputN2,campo,guardado,mensajeError);
          }else{
           render->dibujarPanel(*partida);
 render->dibujarTablero(*partida,celdaHover);
  render->dibujarHistorial(historialRondas);
     if(pantalla==Pantalla::RESULTADO){
      render->dibujarResultado(*partida);
             }
            }

 if(mostrarStats){
render->dibujarEstadisticas(mapaJugadores);
           }

         ventana.display();
        }
    }
};

#endif

