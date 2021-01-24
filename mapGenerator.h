#include "jsonConverter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

struct Map {
   char  *name;
   int   width;
   int   length;
   int   currentX;
   int   currentY;
   char  currentField;
   char  currentDirection;
   char* fields;
};  

void zapiszMape();
void inicjujMape(char* nazwa);
void updateMap(char* json, int infoRequest);
void wyczyscMape();
void zwiekszRozmiarMapy(int sizeX, int sizeY);
void wypiszMape();

char* dajInfoLink();
char* dajExploreLink();
char* dajMoveLink();
char* dajLeftLink();
char* dajRightLink();
char* dajResetLink();

int dajSzerokoscMapy();
int dajWysokoscMapy();
char* dajAktualnaMape();
