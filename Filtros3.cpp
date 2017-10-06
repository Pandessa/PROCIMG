#include "pixelLab.h"
#include "GL/glut.h"
#include <stdlib.h>

int media[3][3] = {{1, 1, 1},
                   {1, 1, 1},
                   {1, 1, 1}};

int gauss[3][3] = {{1, 2, 1},
                   {2, 4, 2},
                   {1, 2, 1}};

int sobelH[3][3] = {{-1,-2,-1},
                    { 0, 0, 0},
                    { 1, 2, 1}};

int sobelV[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

int prewitH[3][3] = {{-1,-1,-1},
                    {  0, 0, 0},
                    {  1, 1, 1}};

int prewitV[3][3] = {{-1, 0, 1},
                     {-1, 0, 1},
                     {-1, 0, 1}};

// Image Object
PixelLab *img           = NULL;
PixelLab *imgResultado = NULL;

void idle()
{
   glutPostRedisplay();
}

static void display(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   imgResultado->ViewImage();
   glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
        break;
    }
    glutPostRedisplay();
}

void filtroMedia()
{
   pixel **m;
   pixel **resultado;

    // Cria imagem com as dimensões definidas
   imgResultado->CreateImage(img->GetWidth(), img->GetHeight(), 3);

   // Alloca Matrizes
   img->AllocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->AllocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth());

   // Pega dados da imagem
   img->GetDataAsMatrix(m);
   //imgResultado->GetDataAsMatrix(resultado);

   if(img)
   {
        int r = 0;
        int g = 0;
        int b = 0;

      for(int y = 0; y < img->GetHeight(); y++)
      {
         for(int x = 0; x < img->GetWidth(); x++)
         {
            r = 0;
            g = 0;
            b = 0;

            if(x > 0 && x < img->GetWidth()-1)
            {
                if(y > 0 && y < img->GetHeight()-1)
                {
                    r += m[y-1][x-1].R  * media[0][0];
                    g += m[y-1][x-1].G  * media[0][0];
                    b += m[y-1][x-1].B  * media[0][0];

                    r += m[y-1][x].R    * media[0][1];
                    g += m[y-1][x].G    * media[0][1];
                    b += m[y-1][x].B    * media[0][1];

                    r += m[y-1][x+1].R  * media[0][2];
                    g += m[y-1][x+1].G  * media[0][2];
                    b += m[y-1][x+1].B  * media[0][2];

                    r += m[y][x-1].R    * media[1][0];
                    g += m[y][x-1].G    * media[1][0];
                    b += m[y][x-1].B    * media[1][0];

                    r += m[y][x].R      * media[1][1];
                    g += m[y][x].G      * media[1][1];
                    b += m[y][x].B      * media[1][1];

                    r += m[y][x+1].R    * media[1][2];
                    g += m[y][x+1].G    * media[1][2];
                    b += m[y][x+1].B    * media[1][2];

                    r += m[y+1][x-1].R  * media[2][0];
                    g += m[y+1][x-1].G  * media[2][0];
                    b += m[y+1][x-1].B  * media[2][0];

                    r += m[y+1][x].R    * media[2][1];
                    g += m[y+1][x].G    * media[2][1];
                    b += m[y+1][x].B    * media[2][1];

                    r += m[y+1][x+1].R  * media[2][2];
                    g += m[y+1][x+1].G  * media[2][2];
                    b += m[y+1][x+1].B  * media[2][2];
                }
            }

            r = r/9;
            g = g/9;
            b = b/9;

            resultado[y][x].R = r;
            resultado[y][x].G = g;
            resultado[y][x].B = b;
         }
   }
}
   // Atualiza objeto PixelLab
   // img->SetDataAsMatrix(m);
   imgResultado->SetDataAsMatrix(resultado);


   // Desaloca Matriz
   //img->DeallocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->DeallocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth() );

   // Salva imagem alterada
   imgResultado->Save("../figs/womanF.png");
}

