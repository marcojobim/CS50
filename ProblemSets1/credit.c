#include <stdio.h>

int main(void)
{
    // Os números tem 16 digitos
    long long numero;
    int soma = 0;
    printf("Numero: ");
    scanf("%lld", &numero);
    long long aux = numero;
    int digitos[16];

    for (int i = 15; i >= 0; i--)
    {
        digitos[i] = numero % 10;
        numero /= 10;
    }

    for (int i = 14; i >= 0; i -= 2)
    {
        digitos[i] *= 2;
    }

    for (int i = 15; i >= 0; i--)
    {
        if (digitos[i] >= 10)
        {
            soma += digitos[i] % 10 + digitos[i] / 10;
        }
        else
        {
            soma += digitos[i];
        }
    }

    if (soma % 10 != 0)
    {
        printf("INVALIDO\n");
        return 1;
    }

    int num_digitos = 2;
    while (aux >= 100)
    {
        aux /= 10;
        num_digitos++;
    }

    if (num_digitos == 15 && aux == 34 || aux == 37)
    {
        printf("AMEX\n");
    }
    else if (num_digitos == 16 && aux >= 51 && aux <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (num_digitos == 13 || num_digitos == 16 && aux / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALIDO\n");
    }
}
