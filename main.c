#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define NUM_JOGADORES 2
#define NUM_SELECOES 2
#define TAMANHO_PALAVRA 10
#define QTD_INIMIGOS 3
#define ESC_KEY 27
#define ENTER_KEY 10

typedef struct {
    char nome[100];
    int idade;
    float altura;
} jogador;

typedef struct {
    char nome[50];
    jogador jogadores[NUM_JOGADORES];
} selecao;

typedef struct {
    char palavra[TAMANHO_PALAVRA];
    char chave;
} cifraPalavra;

typedef enum { Jogador, Monstro, Chefe } TipoPersonagem;

typedef struct {
    char nome[30];
    TipoPersonagem tipo;
    int forca;
    int vida;
} Personagem;



void exibeMenuPrincipal(int *opcao){
    
    printf("Selecione a atividade: \n");
    printf("1) Criar jogadores\n");
    printf("2) Encontrar a quantidade de jogadores com idade inferior a 18 anos\n");
    printf("3) A média das idades dos jogadores\n");
    printf("4) A média das alturas de todos os jogadores do campeonato\n");
    printf("5) Cifrar (XOR) palavra\n");
    printf("6) Decriptar palavra cifrada\n");
    printf("7) Jogar Dungeon Bash\n");
    printf("0) Sair\n");
    /* Como a variável *opção já é o endereço de memória */
    /* não usa & para receber o valor passado pelo usuário*/
    scanf("%d",opcao);
}

void criaDadosSelecao(selecao *selecoes, int tamanho){
    int i, j;
    for (i = 0; i < tamanho; i++){
                printf("\nEntre com o nome da seleção No. %d: ", i+1);
                setbuf(stdin, NULL);
                fgets(selecoes[i].nome, 50, stdin);
                printf("\nEntre com os jogadores\n");
                for (j = 0; j < NUM_JOGADORES; j++){
                    printf("\nJogador %d: \n",(j+1));
                    printf("Nome: ");
                    setbuf(stdin, NULL);
                    fgets(selecoes[i].jogadores[j].nome, 100, stdin);
                    printf("Idade: ");
                    scanf("%d", &selecoes[i].jogadores[j].idade);
                    printf("Altura: ");
                    scanf("%f", &selecoes[i].jogadores[j].altura);
                }
                printf("\n--------------------------------------------");
            }
}

void exibeDadosCriados(selecao *selecoes, int tamanho, bool menoresDeIdade, bool exibeMediaIdade, bool mediaDeAlturas){
    int k,l, countMenoresSelecao = 0, countMenoresTotal = 0;
    int somaIdadeSelecao = 0;
    float somaAlturaSelecao = 0.0, somaAlturaTodasSelecoes= 0.0;
    float mediaAlturaSelecaoTodasSelecoes = 0.0;
    printf("\n********************************************\n");
    printf("\t\tInfo:");
    printf("\n********************************************\n");
    for(k = 0; k < tamanho; k++){
        printf("\nSeleção: %s", selecoes[k].nome);
        somaIdadeSelecao = 0;
        somaAlturaSelecao = 0;
        countMenoresSelecao = 0;

        for(l = 0; l < NUM_JOGADORES; l++){
            
            printf("\nJogador: %s", selecoes[k].jogadores[l].nome);
            printf("Idade: %d\n", selecoes[k].jogadores[l].idade);
            printf("Altura: %.2f\n", selecoes[k].jogadores[l].altura);
            
            if(selecoes[k].jogadores[l].idade < 18)
                countMenoresSelecao++;

            somaIdadeSelecao += selecoes[k].jogadores[l].idade;
            somaAlturaSelecao += selecoes[k].jogadores[l].altura;
        }

        somaAlturaTodasSelecoes += somaAlturaSelecao;

        if(menoresDeIdade){
            printf("\n--------------------------------------------\n");
            printf("Jogadores com idade inferior a 18 anos %s: %d\n", selecoes[k].nome, countMenoresSelecao);
            printf("--------------------------------------------\n");
        }
        
        if(exibeMediaIdade){
            float mediaIdadeSelecao = somaIdadeSelecao / NUM_JOGADORES;
            printf("\n---------------------------------------\n");
            printf("Média de idade da seleção %s: %.2f\n", selecoes[k].nome, mediaIdadeSelecao);
            printf("---------------------------------------\n");
        }

        if(mediaDeAlturas){
            float mediaAlturaSelecao = somaAlturaSelecao / NUM_JOGADORES;
            printf("\n--------------------------------------------\n");
            printf("Média de altura da seleção %s: %.2f\n", selecoes[k].nome, mediaAlturaSelecao);
            printf("--------------------------------------------\n");
        }

        countMenoresTotal += countMenoresSelecao;
        
        printf("--------------------------------------------\n");

    }

    if(mediaDeAlturas){
        mediaAlturaSelecaoTodasSelecoes = somaAlturaTodasSelecoes / (NUM_JOGADORES * NUM_SELECOES);
        printf("\n--------------------------------------------\n");
        printf("Média de altura total: %.2f\n", mediaAlturaSelecaoTodasSelecoes);
        printf("--------------------------------------------\n");
    }
    printf("\n********************************************\n");
}

