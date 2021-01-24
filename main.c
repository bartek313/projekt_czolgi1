#include "headerFiles/main.h"

void manualSteering(){//menu sterowania recznego
printf("###MENU STEROWANIA RECZNEGO### \n");
printf("1 - powrot do poprzedniego menu \n");
printf("2 - info \n");
printf("3 - ruch \n");
printf("4 - obrot w lewo\n");
printf("5 - obort w prawo \n");
printf("6 - odkryj swiat \n");
printf("7 - resetuj swiat \n");
printf("8 - zapisz mape \n");
printf("9 - wyswietl mape \n");
printf("0 - zamkniecie aplikacji \n");

do{
	printf("opcja: \n");
	scanf("%d", &choice);
	(void) getchar();

	switch(choice){
	case 1:
	   workModeSelection(); 
	   break;
	case 2:
	   info(); 
	   break;
	case 3:
	   move();
	   break;
	case 4:
	   rotateLeft();
	   break;
	case 5:
	   rotateRight();
	   break;
	case 6:
	   exploreWorld();
	case 7:
	   reset();
	   break;
	case 8:
	   saveMap();
	   printMap();
	   break;
	case 9:
	   printMap();
	   break;
	case 0:
	   break;
	default:
	printf("Nieznana opcja! \n");
	}
}while(choice != 0);
}

void automaticSteering(){//uruchomienie algorytmu

printf("###MENU STEROWANIA AUTOMATYCZNEGO### \n");
printf("1 - powrot do poprzedniego menu \n");
printf("2 - uruchom  \n");
printf("3 - wyswietl mape \n");
printf("0 - zamkniecie aplikacji \n");

do{
	printf("opcja: \n");
	scanf("%d", &choice);
	(void) getchar();

	switch(choice){
	case 1:
	   workModeSelection(); 
	   break;
	case 2:
	   startAutomaticExploring(); 
	   break;
	case 3:
	   printMap();
	   break;
	case 0:
	   break;
	default:
	   printf("Nieznana opcja! \n");
	}
}while(choice != 0);
}

void workModeSelection(){
printf("###WYBOR TRYBU PRACY### \n");
printf("1 - reczny \n");
printf("2 - automatyczny \n");
printf("0 - zamknij \n");

printf("opcja: \n");
scanf("%d", &choice);
(void) getchar();

if(choice == 0){
	return;
}
else if(choice == 1){
	manualSteering();
}
else if(choice == 2){
	automaticSteering();
}
else{
	do{
		printf("Nieznana opcja! \n");
		printf("1 - reczny \n");
		printf("2 - automatyczny \n");
		printf("0 - zamknij \n");
	}while(choice == 1 || choice == 2 || choice == 0);
}
}

int main(int argc, char** argv)
{
	initMap("qwerty_31");
	workModeSelection();
	cleanMap();
    	return 0;
}

