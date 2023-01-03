int busca_binaria(int vet[], int procurado, int inicio, int fim) //faz uma busca binaria
{
    if (inicio==fim)
    {
        return (vet[inicio]==procurado ? inicio : -1);
    }
    if (vet[(inicio+fim)/2]<=procurado)
    {
       return busca_binaria(vet, procurado, ((inicio+fim)/2)+1, fim);
    }
       return busca_binaria(vet, procurado,inicio , ((inicio+fim)/2));
}