void exibeJogadoresMenoresIdade(selecao *selecoes, int tamanho, bool *selecoesCriadas){
    if(*selecoesCriadas){
        exibeDadosCriados(selecoes, tamanho, true, false, false);
    }
    else{
        printf("\nNenhuma seleção foi encontrada\n");
    }
}

void exibeMediaIdadesTime(selecao *selecoes, int tamanho, bool *selecoesCriadas){
    if(*selecoesCriadas){
        exibeDadosCriados(selecoes, tamanho, false, true, false);
    }
    else{
        printf("\nNenhuma seleção foi encontrada\n");
    }
}

void exibeMediaAltura(selecao *selecoes, int tamanho, bool *selecoesCriadas){
    if(*selecoesCriadas){
        exibeDadosCriados(selecoes, tamanho, false, false, true);
    }
    else{
        printf("\nNenhuma seleção foi encontrada\n");
    }
}

void criptografarPalavra(cifraPalavra *palavra){
    int i;

    printf("\n********************************************\n");
    printf("\t\tCifra de Palavras");
    printf("\n********************************************\n");
    printf("Entre com a palavra a ser criptografada: ");
    setbuf(stdin, NULL);
    fgets(palavra->palavra, TAMANHO_PALAVRA, stdin);
    printf("Entre com a sua chave: ");
    scanf("%c", &palavra->chave);
    printf("Criptografando palavra %s...", palavra->palavra);
    
    for(i = 0; i < TAMANHO_PALAVRA; i++){
        palavra->palavra[i] = palavra->palavra[i]^palavra->chave;
    }
    printf("\nPalavra criptografada : %s", palavra->palavra);
}

void decriptografarPalavra(cifraPalavra *palavra){
    int i;

    printf("\n********************************************\n");
    printf("\t\tCifra de Palavras");
    printf("\n********************************************\n");
    printf("Decriptografando palavra %s...", palavra->palavra);
    
    for(i = 0; i < TAMANHO_PALAVRA; i++){
        palavra->palavra[i] = palavra->palavra[i]^palavra->chave;
    }
    printf("\nPalavra decriptografada : %s", palavra->palavra);
}

int gerarAtributoRandomico(int min, int max){

    int num = 0;
    num = (rand() % (max - min + 1)) + min;
	return num;
}

void criarPersonagemJogador(Personagem *jogador){

    printf("Entre com o nome do seu personagem: ");
    setbuf(stdin, NULL);
    fgets(jogador->nome, 30, stdin);
    jogador->nome[strlen(jogador->nome) - 1] = 0;
    jogador->vida = 100;
    jogador->forca = 10;
    jogador->tipo = Jogador;
    printf("\nPersonagem %s criado \n", jogador->nome);
    printf("Vida: %d\n", jogador->vida);
    printf("Força: %d\n", jogador->forca);

}

void exibirInimigos(Personagem *inimigos, int qtdInimigos){
    int i;
    printf("Exibindo inimigos gerados \n");
    printf("--------------------------\n");
    for(i = 0; i < qtdInimigos; i++)
    {
        char tipoInimigo[30];
        if(inimigos[i].tipo == Monstro)
            strcpy(tipoInimigo, "Monstro");
        else
            strcpy(tipoInimigo, "Chefe");
        printf("Tipo: %s | Nome: %s | Vida: %d | Força: %d \n", tipoInimigo, inimigos[i].nome, inimigos[i].vida, inimigos[i].forca);
    }
    printf("--------------------------\n");
    
}

void criarInimigosDungeon(Personagem *inimigos, int qtdInimigos){
    int i, forca = 0, vida = 0;

    printf("Gerando inimigos ...\n");
    srand( (unsigned)time(NULL) );

    for(i = 0; i < qtdInimigos; i++){
        forca = 0;
        vida = 0;
        

        if(i+1 != qtdInimigos){
            forca = gerarAtributoRandomico(5,10);
            vida =   gerarAtributoRandomico(10,25);
            Personagem inimigo = { "Fera Sinistra", Monstro,  forca, vida };
            inimigos[i] = inimigo;
        }
        else{
            forca = gerarAtributoRandomico(20,25);
            vida = gerarAtributoRandomico(20,40);
            Personagem inimigo = { "Lorde das Feras", Chefe, forca, vida };
            inimigos[i] = inimigo;
        }
    }
    printf("Inimigos Criados\n");
}

