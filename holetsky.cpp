#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>

int i = 0, j = 0, vy = 0, p = 0, n = 0, k = 1, r = 0;

float a[20][21], b[20][21], c[20][21], z[90], sum = 0, y[10], x[10], det = 0;

float d[3], det1, det2, det3;

void klava() { 
	std::cout << "ok. Bы Bы6paлu нa6op c kлa-тypы" << std::endl;
	std::cout << "Bвegute nop9gok Baшeu мatpuцы - "; 
	std::cin >> p;
	std::cout << "Ok.";

	for (i = 1; i <= p; i++) {
		for (j = 1; j <= p; j++) {
			std::cout << "Bвegute ["<<i<<"]["<<j<<"] элeмeнt мatpuцы - ";
			std::cin >> a[i][j];
		}
		std::cout << std::endl;
	}
	
	std::cout << "tBвegute ctoл6uk cвo6ogныx члeнoв\n";
	
	for (i = 1; i <= p; i++) { 
		std::cout << "Bвegute ["<<i<<"]["<<(p + 1)<<"] элeмeнt - ";
		std::cin >> a[i][p + 1];
	}
}

void faila() {
	std::cout << "Ok. Bы Bы6paлu 3arpy3ka u3 фauлa. ";
	p = 4;
	n = (p * p) + p;
	std::cout << "Bыnoлняetcя ввоg gанныx u3 фauлa data.txt";
	std::ifstream file1("data.txt");
	if (!file1) {std::cerr << "! ! ! He мory otkpыtb data.txt ! ! !";}

	for (i = 0; i < n; i++) file1 >> z[i];

	for (i = 1; i <= p; i++)
	{ for (j = 1; j <= p + 1; j++)
	{ a[i][j] = z[k]; k++; };};
	std::cout << "\n\t3arpy3ka okoH4eHa yCnEшHO!\n";
}

void vivod(int r)
{ for (i = 1; i <= p; i++) std::cout << "  x("<<i<<") = " << x[i]<<";"; std::cout << '\n';
//сохранение файла
if (r != 1) {std::cout << "\n\tcoxpaнeнue в result.txt";
std::ofstream file2("result.txt");
if (!file2) {std::cerr << "He моry COXPAHITb DAHHыE B result.txt"; return;};
for (i = 1; i <= p; i++) file2 << x[i] << ' ';
std::cout << "\n\tCOXPAHEHIE yCnEшHO 3ABEPшEHO"; };
}

