/*
	Linguagens e Ambientes de Programação - Projeto de 2020/2021

	Imageomatic module body

largura maxima = 100 colunas
tab = 4 espaços
0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789

	Este ficheiro constitui apenas um ponto de partida para o
	seu trabalho. Todo este ficheiro pode e deve ser alterado
	à vontade, a começar por este comentário.


 IDENTIFICAÇÃO DOS AUTORES -
	Aluno 1: 57796, Afonso Batista
	Aluno 2: 57994, Joao Jorge

Comentarios:

?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????

*/

#include "Imageomatic.h"



/*** TYPE Int2 ***/

/* More Int2 functions, in case you need them */




/*** TYPE Pixel ***/

/* More Pixel functions, in case you need them */




/*** TYPE Image ***/

void initialization(void)
{
	// This function is automatically called when the interpreter starts.
	// If you need to perform some initialization, this is the place
	// to write the initialization code.
}

Int2 imageCopy(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y] = img[i.x][i.y];
		}
	return i;
}

Int2 imagePaint(String cor, Int2 n, Image res)
{	
	#define MAX_LINE   1024
	typedef char Line[MAX_LINE];
	FILE *fp = fopen(colorsFileName, "r");
	Line s;
	int total_read;
	Pixel p = pixel(0,0,0);

	char rgb[6], name[30];
	char red[3], blue[3], green[3];

	 while( fgets(s, MAX_LINE, fp) != NULL ){
		 sscanf(s,"%s %s", rgb, name);
		 if(!strcmp(name, cor)){
			memset(red, '\0', sizeof(red));
			strncpy(red, rgb, 2);
			memset(blue, '\0', sizeof(blue));
			strncpy(blue, rgb+2, 2);
			memset(green, '\0', sizeof(green));
			strncpy(green, rgb+4, 2);

			p = pixel(strtol(red,NULL, 16),strtol(blue,NULL, 16),strtol(green,NULL, 16));
		 }
	 }

	 Int2 i;

	 for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y] = p;
		}

	return i;
}

Int2 imageNegative(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y].blue = MAX_COLOR - img[i.x][i.y].blue;
			res[i.x][i.y].red = MAX_COLOR - img[i.x][i.y].red;
			res[i.x][i.y].green = MAX_COLOR - img[i.x][i.y].green;
		}

	return i;
}

Int2 imageDroplet(Int2 n, Image res)
{
		Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y] = pixelGray(0.7 * MAX_COLOR + 0.3 * sin(int2Distance(int2Half(n), i) / 20.0) * MAX_COLOR);
		}

	return i;
}

Int2 imageMask(Image img1, Int2 n1, Image img2, Int2 n2, Image res) // pre: int2Equals(n1, n2)
{
	return int2Error;
}

Int2 imageGrayscale(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y] = pixelGray(pixelGrayAverage(img[i.x][i.y]));
		}

	return i;
}

Int2 imageBlur(Image img, Int2 n, int nivel, Image res)
{
	return int2Error;
}

Int2 imageRotation90(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y] = img[n.x - i.y][n.y - i.x];
		}

	return i;
}

Int2 imagePosterize(Image img, Int2 n, int factor, Image res)
{	
	int nColors;
	if( factor != 0) {
		nColors = pow(2, factor);
	} else nColors = 0;

	int diff = MAX_COLOR/nColors;

	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			res[i.x][i.y] = pixel((img[i.x][i.y].red/diff)*diff, (img[i.x][i.y].green/diff)*diff,(img[i.x][i.y].blue/diff)*diff);
		}

	return i;
}

Int2 imageHalf(Image img, Int2 n, Image res)
{
	Int2 i;

	for(i.y = 0; i.y < n.y/2; i.y++)
		for(i.x = 0; i.x < n.x/2; i.x++) {
			res[i.x][i.y] = img[i.x*2][i.y*2];
		}
	
	return i;
}

Int2 imageFunctionPlotting(DoubleFun fun, int scale, Int2 n, Image res)
{
	return int2Error;
}

Int2 imageOrderedDithering(Image img, Int2 n, Image res)
{
	#define INDEX_SIDE  8
	Byte indexMatrix[INDEX_SIDE][INDEX_SIDE] = {
					{ 0, 32,  8, 40,  2, 34, 10, 42}, 
					{48, 16, 56, 24, 50, 18, 58, 26},
					{12, 44,  4, 36, 14, 46,  6, 28},
					{60, 28, 52, 20, 62, 30, 54, 22},
					{ 3, 35, 11, 43,  1, 33,  9, 41},
					{51, 19, 59, 27, 49, 17, 57, 25},
					{15, 47,  7, 39, 13, 45,  5, 37},
					{63, 31, 55, 23, 61, 29, 53, 21}
			};
	return int2Error;
}

Int2 imageSteganography(Image img, Int2 n, String s, Image res)
{
	return int2Error;
}


void imageTests(void)
{
	static Image img, img2, res;
	Int2 n;

	// Q
	n = imageLoad("img/frutos.png", img);
	n = imageGrayscale(img, n, res);
	imageStore("img/cinzento.png", res, n);

	// N
	n = imageLoad("img/frutos.png", img);
	n = imageNegative(img, n, res);
	imageStore("img/negativo.png", res, n);	

	// H
	n = imageLoad("img/frutos.png", img);
	n = imageHalf(img, n, res);
	imageStore("img/metade.png", res, n);

	// P
	n = int2(512, 512);
	n = imagePaint("green", n, res);
	imageStore("img/pintar.png", res, n);

	// R
	n = imageLoad("img/frutos.png", img);
	n = imageRotation90(img, n, res);
	imageStore("img/rotacao_90.png", res, n);

	// O
	n = imageLoad("img/frutos.png", img);
	n = imagePosterize(img, n, 3, res);
	imageStore("img/poster.png", res, n);

	// G
	n = int2(512, 512);
	n = imageDroplet(n, res);
	imageStore("img/goticula.png", res, n);

	// D
	n = imageLoad("img/frutos.png", img);
	n = imageBlur(img, n, 5, res);
	imageStore("img/desfocado.png", res, n);

	// M
	n = imageLoad("img/frutos.png", img);
	n = imageDroplet(n, img2);
	n = imageMask(img, n, img2, n, res);
	imageStore("img/mascarar.png", res, n);

	// F
	n = int2(512, 512);
	n = imageFunctionPlotting(sin, 50, n, res);
	imageStore("img/funcao.png", res, n);

	// T
	n = imageLoad("img/frutos.png", img);
	n = imageOrderedDithering(img, n, res);
	imageStore("img/matizacao.png", res, n);

	// E
	n = imageLoad("img/frutos.png", img);
	n = imageSteganography(img, n, "atacamos ao amanhecer", res);
	imageStore("img/esteganografia.png", res, n);
}

