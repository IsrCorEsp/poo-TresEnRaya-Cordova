#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "../logica/Partida.h"
#include "../logica/GestorPartidas.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Render{
private:
    sf::RenderWindow& ventana;
    sf::Font& fuente;

    void dibujarTexto(string texto, float x, float y, int tam, sf::Color color){
        sf::Text t;
       t.setFont(fuente);
        t.setString(texto);
     t.setCharacterSize(tam);
        t.setFillColor(color);
        t.setPosition(x,y);
        ventana.draw(t);
   }

void dibujarBoton(sf::FloatRect r, string texto){
  sf::RectangleShape btn(sf::Vector2f(r.width,r.height));
        btn.setPosition(r.left,r.top);
     btn.setFillColor(sf::Color(70,130,180));
      btn.setOutlineColor(sf::Color::White);
        btn.setOutlineThickness(2);
        ventana.draw(btn);

        sf::Text t;
        t.setFont(fuente);
        t.setString(texto);
        t.setCharacterSize(20);
        t.setFillColor(sf::Color::White);
      sf::FloatRect b=t.getLocalBounds();
t.setOrigin(b.left+b.width/2,b.top+b.height/2);
t.setPosition(r.left+r.width/2,r.top+r.height/2);
        ventana.draw(t);
    }

public:
    Render(sf::RenderWindow& v, sf::Font& f):ventana(v),fuente(f){}

    void dibujarPanel(Partida& p){
        float W=ventana.getSize().x;

sf::RectangleShape panel(sf::Vector2f(W,120));
   panel.setFillColor(sf::Color(30,30,30));
        ventana.draw(panel);

        Jugador* j1=p.getJugador1();
        Jugador* j2=p.getJugador2();

      dibujarTexto(j1->getNombre()+" (X)",20,15,20,sf::Color(220,60,60));
        dibujarTexto("Victorias: "+to_string(j1->getVictorias()),20,45,15,sf::Color(180,180,180));
    dibujarTexto("Puntos: "+to_string(j1->getPuntos()),20,68,15,sf::Color(180,180,180));

      dibujarTexto(j2->getNombre()+" (O)",W-210,15,20,sf::Color(60,110,220));
      dibujarTexto("Victorias: "+to_string(j2->getVictorias()),W-210,45,15,sf::Color(180,180,180));
      dibujarTexto("Puntos: "+to_string(j2->getPuntos()),W-210,68,15,sf::Color(180,180,180));

      dibujarTexto("Empates: "+to_string(p.getEstadisticas().at("empates")),W/2-50,45,15,sf::Color(180,180,180));

if(p.getEstado()==EstadoJuego::EN_CURSO){
 dibujarTexto("Turno: "+p.getJugadorActual()->getNombre(),W/2-60,15,18,sf::Color::Yellow);
        }

       dibujarTexto("[S] Guardar  [Z] Deshacer  [ESC] Menu  [H] Estadisticas",20,97,11,sf::Color(100,100,100));
    }

