/**
 *
 * @file SparseMatrix.h
 * @author Gabriele Canesi
 * @brief File contenente la definizione della classe SparseMatrix
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include "sparse_matrix_exceptions.h"
#include <algorithm>
#include <limits>
#include <cstddef>
#include <iterator>

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

    typedef long size_type;

    /**
     * @brief Struttura che contiene i dati relativi a un elemento: riga, colonna e valore effettivo.\n
     * Viene ritornata dal const_iterator.
     */
    class element{
        // Faccio in modo che SparseMatrix sia in grado di accedere agli attributi privati di element
        friend class SparseMatrix;

        /**
         * @brief Il dato effettivo
         */
        T m_value;

        /**
         * @brief Riga in cui si trova il dato
         */
        size_type m_i;

        /**
         * @brief Colonna in cui si trova il dato
         */
        size_type m_j;



    public:
        /**
         * @brief Costruttore di default
         *
         * @post m_i == 0
         * @post m_j == 0
         */
        element() : m_value(), m_i(0), m_j(0) {}

        /**
         *
         * @param i Valore della riga
         * @param j Valore della colonna
         * @param data il valore memorizzato
         *
         *
         * @post m_i = i
         * @post m_j = j
         * @post m_value = m_value
         */

        /*
         * Se la copia del valore ha successo, imposto gli indici.
         * */
        element(size_type i, size_type j, const T &data) : m_value(data), m_i(i), m_j(j) {}


        /**
         * @brief costruttore di copia
         * @param other l'elemento da copiare
         */
        element(const element &other) : m_value(other.m_value), m_j(other.m_j), m_i(other.m_i) {}

        /**
         * @brief Distruttore
         */

        ~element(){
            m_i = 0;
            m_j = 0;
        }


        /**
         * @brief Operatore di assegnamento
         * @param other l'elemento da assegnare
         * @return se stesso
         */

        element& operator=(const element &other){
            if (this != &other){
                m_value = other.m_value;
                m_i = other.m_i;
                m_j = other.m_j;
            }

            return *this;
        }


        /**
         * @brief getter per la riga dell'elemento
         * @return valore della riga
         */

        size_type row() const {
            return m_i;
        }

        /**
         * @brief getter per la colonna del valore
         * @return valore della colonna
         */

        size_type column() const {
            return m_j;
        }

        /**
         * @brief getter per il valore effettivo
         * @return const reference al valore effettivo
         */
        const T& value() const {
            return m_value;
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
     * @post m_rows == 0
     * @post m_columns == 0
     * @post m_data == nullptr
     */

    SparseMatrix() : m_rows(0), m_columns(0), m_data(nullptr), m_inserted_elements(0), m_default() {}


    /**
     * @brief Costruttore che prende in input la dimensione della matrice e il valore di default.\n
     * Per assicurare la coerenza con il numero di elementi inseriti, il numero totale di possibili elementi non può
     * superare il valore massimo di size_type.
     * @param n numero di righe
     * @param m numero di colonne
     * @param default_value valore di default
     */
    SparseMatrix(size_type n, size_type m, const T &default_value) : m_data(nullptr), m_rows(0),
                                                                     m_columns(0), m_inserted_elements(0),
                                                                     m_default(default_value){
        if(n < 0 || m < 0){
            throw invalid_matrix_dimension_exception("Dimensione richiesta negativa");
        }

        if(m != 0 && n != 0 && std::numeric_limits<size_type>::max()/m < n){
            throw invalid_matrix_dimension_exception("Dimensione richiesta troppo grande");
        }
        m_columns = n;
        m_rows = m;
    }


    /**
     * @brief costruttore di copia
     * @param other l'oggetto da copiare
     * @post m_rows == other.m_rows
     * @post m_columns == other.m_columns
     * @post m_default == other.m_default
     */
    SparseMatrix(const SparseMatrix &other) : m_default(other.m_default), m_columns(other.m_columns),
                                              m_rows(other.m_rows), m_data(nullptr),
                                              m_inserted_elements(0) {
        node* temp = other.m_data;

        /* Dal momento che set chiamerà una new, devo gestire eventuali errori
        *  per riportare l'oggetto a uno stato coerente nel caso la copia non dovesse terminare correttamente.
        */
        try{
            while (temp != nullptr){
                set(temp->data.m_i, temp->data.m_j, temp->data.m_value);
                temp = temp->next;
            }
        }catch(...){
            destroy_matrix();
            throw;
        }
    }

    /**
     * @brief Distruttore
     */
    ~SparseMatrix() {
        destroy_matrix();
    }

    /**
     * @brief Operatore di assegnamento
     * @param other Reference all'oggetto da assegnare
     * @return Reference all'oggetto assegnato
     */
    SparseMatrix& operator=(const SparseMatrix &other) {
        if (this != &other){
            SparseMatrix temp(other);
            std::swap(m_data, temp.m_data);
            std::swap(m_columns, temp.m_columns);
            std::swap(m_rows, temp.m_rows);
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
    void set(size_type i, size_type j, const T &data){
        if(i > m_columns || j > m_rows || i < 0 || j < 0){
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
            found->data.m_value = data;
        }
    }

    /**
     * @brief operatore per ottenere il valore alla posizione specificata
     * @param i indice della riga
     * @param j indice della colonna
     * @return il reference costante alla posizione specificata se esiste, il valore di default altrimenti
     */

    const T& operator()(size_type i, size_type j) const {
        if (i >= m_columns || j >= m_rows || i < 0 || j < 0){
            throw matrix_out_of_bounds_exception("Gli indici specificati non rientrano nei limiti di dimensione della matrice.");
        }

        node *found = get_node(i, j);
        if(found == nullptr){
            return m_default;
        }

        return found->data.m_value;
    }

    /**
     * @brief getter per il numero di elementi inseriti
     * @return numero di elementi inseriti
     */

    size_type inserted_items() const {
        return m_inserted_elements;
    }


    /**
     * @brief getter per il numero di righe della matrice
     * @return numero di righe della matrice
     */
    size_type rows() const {
        return m_columns;
    }

    /**
     * @brief getter per il numero di colonne della matrice
     * @return numero di colonne della matrice
     */

    size_type columns() const {
        return m_rows;
    }

    /**
     * @brief getter per il numero di elementi inseriti
     * @return const reference al valore di default
     */

    const T& default_value() const {
        return m_default;
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


        /**
         * @brief costruttore di default
         */
        const_iterator() : ptr(nullptr) {}

        /**
         * @brief costruttore di copia
         * @param other l'iteratore da copiare
         */
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


        /**
         * @brief operatore di dereferenziamento
         * @return reference all'elemento puntato dall'iteratore
         */
        reference operator*() const {
            return ptr->data;
        }

        /**
         * @return puntatore all'elemento puntato dall'iteratore
         */
        pointer operator->() const {
            return &(ptr->data);
        }


        /**
         * @brief operatore di post incremento
         * @return l'iteratore allo stato antecedente la modifica
         */
        const_iterator operator++(int) {
            const_iterator temp = *this;
            temp.ptr = temp.ptr->next;
            return temp;
        }


        /**
         * @operatore di preincremento
         * @return l'iteratore al nuovo elemento
         */
        const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }


        /**
         * @param other l'iteratore da confrontare
         * @return true se this e other puntano allo stesso elemento
         */
        bool operator==(const const_iterator &other) const {
            return ptr == other.ptr;
        }

        /**
         * @param other l'iteratore da confrontare
         * @return false se this e other puntano allo stesso elemento
         */
        bool operator!=(const const_iterator &other) const {
            return ptr != other.ptr;
        }

    private:
        const node *ptr;


        friend class SparseMatrix;

        explicit const_iterator(const node *ptr) : ptr(ptr) {}

    };


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
        node(const node &other) : data(other.data), next(other.next) {}

        // Costruttore che prende in input gli indici e il dato da inserire.
        node(size_type i, size_type j, const T &data) : data(element(i, j, data)), next(nullptr){}

        // Distruttore. è vuoto perchè la distruzione dei nodi viene gestita dalla classe SparseMatrix e
        // la classe non è accessibile dall'esterno
        ~node(){}

        // Operatore di assegnamento.
        node& operator=(const node &other){
            if (this != &other){
                data = other.data;
                next = other.next;
            }
            return *this;
        }
    };


    // La matrice vera e propria
    node *m_data;

    // Gli attributi che memorizzano larghezza e altezza della matrice
    size_type m_rows;
    size_type m_columns;

    size_type m_inserted_elements;

    // Il valore di default nel caso venga richiesta una cella vuota
    T m_default;

    // Funzione di appoggio che cerca il puntatore a un elemento con indici (i, j) e lo ritorna se
    // esiste, nullptr altrimenti
    node* get_node(size_type i, size_type j) const {
        node* temp = m_data;
        while (temp != nullptr && (temp->data.m_i != i || temp->data.m_j != j)){
            temp = temp->next;
        }
        return temp;
    }

    void destroy_matrix(){
        node* it = m_data;
        while (it != nullptr){
            node* temp = it;
            it = it->next;
            delete temp;
        }

        // Riporto uno stato coerente

        m_columns = 0;
        m_rows = 0;
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
typename SparseMatrix<T>::size_type evaluate(const SparseMatrix<T> &M, Pred P){
    typename SparseMatrix<T>::size_type  result = 0;
    typename SparseMatrix<T>::const_iterator begin, end;
    for(begin = M.begin(), end = M.end(); begin != end; ++begin){
        if(P(begin->value())){
            ++result;
        }
    }
    if(P(M.default_value())){
        result += (M.rows() * M.columns() - M.inserted_items());
    }

    return result;
}

// Operatore utile per debug
template<typename T>
std::ostream& operator<<(std::ostream &stream, const SparseMatrix<T> &mat){
    typename SparseMatrix<T>::const_iterator it = mat.begin();
    stream << "{";
    while (it != mat.end()){
        stream << "(" << it->row() << ", " << it->column() << ") -> " << it->value();
        ++it;
        if(it != mat.end()){
            stream << "; ";
        }
    }
    stream << "}";
    return stream;
}

#endif // SPARSE_MATRIX_H
