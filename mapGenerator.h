#include "jsonConverter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void saveMap();
void initMap(char* name);
void updateMap(char* json, int infoRequest);
void cleanMap();
void increaseMapSize(int sizeX, int sizeY);
void printMap();
