// Gabriele Canesi
// Matricola 851637

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
 * @brief Classe che implementa una matrice sparsa.
 *
 * Questa classe permette di rappresentare delle matrici sparse minimizzando il quantitativo di memoria utilizzato.
 * Quando una cella della memoria è virtualmente vuota, viene ritornato un valore di default precedentemente passato al
 * costruttore. Nel costruttore di defaulr, questo valore corrisponde al valore di default del tipo generico.
 * */


/**
 * @tparam T Il tipo di dato da memorizzare all'interno della matrice
 */

template<typename T>
class SparseMatrix {
private:
    struct node;
public:

    /**
     * @typedef size_type
     * @brief Un wrapper per mascherare il vero tipo di dati che rappresenta la dimensione della matrice
     */
    typedef long size_type;

    /**
     * @brief Classe che contiene le informazioni sui valori inseriti nella SparseMatrix.
     */
    class element{
        // Faccio in modo che SparseMatrix sia in grado di accedere agli attributi privati di element
        friend class SparseMatrix;

        T m_value; ///< Il valore effettivo

        size_type m_i; ///< Il valore della riga in cui si trova l'elemento

        size_type m_j; ///< Il valore della colonna in cui si trova l'elemento



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
         * Costruttore di copia
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
     * @brief Costruttore di default. Istanzia una matrice vuota e ha come dato di default il valore
     * di default del tipo T.
     *
     * @post m_rows == 0
     * @post m_columns == 0
     * @post m_data == nullptr
     */

    SparseMatrix() : m_rows(0), m_columns(0), m_data(nullptr), m_inserted_elements(0), m_default() {}


    /**
     * @brief Costruttore che prende in input la dimensione della matrice e il valore di default.
     *
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

        // Devo catturare eventuali eccezioni per riportare la matrice allo stato precedente (distruggerla)
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
     * @brief Forward const_iterator per SparseMatrix.
     *
     * Questo iteratore visita gli elementi in ordine di inserimento, passando prima dagli elementi inseriti per ultimi.
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

        /**
         * @param other l'iteratore da copiare
         * @return reference al nuovo stato dell'iteratore
         */
        const_iterator& operator=(const const_iterator &other) {
            if(this != &other){
                ptr = other.ptr;
            }
            return *this;
        }


        /**
         * @brief Distruttore
         *
         * È vuoto perchè il ciclo di vita del nodo dipende da SparseMatrix.
         */
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


    /**
     * @brief Struttura che rappresenta un elemento fisico della SparseMatrix.
     *
     * Questa struttura è parte della lista concatenata
     */
    struct node{

        element data; ///< Informazioni sull'elemento inserito priva di puntatori interni alla SparseMatrix
        node *next; ///< Puntatore al nodo successivo


        /**
         * @brief Costruttore di default
         *
         * @post next == nullptr
         */
        node() : next(nullptr){}


        /**
         * @brief Costruttore di copia
         *
         * Questo costruttore non copia tutti gli elementi della lista, ma copia solo il valore del puntatore successivo.
         *
         * @param other il nodo da copiare
         */
        node(const node &other) : data(other.data), next(other.next) {}

        /**
         *
         * @param i La riga dell'elemento
         * @param j La colonna dell'elemento
         * @param data il valore effettivo
         */
        node(size_type i, size_type j, const T &data) : data(element(i, j, data)), next(nullptr){}

        /**
         * @brief Distruttore
         *
         */
        ~node(){}

        /**
         *
         * @param other il nodo da copiare
         * @return reference al nuovo stato del nodo.
         */
        node& operator=(const node &other){
            if (this != &other){
                data = other.data;
                next = other.next;
            }
            return *this;
        }
    };


    node *m_data; ///< Puntatore alla testa della lista di nodi

    size_type m_rows; ///< Numero di righe logiche della matrice
    size_type m_columns; ///< Numero di colonne logiche della matrice

    size_type m_inserted_elements; ///< Numero di elementi fisicamente inseriti nella matrice

    T m_default; ///< Valore di default


    /**
     * @brief funzione di appoggio per cercare un nodo partendo dalle coordinate.
     * @param i La riga da cercare
     * @param j La colonna da cercare
     * @return Il puntatore al nodo che contiene l'elemento (i, j) se esiste, nullptr altrimenti.
     */
    node* get_node(size_type i, size_type j) const {
        node* temp = m_data;
        while (temp != nullptr && (temp->data.m_i != i || temp->data.m_j != j)){
            temp = temp->next;
        }
        return temp;
    }

    /**
     * @brief funzione di appoggio per il distruttore
     *
     * Si occupa di distruggere tutti i nodi della matrice e di resettare i valori dei vari attributi.
     */
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
 * @brief Funzione che testa un predicato sugli elementi di una SparseMatrix.
 *
 * Questa funzione conta tutti gli elementi logici di una SparseMatrix generica che soddisfano un predicato generico
 * passato come argomento.
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
    typename SparseMatrix<T>::const_iterator begin;
    for(begin = M.begin(); begin != M.end(); ++begin){
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

#endif
