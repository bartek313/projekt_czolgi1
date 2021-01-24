#include "headerFiles/apiConnector.h"
#include "headerFiles/mapGenerator.h"

int requestType[] = {0,0,0,0,0,0};//tablica informujaca o ostatnio wykonanym zapytaniu -> [info, exploreWorld, move, rotateLeft, rotateRight, reset]

typedef struct _Memory
{
    char* response;
    size_t size;
} Memory;

void resetRequestArray(){
for(int i=0; i<6;i++){
	requestType[i] = 0;
}
}

int makeRequest(char* url){
    CURL* curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;
        
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            printf("%s", chunk.response);
        }
	//odczyt danych z json
	if(requestType[0] == 1 || requestType[2] == 1 || requestType[3] == 1 || requestType[4] == 1){
		updateMap(chunk.response, requestType[0]);
	}

        free(chunk.response);
        curl_easy_cleanup(curl);
	resetRequestArray();
	return 1;
    }
    else return 0;	
}

size_t write_callback(void* data, size_t size, size_t nmemb, void* userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory* mem = (Memory*)userp;

    char* ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

int info() {//info
	requestType[0] = 1;
	return makeRequest("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_31");	
}

int exploreWorld(){//odkrywanie swiata
	requestType[1] = 1;
	return makeRequest("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_31");
}

int move() {//ruch do przodu
	requestType[2] = 1;
	return makeRequest("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_31");
}

int rotateLeft() {//obrot w lewo
	requestType[3] = 1;
	return makeRequest("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_31/left");
}

int rotateRight() {//obrot w prawo
	requestType[4] = 1;
	return makeRequest("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_31/right");
}

int reset() {//reset
	requestType[5] = 1;
	return makeRequest("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/qwerty_31");
}