void filtroGauss()
{
   pixel **m;
   pixel **resultado;

    // Cria imagem com as dimensões definidas
   imgResultado->CreateImage(img->GetWidth(), img->GetHeight(), 3);

   // Alloca Matrizes
   img->AllocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->AllocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth());

   // Pega dados da imagem
   img->GetDataAsMatrix(m);
   //imgResultado->GetDataAsMatrix(resultado);

   if(img)
   {
        int r = 0;
        int g = 0;
        int b = 0;

      for(int y = 0; y < img->GetHeight(); y++)
      {
         for(int x = 0; x < img->GetWidth(); x++)
         {
            r = 0;
            g = 0;
            b = 0;

            if(x > 0 && x < img->GetWidth()-1)
            {
                if(y > 0 && y < img->GetHeight()-1)
                {
                    r += m[y-1][x-1].R  * gauss[0][0];
                    g += m[y-1][x-1].G  * gauss[0][0];
                    b += m[y-1][x-1].B  * gauss[0][0];

                    r += m[y-1][x].R    * gauss[0][1];
                    g += m[y-1][x].G    * gauss[0][1];
                    b += m[y-1][x].B    * gauss[0][1];

                    r += m[y-1][x+1].R  * gauss[0][2];
                    g += m[y-1][x+1].G  * gauss[0][2];
                    b += m[y-1][x+1].B  * gauss[0][2];

                    r += m[y][x-1].R    * gauss[1][0];
                    g += m[y][x-1].G    * gauss[1][0];
                    b += m[y][x-1].B    * gauss[1][0];

                    r += m[y][x].R      * gauss[1][1];
                    g += m[y][x].G      * gauss[1][1];
                    b += m[y][x].B      * gauss[1][1];

                    r += m[y][x+1].R    * gauss[1][2];
                    g += m[y][x+1].G    * gauss[1][2];
                    b += m[y][x+1].B    * gauss[1][2];

                    r += m[y+1][x-1].R  * gauss[2][0];
                    g += m[y+1][x-1].G  * gauss[2][0];
                    b += m[y+1][x-1].B  * gauss[2][0];

                    r += m[y+1][x].R    * gauss[2][1];
                    g += m[y+1][x].G    * gauss[2][1];
                    b += m[y+1][x].B    * gauss[2][1];

                    r += m[y+1][x+1].R  * gauss[2][2];
                    g += m[y+1][x+1].G  * gauss[2][2];
                    b += m[y+1][x+1].B  * gauss[2][2];
                }
            }

            r = r/16;
            g = g/16;
            b = b/16;

            resultado[y][x].R = r;
            resultado[y][x].G = g;
            resultado[y][x].B = b;
         }
   }
}
   // Atualiza objeto PixelLab
   // img->SetDataAsMatrix(m);
   imgResultado->SetDataAsMatrix(resultado);


   // Desaloca Matriz
   //img->DeallocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->DeallocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth() );

   // Salva imagem alterada
   imgResultado->Save("../figs/womanG.png");
}