void dibujarTablero(Partida& p, int celdaHover){
        float cell=200;
        float oy=120;

  sf::RectangleShape fondo(sf::Vector2f(600,600));
        fondo.setPosition(0,oy);
 fondo.setFillColor(sf::Color(245,245,240));
        ventana.draw(fondo);

        sf::RectangleShape lin;
       lin.setFillColor(sf::Color(50,50,50));
        for(int i=1;i<3;i++){
            lin.setSize(sf::Vector2f(6,600));
            lin.setPosition(cell*i-3,oy);
            ventana.draw(lin);
            lin.setSize(sf::Vector2f(600,6));
            lin.setPosition(0,oy+cell*i-3);
            ventana.draw(lin);
        }

     array<int,3> lg=p.getLineaGanadora();

        for(int f=0;f<3;f++){
            for(int c=0;c<3;c++){
          Simbolo s=p.getTablero().get(f,c);
                int idx=f*3+c;

                if(s==Simbolo::VACIO&&idx==celdaHover){
sf::RectangleShape hl(sf::Vector2f(cell-4,cell-4));
         hl.setPosition(c*cell+2,oy+f*cell+2);
   hl.setFillColor(sf::Color(200,200,200,60));
                    ventana.draw(hl);
                }

                if(s==Simbolo::VACIO){
                    continue;
                }

                float cx=c*cell+cell/2;
                float cy=oy+f*cell+cell/2;
  bool esLG=(lg[0]== idx||lg[1]==idx||lg[2]==idx);

        sf::Color col;
        if(esLG){
          col=sf::Color(50,200,100);
           }else if(s==Simbolo::X){
          col=sf::Color(220,60,60);
           }else{
      col=sf::Color(60,110,220);
             }

    if(s==Simbolo::X){
              float lon=130,gros=18;
 sf::RectangleShape l1(sf::Vector2f(lon,gros));
            l1.setOrigin(lon/2,gros/2);
                l1.setPosition(cx,cy);
         l1.setRotation(45);
                l1.setFillColor(col);
                ventana.draw(l1);

 sf::RectangleShape l2(sf::Vector2f(lon,gros));
            l2.setOrigin(lon/2,gros/2);
             l2.setPosition(cx,cy);
           l2.setRotation(-45);
            l2.setFillColor(col);
            ventana.draw(l2);
                }else{
               sf::CircleShape circ(65);
                   circ.setOrigin(65,65);
                circ.setPosition(cx,cy);
     circ.setFillColor(sf::Color::Transparent);
            circ.setOutlineColor(col);
                 circ.setOutlineThickness(18);
                    ventana.draw(circ);
               }
            }
        }
    }

 void dibujarHistorial(vector<string>& historial){
        float px=620;
        float py=120;
        float pw=280;
        float ph=600;

sf::RectangleShape panel(sf::Vector2f(pw,ph));
   panel.setPosition(px,py);
        panel.setFillColor(sf::Color(25,25,45));
  panel.setOutlineColor(sf::Color(60,60,80));
   panel.setOutlineThickness(1);
        ventana.draw(panel);

        dibujarTexto("Historial",px+pw/2-40,py+12,18,sf::Color::White);

sf::RectangleShape sep(sf::Vector2f(pw-20,1));
        sep.setPosition(px+10,py+40);
        sep.setFillColor(sf::Color(60,60,80));
        ventana.draw(sep);

     if(historial.empty()){
     dibujarTexto("Sin rondas",px+pw/2-40,py+ph/2,14,sf::Color(100,100,100));
        }else{
      int inicio=0;
      if((int)historial.size()>12){
      inicio=(int)historial.size()-12;
            }
   for(int i=inicio;i<(int)historial.size();i++){
          float y=py+55+(i-inicio)*42;
       dibujarTexto(historial[i],px+10,y,13,sf::Color(200,200,200));
            }
        }
    }

    void dibujarEstadisticas(map<string,DatosJugador>& mapa){
      float W=ventana.getSize().x;
        float H=ventana.getSize().y;

sf::RectangleShape overlay(sf::Vector2f(W,H));
  overlay.setFillColor(sf::Color(0,0,0,180));
       ventana.draw(overlay);

        float ph=80.f+(float)mapa.size()*50.f;
     if(ph>500.f){
            ph=500.f;
        }
     if(ph<130.f){
            ph=130.f;
        }
        float pw=500;
        float px=W/2-pw/2;
        float py=H/2-ph/2;

sf::RectangleShape panel(sf::Vector2f(pw,ph));
      panel.setPosition(px,py);
        panel.setFillColor(sf::Color(25,25,45));
        panel.setOutlineColor(sf::Color::White);
        panel.setOutlineThickness(2);
        ventana.draw(panel);

       dibujarTexto("Estadisticas de jugadores",px+pw/2-120,py+15,18,sf::Color::White);

sf::RectangleShape sep(sf::Vector2f(pw-20,1));
   sep.setPosition(px+10,py+45);
        sep.setFillColor(sf::Color(80,80,100));
        ventana.draw(sep);

   dibujarTexto("Nombre", px+20, py+55,14,sf::Color(180,180,180));
        dibujarTexto("V", px+220,py+55,14,sf::Color(180,180,180));
        dibujarTexto("D", px+280,py+55,14,sf::Color(180,180,180));
        dibujarTexto("E", px+340,py+55,14,sf::Color(180,180,180));
        dibujarTexto("Pts", px+400,py+55,14,sf::Color(180,180,180));

      if(mapa.empty()){
      dibujarTexto("Sin jugadores registrados",px+pw/2-100,py+ph/2,14,sf::Color(100,100,100));
        }else{
        int fila=0;
       for(auto& par:mapa){
          float y=py+80+(float)fila*40;
 dibujarTexto(par.first, px+20, y,14, sf::Color::White);
  dibujarTexto(to_string(par.second.victorias), px+220,y,14,sf::Color(50,200,100));
   dibujarTexto(to_string(par.second.derrotas), px+280,y,14,sf::Color(220,60,60));
    dibujarTexto(to_string(par.second.empates), px+340,y,14,sf::Color::Yellow);
  dibujarTexto(to_string(par.second.puntos), px+400,y,14,sf::Color(60,110,220));
        fila++;
            }
        }

   dibujarTexto("[H] Cerrar",px+pw/2-40,py+ph-25,13,sf::Color(100,100,100));
    }

    void dibujarResultado(Partida& p){
        float W=ventana.getSize().x;
        float H=ventana.getSize().y;

sf::RectangleShape overlay(sf::Vector2f(W,H));
     overlay.setFillColor(sf::Color(0,0,0,150));
     ventana.draw(overlay);

 sf::RectangleShape caja(sf::Vector2f(400,200));
     caja.setPosition(W/2-200,H/2-100);
     caja.setFillColor(sf::Color(30,30,50));
   caja.setOutlineColor(sf::Color::White);
       caja.setOutlineThickness(2);
      ventana.draw(caja);

        string msg;
        sf::Color col;
if(p.getEstado()== EstadoJuego::GANADOR_X){
     msg="Gana "+p.getJugador1()->getNombre()+"!";
   col=sf::Color(220,60,60);
        }else if(p.getEstado()== EstadoJuego::GANADOR_O){
   msg="Gana "+p.getJugador2()->getNombre()+"!";
    col=sf::Color(60,110,220);
        }else{
            msg="Empate!";
            col=sf::Color::Yellow;
        }

        sf::Text t;
        t.setFont(fuente);
        t.setString(msg);
        t.setCharacterSize(34);
        t.setFillColor(col);
        sf::FloatRect b=t.getLocalBounds();
t.setOrigin(b.left+b.width/2,b.top+b.height/2);
    t.setPosition(W/2,H/2-40);
        ventana.draw(t);

    dibujarBoton({W/2-185,H/2+20,170,50},"Nueva Ronda");
    dibujarBoton({W/2+15,H/2+20,170,50},"Menu");
    }

   void dibujarMenu(string n1, string n2, int campo, GestorPartidas::DatosGuardados& guardado, string mensajeError){
       float W=ventana.getSize().x;
        float H=ventana.getSize().y;

 sf::RectangleShape fondo(sf::Vector2f(W,H));
    fondo.setFillColor(sf::Color(20,20,40));
        ventana.draw(fondo);

        sf::Text titulo;
        titulo.setFont(fuente);
     titulo.setString("TRES EN RAYA");
       titulo.setCharacterSize(52);
        titulo.setFillColor(sf::Color::White);
   sf::FloatRect b=titulo.getLocalBounds();
  titulo.setOrigin(b.left+b.width/2,b.top+b.height/2);
        titulo.setPosition(W/2,60);
        ventana.draw(titulo);

        float fx=W/2-150;

  dibujarTexto("Jugador 1 (X):",fx,130,18,sf::Color(220,100,100));
 sf::RectangleShape c1(sf::Vector2f(300,44));
        c1.setPosition(fx,155);
        c1.setFillColor(sf::Color(40,40,40));
       if(campo==0){
  c1.setOutlineColor(sf::Color(220,60,60));
        }else{
    c1.setOutlineColor(sf::Color(80,80,80));
     }
   c1.setOutlineThickness(2);
        ventana.draw(c1);
        string cursor1="";
        if(campo==0){
            cursor1="|";
        }
     dibujarTexto(n1+cursor1,fx+8,165,20,sf::Color::White);

       dibujarTexto("Jugador 2 (O):",fx,220,18,sf::Color(100,130,220));
 sf::RectangleShape c2(sf::Vector2f(300,44));
      c2.setPosition(fx,245);
        c2.setFillColor(sf::Color(40,40,40));
        if(campo==1){
   c2.setOutlineColor(sf::Color(60,110,220));
    }else{
    c2.setOutlineColor(sf::Color(80,80,80));
        }
        c2.setOutlineThickness(2);
     ventana.draw(c2);
        string cursor2="";
     if(campo==1){
            cursor2="|";
     }
        dibujarTexto(n2+cursor2,fx+8,255,20,sf::Color::White);

      if(mensajeError.empty()){
 dibujarTexto("Clic para escribir  |  Tab para cambiar  |  Enter para jugar",
     W/2-230,308,13,sf::Color(90,90,90));
        }else{
        dibujarTexto(mensajeError,W/2-180,308,14,sf::Color(220,60,60));
        }

dibujarBoton({W/2-100,330,200,50},"Jugar");

        if(guardado.valido){
   dibujarBoton({W/2-210,395,420,50}, "Cargar: "+guardado.nombre1+" vs "+guardado.nombre2);
        }
 dibujarBoton({W/2-100,465,200,50},"Salir");

  dibujarTexto("[H] Ver estadisticas de jugadores",W/2-130,535,13,sf::Color(90,90,90));
    }
};

#endif

