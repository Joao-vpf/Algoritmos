void marge(int vet[], int inicio, int fim) //faz o marge sort
{
    int meio=(inicio+fim)/2, aux[(fim-inicio)+1];
    for (int i=inicio, j=meio+1, k=0; i<=meio || j<=fim;)
    {
        if (i<=meio && j<=fim)
        {
            if (vet[i]<vet[j])
            {
                aux[k]=vet[i];
                k++;
                i++;
            }
            else
            {
                aux[k]=vet[j];
                k++;
                j++;
            }
        }
        else
        {
            if (i>meio)
            {
                aux[k]=vet[j];
                k++;
                j++;
            }
            else
            {
                aux[k]=vet[i];
                k++;
                i++;
            }
        }
    }

    for (int i=0, j=inicio;i<(fim-inicio)+1; j++, i++)
    {
        vet[j]=aux[i];
    }
}

void margesort(int vet[], int inicial, int fim)
{
    if (inicial!=fim)
    {
        if (vet[(inicial+fim)/2])
        {
            margesort(vet, inicial , (inicial+fim)/2);
        }
        margesort(vet, ((inicial+fim)/2)+1, fim);
        marge(vet, inicial, fim);
    }
}