void filtroSobel(int escolha)
{
   pixel **m;
   pixel **resultado;

    // Cria imagem com as dimensões definidas
   imgResultado->CreateImage(img->GetWidth(), img->GetHeight(), 3);

   // Alloca Matrizes
   img->AllocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->AllocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth());

   // Pega dados da imagem
   img->GetDataAsMatrix(m);
   //imgResultado->GetDataAsMatrix(resultado);

   if(img && escolha == 1)
   {
        int r = 0;
        int g = 0;
        int b = 0;

      for(int y = 0; y < img->GetHeight(); y++)
      {
         for(int x = 0; x < img->GetWidth(); x++)
         {
            r = 0;
            g = 0;
            b = 0;

            if(x > 0 && x < img->GetWidth()-1)
            {
                if(y > 0 && y < img->GetHeight()-1)
                {
                    r += m[y-1][x-1].R  * sobelH[0][0];
                    g += m[y-1][x-1].G  * sobelH[0][0];
                    b += m[y-1][x-1].B  * sobelH[0][0];

                    r += m[y-1][x].R    * sobelH[0][1];
                    g += m[y-1][x].G    * sobelH[0][1];
                    b += m[y-1][x].B    * sobelH[0][1];

                    r += m[y-1][x+1].R  * sobelH[0][2];
                    g += m[y-1][x+1].G  * sobelH[0][2];
                    b += m[y-1][x+1].B  * sobelH[0][2];

                    r += m[y][x-1].R    * sobelH[1][0];
                    g += m[y][x-1].G    * sobelH[1][0];
                    b += m[y][x-1].B    * sobelH[1][0];

                    r += m[y][x].R      * sobelH[1][1];
                    g += m[y][x].G      * sobelH[1][1];
                    b += m[y][x].B      * sobelH[1][1];

                    r += m[y][x+1].R    * sobelH[1][2];
                    g += m[y][x+1].G    * sobelH[1][2];
                    b += m[y][x+1].B    * sobelH[1][2];

                    r += m[y+1][x-1].R  * sobelH[2][0];
                    g += m[y+1][x-1].G  * sobelH[2][0];
                    b += m[y+1][x-1].B  * sobelH[2][0];

                    r += m[y+1][x].R    * sobelH[2][1];
                    g += m[y+1][x].G    * sobelH[2][1];
                    b += m[y+1][x].B    * sobelH[2][1];

                    r += m[y+1][x+1].R  * sobelH[2][2];
                    g += m[y+1][x+1].G  * sobelH[2][2];
                    b += m[y+1][x+1].B  * sobelH[2][2];
                }
            }

            //r = r/16;
            //g = g/16;
            //b = b/16;

            resultado[y][x].R = r;
            resultado[y][x].G = g;
            resultado[y][x].B = b;
         }
   }
}

  else if(img && escolha == 2)
  {
     int r = 0;
     int g = 0;
     int b = 0;

      for(int y = 0; y < img->GetHeight(); y++)
      {
         for(int x = 0; x < img->GetWidth(); x++)
         {
            r = 0;
            g = 0;
            b = 0;

            if(x > 0 && x < img->GetWidth()-1)
            {
                if(y > 0 && y < img->GetHeight()-1)
                {
                    r += m[y-1][x-1].R  * sobelV[0][0];
                    g += m[y-1][x-1].G  * sobelV[0][0];
                    b += m[y-1][x-1].B  * sobelV[0][0];

                    r += m[y-1][x].R    * sobelV[0][1];
                    g += m[y-1][x].G    * sobelV[0][1];
                    b += m[y-1][x].B    * sobelV[0][1];

                    r += m[y-1][x+1].R  * sobelV[0][2];
                    g += m[y-1][x+1].G  * sobelV[0][2];
                    b += m[y-1][x+1].B  * sobelV[0][2];

                    r += m[y][x-1].R    * sobelV[1][0];
                    g += m[y][x-1].G    * sobelV[1][0];
                    b += m[y][x-1].B    * sobelV[1][0];

                    r += m[y][x].R      * sobelV[1][1];
                    g += m[y][x].G      * sobelV[1][1];
                    b += m[y][x].B      * sobelV[1][1];

                    r += m[y][x+1].R    * sobelV[1][2];
                    g += m[y][x+1].G    * sobelV[1][2];
                    b += m[y][x+1].B    * sobelV[1][2];

                    r += m[y+1][x-1].R  * sobelV[2][0];
                    g += m[y+1][x-1].G  * sobelV[2][0];
                    b += m[y+1][x-1].B  * sobelV[2][0];

                    r += m[y+1][x].R    * sobelV[2][1];
                    g += m[y+1][x].G    * sobelV[2][1];
                    b += m[y+1][x].B    * sobelV[2][1];

                    r += m[y+1][x+1].R  * sobelV[2][2];
                    g += m[y+1][x+1].G  * sobelV[2][2];
                    b += m[y+1][x+1].B  * sobelV[2][2];
                }
            }

            //r = r/16;
            //g = g/16;
            //b = b/16;

            resultado[y][x].R = r;
            resultado[y][x].G = g;
            resultado[y][x].B = b;
         }
   }
}
   // Atualiza objeto PixelLab
   // img->SetDataAsMatrix(m);
   imgResultado->SetDataAsMatrix(resultado);


   // Desaloca Matriz
   //img->DeallocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->DeallocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth() );

   // Salva imagem alterada

   if(escolha == 1)
     imgResultado->Save("../figs/lenaGrayF1.png");
   else if (escolha == 2)
     imgResultado->Save("../figs/lenaGrayF2.png");
}

