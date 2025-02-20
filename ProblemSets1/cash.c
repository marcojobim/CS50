#include <stdio.h>

int main(void)
{
    int moedas[] = {25, 10, 5, 1};
    int troco;
    printf("Troco: ");
    scanf("%d", &troco);

    int i = 0;
    int quantidade_moedas = 0;
    while (troco > 0)
    {
        if (moedas[i] <= troco)
        {
            troco = troco - moedas[i];
            quantidade_moedas++;
        }
        else
        {
            i++;
        }
    }
    printf("%d", quantidade_moedas);
}