/*
* Super Trunfo de Países - Nível Mestre
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char estado;
    char codigo[4];
    char cidade[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Carta;

typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE_POPULACIONAL,
    PIB_PER_CAPITA
} TipoAtributo;

typedef enum {
    CARTA1_VENCE = 1,
    CARTA2_VENCE,
    EMPATE
} ResultadoComparacao;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerCarta(Carta *carta, int numero) {
    printf("\n=== Cadastro da Carta %d ===\n", numero);
    
    printf("Estado (A-H): ");
    scanf(" %c", &(carta->estado));
    
    printf("Código da Carta (ex: A01): ");
    scanf("%s", carta->codigo);
    limparBuffer();
    
    printf("Nome da Cidade: ");
    fgets(carta->cidade, 50, stdin);
    carta->cidade[strcspn(carta->cidade, "\n")] = '\0';
    
    printf("População: ");
    scanf("%d", &(carta->populacao));
    
    printf("Área (km²): ");
    scanf("%f", &(carta->area));
    
    printf("PIB (bilhões de reais): ");
    scanf("%f", &(carta->pib));
    
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &(carta->pontos_turisticos));
    
    carta->densidade_populacional = carta->populacao / carta->area;
    carta->pib_per_capita = (carta->pib * 1000000000) / carta->populacao;
}

void exibirCarta(const Carta *carta, int numero) {
    printf("\n=== Carta %d ===\n", numero);
    printf("Estado: %c\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Nome da Cidade: %s\n", carta->cidade);
    printf("População: %d habitantes\n", carta->populacao);
    printf("Área: %.2f km²\n", carta->area);
    printf("PIB: %.2f bilhões de reais\n", carta->pib);
    printf("Número de Pontos Turísticos: %d\n", carta->pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta->densidade_populacional);
    printf("PIB per Capita: %.2f reais\n", carta->pib_per_capita);
}

int exibirMenu(const char *titulo, const char **opcoes, int numOpcoes) {
    int i, escolha;
    
    printf("\n=== %s ===\n", titulo);
    for (i = 0; i < numOpcoes; i++) {
        printf("%d. %s\n", i + 1, opcoes[i]);
    }
    printf("Digite sua escolha (1-%d): ", numOpcoes);
    scanf("%d", &escolha);
    
    return (escolha >= 1 && escolha <= numOpcoes) ? escolha : 0;
}

float obterValorAtributo(const Carta *carta, TipoAtributo atributo) {
    switch (atributo) {
        case POPULACAO: return (float)carta->populacao;
        case AREA: return carta->area;
        case PIB: return carta->pib;
        case PONTOS_TURISTICOS: return (float)carta->pontos_turisticos;
        case DENSIDADE_POPULACIONAL: return carta->densidade_populacional;
        case PIB_PER_CAPITA: return carta->pib_per_capita;
        default: return 0.0f;
    }
}

const char* obterNomeAtributo(TipoAtributo atributo) {
    static const char *nomes[] = {
        "", "População", "Área", "PIB", "Pontos Turísticos", "Densidade Populacional", "PIB per Capita"
    };
    return nomes[atributo];
}

int menorVenceTipoAtributo(TipoAtributo atributo) {
    return atributo == DENSIDADE_POPULACIONAL;
}

ResultadoComparacao compararAtributo(float valor1, float valor2, int menorVence) {
    if (menorVence) {
        return (valor1 < valor2) ? CARTA1_VENCE : ((valor1 > valor2) ? CARTA2_VENCE : EMPATE);
    } else {
        return (valor1 > valor2) ? CARTA1_VENCE : ((valor1 < valor2) ? CARTA2_VENCE : EMPATE);
    }
}

void exibirResultadoComparacao(ResultadoComparacao resultado, const Carta *carta1, const Carta *carta2, 
                              TipoAtributo atributo, float valor1, float valor2) {
    const char *nomeAtributo = obterNomeAtributo(atributo);
    int menorVence = menorVenceTipoAtributo(atributo);
    
    printf("Comparando %s:\n", nomeAtributo);
    
    if (resultado == CARTA1_VENCE) {
        printf("- Carta 1 (%s) vence com ", carta1->cidade);
        menorVence ? printf("menor valor: %.2f!\n", valor1) : printf("maior valor: %.2f!\n", valor1);
    } else if (resultado == CARTA2_VENCE) {
        printf("- Carta 2 (%s) vence com ", carta2->cidade);
        menorVence ? printf("menor valor: %.2f!\n", valor2) : printf("maior valor: %.2f!\n", valor2);
    } else {
        printf("- Empate! Ambas as cartas têm o mesmo valor: %.2f.\n", valor1);
    }
}

void realizarComparacao(const Carta *carta1, const Carta *carta2) {
    static const char *opcoesAtributos[] = {
        "População (maior vence)",
        "Área (maior vence)",
        "PIB (maior vence)",
        "Pontos Turísticos (maior vence)",
        "Densidade Populacional (menor vence)",
        "PIB per Capita (maior vence)"
    };
    
    TipoAtributo atributo1, atributo2;
    float valor1_1, valor1_2, valor2_1, valor2_2;
    ResultadoComparacao resultado1, resultado2, resultadoFinal;
    
    atributo1 = exibirMenu("Escolha o primeiro atributo para comparação", opcoesAtributos, 6);
    if (atributo1 == 0) {
        printf("Opção inválida!\n");
        return;
    }
    
    atributo2 = exibirMenu("Escolha o segundo atributo para comparação", opcoesAtributos, 6);
    if (atributo2 == 0) {
        printf("Opção inválida!\n");
        return;
    }
    
    valor1_1 = obterValorAtributo(carta1, atributo1);
    valor1_2 = obterValorAtributo(carta2, atributo1);
    valor2_1 = obterValorAtributo(carta1, atributo2);
    valor2_2 = obterValorAtributo(carta2, atributo2);
    
    resultado1 = compararAtributo(valor1_1, valor1_2, menorVenceTipoAtributo(atributo1));
    resultado2 = compararAtributo(valor2_1, valor2_2, menorVenceTipoAtributo(atributo2));
    
    printf("\n=== Resultado da Comparação ===\n");
    
    exibirResultadoComparacao(resultado1, carta1, carta2, atributo1, valor1_1, valor1_2);
    exibirResultadoComparacao(resultado2, carta1, carta2, atributo2, valor2_1, valor2_2);
    
    resultadoFinal = (resultado1 == resultado2) ? resultado1 : 
                     (resultado1 != EMPATE && resultado2 == EMPATE) ? resultado1 : 
                     (resultado1 == EMPATE && resultado2 != EMPATE) ? resultado2 : EMPATE;
    
    printf("\nResultado Final:\n");
    
    if (resultadoFinal == CARTA1_VENCE) {
        printf("Carta 1 (%s) é a VENCEDORA!\n", carta1->cidade);
    } else if (resultadoFinal == CARTA2_VENCE) {
        printf("Carta 2 (%s) é a VENCEDORA!\n", carta2->cidade);
    } else if (resultado1 != EMPATE && resultado2 != EMPATE && resultado1 != resultado2) {
        printf("EMPATE! Cada carta venceu em um atributo.\n");
    } else {
        printf("EMPATE TOTAL! As cartas têm valores iguais nos atributos escolhidos.\n");
    }
}

int main() {
    Carta carta1, carta2;
    int opcao;
    static const char *opcoesPrincipais[] = {
        "Exibir dados da Carta 1",
        "Exibir dados da Carta 2",
        "Comparar cartas",
        "Sair"
    };
    
    printf("=== Super Trunfo de Países - Nível Mestre ===\n");
    printf("Bem-vindo ao jogo! Vamos começar cadastrando as cartas.\n");
    
    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);
    
    do {
        opcao = exibirMenu("Menu Principal", opcoesPrincipais, 4);
        
        switch(opcao) {
            case 1:
                exibirCarta(&carta1, 1);
                break;
            case 2:
                exibirCarta(&carta2, 2);
                break;
            case 3:
                realizarComparacao(&carta1, &carta2);
                break;
            case 4:
                printf("Obrigado por jogar! Até a próxima.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while(opcao != 4);
    
    return 0;
}