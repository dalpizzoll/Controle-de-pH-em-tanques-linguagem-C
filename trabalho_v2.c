#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float **sensores;
    int linhas;
    int colunas;
} PlantaIndustrial;

typedef struct {
    float *vetor_medias;
    int *vetor_atuadores;
    int total_alarmes;
} SistemaControle;

int alocar_sistema(PlantaIndustrial *p, SistemaControle *c, int l, int c_col) {
    p->linhas = l;
    p->colunas = c_col;
    c->total_alarmes = 0;

    p->sensores = (float **) malloc(l * sizeof(float *));
    if (p->sensores == NULL) return 0;

    for (int i = 0; i < l; i++) {
        p->sensores[i] = (float *) malloc(c_col * sizeof(float));
        if (p->sensores[i] == NULL) return 0;
    }

    c->vetor_medias = (float *) malloc(l * sizeof(float));
    c->vetor_atuadores = (int *) malloc(l * sizeof(int));

    if (c->vetor_medias == NULL || c->vetor_atuadores == NULL) {
        return 0;
    }

    for (int i = 0; i < l; i++) {
        c->vetor_atuadores[i] = 1;
    }

    return 1;
}

void inicializar_sensores(PlantaIndustrial *p) {
    for (int i = 0; i < p->linhas; i++) {
        for (int j = 0; j < p->colunas; j++) {
            printf("Digite o pH (Tanque %d, Sensor %d): ", i + 1, j + 1);
            scanf("%f", &p->sensores[i][j]);
        }
    }
}

void processar_dados(PlantaIndustrial *p, SistemaControle *c) {
    for (int i = 0; i < p->linhas; i++) {
        float soma = 0;
        for (int j = 0; j < p->colunas; j++) {
            soma += p->sensores[i][j];
        }
        c->vetor_medias[i] = soma / p->colunas;
    }
}

void avaliar_seguranca(const PlantaIndustrial *p, SistemaControle *c) {
    for (int i = 0; i < p->linhas; i++) {
        for (int j = 0; j < p->colunas; j++) {
            if (p->sensores[i][j] < 6.5f || p->sensores[i][j] > 7.5f) {
                c->total_alarmes++;
                c->vetor_atuadores[i] = 0;
            }
        }
    }
}

void emitir_relatorio(const PlantaIndustrial *p, const SistemaControle *c) {
    printf("\n--- RELATORIO DE OPERACAO ---\n");
    for (int i = 0; i < p->linhas; i++) {
        printf("Tanque %d -> Media: %.2f | Status: %s\n", 
               i + 1, 
               c->vetor_medias[i], 
               c->vetor_atuadores[i] == 1 ? "Valvula Operando" : "Bloqueada / Recirculacao");
    }
    printf("Total de Alarmes Criticos: %d\n", c->total_alarmes);
} // Chave extra removida daqui

void liberar_memoria(PlantaIndustrial *p, SistemaControle *c) {
    for (int i = 0; i < p->linhas; i++) {
        free(p->sensores[i]);
    }
    free(p->sensores);
    free(c->vetor_medias);
    free(c->vetor_atuadores);
}

int main(void) {
    PlantaIndustrial planta;
    SistemaControle controle;

    if (!alocar_sistema(&planta, &controle, 4, 3)) {
        return 1;
    }

    inicializar_sensores(&planta);
    processar_dados(&planta, &controle);
    avaliar_seguranca(&planta, &controle);
    emitir_relatorio(&planta, &controle);
    liberar_memoria(&planta, &controle);

    return 0;
}