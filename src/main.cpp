/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "bmp.h"

Bmp *img1;
unsigned char *data;
int bytesLine;
//variavel global para selecao do que sera exibido na canvas.
int opcao  = 50;
int screenWidth = 720, screenHeight = 720; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().


void DesenhaCoseno()
{
   float x=0, y=0, pi=3.14;
   float m = 10.0;
   for(float j=80; j < 680; j+=60){
       CV::color(6);
       CV::translate(10, j); //desenha o objeto a partir da coordenada (200, 200)
       for(float i=0; i < 68; i+=0.001)
       {
           y = cos((2*i + 1)*pi/(2*m))*20;
          CV::point(x, y);
          x+=0.01;
       }
       CV::translate(0, 0);
       m--;
       x=0;
       y=0;
   }
}

void DesenhaImagem(){
    CV::translate(100, 200);
    for(int y=0; y<img1->getHeight(); y++){
        for(int x=0; x<img1->getWidth()*3; x+=3){
            CV::color(data[y*bytesLine+x], data[y*bytesLine+x+1], data[y*bytesLine+x+2]);
            CV::point(x/3,y);
        }
    }
    CV::clear(100,100,100);
}


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
    DesenhaImagem();
    //DesenhaCoseno();
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      opcao = key;
   }

   switch(key)
   {
      case 27:
	     exit(0);
	  break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 ) //clicou
   {
   }

}

int main(void)
{
    img1 = new Bmp(".\\atividades_imagem\\resources\\glider.bmp");
   img1->convertBGRtoRGB();
   data = img1->getImage();
   bytesLine = (3 * (img1->getWidth() + 1) / 4) * 4;

   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
