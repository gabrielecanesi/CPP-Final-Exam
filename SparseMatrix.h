/**
 *
 * @file SparseMatrix.h
 * @author Gabriele Canesi - Matricola 851637
 * @brief File contenete la definizione della classe SparseMatrix
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include "sparse_matrix_exceptions.h"
#include <algorithm>
#include <limits>



/**
 *
 * @brief Matrice sparsa. Questa classe permette di memorizzare i dati in una matrice, in posizioni scelte dall'utente.
 * La dimensione della matrice è scelta a runtime.
 * */


/**
 * @tparam T Il tipo di dato da memorizzare all'interno della matrice
 */

template<typename T>
class SparseMatrix {
private:
    struct node;
public:

    typedef long long size_type;

    /**
     * @brief Struttura che contiene i dati relativi a un elemento: riga, colonna e valore effettivo.\n
     * Viene ritornata dal const_iterator.
     */
    struct element{
        /**
         * @brief Riga in cui si trova il dato
         */
        size_type m_i;

        /**
         * @brief Colonna in cui si trova il dato
         */
        size_type m_j;

        /**
         * @brief Il dato effettivo
         */
        T data;

        /**
         * @brief Costruttore di default
         *
         * @post m_i == 0
         * @post m_j == 0
         */
        element() : m_i(0), m_j(0) {}

        /**
         *
         * @param i Valore della riga
         * @param j Valore della colonna
         * @param data il valore memorizzato
         *
         *
         * @post m_i = i
         * @post m_j = j
         * @post data = data
         */
        element(size_type i, size_type j, const T& data) : m_i(i), m_j(j), data(data){}


        /**
         * @brief costruttore di copia
         * @param other l'elemento da copiare
         */
        element(const element& other) : data(other.data), m_j(other.m_j), m_i(other.m_i) {}

        /**
         * @brief Distruttore
         */

        // Il distruttore è vuoto perchè ad occuparsi della distruzione dei nodi è SparseMatrix,
        // dal momento che la classe è utilizzabile solo da essa.
        ~element(){}


        /**
         * @brief Operatore di assegnamento
         * @param other l'elemento da assegnare
         * @return se stesso
         */
        element& operator=(const element& other){
            if (this != &other){
                element temp = other;
                data = temp.data;
                m_i = other.m_i;
                m_j = other.m_j;
            }
            return *this;
        }
    };
    /**
     * @typedef size_type
     * @brief Un wrapper per mascherare il vero tipo di dati che rappresenta la dimensione della matrice
     */


    /**
     * @brief Costruttore di default. Istanzia una matrice vuota e ha come dato di default il risultato del costruttore
     * di default del tipo T.
     *
     * @post m_width == 0
     * @post m_height == 0
     * @post m_data == nullptr
     */
    SparseMatrix() : m_width(0), m_height(0), m_data(nullptr), m_inserted_elements(0) {}


    /**
     * @brief Costruttore che prende in input la dimensione della matrice e il valore di default
     * @param n numero di righe
     * @param m numero di colonne
     * @param default_value valore di default
     */
    SparseMatrix(size_type n, size_type m, const T& default_value) : m_data(nullptr), m_width(0),
    m_height(0), m_default(default_value), m_inserted_elements(0) {
        if(n < 0 || m < 0){
            throw invalid_matrix_dimension_exception("Dimensione specificata non valida");
        }
        m_height = n;
        m_width = m;
    }

    /**
     * @brief Copy constructor
     * @param other Reference all'oggetto da copiare
     */


    /**
     * @brief costruttore di copia
     * @param other l'oggetto da copiare
     * @post m_width == other.m_width
     * @post m_height == other.m_height
     * @post m_default == other.m_default
     */
    SparseMatrix(const SparseMatrix& other) : m_height(other.m_height), m_width(other.m_width), m_data(nullptr),
    m_default(other.m_default), m_inserted_elements(0) {
        node* temp = other.m_data;

        /* Dal momento che set chiamerà una new, devo gestire eventuali errori di memoria
        *  per riportare l'oggetto a uno stato coerente
        */
         try{
            while (temp != nullptr){
                set(temp->data.m_i, temp->data.m_j, temp->data.data);
                temp = temp->next;
            }
        }catch(std::bad_alloc& e){
            distruggi_matrice();
            throw e;
        }

    }

    /**
     * @brief Distruttore
     */
    ~SparseMatrix() {
        distruggi_matrice();
    }

