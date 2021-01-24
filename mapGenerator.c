#include "headerFiles/mapGenerator.h"

int dx = 20;//delty
int dy = 20;

int dimX = 50;//wymiary macierzy
int dimY = 50;

struct Map mapa;
void saveMap(){
    char *data;
    FILE * fPtr;
    fPtr = fopen("map/map.txt", "w");

    if(fPtr == NULL)
    {
        printf("Nie udalo sie otworzyc pliku.\n");
        exit(EXIT_FAILURE);
    }
int counter = 0;

data = malloc((dimX*dimY + 1)*sizeof(char));
for(int j=0; j < dimY; j++){
	for(int i=0; i < dimX; i++){
		if((int)*(mapa.fields + i*dimY + j) != 0)
			data[counter] = (char)*(mapa.fields + i*dimY + j);
		else
			data[counter] = ' ';
		counter+=1;
	}
data[counter] = '\n';
		counter+=1;
}
data[counter+1] = '\0';

    fputs(data, fPtr);
    printf("\n %s \n", data);
    fclose(fPtr);
    free(data);
    printf("Mapa wygenerowana. :) \n");
}

void initMap(char* name){
	mapa.name = name;
	mapa.fields = (char *)malloc(dimX * dimY * sizeof(char));
	mapa.currentX = getCurrentX();
	mapa.currentY = getCurrentY();
}

void updateMap(char* json, int infoRequest){
	int prevX = mapa.currentX;
	int prevY = mapa.currentY;

	jsonParserPayload(json);
//aktualizacja mapy

	mapa.currentX = getCurrentX();
	mapa.currentY = getCurrentY();
	mapa.currentField = getFieldType();
	mapa.currentDirection = getDirection();
	
	if(infoRequest != 1){
		if(dx < 0 ){
			dimX += dimX;
			increaseMapSize(dimX, dimY);
		}
		else if(dx > dimX)//dodanie kolumny z prawej
		{
			dimX += dimX;
			increaseMapSize(dimX, dimY);
		}
		
		if(dy < 0 ){
			dimY += 1;
			increaseMapSize(dimX, dimY);
		}
		else if(dy > dimY)//dodanie kolumny z prawej
		{
			dimY += dimY;
			increaseMapSize(dimX, dimY);
		}

		printf("\n dx = %d dy = %d \n", dx, dy);

		if(mapa.currentX > prevX)
			dx+=1;
		else if(mapa.currentX < prevX)
			dx-=1;

		if(mapa.currentY > prevY)
			dy+=1;
		else if(mapa.currentY < prevY)
			dy-=1;

		printf("\n currentX = %d prevX = %d currentY = %d prevY = %d \n", mapa.currentX, prevX, mapa.currentY, prevY);
	}
	if(mapa.currentX == prevX && mapa.currentY == prevY){//napotkano sciane
		if(mapa.currentDirection == 'E')
			 mapa.fields[dimX + (dx + 1)*dimY + dy] = 'w';
		else if(mapa.currentDirection == 'W')
			 mapa.fields[dimX + (dx - 1)*dimY + dy] = 'w';
		else if(mapa.currentDirection == 'N')
			 mapa.fields[dimX + dx*dimY + (dy + 1)] = 'w';
		else if(mapa.currentDirection == 'S')
			 mapa.fields[dimX + dx *dimY + (dy - 1)] = 'w';
	}
	else
		mapa.fields[dimX + dx*dimY + dy] = mapa.currentField;

	printf("\n dx = %d dy = %d \n", dx, dy);
}

void cleanMap(){
	free(mapa.fields);
}

void increaseMapSize(int sizeX, int sizeY){
	printf("\n POWIEKSZENIE sizex = %d sizey = %d\n", sizeX, sizeY);

	mapa.fields = realloc(mapa.fields, (sizeX + sizeX) * (sizeY + sizeY) * sizeof(char));

	dimX = sizeX + sizeX;
	dimY = sizeY + sizeY;
	
	dx += sizeX;
	dy += sizeY;
}

void printMap(){
FILE* filePointer;

filePointer = fopen("map/map.txt", "r");

printf("DANE MAPY:\n");
printf("name: %s\n", mapa.name);
printf("aktualna pozycja x: %d\n", mapa.currentX);
printf("aktualna pozycja y: %d\n", mapa.currentY);
printf("typ pola: %c\n", mapa.currentField);
printf("Aktualny kierunek: %c\n", mapa.currentDirection);

for(int j=0; j < dimY; j++){
	for(int i=0; i < dimX; i++){
		if((int)*(mapa.fields + i*dimY + j) != 0)
			printf("%c",mapa.fields[i*dimY + j]);
		else
			printf(" ");
	}
printf("\n");
}

fclose(filePointer);
}