void filtroPrewit(int escolha)
{
   pixel **m;
   pixel **resultado;

    // Cria imagem com as dimensões definidas
   imgResultado->CreateImage(img->GetWidth(), img->GetHeight(), 3);

   // Alloca Matrizes
   img->AllocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->AllocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth());

   // Pega dados da imagem
   img->GetDataAsMatrix(m);
   //imgResultado->GetDataAsMatrix(resultado);

   if(img && escolha == 1)
   {
        int r = 0;
        int g = 0;
        int b = 0;

      for(int y = 0; y < img->GetHeight(); y++)
      {
         for(int x = 0; x < img->GetWidth(); x++)
         {
            r = 0;
            g = 0;
            b = 0;

            if(x > 0 && x < img->GetWidth()-1)
            {
                if(y > 0 && y < img->GetHeight()-1)
                {
                    r += m[y-1][x-1].R  * prewitH[0][0];
                    g += m[y-1][x-1].G  * prewitH[0][0];
                    b += m[y-1][x-1].B  * prewitH[0][0];

                    r += m[y-1][x].R    * prewitH[0][1];
                    g += m[y-1][x].G    * prewitH[0][1];
                    b += m[y-1][x].B    * prewitH[0][1];

                    r += m[y-1][x+1].R  * prewitH[0][2];
                    g += m[y-1][x+1].G  * prewitH[0][2];
                    b += m[y-1][x+1].B  * prewitH[0][2];

                    r += m[y][x-1].R    * prewitH[1][0];
                    g += m[y][x-1].G    * prewitH[1][0];
                    b += m[y][x-1].B    * prewitH[1][0];

                    r += m[y][x].R      * prewitH[1][1];
                    g += m[y][x].G      * prewitH[1][1];
                    b += m[y][x].B      * prewitH[1][1];

                    r += m[y][x+1].R    * prewitH[1][2];
                    g += m[y][x+1].G    * prewitH[1][2];
                    b += m[y][x+1].B    * prewitH[1][2];

                    r += m[y+1][x-1].R  * prewitH[2][0];
                    g += m[y+1][x-1].G  * prewitH[2][0];
                    b += m[y+1][x-1].B  * prewitH[2][0];

                    r += m[y+1][x].R    * prewitH[2][1];
                    g += m[y+1][x].G    * prewitH[2][1];
                    b += m[y+1][x].B    * prewitH[2][1];

                    r += m[y+1][x+1].R  * prewitH[2][2];
                    g += m[y+1][x+1].G  * prewitH[2][2];
                    b += m[y+1][x+1].B  * prewitH[2][2];
                }
            }

            //r = r/16;
            //g = g/16;
            //b = b/16;

            resultado[y][x].R = r;
            resultado[y][x].G = g;
            resultado[y][x].B = b;
         }
   }
}

  else if(img && escolha == 2)
  {
     int r = 0;
     int g = 0;
     int b = 0;

      for(int y = 0; y < img->GetHeight(); y++)
      {
         for(int x = 0; x < img->GetWidth(); x++)
         {
            r = 0;
            g = 0;
            b = 0;

            if(x > 0 && x < img->GetWidth()-1)
            {
                if(y > 0 && y < img->GetHeight()-1)
                {
                    r += m[y-1][x-1].R  * prewitV[0][0];
                    g += m[y-1][x-1].G  * prewitV[0][0];
                    b += m[y-1][x-1].B  * prewitV[0][0];

                    r += m[y-1][x].R    * prewitV[0][1];
                    g += m[y-1][x].G    * prewitV[0][1];
                    b += m[y-1][x].B    * prewitV[0][1];

                    r += m[y-1][x+1].R  * prewitV[0][2];
                    g += m[y-1][x+1].G  * prewitV[0][2];
                    b += m[y-1][x+1].B  * prewitV[0][2];

                    r += m[y][x-1].R    * prewitV[1][0];
                    g += m[y][x-1].G    * prewitV[1][0];
                    b += m[y][x-1].B    * prewitV[1][0];

                    r += m[y][x].R      * prewitV[1][1];
                    g += m[y][x].G      * prewitV[1][1];
                    b += m[y][x].B      * prewitV[1][1];

                    r += m[y][x+1].R    * prewitV[1][2];
                    g += m[y][x+1].G    * prewitV[1][2];
                    b += m[y][x+1].B    * prewitV[1][2];

                    r += m[y+1][x-1].R  * prewitV[2][0];
                    g += m[y+1][x-1].G  * prewitV[2][0];
                    b += m[y+1][x-1].B  * prewitV[2][0];

                    r += m[y+1][x].R    * prewitV[2][1];
                    g += m[y+1][x].G    * prewitV[2][1];
                    b += m[y+1][x].B    * prewitV[2][1];

                    r += m[y+1][x+1].R  * prewitV[2][2];
                    g += m[y+1][x+1].G  * prewitV[2][2];
                    b += m[y+1][x+1].B  * prewitV[2][2];
                }
            }

            //r = r/16;
            //g = g/16;
            //b = b/16;

            resultado[y][x].R = r;
            resultado[y][x].G = g;
            resultado[y][x].B = b;
         }
   }
}
   // Atualiza objeto PixelLab
   // img->SetDataAsMatrix(m);
   imgResultado->SetDataAsMatrix(resultado);


   // Desaloca Matriz
   //img->DeallocatePixelMatrix(&m, img->GetHeight(), img->GetWidth() );
   imgResultado->DeallocatePixelMatrix(&resultado, img->GetHeight(), img->GetWidth() );

   // Salva imagem alterada

   if(escolha == 1)
     imgResultado->Save("../figs/lenaGrayP1.png");
   else if (escolha == 2)
     imgResultado->Save("../figs/lenaGrayP2.png");
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);

   // Cria imagem do resultado com as mesmas dimensões da imagem original
   img          = new PixelLab();
   imgResultado = new PixelLab();

   img->Read("../figs/lenaGray.png");
   //imgResultado->Read("../figs/lena.png");;

   // Modifica os canais RGB da imagem
   //filtroMedia();
   //filtroGauss();
   //filtroSobel(1);
   //filtroSobel(2);
   filtroPrewit(1);
   filtroPrewit(2);

   glutInitWindowSize(img->GetWidth(),img->GetHeight());
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   glutCreateWindow("Filtros");

   glutKeyboardFunc(key);
   glutIdleFunc( idle);
   glutDisplayFunc(display);

   glutMainLoop();

   return 1;
}