int main()
{ srand(time(nullptr));

for (i = 0; i <= 20; i++)
{ for (j = 0; j <=21; j++)
{ a[i][j] = 0.0; b[i][j] = 0.0; c[i][j] = 0.0;};};
std::cout << "\t\t    The studio \"Ozzy elements\" represents\n";
for (i = 1; i <= 80; i++) std::cout << '-'; 
std::cout << '\n';
std::cout << "\tuHguBugyaлbHoe 3agaHue no Tn. Bepcu9 1.0\n";
for (i = 1; i <= 80; i++) std::cout << '-'; 
std::cout << '\n';
std::cout << "  3AgAHuE: cocTaBлeHue HopMaлbHыx ypaBHeHuu  u\n";
std::cout << "             uX PeшeHue MeTogoM XoлeцKoro\n";
std::cout << "\t\t\t\tprogrammed by Piskunov Sergey, IS - 21\n";
for (i = 1; i <= 80; i++) std::cout << '-';// std::cout << '\n';
std::cout << "\tKak 3agatb MaTpuцy:\n\t\t1 - C KлaBuaTypы;";
std::cout << "\n\t\t2 - Cлy4auHo (He pa6oTaeT);\n\t\t3 - u3 фauлa;\n\t\t4 - Bыxog.\n\t";
povt:  std::cout << "Baш Bы6op - ";
std::cin >> vy;

if ((vy < 1) || (vy > 4)) {std::cout << "\n\tnoBToPuTe "; goto povt;};

if (vy == 1) klava();

if (vy == 2) { std::cout << "    Ok. Bы Bы6PATb HA6OP Cлy4AuHo\n";
std::cout << "\tBвegute nop9gok Baшeu MaTpuцы - "; std::cin >> p;
std::cout << "Ok.";
for (i = 1; i <= p; i++)
{ for (j = 1; j <= p + 1; j++) {
naz:  a[i][j] = (rand() % 5) * pow((-1),rand() % 2);};
if (a[i][i] == 0) goto naz;
};
std::cout << " CлyчauHo 3agaHa Matpuцa. ";
}

if (vy == 3) faila();

if (vy == 4) {std::cout << "эto HekpopektHыu Bыxog"; r = 1;};

//суммирование матрицы
for (i = 1; i <=p; i++)
{ for (j = 1; j <= p + 1; j++)
{ a[i][p+2] = a[i][p+2] + a[i][j];};
};
//вывод матрицы на экран
if (r != 1) {std::cout << "\tBot BвegeHa9 Matpuцa:\n";};
for (i = 1; i <= p; i++)
{ std::cout << '\t';
for (j = 1; j <= p + 2; j++)
{ if (a[i][j] >= 0) std::cout << " ";
if (a[i][j] > 9) std::cout << " ";
std::cout << a[i][j] << " ";};
std::cout << '\n'; };
std::cout << '\n';

if (p == 4) {
for (i = 1; i <= p; i++) b[i][1] = a[i][1];
for (i = 1; i <= p + 2; i++) c[1][i] = a[1][i] / b[1][1];

b[2][2] = a[2][2] - b[2][1] * c[1][2];
b[3][2] = a[3][2] - b[3][1] * c[1][2];
b[4][2] = a[4][2] - b[4][1] * c[1][2];

c[2][3] = (1/b[2][2])*(a[2][3] - b[2][1]*c[1][3]);
c[2][4] = (1/b[2][2])*(a[2][4] - b[2][1]*c[1][4]);
c[2][5] = (1/b[2][2])*(a[2][5] - b[2][1]*c[1][5]);
c[2][6] = (1/b[2][2])*(a[2][6] - b[2][1]*c[1][6]);

b[3][3] = a[3][3] - (b[3][1] * c[1][3] + b[3][2] * c[2][3]);
b[4][3] = a[4][3] - (b[4][1] * c[1][3] + b[4][2] * c[2][3]);

c[3][4] = (1/b[3][3])*(a[3][4] - (b[3][1]*c[1][4] + b[3][2]*c[2][4]));
c[3][5] = (1/b[3][3])*(a[3][5] - (b[3][1]*c[1][5] + b[3][2]*c[2][5]));
c[3][6] = (1/b[3][3])*(a[3][6] - (b[3][1]*c[1][6] + b[3][2]*c[2][6]));

b[4][4] = a[4][4] - (b[4][1] * c[1][4] + b[4][2] * c[2][4] + b[4][3] * c[3][4]);

c[4][5] = (1/b[4][4])*(a[4][5] - (b[4][1]*c[1][5] + b[4][2]*c[2][5] + b[4][3]*c[3][5]));
c[4][6] = (1/b[4][4])*(a[4][6] - (b[4][1]*c[1][6] + b[4][2]*c[2][6] + b[4][3]*c[3][6]));

y[1] = a[1][5]/b[1][1];

for (i = 2; i <= 4; i++)
{ k = 1;
if (i == 2) sum = b[i][k]*y[k];
if (i == 3) sum = (b[i][k]*y[k] + b[i][k+1]*y[k+1]);
if (i == 4) sum = (b[i][k]*y[k] + b[i][k+1]*y[k+1] + b[i][k+2]*y[k+2]);
y[i] = (1/b[i][i])*(a[i][5] - sum);
}
sum = 0;
x[4] = y[4];
x[3] = y[3] - c[3][4]*x[4];
x[2] = y[2] - (c[2][3]*x[3] + c[2][4]*x[4]);
x[1] = y[1] - (c[1][2]*x[2] + c[1][3]*x[3] + c[1][4]*x[4]);

for (i = 1; i <= p; i++)
{ std::cout << '\t';
for (j = 1; j <= p; j++)
{ if (b[i][j] >= 0) std::cout << " ";
std::cout << b[i][j] << " ";};
std::cout << '\n'; };
std::cout << '\n';

for (i = 1; i <= p; i++)
{ std::cout << '\t';
for (j = 1; j <= p + 2; j++)
{ if (c[i][j] >= 0) std::cout << " ";
std::cout << c[i][j] << " ";};
std::cout << '\n'; };
std::cout << '\n';
}

if (p == 4) {
for (i = 1; i <= p; i++) 
std::cout << "  y(" << i << ") = " << y[i] << ";";
std::cout << '\n';
}

if (p == 3) {
det = (a[1][1]*a[2][2]*a[3][3])+(a[1][2]*a[2][3]*a[3][1])+(a[2][1]*a[3][2]*a[1][3])-(a[1][3]*a[2][2]*a[3][1])-(a[1][1]*a[2][3]*a[3][2])-(a[3][3]*a[2][1]*a[1][2]);
if (det == 0) {std::cout << "\nHE PEшAEMO!"; goto con;};

d[1] = a[1][1]; d[2] = a[2][1]; d[3] = a[3][1];
a[1][1] = a[1][p + 1]; a[2][1] = a[2][p + 1]; a[3][1] = a[3][p + 1];
det1 = (a[1][1]*a[2][2]*a[3][3])+(a[1][2]*a[2][3]*a[3][1])+(a[2][1]*a[3][2]*a[1][3])-(a[1][3]*a[2][2]*a[3][1])-(a[1][1]*a[2][3]*a[3][2])-(a[3][3]*a[2][1]*a[1][2]);
a[1][1] = d[1]; a[2][1] = d[2]; a[3][1] = d[3];

d[1] = a[1][2]; d[2] = a[2][2]; d[3] = a[3][2];
a[1][2] = a[1][p + 1]; a[2][2] = a[2][p + 1]; a[3][2] = a[3][p + 1];
det2 = (a[1][1]*a[2][2]*a[3][3])+(a[1][2]*a[2][3]*a[3][1])+(a[2][1]*a[3][2]*a[1][3])-(a[1][3]*a[2][2]*a[3][1])-(a[1][1]*a[2][3]*a[3][2])-(a[3][3]*a[2][1]*a[1][2]);
a[1][2] = d[1]; a[2][2] = d[2]; a[3][2] = d[3];

d[1] = a[1][3]; d[2] = a[2][3]; d[3] = a[3][3];
a[1][3] = a[1][p + 1]; a[2][3] = a[2][p + 1]; a[3][3] = a[3][p + 1];
det3 = (a[1][1]*a[2][2]*a[3][3])+(a[1][2]*a[2][3]*a[3][1])+(a[2][1]*a[3][2]*a[1][3])-(a[1][3]*a[2][2]*a[3][1])-(a[1][1]*a[2][3]*a[3][2])-(a[3][3]*a[2][1]*a[1][2]);
a[1][3] = d[1]; a[2][3] = d[2]; a[3][3] = d[3];

x[1] = det1/det;  x[2] = det2/det;  x[3] = det3/det;
con:;
}
vivod(r);
return 0;
}
