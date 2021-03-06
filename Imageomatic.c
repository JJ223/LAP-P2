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
	FILE *file = fopen(colorsFileName, "r");
	Line line;
	Int2 i;
	char *seq;

	char rgb[6], name[30];

	int hex = strtol(cor, &seq, 16);

	if(strlen(seq)!=0)
		while( fgets(line, MAX_LINE, file) != NULL ){
			sscanf(line,"%s %s", rgb, name);
			if(!strcmp(name, cor)) {
				hex = strtol(rgb, NULL, 16);
				break;
			}
		}

	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++)           //Painting
			res[i.x][i.y] = pixel((hex >> 16), ((hex >> 8) & 0x00FF), hex & 0x0000FF);

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
			res[i.x][i.y] = pixelGray(0.7 * MAX_COLOR + 0.3 * 
				sin(int2Distance(int2Half(n), i) / 20.0) * MAX_COLOR);
		}

	return i;
}

Int2 imageMask(Image img1, Int2 n1, Image img2, Int2 n2, Image res) // pre: int2Equals(n1, n2) valor1 * (valor2/256)
{
	Int2 i;

	for(i.y=0; i.y < n1.y; i.y++)
		for(i.x=0; i.x < n1.x; i.x++) {
			res[i.x][i.y].blue = img1[i.x][i.y].blue*((double)img2[i.x][i.y].blue/MAX_COLOR);
			res[i.x][i.y].red = img1[i.x][i.y].red*((double)img2[i.x][i.y].red/MAX_COLOR);
			res[i.x][i.y].green = img1[i.x][i.y].green*((double)img2[i.x][i.y].green/MAX_COLOR);
		}
	return i;
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
	int red, green, blue, counter;
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++){
			red = 0, green = 0, blue = 0, counter = 0;

			for(int j = -nivel; j < nivel+1; j++)
				for(int k = -nivel; k < nivel+1; k++)
					if( n.y > i.y+j && i.y+j >= 0 && n.x > i.x+k && i.x+k >= 0){
						red += img[i.x+k][i.y+j].red;
						green += img[i.x+k][i.y+j].green;
						blue += img[i.x+k][i.y+j].blue;
						counter++;
					}
			
			res[i.x][i.y] = pixel(red/counter, green/counter, blue/counter);
		}

	return i;
}

Int2 imageRotation90(Image img, Int2 n, Image res)
{
	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++)
			res[n.x-1 - i.y][i.x] = img[i.x][i.y];

	return i;
}

Int2 imagePosterize(Image img, Int2 n, int factor, Image res)
{	
	int nColors;
	if( factor != 0) {
		nColors = pow(2, factor);
	} else nColors = 0;

	int mult = 256/nColors;

	Int2 i;
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++)
			res[i.x][i.y] = pixel((img[i.x][i.y].red/mult)*mult,
				(img[i.x][i.y].green/mult)*mult, (img[i.x][i.y].blue/mult)*mult);

	return i;
}

Int2 imageHalf(Image img, Int2 n, Image res)
{
	Int2 i;
	
	for(i.y = 0; i.y < n.y/2; i.y++)
		for(i.x = 0; i.x < n.x/2; i.x++)
			res[i.x][i.y] = img[i.x*2][i.y*2];
	
	return i;
}

Int2 imageFunctionPlotting(DoubleFun fun, int scale, Int2 n, Image res)
{
	Int2 i;
	for(i.x = 0; i.x < n.x; i.x++){
		for(i.y = 0; i.y < n.y; i.y++) {
			if(n.x/2 == i.x || n.y/2 == i.y)
				res[i.x][n.y/2] = pixelGray(0);
			else res[i.x][i.y] = pixelGray(MAX_COLOR);
		}
		double v = fun((double)(i.x-n.x/2)/(double)scale)*scale;
		res[i.x][(int) ((double)n.y/2 - v)] = pixelGray(0);
	}

	return i;
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
	
	Int2 i;
	
	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			double avg = (double) pixelGrayAverage(img[i.x][i.y]);
			double intensity = avg / 4.0;
			if(indexMatrix[i.x%8][i.y%8] < intensity)
				res[i.x][i.y] = pixelGray(MAX_COLOR);
			else
				res[i.x][i.y] = pixelGray(0);
		}
	
	return i;
}

void charToImg(Pixel *pixel, char character) {
	if(character>=0x40 || character<=0x5F) character = character - 0x40;

	pixel->red = (pixel->red & 0xFC) | (character >> 4);		   				   	   /* RED sem os dois ultimos bits e  
																					   juntar com os bits mais significativos do char */


	pixel->green = (pixel->green & 0xFC) | ((character & 0b1100)>>2);	   			   /* GREEN sem os dois ultimos bits
																	   	 			   juntar com os bits do meio do char */


	pixel->blue = (pixel->blue & 0xFC) | (character & 0b11);		  	   			   /* BLUE sem os dois ultimos bits
																		 			   juntar com os bits menos significativos do char */
}

Int2 imageSteganography(Image img, Int2 n, String s, Image res)
{
	#define END_OF_MESSAGE  '\0'

	Int2 i;
	void stringToUpperCase(String s);

	stringToUpperCase(s);

	char *pos = s;
	bool endOfMessage=false;

	for(i.y = 0; i.y < n.y; i.y++)
		for(i.x = 0; i.x < n.x; i.x++) {
			
			res[i.x][i.y] = img[i.x][i.y];

			if(!endOfMessage) {
				if( (*pos < 32 ||  *pos > 95 ||  *pos == 64) && *pos != END_OF_MESSAGE)
			 		*pos = '?';
					 
				charToImg(&(res[i.x][i.y]), *pos);
				
				if(*pos == END_OF_MESSAGE) endOfMessage=true;
				pos++;
			} 
		}

	if(!endOfMessage) charToImg(&(res[n.x-1][n.y-1]), END_OF_MESSAGE);


	return i;
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

