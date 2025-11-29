//Gustavo Secco
//Gustavo Silva
//Luiz Saia
//Vinícius Heleno

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cross-platform compatibility
#ifdef _WIN32
#include <conio.h>
#else
// Linux/Unix compatibility functions
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif

#define MAX_LINHA 15
#define MAX_COLUNA 15
#define MAX_HUD_LINES 25
#define PLAYER "P"

//Seção i18n
#define FALA_DA_INTRO_PTBR "Voce se encontra num lugar escuro apenas com uma espada desgastada, e consegue ouvir algo se aproximando lentamente!"
#define FALA_DA_VITORIA_EN "You use the key and open the door, finding an exit from this place!\n\nYou won!\n\n"

// melhorias status da porta com enum
enum StatusPorta { ABERTA, FECHADA, TRANCADA, BLOQUEADA };

int main (void)
{
    srand(time(NULL));
    int px = 1, py = 1;                                             //Posicao Player
    int ox, oy;                                                     //Variaveis do Bau
    int mx = (int)(MAX_LINHA * 0.7), my = (int)(MAX_COLUNA * 0.6);  //Posicao Monstro
    int x, y, movimentoRealizado, xDoor, yDoor;                     //Variaveis relacionadas a movimento e posição
    int colisaoM = 0, colisaoBau = 0, bauCheio = 1;                 //Variaveis de condição de objetos e ações
    int timer = 0;                                                  //Var para duração de tocha
    int monstroCD = 0;                                              //Var para movimentar monstro
    int visao = 2, tocha = 0;                                       //Var relacionada a visao do personagem
    int danoPlayer = 0, vidaPlayer = 3;                             //Var para rastrear dano no personagem
    int vidaMonstro = 5, monstroVivo = 1;                           //Var para rastrear dano no monstro
    int chave = 0, logPorta = 0, abriuPorta = 0;                    //Armazena se possui a chave para sair
    int intro = 1;                                                  //Texto para introdução
    char comando;                                                   //Pega o comando para agir


    if (rand() % 2 == 0)                                                                        //Posição Baú // Início
    {
        ox = (rand() % 8) + 4;
        oy = (rand() % 3) + 1;
    }

    else
    {
        ox = (rand() % 3) + 1;
        oy = (rand() % 8) + 4;
    }                                                                                           // Posição Baú // Fim

    if (rand() % 2 == 0)                                                                        //Posição Porta // Início
    {
        xDoor = (rand() % (MAX_LINHA - 1)) + 1;
        yDoor = MAX_COLUNA;
    }

    else
    {
        xDoor = MAX_LINHA;
        yDoor = (rand() % (MAX_COLUNA - 1)) + 1;
    }                                                                                           //Posição Porta // Fim

    for (;;)
    {
        system("CLS");

        // Renderização limitada a 25 linhas totais (jogo + HUD)
        for (y = 0; y <= MAX_COLUNA && y < MAX_HUD_LINES; y++)                             //Mapa/Tela // Início
        {
            for (x = 0; x <= MAX_LINHA; x++)
            {
                if (px == x && y == py)
                {
                    printf(PLAYER);
                }

                else if ((x == xDoor && y == yDoor) && (x >= px-visao && x <= px+visao && y >= py-visao && y <= py+visao))
                {
                    printf("O");
                }

                else if (x == 0 || x == MAX_LINHA || y == 0 || y == MAX_COLUNA)
                {
                    printf("#");
                }


                else if (x >= px-visao && x <= px+visao && y >= py-visao && y <= py+visao)
                {
                    if (x == mx && y == my && monstroVivo == 1)
                    {
                        printf("M");
                    }

                    else if (x == ox && y == oy)
                    {
                        printf("@");
                    }

                    else
                    {
                        printf(".");
                    }
                }

                else
                {
                    printf(" ");
                }

                printf(" ");
            }
            printf("\n");
        }                                                                                       //Mapa/Tela // Fim

        printf("\n");

        if (intro == 1)
        {
            intro = 0;
            printf("Voce se encontra num lugar escuro apenas com uma espada desgastada, e consegue ouvir algo se aproximando lentamente!");
        }

        // O que é Números Mágicos?
        if (logPorta == 1)                                                                      //Log // Início
        {
            printf("Voce encontra esta porta trancada");
            logPorta = 0;
        }

        else if (abriuPorta == 1)
        {
            printf("Voce usa a chave e abre a porta, encontrando uma saida deste lugar!\n\nVoce venceu!\n\n");
            system("PAUSE");
            return 0;
        }

        if (colisaoBau == 1 && bauCheio == 1)
        {
            tocha = 1;
            timer = timer + 100;
            bauCheio = 0;
            vidaPlayer = 3;
            printf("Voce abre o bau e encontra uma tocha e uma pocao de cura!");
        }

        else if (colisaoBau == 1 && bauCheio == 0)
        {
            printf("Voce ja abriu esse bau");
        }

        if (colisaoM == 1)
        {
            vidaMonstro--;
            printf("\nVoce atacou o monstro!");
            if (vidaMonstro == 0)
            {
                monstroVivo = 0;
                printf("\nO monstro foi derrotado e voce nota que ele carregava uma chave");
                chave = 1;
                mx = 0;
                my = 0;
            }

            else
            {
                printf("\n");
            }
        }

        else
        {
            printf("\n\n");
        }

        if (danoPlayer == 1)
        {
            vidaPlayer--;
            danoPlayer = 0;
            printf("\nVoce se feriu");
        }

        else
        {
            printf("\n");
        }

        if (timer == 0 && tocha == 1)
        {
            tocha = 0;
            visao = 2;
            printf("\nSua tocha apagou!");
        }

        else
        {
            printf("\n");
        }

        int hp = 219;
        int dano = 176;
        if (vidaPlayer == 3)
        {
        printf("\nPontos de Vida: %c %c %c\n", hp, hp, hp);
        }

        else if (vidaPlayer == 2)
        {
        printf("\nPontos de Vida: %c %c %c\n", hp, hp, dano);
        }

        else if (vidaPlayer == 1)
        {
        printf("\nPontos de Vida: %c %c %c\n", hp, dano, dano);
        }

        else if (vidaPlayer == 0)
        {
        printf("\Pontos de Vida: %c %c %c\n", dano, dano, dano);
        printf("Sua visao comeca a escurecer...\n\nFim de jogo!\n\n");
        system("PAUSE");
        break;
        }

        printf("\n[W] [A] [S] [D] | [Q]uit > ");
        comando = getch();                                                                       //Input simples

        if (tocha == 1)                                                                         //Condições e lógica // Início
        {
            visao = 5;
            timer--;
        }

        movimentoRealizado = 1;
        danoPlayer = 0;
        colisaoM = 0;
        colisaoBau = 0;                                                                         //Condições e lógica // Fim

        // Feedback visual do movimento
        intro = 0;

        switch (comando)                                                                        //Movimentação // Início
        {
            case 'w':
            case 'W':
                if ((px == xDoor) && (py - 1 == yDoor) && chave == 0)
                {
                    logPorta = 1;
                    movimentoRealizado = 0;
                }

                else if ((px == xDoor) && (py - 1 == yDoor) && chave == 1)
                {
                    abriuPorta = 1;
                    py--;
                    movimentoRealizado = 0;
                }

                else if (px == ox && py - 1 == oy) // Mover pra Bau
                {
                    colisaoBau = 1;
                    movimentoRealizado = 0;
                }

                else if (px == mx && py - 1 == my) // Mover pra monstro
                {
                    colisaoM = 1;
                    movimentoRealizado = 0;
                }

                else if (py >= 2)
                {
                    py--;
                    movimentoRealizado = 0;
                }
                break;

            case 'a':
            case 'A':
                if ((px - 1 == xDoor) && (py == yDoor) && chave == 0)
                {
                    logPorta = 1;
                    movimentoRealizado = 0;
                }

                else if ((px - 1 == xDoor) && (py == yDoor) && chave == 1)
                {
                    abriuPorta = 1;
                    px--;
                    movimentoRealizado = 0;
                }

                else if (px - 1 == ox && py == oy) // Bau
                {
                    colisaoBau = 1;
                    movimentoRealizado = 0;
                }

                else if (px - 1 == mx && py == my) // Monstro
                {
                    colisaoM = 1;
                    movimentoRealizado = 0;
                }

                else if (px >= 2)
                {
                    px--;
                    movimentoRealizado = 0;
                }
                break;

            case 's':
            case 'S':
                if ((px == xDoor) && (py + 1 == yDoor) && chave == 0)
                {
                    logPorta = 1;
                    movimentoRealizado = 0;
                }

                else if ((px == xDoor) && (py + 1 == yDoor) && chave == 1)
                {
                    abriuPorta = 1;
                    py++;
                    movimentoRealizado = 0;
                }

                else if (px == ox && py + 1 == oy) // Bau
                {
                    colisaoBau = 1;
                    movimentoRealizado = 0;
                }

                else if (px == mx && py + 1 == my) // Monstro
                {
                    colisaoM = 1;
                    movimentoRealizado = 0;
                }

                else if (py <= MAX_COLUNA-2)
                {
                    py++;
                    movimentoRealizado = 0;
                }
                break;

            case 'd':
            case 'D':
                if ((px + 1 == xDoor) && (py == yDoor) && chave == 0)
                {
                    logPorta = 1;
                    movimentoRealizado = 0;
                }

                else if ((px + 1 == xDoor) && (py == yDoor) && chave == 1)
                {
                    abriuPorta = 1;
                    px++;
                    movimentoRealizado = 0;
                }

                else if (px + 1 == ox && py == oy) // Bau
                {
                    colisaoBau = 1;
                    movimentoRealizado = 0;
                }

                else if (px + 1 == mx && py == my) // Monstro
                {
                    colisaoM = 1;
                    movimentoRealizado = 0;
                }

                else if (px <= MAX_LINHA-2)
                {
                    px++;
                    movimentoRealizado = 0;
                }
                break;

            // Removido comando H - controles agora sempre visíveis

            case 'q':
            case 'Q':
                {
                    printf("\nTem certeza que deseja sair? (Q novamente para confirmar)\n> ");
                    char confirm = getch();
                    if (confirm == 'q' || confirm == 'Q') {
                        exit(0);
                    }
                    movimentoRealizado = 0;
                }
                break;

            default:
                // Comando inválido - não mostra erro, apenas não move
                movimentoRealizado = 1; // força recálculo do movimento
                break;
        }                                                                                       //Movimentação // Fim

                                                                                                //Movimento Monstro // Início
        if (((px + visao >= mx) && (px - visao <= mx) && (py + visao >= my) && (py - visao <= my)) && monstroCD == 0 && monstroVivo == 1) //Persegue a cada 2 turnos quando próximo
        {
            if (rand() % 2 == 0 && my < py)                     //Aleatoriza entre andar horizontalmente ou verticalmente
            {
                my++;
                monstroCD++;
                if (my == py && mx == px)
                {
                    my--;
                    danoPlayer = 1;
                }
            }

            else if (rand() % 2 == 0 && my > py)                //Aleatoriza entre andar horizontalmente ou verticalmente
            {
                my--;
                monstroCD++;
                if (my == py && mx == px)
                {
                    my++;
                    danoPlayer = 1;
                }
            }

            else if (mx < px)
            {
                mx++;
                monstroCD++;
                if (my == py && mx == px)
                {
                    mx--;
                    danoPlayer = 1;
                }
            }

            else if (mx > px)
            {
                mx--;
                monstroCD++;
                if (my == py && mx == px)
                {
                    mx++;
                    danoPlayer = 1;
                }
            }

            else if (my < py)
            {
                my++;
                monstroCD++;
                if (my == py && mx == px)
                {
                    my--;
                    danoPlayer = 1;
                }
            }

            else if (my > py)
            {
                my--;
                monstroCD++;
                if (my == py && mx == px)
                {
                    my++;
                    danoPlayer = 1;
                }
            }
        }

        else if (((px - 1 + visao < mx) || (px + 1 - visao > mx) || (py - 1 + visao < my) || (py + 1 - visao > my)) && monstroCD == 0 && monstroVivo == 1) //Persegue a cada 4 turnos quando longe
        {
            if (rand() % 2 == 0 && my < py)                     //Aleatoriza entre andar horizontalmente ou verticalmente
            {
                my++;
                monstroCD += 3;
                if (my == py && mx == px)
                {
                    my--;
                    danoPlayer = 1;
                }
            }

            else if (rand() % 2 == 0 && my > py)                //Aleatoriza entre andar horizontalmente ou verticalmente
            {
                my--;
                monstroCD += 3;
                if (my == py && mx == px)
                {
                    my++;
                    danoPlayer = 1;
                }
            }

            else if (mx < px)
            {
                mx++;
                monstroCD += 3;
                if (my == py && mx == px)
                {
                    mx--;
                    danoPlayer = 1;
                }
            }

            else if (mx > px)
            {
                mx--;
                monstroCD += 3;
                if (my == py && mx == px)
                {
                    mx++;
                    danoPlayer = 1;
                }
            }

            else if (my < py)
            {
                my++;
                monstroCD += 3;
                if (my == py && mx == px)
                {
                    my--;
                    danoPlayer = 1;
                }
            }

            else if (my > py)
            {
                my--;
                monstroCD += 3;
                if (my == py && mx == px)
                {
                    my++;
                    danoPlayer = 1;
                }
            }
        }

        else
        {
            monstroCD--;
            if (monstroCD < 0)
            {
                monstroCD = 0;
            }
        }                                                                                       //Movimento Monstro // Fim
    }
}