void iniciarDungeonBash(Personagem *jogador, Personagem *inimigos, int qtdInimigos){
    int i;
    bool gameover = false;

    printf("Iniciando partida...\n");

    for(i = 0; i < qtdInimigos; i++){
        char tipoInimigo[30];
        if(inimigos[i].tipo == Monstro)
            strcpy(tipoInimigo, "Monstro");
        else
            strcpy(tipoInimigo, "Chefe");

        printf("Encontrou um %s \n", tipoInimigo);

        while(inimigos[i].vida > 0 || jogador->vida > 0){
            inimigos[i].vida -= jogador->forca;
            printf("%s atacou o inimigo %s\n", jogador->nome , inimigos[i].nome);
            printf("%s recebeu -%d de dano\n",inimigos[i].nome , jogador->forca);

            if(inimigos[i].vida <= 0){
                printf("%s foi derrotado\n", inimigos[i].nome);
                break;
            }

            jogador->vida -= inimigos[i].forca;
            printf("%s atacou %s\n", inimigos[i].nome, jogador->nome);
            printf("%s sofreu -%d de dano\n", jogador->nome, inimigos[i].forca);

            if(jogador->vida <= 0){
                printf("%s foi derrotado\n", jogador->nome);
                printf("\nGAME OVER!\n");
                gameover = true;
                break;
            }
            
        }

        if(gameover) 
            break;

        printf("Level %d\n", i+2);
        printf("Vida restante: %d\n", jogador->vida);
            
    }
    if(!gameover)
        printf("\nParabéns, você derrotou todos os inimigos da Dungeon Bash!\n");

}

void dungeonBash(){
    Personagem jogador;
    Personagem inimigos[QTD_INIMIGOS];
    char key;

    do
    {
        printf("\n********************************************\n");
        printf("\tBem vindo ao DUNGEON BASH!\n");
        printf("\n********************************************\n");
        printf("Pressione ENTER para começar, ESC para sair\n");
        
        key = getchar();
        
        switch (key)
        {
            case ENTER_KEY:
                criarPersonagemJogador(&jogador);
                criarInimigosDungeon(inimigos, QTD_INIMIGOS);
                exibirInimigos(inimigos, QTD_INIMIGOS);
                iniciarDungeonBash(&jogador, inimigos,QTD_INIMIGOS);
                break;
            default: 
                break;
        }

    } while (key != ESC_KEY);
}

void executaOpcao(int opcao, selecao *selecoes, bool *selecoesCriadas, cifraPalavra *palavra){
    printf("\n============================================\n");
    
    switch (opcao)
    {
        case 1:
            criaDadosSelecao(selecoes, NUM_SELECOES);
            *selecoesCriadas = true;
            exibeDadosCriados(selecoes, NUM_SELECOES, false, false, false);
            break;
        case 2:
            exibeJogadoresMenoresIdade(selecoes, NUM_SELECOES, selecoesCriadas);
            break;
        case 3: 
            exibeMediaIdadesTime(selecoes, NUM_SELECOES, selecoesCriadas);
            break;
        case 4:
            exibeMediaAltura(selecoes, NUM_SELECOES, selecoesCriadas);
            break;
        case 5: 
            criptografarPalavra(palavra);
            break;
        case 6:
            decriptografarPalavra(palavra);
            break;
        case 7: 
            dungeonBash();
            break;
        default:
            break;
    }
    printf("\n============================================\n");
}

int main() {
    int opcao;
    /* Alternativa para o controle do array seleções, se nulo ou não*/
    bool selecoesCriadas = false;
    selecao selecoes[NUM_SELECOES];
    cifraPalavra palavra;

    printf("Seleções criadas? %s\n", selecoesCriadas ? "true" : "false");
    printf("Bem vindo a resolução dos exercícios!\n");
     do{
         /* passa o endereço de memória da variavel criada no escopo main */
         exibeMenuPrincipal(&opcao);
         if(opcao > 0){
            printf("Opção escolhida: %d\n", opcao);
            executaOpcao(opcao, selecoes, &selecoesCriadas, &palavra);
         }
     }
     while(opcao != 0);

     /* getchar(); */
     return 0;
}
