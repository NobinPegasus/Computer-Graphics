#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

struct PT
{
    double xxi, yyi;
    PT(){}
    PT(double aai, double bbi)
    {
        xxi = aai;
        yyi = bbi;
    }
};

const int WINDOW_W = 800, WINDOW_H = 600;

void drawAxis()
{
    for(int i=0; i<WINDOW_H; i++) putpixel(WINDOW_W/2, i, WHITE);
    for(int i=0; i<WINDOW_W; i++) putpixel(i, WINDOW_H/2, WHITE);
}

PT convertPixel(PT p)
{
    p.xxi += WINDOW_W/2;
    p.yyi = -p.yyi;
    p.yyi += WINDOW_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    delay(0.1);
    p = convertPixel(p);
    putpixel((int)(p.xxi+0.5), (int)(p.yyi+0.5), color);
}

void drawLine(PT aai, PT bbi,int color)
{


    

    if(aai.yyi == bbi.yyi)
    {
        if(aai.xxi > bbi.xxi) swap(aai, bbi);
        for(int xxi = aai.xxi; xxi <= bbi.xxi; xxi++)
        {
            drawPixel(PT(xxi, aai.yyi), color);
        }
    }

  

    else if(aai.xxi == bbi.xxi)
    {
        if(aai.yyi > bbi.yyi) swap(aai, bbi);
        for(int yyi = aai.yyi; yyi <= bbi.yyi; yyi++)
        {
            drawPixel(PT(aai.xxi, yyi), color);
        }
    }

    else
    {
       double m=(bbi.yyi-aai.yyi)/(bbi.xxi-aai.xxi);
       double m_inv=1.0/m;
       if(fabs(m)<=1.0)
       {
           if(aai.xxi>bbi.xxi) swap(aai,bbi);
           while(aai.xxi<=bbi.xxi)
           {
               drawPixel(aai,color);
               aai.xxi+=1;
               aai.yyi+=m;
           }
       }
       else{
             if(aai.yyi>bbi.yyi) swap(aai,bbi);
             while(aai.yyi<=bbi.yyi)
             {
                 drawPixel(aai,color);
                 aai.xxi+=m_inv;
                 aai.yyi+=1;
             }
       }
    }
}

void DrawPolygon(vector<PT> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],YELLOW);
    }
}
void drawPolygon(vector<PT> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        int colr;
        if(i%3==0)
        {
            colr=GREEN;
        }
        else if(i%3==1)
        {
            colr=BLUE;
        }
        else{
            colr=YELLOW;
        }
        drawLine(points[i], points[(i+1)%n],colr);
    }
}

void BoundaryFill(PT currPixel, int boundaryColor, int fillColor)
{
    PT pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.xxi, pixel.yyi);
    if(currColor == boundaryColor || currColor == fillColor)
    {
        return;
    }

    drawPixel(currPixel, fillColor);

    BoundaryFill(PT(currPixel.xxi, currPixel.yyi+1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.xxi, currPixel.yyi-1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.xxi+1, currPixel.yyi), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.xxi-1, currPixel.yyi), boundaryColor, fillColor);
}
void Floodfill(PT currPixel, int boundaryColor, int fillColor,int oldcolor)
{
    PT pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.xxi, pixel.yyi);
    if(currColor!=oldcolor)
    {
        return;
    }

    drawPixel(currPixel, fillColor);

    Floodfill(PT(currPixel.xxi, currPixel.yyi+1), boundaryColor, fillColor,oldcolor);
    Floodfill(PT(currPixel.xxi, currPixel.yyi-1), boundaryColor, fillColor,oldcolor);
    Floodfill(PT(currPixel.xxi+1, currPixel.yyi), boundaryColor, fillColor,oldcolor);
    Floodfill(PT(currPixel.xxi-1, currPixel.yyi), boundaryColor, fillColor,oldcolor);
}


int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    

    vector<PT> poly;
    vector<PT>Poly;

    poly.push_back(PT(40, 35));
    poly.push_back(PT(100, 70));
    
    poly.push_back(PT(45, 140));
    poly.push_back(PT(50, 180));

    poly.push_back(PT(-60, 100));
    poly.push_back(PT(-30, -100));

    Poly.push_back(PT(40, 35));
    Poly.push_back(PT(100, 70));

    Poly.push_back(PT(45, 140));
    Poly.push_back(PT(50, 180));

    Poly.push_back(PT(-60, 100));
    Poly.push_back(PT(-30, -100));
    drawPolygon(poly);

    PT pixel = convertPixel(PT(0,0));
    int currColor = getpixel(pixel.xxi, pixel.yyi);
    Floodfill(PT(0, 0), YELLOW, 1,currColor);
    drawAxis();
    DrawPolygon(Poly);
    BoundaryFill(PT(0, 0), YELLOW, 5);
    getch();



    return 0;
}

