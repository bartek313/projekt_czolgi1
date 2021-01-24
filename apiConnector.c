#include "headerFiles/apiConnector.h"
#include "headerFiles/mapGenerator.h"

int typRequesta[] = { 0, 0, 0, 0, 0, 0 };	//tablica informujaca o ostatnio wykonanym zapytaniu -> [info, exploreWorld, move, rotateLeft, rotateRight, reset]

typedef struct _Memory {
    char *response;
    size_t size;
} Memory;

void resetujTabliceRequestow()
{
    for (int i = 0; i < 6; i++) {
	typRequesta[i] = 0;
    }
}

int wykonajRequest(char *url)
{
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	    fprintf(stderr,
		    "Błąd! curl_easy_perform() niepowodzenie: %s\n",
		    curl_easy_strerror(res));
	else {
	    printf("%s", chunk.response);
	}
	//odczyt danych z json
	if (typRequesta[0] == 1 || typRequesta[2] == 1
	    || typRequesta[3] == 1 || typRequesta[4] == 1) {
	    updateMap(chunk.response, typRequesta[0]);
	}

	free(chunk.response);
	curl_easy_cleanup(curl);
	resetujTabliceRequestow();
	return 1;
    } else
	return 0;
}

size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;

    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    if (mem->response != NULL)
	ptr = realloc(mem->response, mem->size + realsize + 1);
    else
	ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
	return 0;	
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;	

    return realsize;
}

int info(char swiat[])
{				//info
    typRequesta[0] = 1;
    return wykonajRequest(dajInfoLink());
}

int odkryjSwiat(char swiat[])
{				//odkrywanie swiata
    typRequesta[1] = 1;
    return wykonajRequest(dajExploreLink());
}

int ruchDoPrzodu(char swiat[])
{				//ruch do przodu
    typRequesta[2] = 1;
    return wykonajRequest(dajMoveLink());
}

int obrocWLewo(char swiat[])
{				//obrot w lewo
    typRequesta[3] = 1;
    return wykonajRequest(dajLeftLink());
}

int obrocWPrawo(char swiat[])
{				//obrot w prawo
    typRequesta[4] = 1;
    return wykonajRequest(dajRightLink());
}

int resetujSwiat(char swiat[])
{				//reset
    typRequesta[5] = 1;
    return wykonajRequest(dajResetLink());
}
