#include <stdio.h>        // подключаем заголовочный файл stdio.h

int calcNum(int a,int b,int c)
{
    double f;
    if (a == 10 && b!=c) {
        a = 10;
        calcNum(0, 0, 0);
    }
    else
        a=a*b+c;
    float g;
    return a;
}

/*some comment
dkASF
ds

ljhjuf*/

bool myFunc(doule afg,int b)
{
    /*float oo = 1, pla;*/
    for (; ; ;) { oo++; }
    return oo;
}

double main(){
    /**/
    printf("Hello world! \n");
    int a= 10, b=4, c =-10,d;
    for (int i=0;i<10;i++){
        do {} while (a);
        d=calcNum(a,b,c);
        a++;
        b=a/2;      /*some comment
        blablabla*/
        c--;
        printf("%d\n",d);    }

    return 0;}