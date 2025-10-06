#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

#define API_KEY "SUA_CHAVE_API"
#define URL_FORMAT "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&lang=pt_br&units=metric"

// Estrutura para armazenar os dados da resposta
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Função de callback para armazenar a resposta
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, struct MemoryStruct *userp) {
    size_t realsize = size * nmemb;
    userp->memory = realloc(userp->memory, userp->size + realsize + 1);
    if (userp->memory == NULL) {
        printf("Erro ao alocar memória!\n");
        return 0;
    }
    memcpy(&(userp->memory[userp->size]), contents, realsize);
    userp->size += realsize;
    userp->memory[userp->size] = 0;
    return realsize;
}

// Função para obter o clima
void obter_clima(const char *cidade) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  // Inicializa a memória
    chunk.size = 0;             // Tamanho inicial

    char url[256];
    snprintf(url, sizeof(url), URL_FORMAT, cidade, API_KEY);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Processar os dados JSON
            cJSON *json = cJSON_Parse(chunk.memory);
            if (json) {
                cJSON *main = cJSON_GetObjectItem(json, "main");
                cJSON *weather = cJSON_GetArrayItem(cJSON_GetObjectItem(json, "weather"), 0);

                if (main && weather) {
                    double temperatura = cJSON_GetObjectItem(main, "temp")->valuedouble;
                    const char *descricao = cJSON_GetObjectItem(weather, "description")->valuestring;
                    printf("Temperatura: %.2f°C\nDescrição: %s\n", temperatura, descricao);
                }
                cJSON_Delete(json);
            } else {
                printf("Erro ao processar JSON: %s\n", cJSON_GetErrorPtr());
            }
        }
        free(chunk.memory);
    }
    curl_global_cleanup();
}

int main() {
    char cidade[50];
    printf("Digite o nome da cidade: ");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = 0; // Remove a nova linha

    obter_clima(cidade);
    return 0;
}
