#include "SDL.h"
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "iostream"
#include "vector"
#include <fstream>
#include "string"
#include "cmath"
#include "sstream"
#include "cstdio"
#include <typeinfo>
#include<windows.h>
#include<tuple>




float minima_x;
float maxima_x;

float minima_y;
float maxima_y;
float m;
int del_x;
int del_y;
float xf = 0;
float yf;
int xl;
int yl;
int del;
float c_x; 
float c_y; 
float r;

using namespace std;

vector<float>xxi;
vector<float>yyi;

void midPoint_circle(int x_centre, int y_centre, int r)
{
    int x = r, y = 0;


    xxi.push_back(x + x_centre);
    yyi.push_back(y + y_centre);
    cout << "(" << x + x_centre << ", " << y + y_centre << ") ";

    // When radius is zero only a single
    // point will be printed


    if (r > 0)
    {
        xxi.push_back(x + x_centre);
        yyi.push_back(-y + y_centre);

        xxi.push_back(y + x_centre);
        yyi.push_back(x + y_centre);

        xxi.push_back(-y + x_centre);
        yyi.push_back(x + y_centre);

        cout << "(" << x + x_centre << ", " << -y + y_centre << ") ";
        cout << "(" << y + x_centre << ", " << x + y_centre << ") ";
        cout << "(" << -y + x_centre << ", " << x + y_centre << ")\n";

    }


    int P = 1 - r;
    while (x > y)
    {
        y++;


        if (P <= 0)
            P = P + 2 * y + 1;

        else
        {
            x--;
            P = P + 2 * y - 2 * x + 1;
        }


        if (x < y)
            break;


        cout << "(" << x + x_centre << ", " << y + y_centre << ") ";
        cout << "(" << -x + x_centre << ", " << y + y_centre << ") ";
        cout << "(" << x + x_centre << ", " << -y + y_centre << ") ";
        cout << "(" << -x + x_centre << ", " << -y + y_centre << ")\n";

        // If the generated point is on the line x = y then
        // the perimeter points have already been printed


        xxi.push_back(x + x_centre);
        yyi.push_back(y + y_centre);

        xxi.push_back(-x + x_centre);
        yyi.push_back(y + y_centre);

        xxi.push_back(x + x_centre);
        yyi.push_back(-y + y_centre);

        xxi.push_back(-x + x_centre);
        yyi.push_back(-y + y_centre);


        if (x != y)
        {
            xxi.push_back(y + x_centre);
            yyi.push_back(x + y_centre);

            xxi.push_back(-y + x_centre);
            yyi.push_back(x + y_centre);

            xxi.push_back(y + x_centre);
            yyi.push_back(-x + y_centre);

            xxi.push_back(-y + x_centre);
            yyi.push_back(-x + y_centre);

            cout << "(" << y + x_centre << ", " << x + y_centre << ") ";
            cout << "(" << -y + x_centre << ", " << x + y_centre << ") ";
            cout << "(" << y + x_centre << ", " << -x + y_centre << ") ";
            cout << "(" << -y + x_centre << ", " << -x + y_centre << ")\n";

        }
    }
}




void bressenham_Circle(int x, int y, int xc, int yc)
{
    xxi.push_back(x + xc);
    yyi.push_back(y + yc);

    xxi.push_back(-x + xc);
    yyi.push_back(y + yc);
    
    xxi.push_back(x + xc);
    yyi.push_back(-y + yc);

    xxi.push_back(-x + xc);
    yyi.push_back(-y + yc);

    xxi.push_back(y + xc);
    yyi.push_back(x + yc);

    xxi.push_back(y + xc);
    yyi.push_back(-x + yc);

    xxi.push_back(-y + xc);
    yyi.push_back(x + yc);

    xxi.push_back(-y + xc);
    yyi.push_back(-x + yc);
    
}



int main(int argc, char* argv[])
{


    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        int window_height = 620;
        int window_width = 620;
        int x_center;
        int y_center;
        int r;
        if (SDL_CreateWindowAndRenderer(window_height, window_width, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;
 



                int x;
                int y;
                int P;
                
                cout << "Enter the center co-ordinates\n";
                cin >> x_center >> y_center;
                cout << "Enter the radius of circle\n";
                cin >> r;



                //Bressenham Circle Drawing
                P = 3 - 2 * r;
                x = 0; y = r;
                bressenham_Circle(x, y, x_center, y_center);
                while (x < y)
                {
                    if (P <= 0)
                    {
                        P = P + (4 * x) + 6;
                        bressenham_Circle(++x, y, x_center, y_center);
                    }
                    else
                    {
                        P = P + (4 * (x - y)) + 10;
                        bressenham_Circle(++x, --y, x_center, y_center);
                    }
                }

               


                // Initialize midpoint circle drawing
                //midPoint_circle(x_center, y_center, r);


                  // Show the points of the circle 
                   for (auto i = xxi.begin(); i != xxi.end(); ++i)
                       cout <<"x =    " << * i << ' ';

                   for (auto i = yyi.begin(); i != yyi.end(); ++i)
                       cout << "Y =    " << *i << ' ';


   

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, 0, window_width / 2, window_height, window_width / 2);
                SDL_RenderDrawLine(renderer, window_height / 2, 0, window_height / 2, window_width);
                SDL_RenderPresent(renderer);

          

  

                //Drawing the pixels
                for (int i = 0; i < xxi.size();i++) {
                    SDL_RenderDrawPoint(renderer, (window_height / 2) + xxi[i], -yyi[i] + (window_width / 2));
                    SDL_RenderPresent(renderer);
                }


                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}