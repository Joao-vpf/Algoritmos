#include "order.hpp"
void order::selection_sort(int *x, bool inc, int n) //
{
    int *vet=x;
    if(inc)
    {
        for(int i=0; i<n; i++)
        {
            int idx=i; //index 
            for(int j=i+1; j<n; j++)
            {
                if(vet[idx]>vet[j])
                    idx=j;
            }
            //troca o elemento do idx (maior elemento do i)
            int aux=vet[idx];
            vet[idx]=vet[i];
           vet[i]=aux;
        }
        x=vet;
        return;
    }
    
   for(int i=0; i<n; i++)
    {
        int idx=i; //index 
        for(int j=i+1; j<n; j++)
        {
            if(vet[idx]<vet[j])
                idx=j;
        }
        //troca o elemento do idex(menor elemento do i)
        int aux=vet[idx];
        vet[idx]=vet[i];
        vet[i]=aux;
    }
    x=vet;
}

void  order::bubble_sort(int *x, bool inc, int n)
{
    int aux;
    int* vet=x;
    if(inc)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=i; j<n ; j++)
            {
                if(vet[i]<vet[j]) //verifica se é menor caso seja troca
                {
                    aux = vet[i];
                    vet[i]=vet[j];
                    vet[j]=aux;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<n; i++)
        {
            for(int j=i; j<n ; j++)
            {
                if(vet[i]>vet[j])//verifica se é maior caso seja troca
                {
                    aux = vet[i];
                    vet[i]=vet[j];
                    vet[j]=aux;
                }
            }
        }
    }
}

void  order::insertion(int *x, bool inc, int n)
{
    int *vet=x;
    int pivo, pos;
    if(inc)
    {
        for(int i=0, j; i<n; i++)
        {
            pos=i;
            pivo=vet[i];  //seleciona um elemento para comparação (pivo)
            for(j=i;j<n; j++)
            {
                if(vet[j]<pivo) //caso esse elemento nao seja troca o elemento pivo
                {
                    pos=j;
                    pivo=vet[j];
                }
            }
            pivo=vet[pos];
            vet[pos]=vet[i];
            vet[i]=pivo;
        }
    }
    else
    { 
        for(int i=0, j; i<n; i++)
        {
            pos=i;
            pivo=vet[i];  
            for(j=i;j<n; j++)
            {
                if(vet[j]>pivo)
                {
                    pos=j;
                    pivo=vet[j];
                }
            }
            pivo=vet[pos];
            vet[pos]=vet[i];
            vet[i]=pivo;
        }
    }
}

int order::part(int *vet, int left, int right, bool inc)
{
    //a partir do left e right é escolhido o elemento pivo nesse caso por preferencia foi o mais a direita
    int cont=0;
    int i=left, j=right, aux=0;
    if(inc)
    {
        for(; i<j; i++) //conta quantos sao menores que esse pivo
        {
            if(vet[i]<vet[right])
            {
                cont++;
            }
        }
        //coloca o pivo em comparação ao meior do left e right
        cont+=left;
        //troca
        aux=vet[cont];
        vet[cont]=vet[right];
        vet[right]=aux;
        i=j=cont;
        i--;
        j++;
        while(i>=left && j<=right)
        {
            aux=0;
            if(vet[i]>=vet[cont])
            {
                aux=vet[i];
                vet[i]=vet[j];
                vet[j]=aux;
            }
            else
            {
                i--;
            }
            if(vet[j]>=vet[cont])
            j++;
        }
        return cont;
    }
    for(; i<j; i++)
    {
        if(vet[i]>vet[right])
        {
            cont++;
        }
    }
    cont+=left;
    aux=vet[cont];
    vet[cont]=vet[right];
    vet[right]=aux;
    i=j=cont;
    i--;
    j++;
    while(i>=left && j<=right)
    {
        aux=0;
        if(vet[i]<=vet[cont])
        {
            aux=vet[i];
            vet[i]=vet[j];
            vet[j]=aux;
        }
        else
        {
            i--;
        }
        if(vet[j]<=vet[cont])
        j++;
    }
    return cont;
}

