#ifndef hashtable_h
#define hashtable_h
#include <vector>
#include <list>
#include <string>
#include <utility> 
#include <functional> 

using namespace std;



// This hashtable works only for Tkey objects that
// provide a hash function and equality operator==
// and operator!=
template <typename Tkey, typename Tval>
class HashTable {
private:
    
    vector<list<pair<Tkey,Tval>>> table; // vector de list de pair<Tkey,Tval>

    int currentSize; // Guarda o numero de chaves da tabela

    // Funcao que recebe como entrada uma chave x e devolve um
    // inteiro sem sinal que representa o indice da tabela em que
    // essa chave x deve ser inserida. O indice da tabela eh um 
    // valor que sempre varia de 0 a table.size()-1.
    size_t hashFunction(const Tkey& x) const;

    // Quando essa funcao for chamada, uma nova tabela maior que a anterior deve ser criada. 
    // Para descobrir o tamanho da nova tabela, primeiro multiplique o tamanho da tabela atual
    // por 2 e depois passe esse numero para a funcao nextPrime para que ela calcule o tamanho
    // correto da nota tabela (sera um numero primo, sempre!)
    // Essa nova tabela deve ter as mesmas chaves que a anterior tinha, mas essas chaves 
    // podem estar em listas diferentes da que estavam antes.
    // Note que os pares (chave,valor) terao que ser inseridos um por um na nova tabela criada.
    void rehash();
    

public:
    
    // As linhas abaixo fazem com que as duas funcoes sejam deletadas.
    // Ou seja, nao sera possivel usar o operador de atribuicao entre 
    // dois objetos desta classe, assim como nao sera possivel 
    // instanciar um objeto desta classe usando outro objeto desta mesma classe. 
    HashTable& operator=(const HashTable&) = delete; // Not copy assignable
    HashTable(const HashTable&) = delete; // Non copy constructible

    // Construtor. Possui o parametro do tipo inteiro 'tableSize' que 
    // guarda com o tamanho da tabela.
    // Esse construtor garante que a tabela tera um tamanho primo maior ou igual
    // ao valor passado como parametro. 
    HashTable(int tableSize);

    // Recebe como entrada uma chave e:
    // devolve 'true' se a chave existe na tabela;
    // ou devolve 'false' caso contrario.
    bool contains(const Tkey& x) const;

    // Recebe como entrada uma chave e um valor associado a chave e:
    // se a chave nao estiver na tabela, entao insere o par (chave,valor) na tabela;
    // se a chave ja estiver na tabela, nao faz nada.
    void insert(const Tkey& x, const Tval& y);

    // Recebe como entrada uma chave e uma referencia para uma variavel do tipo Tval.
    // Se a chave estiver na tabela, devolve 'true' e guarda o valor associado a chave
    // na variavel y. Se a chave nao estiver na tabela, devolve 'false'. Neste caso, 
    // o valor em y pode ser qualquer um (lixo).
    bool search(const Tkey& x, Tval& y);

    // Recebe como entrada uma chave x e a remove da tabela se ela existir na tabela.
    // Atencao: remove nao apenas x mas tambem a chave associada a ele
    void remove(const Tkey& x);

    // Devolve o numero de chaves armazenados na tabela
    int size() const;

    // Deixa a tabela vazia (sem chaves)
    void clear();

    // Imprime a tabela hash apenas para fins de teste.
    // Essa funcao geralmente nao existe numa tabela hash profissional.
    void print() const;
  


};
// Funcao auxiliar
// Devolve 'true' se o inteiro n for primo;
// Devolve 'false' caso contrario.
bool isPrime (int n) { 
    if (n == 2 || n == 3)
        return true;
    if (n == 1 || n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

// Funcao auxiliar
// Se n for primo, devolve n;
// Se n nao for primo, devolve o proximo valor primo que eh maior do que n.
int nextPrime(int n) { 
    if( n % 2 == 0 ) n++;
    while( !isPrime(n) ) n += 2;
    return n;
}
template <typename Tkey, typename Tval>
HashTable<Tkey,Tval>::HashTable(int tableSize) {
    table.resize(tableSize);
    currentSize = 0;
}

template <typename Tkey, typename Tval>
size_t HashTable<Tkey,Tval>::hashFunction(const Tkey& x) const {
    std::hash<Tkey> ff;
    size_t hashcode = ff(x);
    return hashcode % table.size();
}

template <typename Tkey, typename Tval>
void HashTable<Tkey,Tval>::insert(const Tkey& x, const Tval& y) {
    size_t slot = hashFunction(x);
    for(const auto& p : table[slot])
        if(p.first == x)
            return;
    table[slot].push_back( std::make_pair(x,y) );
    currentSize++;

    if(static_cast<float>(currentSize)/table.size() > 0.8)
        rehash();

}

template <typename Tkey, typename Tval>
void HashTable<Tkey,Tval>::print() const {
     for(size_t slot = 0; slot < table.size(); slot++) {
        std::cout << "T[" << slot << "]: ";
        for(const auto& p : table[slot])
            std::cout << "(" << p.first << "," << p.second << ")";
        std::cout << std::endl;
    }
}
template <typename Tkey, typename Tval>
int HashTable<Tkey,Tval>::size() const { // TODO
    return currentSize;
}

template <typename Tkey, typename Tval>
void HashTable<Tkey,Tval>::clear() { // TODO
    for(size_t i = 0; i < table.size(); ++i)
    table[i].clear();
    
    currentSize=0;

}

template <typename Tkey, typename Tval>
bool HashTable<Tkey,Tval>::contains(const Tkey& x) const { // TODO
    size_t slot = hashFunction(x);
        for(const auto& p : table[slot])
        if( x == p.first )
                return true;
    return false;
}

template <typename Tkey, typename Tval>
bool HashTable<Tkey,Tval>::search(const Tkey& x, Tval& y) { // TODO
    size_t slot = hashFunction(x);
         for(const auto& p : table[slot])
            if( x == p.first ){
            y = p.second;
                return true;
        }

    return false;
      

}

template <typename Tkey, typename Tval>
void HashTable<Tkey,Tval>::remove(const Tkey& x) { // TODO
    size_t slot = hashFunction(x);
    list<pair<Tkey,Tval>> list_aux;
        for(const auto& p : table[slot]){
            if( x == p.first){
            this->currentSize --;
            }else{
            list_aux.push_back(p);
            }
        }
    table[slot] = list_aux;
}

template <typename Tkey, typename Tval>
void HashTable<Tkey,Tval>::rehash() { // TODO
     HashTable <Tkey,Tval> table_aux (nextPrime(2*table.size( )));
     for(size_t i = 0; i < table.size(); ++i) 
        for(auto it = table[i].begin(); it != table[i].end(); ++it)
        table_aux.insert(it->first, it->second);
    
    this-> table = table_aux.table;
       
  
    

}

#endif