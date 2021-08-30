#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <vector>
#include <list>

template<typename Tkey> // class template
class PriorityQueue {
public:
    // Construtor: recebe como entrada a capacidade inicial da fila de prioridades
    PriorityQueue( int capacity );

    // Construtor: recebe como entrada um vector e constroi
    // uma fila de prioridades com os elementos desse vector
    PriorityQueue( const std::vector<Tkey>& items );

    // Insere um novo elemento na fila de prioridades
    // Se a fila ficar cheia (atingir a capacidade), o vector usado como base
    // deve aumentar para o dobro da capacidade atual. Ou seja, essa fila de prioridades
    // eh redimensionavel.
    void push( const Tkey& newItem );

    // Acessa o elemento de maior prioridade (com o maior valor)
    // Se for chamado quando a fila estiver vazia, pode lancar uma excecao
    // ou entao abortar o programa (voce escolhe o que fazer neste caso)
    const Tkey& top() const;

    // remove o elemento de maior prioridade
    // Se for chamado quando a fila estiver vazia, pode lancar uma excecao
    // ou entao abortar o programa (voce escolhe o que fazer neste caso)
    void pop();

    // devolve o numero de elementos na fila de prioridade
    int size() const;

    // devolve 'true' se a fila de prioridades estiver vazia e 'false' caso contrario
    bool empty() const;

private:
    int currentSize; // numero de elementos na fila de prioridades
    std::vector<Tkey> vec; // vector que sera o heap maximo

    int parent(int i); // devolve o indice do pai do elemento na posicao vec[i]
    int left(int i); // devolve o indice do filho esquerdo do elemento vec[i]
    int right(int i); // devolve o indice do filho direito do elemento vec[i]
    void moveUp(int i); // move o elemento em vec[i] para cima ate obter um heap maximo
    void moveDown(int i); // move o elemento em vec[i] para baixo ate obter um heap maximo
    void buildMaxHeap(); // controi um heap maximo em tempo O(n)

};
template <typename Tkey>
PriorityQueue<Tkey>::PriorityQueue( int capacity ) {
  currentSize = capacity;
}
template <typename Tkey>
PriorityQueue<Tkey>::PriorityQueue(const std::vector<Tkey>& items) {
      std::list<Tkey> list_aux;
           for(int i = 0; i < items.size(); i++){
            list_aux.push_back(items[i]);
        }
    
}
template <typename Tkey>
const Tkey& PriorityQueue<Tkey>::top() const{
    if(PriorityQueue<Tkey>::empty())
    std::cout << "parou aqui";
        return  vec.back();

}

template <typename Tkey>
void PriorityQueue<Tkey>::push( const Tkey& newItem ) {
    auto it = std::lower_bound(vec.begin(), vec.end(), newItem);
    vec.insert(it, newItem);
}
template <typename Tkey>
void PriorityQueue<Tkey>::pop() {
    vec.pop_back();
}
template <typename Tkey>
bool PriorityQueue<Tkey>::empty() const {
    return vec.empty();
}
template <typename Tkey>
int PriorityQueue<Tkey>::size() const {
     return vec.size();
}
template <typename Tkey>
int PriorityQueue<Tkey>::parent(int i){
    return (i - 1) / 2;
}
template <typename Tkey>
int PriorityQueue<Tkey>::left(int i){
    return 2 * i + 1;
}
template <typename Tkey>
int PriorityQueue<Tkey>::right(int i){
    return 2 * i + 2;
}
template <typename Tkey>
void PriorityQueue<Tkey>::moveUp(int i){
    int parentI;
	if (i != 0){
		parentI = parent(i);
		if (vec[parentI] < vec[i]){
			swap(vec[parentI], vec[i]);
			moveUp(parentI);

		}
		
	}
}
template <typename Tkey>
void PriorityQueue<Tkey>::moveDown(int i){
    int leftI, rightI, minI;

	leftI = left(i);
	rightI = right(i);

	if (rightI >= vec.size()){
		if (leftI >= vec.size())
			  return;
		else
			  minI = leftI;

	}
	else{
		if (vec[leftI] >= vec[rightI])
			  minI = leftI;
		else
			  minI = rightI;

	}

	if (vec[i] < vec[minI]){
		swap(vec[minI], vec[i]);
		moveDown(minI);
		
	}
}
template <typename Tkey>
void PriorityQueue<Tkey>::buildMaxHeap(){
    currentSize = std::vector<Tkey>::size(); 
	for(size_t i = currentSize / 2; i-- > 0;){
    size_t l = left(i), r = right(i); 
    size_t largest = i; 
	if (l < currentSize && (*this)[l] > (*this)[i])
		largest = l; 
	if (r < currentSize && (*this)[r] > (*this)[largest])
		largest = r; 
	if (largest != i) {
		std::swap((*this)[largest], (*this)[i]); 
	buildMaxHeap(largest); 
		}
    }
}
#endif