void order::rquicksort(int *vet, int left, int right, bool inc)
{
    //função recursiva que verifica o vetor a busca da ordenação
    if(left>=right)return;
    int idx = part(vet, left, right,inc);

    rquicksort(vet, idx+1, right, inc);
    rquicksort(vet, left, idx-1, inc);
}

void order::quicksort(int *x,bool inc , int n)
{//arruma para chamar função recursiva corretamente
    int *vet=x;
    rquicksort(vet, 0, n-1, inc);
    x=vet;
}

void order::shell_sort(int *x, bool inc, int n)
{
    int *vet = x;
    if(inc)
    {
        for(int i=n/2; i>0; i/=2)
        {
            for(int j=i; j<n; j++)
            {
                int aux = vet[j];

                int o;
                for(o=j; o>=i && vet[o-i]>aux; o-=i) vet[o]=vet[o-i];
                vet[o]=aux;
            }
        }
    }
    else
    {
        for(int i=n/2; i>0; i/=2)
        {
            for(int j=i; j<n; j++)
            {
                int aux = vet[j];

                int o;
                for(o=j; o>=i && vet[o-i]<aux; o-=i) vet[o]=vet[o-i];
                vet[o]=aux;
            }
        }
    }
}

void order::merge(int* vet, int left, int right, bool inc)
{
    int tam = (right-left)/2+1;
    int mid = (right+left)/2+1;
    int *r = new int[tam+1];
    int *l = new int[tam+1];
    int i, u, j, k;
    for(i=0, j=left; j<mid; i++, j++)
    {
        l[i]=vet[j];
    }

    for(u=0, j=mid; j<=right; u++, j++)
    {
        r[u]=vet[j];
    }
    
    if(inc)
    {
        i=j=u=k=0;
        //merge normal na ordem crescente
        for(k=left; k<=right; k++)
        {
            if(i<tam && j<tam+1)
            {
                if(r[i] < l[j])
                {
                    vet[k]=r[i++];
                }
                else
                {
                    vet[k]=l[j++];
                }
            }
            else
            {
                if(i<tam)
                {
                    vet[k]=r[i++];
                }
                else
                {
                    vet[k]=l[j++];
                }
            }
        }
    }
    else
    {
        u--;
        i--;
        //anda o vetor de tras para frente invertendo a ideia do merge normal
        for(k=right; k>left-1; k--)
        {
            if(i>-1&& u>-1)
            {
                if(r[u] < l[i])
                {
                    vet[k]=r[u--];
                }
                else
                {
                    vet[k]=l[i--];
                }
            }
            else
            {
                if(u>-1)
                {
                    vet[k]=r[u--];
                }
                else
                {
                    vet[k]=l[i--];
                }
            }
        
        }
    }

    delete r;
    delete l;
}

void order::rmergesort(int* vet, int left, int right, bool inc)
{
    if(left>=right) return;
    rmergesort(vet, left, (left+right)/2, inc);
    rmergesort(vet, (left+right)/2+1, right, inc);

    merge(vet, left, right, inc);
}

void order::mergesort(int *x, bool inc, int n)
{
    rmergesort(x, 0, n-1, inc);
}

void order::modheap(int* x,int n, int i, bool inc)
{//transforma o vetor em uma arvore
    int largest = i;   //coloca o maior elemento no "root"
    int left = 2*i + 1;
    int right = 2*i + 2;
 
    if(inc)//crescente
    {
        if (left < n && x[left] > x[largest])
            largest = left;

        if(right < n && x[right] > x[largest])
            largest = right;
    }
    else//decrescente
    {
        if (left < n && x[left] < x[largest])
            largest = left;

        if (right < n && x[right] < x[largest])
            largest = right;
    }

    if (largest != i) 
    {
        int aux = x[i];
        x[i]=x[largest];
        x[largest]=aux;
        modheap(x, n, largest, inc);
    }
}

void order::heapsort(int *x, bool inc, int n)
{
    for (int i = n/2 - 1; i >= 0; i--) 
        modheap(x, n, i, inc);//cria a arvore

    for (int i = n - 1; i >= 0; i--) 
    { 
        int aux = x[i];
        x[i]=x[0];
        x[0]=aux;
        modheap(x, i, 0,inc);
    }
}

