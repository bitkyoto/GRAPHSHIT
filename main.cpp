#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include<iostream>
using namespace std;
int ShiftX = 325,ShiftY = 225, ShiftZ = 25; // сдвиг начала координат
void multiplyMatrices(double mat1[][3],  double mat2[3][8], double res[3][8], int row1, int col1, int row2, int col2) {
    double realreal[3][8];
    for(int i=0; i<row1; i++) {
        for(int j=0; j<col2; j++) {
            realreal[i][j] = 0;
            for(int k=0; k<row2; k++) {
                realreal[i][j] += mat1[i][k] * mat2[k][j];
                cout << mat1[i][k] << " * " << mat2[k][j]<< " = " << mat1[i][k] * mat2[k][j] << " |";
            }
            cout << i << " " << j << " ИТОГО В КЛЕТКЕ: " << realreal[i][j] << endl;
        }
    }
    for (size_t i = 0; i < 3; i++)
    {
        for(int j = 0; j<8; j++){
            res[i][j] = realreal[i][j];
        }
    }
    
}
void print(double mat2[3][8]){
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            cout << mat2[i][j] << " ";
        }
        cout << endl;
    }
    cout << "################################################" << endl;
    
}
void getProjection(double matrix[3][8]){
    for(int i = 0;i<8; i++){
        matrix[0][i] += matrix[2][i]/2;
        matrix[1][i] -= matrix[2][i]/2;
    }
}
void drawAxis(){
    int axis[3][4] = {
        {0, 50, 0 , 0  },
        {0, 0 , -50, 0 },
        {0, 0 , 0 , -50 }
    };
    for(int i = 0;i<4; i++){
        axis[0][i] =  axis[0][i]*3 +ShiftX;
        axis[1][i] =  axis[1][i]*3 +ShiftY;
        axis[2][i] =  axis[2][i]*3 +ShiftZ;
        axis[0][i] += axis[2][i]/2;
        axis[1][i] -= axis[2][i]/2;
    }
    setcolor(GREEN);
    line(axis[0][0], axis[1][0], axis[0][1], axis[1][1]);
    setcolor(RED);
    line(axis[0][0], axis[1][0], axis[0][2], axis[1][2]);
    setcolor(BLUE);
    line(axis[0][0], axis[1][0], axis[0][3], axis[1][3]);
    setcolor(WHITE);
}
void draw(int proj[3][8]){
    for(int i = 0; i<4;i++){
        int j = 0;
        if(i<3){
            j = i+1;
        }else{
            j = 0;
        }
        line(proj[0][i], proj[1][i], proj[0][j], proj[1][j]);
    }
    for(int i = 4; i<8;i++){
        int j;
        if(i<7){
            j = i+1;
        }else{
            j = 4;
        }
        line(proj[0][i], proj[1][i], proj[0][j], proj[1][j]);
    }
    for(int i = 0; i<4; i++){
        int j = i+4;
        line(proj[0][i], proj[1][i], proj[0][j], proj[1][j]);
    }
    drawAxis();
    setcolor(WHITE);
};
void Compute(int angle, string axis)
{
    double projectedM [3][8] = {
        {-25,  25,  25, -25, -25,  25, 25,  -25},

        {-25, -25,  25,  25, -25, -25, 25,   25},

        {-25 , -25, -25, -25,  25,  25, 25,   25},
    };
    int projectedToCoords[3][8] = {
        {-25,  25,  25, -25, -25,  25, 25,  -25},

        {-25, -25,  25,  25, -25, -25, 25,   25},

        {-25 , -25, -25, -25,  25,  25, 25,   25},
    };
    double rotationX[3][3] = {
        {1,0,0},
        {0, cos(angle*M_PI/180), sin(angle*M_PI/180)},
        {0, -sin(angle*M_PI/180), cos(angle*M_PI/180)}
    };
    double rotationY[3][3] = {
        {cos(angle*M_PI/180),0,-sin(angle*M_PI/180)},
        {0, 1, 0},
        {sin(angle*M_PI/180), 0, cos(angle*M_PI/180)}
    };
    double rotationZ[3][3] = {
        {cos(angle*M_PI/180),sin(angle*M_PI/180),0},
        {-sin(angle*M_PI/180), cos(angle*M_PI/180),0},
        {0, 0, 1}
    };
    if(axis=="x"){
        multiplyMatrices(rotationX, projectedM, projectedM,3,3,3,8);
    }
    if(axis=="y"){
        multiplyMatrices(rotationY, projectedM, projectedM,3,3,3,8);
    }
    if(axis=="z"){
        multiplyMatrices(rotationZ, projectedM, projectedM,3,3,3,8);
    }
    for(int i = 0; i<8;i++){
        projectedM[0][i] = projectedM[0][i]*3+ShiftX;
        projectedM[1][i] = projectedM[1][i]*3+ShiftY;
        projectedM[2][i] = projectedM[2][i]*3 +ShiftZ;
    }
    getProjection(projectedM);
    print(projectedM);

    for(int i =0; i<3;i++){
        for(int j =0; j<8; j++){
            projectedToCoords[i][j] = projectedM[i][j];
        }
    }
    cleardevice();
    draw(projectedToCoords);
}
int main()
{
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, (char*)"");
    errorcode = graphresult();
    if (errorcode != grOk)
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        return 1;
    }
    setcolor(WHITE);
    setbkcolor(BLACK);
    setwritemode(COPY_PUT);
    Compute(0, "");
    int angle;
    string axis;
    do{
        cout << "Чтобы выйти введите угол 0" <<endl;
        cout << "Введите угол: " <<endl;
        cin >> angle;
        cout << "Введите ось (x,y,z): " << endl;
        cin >> axis;
        if(axis == "x" || axis== "y" || axis== "z") break;
        Compute(angle, axis);
    } while (angle != 0);
    closegraph();
    return 1;

}