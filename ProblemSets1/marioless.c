#include <stdio.h>

void print_row(int espacos, int blocos);

int main(void)
{

    int altura;
    printf("Altura: ");
    scanf("%d", &altura);

    for (int i = 1; i <= altura; i++)
    {
        print_row(altura - i, i);
    }

    return 0;
}

void print_row(int espacos, int blocos)
{
    for (int i = 0; i < espacos; i++)
    {
        printf(" ");
    }

    for (int i = 0; i < blocos; i++)
    {
        printf("#");
    }
    printf("\n");
}