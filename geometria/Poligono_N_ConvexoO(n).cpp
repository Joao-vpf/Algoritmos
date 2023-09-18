
/*
 A função areaPoligono calcula a área de um polígono não convexo usando o algoritmo do cadarço.
 Ela itera através das arestas do polígono e calcula a contribuição de cada aresta para a área total do polígono. 
 O cálculo é feito usando o método da soma das áreas dos trapézios formados pelas arestas e o eixo x. 
 */
struct Ponto 
{
    ill x=0, y=0;
};

struct Aresta 
{
    Ponto inicio, fim;
};
// Função para verificar se um ponto C está à esquerda da linha AB.
bool esquerda(CNS(Ponto) a, CNS(Ponto)  b, CNS(Ponto)  c) 
{
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) > 0;
}

// Função para calcular a área de um polígono não convexo.
ill areaPoligono(CNS(vector<Aresta>) arestas) 
{
    ill area = 0.0;
    int numArestas = arestas.size();

    for (int i = 0; i < numArestas; i++) 
    {
        CNS(Ponto) p1 = arestas[i].inicio;
        CNS(Ponto) p2 = arestas[i].fim;
        area += (p1.x * p2.y) - (p2.x * p1.y);
    }

    return abs(area) / 2;
}
