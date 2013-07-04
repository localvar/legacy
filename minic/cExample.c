/*////////////////////////////////////////////////////////////////
//  This is the equipollent program of the MiniC test program   //
//			that can be compiled using TurboC 2.0				//
//		ZhangBoMin							   2001.5.20		//
////////////////////////////////////////////////////////////////*/

#include<stdio.h>
#include<graphics.h>
#include<math.h>

/*global variables*/
float x=0, y=0;
float pi = 3.15; /*a little larger than pi*/

float xScale=0,yScale=0;
int xOrg=0, yOrg=0;
float rot=0;

/*parameter passing, recursion an 'return'*/
int gcd(int a, int b)
{
	if(b==0)
		return a;
	else
		return gcd(b, a%b);
}

void CalcCoord()
{
	/*local variables*/
	float xt=0, yt=0;
	/*SCALE*/
	x *= xScale;
	y *= yScale;
	/*ROT*/
    xt = x, yt = y;
	x = xt * cos(rot) - yt * sin(rot);
	y = yt * cos(rot) + xt * sin(rot);
	/*ORIGIN*/
	x += xOrg;
	y += yOrg;
	y = 480.0 - y;
}

void main()
{
	float i=0;
	int year ,j;
	int a,b;
	int sum;
	/*求两个数的最大公约数*/
	scanf("%d",&a);
	scanf("%d",&b);
	/*/test of function call*/
	printf("%d ",gcd(a,b));
	getch();
/*
	//无实际意义,测试各种情况下的变量定义的合法性
	int mmm;
	{int mmm;}
	if(pi==3.15) int mmm;
	if(pi==3.15) int mmm; else int mmm = 3;
	for(a=0; a<10; a++)	int mmm;
	while(0) int mmm;
	do int mmm; while(0);
	//statements which have no use but legal
*/
	;
	a;
	2343;
	(((b)));
	{}
	{b;}
	/*/statements which may cause errors*/
	for(;0;);
	for(a=0; a<10; a++);
	while(0);
	do ; while(0);

	a=VGA,b=VGAHI;
	/*/绘图,绘制辅导教材中logo程序的示例图形*/
	initgraph(&a,&b,"");

	xOrg = 160 + 60;
	yOrg = 240;
	rot = 0;
	xScale = 80;
	yScale = 80;

	i = -pi;

	x = cos(i);
	y = sin(i);
	CalcCoord();
	moveto(x,y);

	/*/for-loop without the first expression*/
	for(; i<=pi+pi/50; i+=pi/50)
	{
		x = cos(i);
		y = sin(i);
		CalcCoord();
		lineto(x,y);
	}

	i = 0;
	x = (1-1/(10.0/7))*cos(i) + 1/(10.0/7)*cos(-i*((10.0/7)-1));
	y = (1-1/(10.0/7))*sin(i) + 1/(10.0/7)*sin(-i*((10.0/7)-1));
	CalcCoord();
	moveto(x,y);
	for(; i<=20*pi; i+=pi/50)
	{
		x = (1-1/(10.0/7))*cos(i) + 1/(10.0/7)*cos(-i*((10.0/7)-1));
		y = (1-1/(10.0/7))*sin(i) + 1/(10.0/7)*sin(-i*((10.0/7)-1));
		CalcCoord();
		lineto(x,y);
	}

	xOrg = 480-60,	yOrg = 240;
	xScale = 80,	yScale = 80/3;

	j = 0;
	/*/a nest of while-loop and for-loop*/
	while(j<3)
	{
		/*/nest of if-else staments and 'if' without 'else'*/
		if(j==0)
			rot = pi/2 + 0*pi/3;
		else if(j==1)
			rot = pi/2 + 2*pi/3;
		else if(j==2)
			rot = pi/2 - 2*pi/3;
		j++;
		setcolor(j*3+1);
		i = -pi;
		x = cos(i);
		y = sin(i);
		CalcCoord();
		moveto(x,y);
		/*/for-loops without the first and third expression
		//since there's no "break" and "goto" statement in this
		//language, a for-loop without the second expression
		//will be a dead-loop, it cannot be tested here*/
		for(; i<=pi+pi/50;)
		{
			x = cos(i);
			y = sin(i);
			CalcCoord();
			lineto(x,y);
			i+=pi/50;
		}
	}

	getch();
	closegraph();

	/*/print the multiplication table, test of nested for-loops
	//here's two for-loops with all the three expressions*/
	for(j=1; j<=9; j++)
	{
		int k;
		for(k=1; k<=9; k++)
			printf("%d*%d=%2d ",j, k, j*k);
		printf("\n");
	}

	/*/do-while-loop
	//get the sum of the numbers between 1 and 100*/
	j = 0;
	sum = 0;
	do{
		j++;
		sum += j;
	}while(j<100);
	printf("%d ",sum);

	/*/print the leap years between 2000 and 2100
	//quite a complex condition justice*/
	printf("\n");
	for(year=2000; year<=2100; year++)
		if((year%4==0 && year%100!=0) || (year%400==0))
			printf("%d ",year);
}
