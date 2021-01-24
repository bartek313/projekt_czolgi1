#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void resetujTabliceRequestow();
int wykonajRequest(char* url);
size_t write_callback(void* data, size_t size, size_t nmemb, void* userp);
int info(char swiat[]);
int odkryjSwiat(char swiat[]);
int ruchDoPrzodu(char swiat[]);
int obrocWLewo(char swiat[]);
int obrocWPrawo(char swiat[]);
int resetujSwiat(char swiat[]);
