#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "search/busca_local.h"

static int tempo_excedido(clock_t start, double limite)
{
    return ((double)(clock() - start) / CLOCKS_PER_SEC) >= limite;
}

static void move_item(
    Solucao *s,
    int i, int j, int k,
    Instancia *inst)
{
    int item = s->bins[i].objetos[j];
    int peso = inst->pesos[item];

    remover_item(&s->bins[i], j, peso);
    adicionar_item_bin(&s->bins[k], item, peso);
}

static int tentar_eliminar_bin(Solucao *s, int bin_idx, Instancia *inst)
{
    Bin *b = &s->bins[bin_idx];
    int n = b->qtd_objetos;

    int *itens = malloc(sizeof(int) * n);
    int *pesos = malloc(sizeof(int) * n);

    if (!itens || !pesos) {
        free(itens);
        free(pesos);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        itens[i] = b->objetos[i];
        pesos[i] = inst->pesos[itens[i]];
    }

    for (int i = 0; i < n; i++) {
        int ok = 0;

        for (int k = 0; k < s->qtd_bins; k++) {
            if (k == bin_idx) continue;

            if (s->bins[k].capacidade_usada + pesos[i] <= inst->capacidade) {
                ok = 1;
                break;
            }
        }

        if (!ok) {
            free(itens);
            free(pesos);
            return 0;
        }
    }

    free(itens);
    free(pesos);
    return 1;
}

static void swap_item(
    Solucao *s,
    int a, int ia,
    int b, int ib,
    Instancia *inst)
{
    int A = s->bins[a].objetos[ia];
    int B = s->bins[b].objetos[ib];

    int pA = inst->pesos[A];
    int pB = inst->pesos[B];

    s->bins[a].objetos[ia] = B;
    s->bins[b].objetos[ib] = A;

    s->bins[a].capacidade_usada += pB - pA;
    s->bins[b].capacidade_usada += pA - pB;
}

static int testar_swaps(
    Solucao *atual,
    Instancia *inst,
    int *best_a,
    int *best_ia,
    int *best_b,
    int *best_ib)
{
    int best_delta = 0;

    Solucao *tmp = copiar_solucao(atual);
    int bins_before = tmp->qtd_bins;

    for (int a = 0; a < atual->qtd_bins; a++) {
        for (int b = a + 1; b < atual->qtd_bins; b++) {

            for (int ia = 0; ia < atual->bins[a].qtd_objetos; ia++) {
                for (int ib = 0; ib < atual->bins[b].qtd_objetos; ib++) {

                    Solucao *teste = copiar_solucao(atual);

                    swap_item(teste, a, ia, b, ib, inst);
                    compactar_bins(teste);

                    int delta = bins_before - teste->qtd_bins;

                    if (delta > best_delta) {
                        best_delta = delta;

                        *best_a = a;
                        *best_ia = ia;
                        *best_b = b;
                        *best_ib = ib;

                        liberar_solucao(teste);
                        liberar_solucao(tmp);
                        return best_delta;
                    }

                    liberar_solucao(teste);
                }
            }
        }
    }

    liberar_solucao(tmp);

    return best_delta;
}

Solucao* busca_local_exaustiva(
    Solucao *inicio,
    Instancia *inst,
    double tempo_max)
{
    clock_t start = clock();
    Solucao *atual = inicio;

    int melhorou = 1;

    while (melhorou && !tempo_excedido(start, tempo_max)) {

        melhorou = 0;

        int best_move_delta = 0;
        int bi = -1, bj = -1, bk = -1;

        int best_bin_delta = 0;
        int best_bin = -1;

        int n_bins = atual->qtd_bins;

        for (int i = 0; i < n_bins; i++) {
            Solucao *t = copiar_solucao(atual);

            if (tentar_eliminar_bin(t, i, inst)) {
                compactar_bins(t);

                int delta = atual->qtd_bins - t->qtd_bins;

                if (delta > best_bin_delta) {
                    best_bin_delta = delta;
                    best_bin = i;
                }
            }

            liberar_solucao(t);
        }

        for (int i = 0; i < n_bins; i++) {
            for (int j = 0; j < atual->bins[i].qtd_objetos; j++) {

                int item = atual->bins[i].objetos[j];
                int peso = inst->pesos[item];

                for (int k = 0; k < n_bins; k++) {
                    if (i == k) continue;

                    if (atual->bins[k].capacidade_usada + peso > inst->capacidade)
                        continue;

                    Solucao *t = copiar_solucao(atual);

                    int before = t->qtd_bins;

                    move_item(t, i, j, k, inst);
                    compactar_bins(t);

                    int delta = before - t->qtd_bins;

                    if (delta > best_move_delta) {
                        best_move_delta = delta;
                        bi = i;
                        bj = j;
                        bk = k;
                    }

                    liberar_solucao(t);
                }
            }
        }

        if (best_bin_delta > best_move_delta && best_bin_delta > 0) {
            tentar_eliminar_bin(atual, best_bin, inst);
            compactar_bins(atual);
            melhorou = 1;
        }
        else if (best_move_delta > 0) {
            move_item(atual, bi, bj, bk, inst);
            compactar_bins(atual);
            melhorou = 1;
        }

        int a, ia, b, ib;
        int delta = testar_swaps(atual, inst, &a, &ia, &b, &ib);

        if (delta > 0) {
            swap_item(atual, a, ia, b, ib, inst);
            compactar_bins(atual);
            melhorou = 1;
        }
    }

    return atual;
}
