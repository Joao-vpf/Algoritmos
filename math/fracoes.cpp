// Função para calcular a representação fracionária contínua de uma fração p/q.

// Parâmetros:
//    p: numerador da fração
//    q: denominador da fração
//    a: vetor para armazenar os termos da representação fracionária contínua
// Complexidade:
// O(log(min(p, q)))
void fraction(int p, int q, vector<int>& a)
{
    while (q != 0) {
        a.push_back(p / q); // Adicionar o quociente da divisão p/q ao vetor a
        // Atualizar p e q usando a técnica de atribuição simultânea
        tie(p, q) = make_pair(q, p % q);
    }
}


