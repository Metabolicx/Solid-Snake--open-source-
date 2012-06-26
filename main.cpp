#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>
#include <iostream>

int randomNb(int min, int max)
{
    //renvoie min <= n < max

    static bool first = true;
    if ( first ) {
        srand(time(NULL));
         first = false;
    }
    return(int)((max-min)*(rand()/(RAND_MAX+1.0)) + min);
}

#include "bonus.cpp"

#include "snake.cpp"

#include "level.cpp"

#include "game.cpp"

#include "interface.cpp"

int main()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D(-15.5,15.5,-15.5,17.5);

    Interface inf = Interface();

    inf.maine();

    return EXIT_SUCCESS;
}
