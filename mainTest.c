#include "headerFiles/mainTest.h"
#include "headerFiles/apiConnectorTest.h"
#include "headerFiles/mapGeneratorTest.h"
#include "headerFiles/jsonConverterTest.h"

void testingMenu(){//menu do testowania
printf("###MENU TESTOWANIA### \n");
printf("1 - test parser json \n");
printf("2 - zapisu mapy \n");
printf("0 - zamkniecie aplikacji \n");

do{
	printf("opcja: \n");
	scanf("%d", &choice);
	(void) getchar();

	switch(choice){
	case 0:
	   break;
	case 1:
	   testJSONParser();
	   break;
	case 2:
	   testZapisuMapy();
	   break;
	default:
	printf("Nieznana opcja! \n");
	}
}while(choice != 0);
}

int main(int argc, char** argv)
{
	testingMenu();
    	return 0;
}

