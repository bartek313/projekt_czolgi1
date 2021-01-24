#include "headerFiles/mapGenerator.h"

int dx = 20;			//delty
int dy = 20;

int dimX = 50;			//wymiary macierzy
int dimY = 50;

char infoLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
char exploreLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
char moveLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
char leftLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
char rightLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
char resetLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/";

struct Map mapa;
void zapiszMape()
{
    char data[dimX*dimY + dimX + 1];
    FILE *fPtr;
    fPtr = fopen("map/map.txt", "w");

    if (fPtr == NULL) {
	printf("Nie udalo sie otworzyc pliku.\n");
	exit(EXIT_FAILURE);
    }
    int counter = 0;

    for (int j = 0; j < dimY; j++) {
	for (int i = 0; i < dimX; i++) {
	    if ((int) mapa.fields[i * dimY + j] != 0)
		data[counter] = mapa.fields[i * dimY + j];
	    else
		data[counter] = ' ';
	    counter += 1;
	}
	data[counter] = '\n';
	counter += 1;
    }
    data[counter+1] = '\0';

    fputs(data, fPtr);
    fclose(fPtr);
    printf("Mapa wygenerowana. :) \n");
}

void inicjujMape(char *nazwa)
{
    mapa.name = nazwa;
    mapa.fields = (char *) malloc(dimX * dimY * sizeof(char));
    mapa.currentX = getCurrentX();
    mapa.currentY = getCurrentY();

    strcat(infoLink, nazwa);
    strcat(exploreLink, nazwa);
    strcat(moveLink, nazwa);
    strcat(resetLink, nazwa);

    strcat(leftLink, nazwa);
    strcat(leftLink, "/left");
    strcat(rightLink, nazwa);
    strcat(rightLink, "/right");
}

void updateMap(char *json, int infoRequest)
{
    int prevX = mapa.currentX;
    int prevY = mapa.currentY;

    jsonParserPayload(json);
//aktualizacja mapy

    mapa.currentX = getCurrentX();
    mapa.currentY = getCurrentY();
    mapa.currentField = getFieldType();
    mapa.currentDirection = getDirection();

    if (infoRequest != 1) {
	if (dx < 0) {
	    dimX += dimX;
	    zwiekszRozmiarMapy(dimX, dimY);
	} else if (dx > dimX)	//dodanie kolumny 
	{
	    dimX += dimX;
	    zwiekszRozmiarMapy(dimX, dimY);
	}

	if (dy < 0) {
	    dimY += 1;
	    zwiekszRozmiarMapy(dimX, dimY);
	} else if (dy > dimY)	//dodanie kolumny 
	{
	    dimY += dimY;
	    zwiekszRozmiarMapy(dimX, dimY);
	}


	if (mapa.currentX > prevX)
	    dx += 1;
	else if (mapa.currentX < prevX)
	    dx -= 1;

	if (mapa.currentY > prevY)
	    dy += 1;
	else if (mapa.currentY < prevY)
	    dy -= 1;

    }
    if (mapa.currentX == prevX && mapa.currentY == prevY) {	//napotkano sciane
	if (mapa.currentDirection == 'E')
	    mapa.fields[dimX + (dx + 1) * dimY + dy] = 'w';
	else if (mapa.currentDirection == 'W')
	    mapa.fields[dimX + (dx - 1) * dimY + dy] = 'w';
	else if (mapa.currentDirection == 'N')
	    mapa.fields[dimX + dx * dimY + (dy + 1)] = 'w';
	else if (mapa.currentDirection == 'S')
	    mapa.fields[dimX + dx * dimY + (dy - 1)] = 'w';
    } else
	mapa.fields[dimX + dx * dimY + dy] = mapa.currentField;

}

void wyczyscMape()
{
    free(mapa.fields);
}

void zwiekszRozmiarMapy(int sizeX, int sizeY)
{
    mapa.fields =
	realloc(mapa.fields,
		(sizeX + sizeX) * (sizeY + sizeY) * sizeof(char));

    dimX = sizeX + sizeX;
    dimY = sizeY + sizeY;

    dx += sizeX;
    dy += sizeY;
}

void wypiszMape()
{
    FILE *filePointer;

    filePointer = fopen("map/map.txt", "r");

    printf("DANE MAPY:\n");
    printf("name: %s\n", mapa.name);
    printf("aktualna pozycja x: %d\n", mapa.currentX);
    printf("aktualna pozycja y: %d\n", mapa.currentY);
    printf("typ pola: %c\n", mapa.currentField);
    printf("Aktualny kierunek: %c\n", mapa.currentDirection);

    for (int j = 0; j < dimY; j++) {
	for (int i = 0; i < dimX; i++) {
	    if ((int) *(mapa.fields + i * dimY + j) != 0)
		printf("%c", mapa.fields[i * dimY + j]);
	    else
		printf(" ");
	}
	printf("\n");
    }

    fclose(filePointer);
}

char* dajInfoLink(){
    return infoLink;
}

char* dajExploreLink(){
    return exploreLink;
}

char* dajMoveLink(){
    return moveLink;
}

char* dajLeftLink(){
    return leftLink;
}

char* dajRightLink(){
    return rightLink;
}

char* dajResetLink(){
    return resetLink;
}

int dajSzerokoscMapy(){
    return dimX;
}

int dajWysokoscMapy(){
    return dimY;
}

char* dajAktualnaMape(){
    return mapa.fields;
}