    /**
     * @brief Operatore di assegnamento
     * @param other Reference all'oggetto da assegnare
     * @return Reference all'oggetto assegnato
     */
    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this != &other){
            SparseMatrix temp(other);
            std::swap(m_data, temp.m_data);
            std::swap(m_height, temp.m_height);
            std::swap(m_width, temp.m_width);
            std::swap(m_default, temp.m_default);
        }
        return *this;
    }

    /**
     * @brief Aggiunge un valore alla matrice ad una posizione precisa
     * @param i indice della riga
     * @param j indice della colonna
     * @param data
     */
    void set(size_type i, size_type j, const T& data){
        if(i > m_height || j > m_width || i < 0 || j < 0){
            throw matrix_out_of_bounds_exception("Gli indici non rientrano nelle dimensioni della matrice");
        }
        node *found = get_node(i, j);
        if(found == nullptr){
            node *new_node = new node(i, j, data);
            new_node->next = m_data;
            m_data = new_node;
            ++m_inserted_elements;
        }
        else {
            found->data.data = data;
        }
    }

    /**
     * @brief operatore per ottenere il valore alla posizione specificata
     * @param i indice della riga
     * @param j indice della colonna
     * @return il valore alla posizione specificata se esiste, il valore di default altrimenti
     */

    T& operator()(size_type i, size_type j) {
        if (i >= m_height || j >= m_width || i < 0 || j < 0){
            throw matrix_out_of_bounds_exception("Gli indici specificati non rientrano nei limiti di dimensione della matrice.");
        }

        node *found = get_node(i, j);
        if(found == nullptr){
            return m_default;
        }
        return found->data.data;
    }

    size_type insertes_items(){
        return m_inserted_elements;
    }

    /**
     * @brief classe che implementa un const forward iterator per gli alementi della classe SparseMatrix. Ritorna oggetti di tipo element
     */
    class const_iterator {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef element                         value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const element*                  pointer;
        typedef const element&                  reference;


        const_iterator() : ptr(nullptr) {}

        const_iterator(const const_iterator &other) {
            ptr = other.ptr;
        }

        const_iterator& operator=(const const_iterator &other) {
            if(this != &other){
                ptr = other.ptr;
            }
            return *this;
        }

        ~const_iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return ptr->data;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return &(ptr->data);
        }

        // Operatore di iterazione post-incremento
        const_iterator operator++(int) {
            const_iterator temp = *this;
            temp.ptr = temp.ptr->next;
            return temp;
        }

        // Operatore di iterazione pre-incremento
        const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        // Uguaglianza
        bool operator==(const const_iterator &other) const {
            return ptr == other.ptr;
        }

        // Diversita'
        bool operator!=(const const_iterator &other) const {
            return ptr != other.ptr;
        }

        // Solo se serve anche iterator aggiungere le precedenti definizioni

    private:
        //Dati membro

        const node *ptr;
        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class SparseMatrix;

        // Costruttore privato di inizializzazione usato dalla classe container
        // tipicamente nei metodi begin e end
        explicit const_iterator(const node* ptr) : ptr(ptr) {}

        // !!! Eventuali altri metodi privati

    }; // classe const_iterator


    /**
     * @return l'iteratore costante che punta al primo elemento disponibile
     */
    const_iterator begin() const {
        return const_iterator(m_data);
    }


    /**
     *
     * @return l'iteratore che rappresenta l'elemento dopo la fine della matrice.
     */
    const_iterator end() const {
        return const_iterator(nullptr);
    }

private:

    // Struttura che implementa il nodo della lista.
    struct node{
        element data;
        node *next;

        // Costruttore di default
        node() : next(nullptr){}

        // Costruttore di copia
        node(const node& other) : data(other.data), next(other.next) {}

        // Costruttore che prende in input gli indici e il dato da inserire.
        node(size_type i, size_type j, const T& data) : data(element(i, j, data)), next(nullptr){}

        // Distruttore. è vuoto perchè la distruzione dei nodi viene gestita dalla classe SparseMatrix e
        // non è accessibile dall'esterno
        ~node(){}

        // Operatore di assegnamento.
        node& operator=(const node& other){
            if (this != &other){
                node temp = other;
                data = other.data;
                next = temp.next;
            }
            return *this;
        }
    };


    // La matrice vera e propria
    node *m_data;

    // Gli attributi che memorizzano larghezza e altezza della matrice
    size_type m_width;
    size_type m_height;

    size_type m_inserted_elements;

    // Il valore di default nel caso venga richiesta una cella vuota
    T m_default;

    // Funzione di appoggio che cerca il puntatore a un elemento con indici (i, j) se esiste, nullptr altrimenti
    node* get_node(size_type i, size_type j){
        node* temp = m_data;
        while (temp != nullptr && temp->data.m_i != i && temp->data.m_j != j){
            temp = temp->next;
        }
        return temp;
    }

    void distruggi_matrice(){
        node* it = m_data;
        while (it != nullptr){
            node* temp = it;
            it = it->next;
            delete temp;
        }

        m_height = 0;
        m_width = 0;
        m_inserted_elements = 0;
        m_data = nullptr;
    }

};


/**
 *
 * @tparam T il tipo di dato della matrice
 * @tparam Pred il tipo del funtore
 * @param M la matrice da visitare
 * @param P il predicato da testare
 * @return il numero di elementi inseriti nella matrice che soddisfano P
 */
template<typename T, typename Pred>
long evaluate(const SparseMatrix<T>& M, Pred P){
    long result = 0;
    typename SparseMatrix<T>::const_iterator begin, end;
    for(begin = M.begin(), end = M.end(); begin != end; ++begin){
        if(P(begin->data)){
            ++result;
        }
    }
    return result;
}


#endif // SPARSE_MATRIX_H
