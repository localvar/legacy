/////////////////////////////////////////////////
//     This is the test program for MiniC.	   //	
//     ZhangBoMin			    2001.05.20	   //
/////////////////////////////////////////////////

//global variables
float x, y;
float pi = 3.15; //a little larger than pi

float xScale,yScale;
int xOrg, yOrg;
float rot;

//parameter passing, recursion an 'return'
int gcd(int a, int b)
{
	if(b==0)
		return a;
	else
		return gcd(b, a%b);
}

void CalcCoord()
{
	//local variables
	float xt, yt;
	//SCALE
	x *= xScale;
	y *= yScale;
	//ROT
    xt = x, yt = y;
	x = xt * cos(rot) - yt * sin(rot);
	y = yt * cos(rot) + xt * sin(rot);
	//ORIGIN
	x += xOrg;
	y += yOrg;
	y = 480.0 - y;
}	

void main()
{
	//求两个数的最大公约数
	int a,b;
	read(a);
	read(b);
	//test of function call
	write(gcd(a,b));
	read();

	//无实际意义,测试各种情况下的变量定义的合法性
	int mmm;
	{int mmm;}
	if(pi==3.15) int mmm;
	if(pi==3.15) int mmm; else int mmm = 3;
	for(a=0; a<10; a++)	int mmm;
	while(0) int mmm;
	do int mmm; while(0);
	//statements which have no use but legal
	;
	a;
	2343;
	(((b)));
	{}
	{b;}
	//statements which may cause errors
	for(;0;);
	for(a=0; a<10; a++);
	while(0);
	do ; while(0);

	//绘图,绘制辅导教材中logo程序的示例图形
	initgraph();

	xOrg = 160 + 60;
	yOrg = 240;
	rot = 0;
	xScale = 80;
	yScale = 80;

	float i = -pi;

	x = cos(i);
	y = sin(i);
	CalcCoord();
	moveto(x,y);

	//for-loop without the first expression
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

	int j = 0;
	//a nest of while-loop and for-loop
	while(j<3)
	{
		//nest of if-else staments and 'if' without 'else'
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
		//for-loops without the first and third expression
		//since there's no "break" and "goto" statement in this
		//language, a for-loop without the second expression
		//will be a dead-loop, it cannot be tested here
		for(; i<=pi+pi/50;)
		{
			x = cos(i);
			y = sin(i);
			CalcCoord();
			lineto(x,y);
			i+=pi/50;
		}
	}

	read();
	closegraph();

	//print the multiplication table, test of nested for-loops
	//here's two for-loops with all the three expressions
	for(j=1; j<=9; j++)
	{
		int k;
		for(k=1; k<=9; k++)
			write(j, k, j*k);
		write();
	}
	
	//do-while-loop
	//get the sum of the numbers between 1 and 100
	j = 0;
	int sum = 0;
	do{
		j++;
		sum += j;
	}while(j<100);
	write(sum);

	//print the leap years between 2000 and 2100
	//quite a complex condition justice
	int year;
	write();
	for(year=2000; year<=2100; year++)
		if((year%4==0 && year%100!=0) || (year%400==0))
			write(year);
}
