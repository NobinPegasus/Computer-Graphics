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
using namespace std;


pair<vector<float>, vector<float>>DDA_line(float xf, float yf, float xl, float yl) {
    vector<float> xxi;
    vector<float> yyi;


   

    del_x = abs(xf - xl);
    del_y = abs(yf - yl);


    if (del_x >= del_y) {


        minima_x = min(xf, xl);
        maxima_x = max(xf, xl);
        minima_y = min(yf, yl);
        cout << "Minima YYYY" << minima_y << endl;
        maxima_y = max(yf, yl);
        //cout << "del_x= " << del_x << " " << "del_y= " << del_y << endl;
        m = (float)del_y / del_x;
        cout << "M = " << m << endl;
        for (int i = 0; minima_x <= maxima_x;i++) {
            xxi.push_back(minima_x);
            minima_x += 1;
            //cout << "Minima_Y " << minima_y << endl;
            yyi.push_back(minima_y);
            minima_y = m + minima_y;
        }
        if ((xf - xl) * (yf - yl) < 0) {
            reverse(xxi.begin(), xxi.end());
        }
    }


    else {

        minima_x = min(xf, xl);
        maxima_x = max(xf, xl);
        minima_y = min(yf, yl);
        maxima_y = max(yf, yl);

        cout << "del_x= " << del_x << " " << "del_y= " << del_y << endl;
        cout << "del_x= " << typeid(del_x).name() << " " << "del_y= " << typeid(del_y).name() << endl;
        m = (float)del_x / del_y;
        cout << "M= " << m << endl;
        for (int i = 0; minima_y <= maxima_y;i++) {
            yyi.push_back(minima_y);
            minima_y += 1;
            // cout << "XF === " << xf << endl;
            xxi.push_back(minima_x);
            minima_x = m + minima_x;

        }
        if ((xf - xl) * (yf - yl) < 0) {
            reverse(yyi.begin(), yyi.end());
        }
    }

    return make_pair(yyi, xxi);
}

pair<vector<float>, vector<float>>bressenham_line(int xf, int yf, int xl, int yl) {

    vector<float> xxi;
    vector<float> yyi;

    

 
                int dx = abs(xl - xf);
                int sx = xf < xl ? 1 : -1;
                int dy = -abs(yl - yf);
                int sy = yf < yl ? 1 : -1;
                int err = dx + dy;  /* error value e_xy */
                while (true) {  /* loop */
                    
                    //cout << "XF === " << xf << " "<< "YF ===== " << yf << endl;
                    xxi.push_back(xf);
                    yyi.push_back(yf);


                    if (xf == xl && yf == yl) break;
                    int e2 = 2 * err;
                    cout << "Errr " << err << " e2  " << e2 << endl;
                    if (e2 >= dy) { /* e_xy+e_x > 0 */
                        err += dy;
                        xf += sx;
                        //cout << "Inside dy " << endl;
                        //cout << "Errr " << err << " e2  " << e2 << " dy  " << dy << " xf " << xf << " sx " << sx << endl;

                    }
                    if (e2 <= dx) { /* e_xy+e_y < 0 */
                        err += dx;
                        yf += sy;
                        //cout << " Inside dx " << endl;
                        //cout << "Errr " << err << " e2  " << e2 << " dx  " << dx << " yf " << yf << " sy " << sy<< endl;

                    }
                    //cout << "XF = ----- " << xf << "  " << "YF = ------ " << yf << endl;
                }
            
                return make_pair(xxi, yyi);
    }




int main(int argc, char* argv[])
{
    

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        int window_height = 620;
        int window_width = 620;
        if (SDL_CreateWindowAndRenderer(window_height, window_width , 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;
                cout << "Enter the first pixel co ordinates\n";
                scanf_s("%f %f", &xf, &yf);
                cout << "Enter the second pixel co ordinates\n";
                scanf_s("%d %d", &xl, &yl);
                

            
                //Initialize DDA
                pair<vector<float>, vector<float>>dda = DDA_line(xf, yf, xl, yl);

              /*  for (auto i = dda.first.begin(); i != dda.first.end(); ++i)
                    cout << "X= " << *i << ' ';

                for (auto i = dda.second.begin(); i != dda.second.end(); ++i)
                    cout << "Y=" << *i << ' ';*/



                //Initialize Bressenham's Line Drawing 
                pair<vector<float>, vector<float>>bressen = bressenham_line(xf, yf, xl, yl);
                
             /*   for (auto i = bressen.first.begin(); i != bressen.first.end(); ++i)
                    cout << "X= " << *i << ' ';

                for (auto i = bressen.second.begin(); i != bressen.second.end(); ++i)
                    cout <<"Y=" << * i << ' ';*/

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                //SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
                //SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
                SDL_RenderDrawLine(renderer, 0, window_width/2, window_height, window_width/2);
                SDL_RenderDrawLine(renderer, window_height/2, 0 , window_height/2, window_width);
                SDL_RenderPresent(renderer);
                
                //bressenham_line(xf, yf, xl, yl);

                //Drawing DDA
              /*  for (int i = 0; i < dda.first.size();i++) {
                    SDL_RenderDrawPoint(renderer, (window_height / 2) + dda.first[i], -dda.second[i] + (window_width / 2));
                    SDL_RenderPresent(renderer);
                }*/

                //Drawing Bressenham's Line Drawing
                for (int i = 0; i < bressen.first.size();i++) {
                    SDL_RenderDrawPoint(renderer, (window_height / 2) + bressen.first[i], -bressen.second[i] + (window_width / 2));
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