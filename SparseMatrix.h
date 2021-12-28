#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

/**
 *
 * @file SparseMatrix.h
 */


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
    struct Node;
public:

    typedef unsigned long size_type;

    /**
     * @struct Struttura che contiene i dati relativi a un valore: riga, colonna e valore.\n
     * Viene ritornata dal const_iterator.
     */
    struct element{
        size_type m_i;
        size_type m_j;
        T data;

        element() : m_i(-1), m_j(-1) {}
        element(size_type i, size_type j, const T& data){
            m_i = i;
            m_j = j;
            this->data = data;
        }
        element(const element& other) : m_i(0), m_j(0) {
            data = other.data;
            m_i = other.m_i;
            m_j = other.m_j;
        }
        ~element(){}
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
     */

    SparseMatrix() : m_width(0), m_height(0), m_data(nullptr) {}
    SparseMatrix(size_type n, size_type m, const T& default_value) : m_data(nullptr), m_width(m), m_height(n), m_default(default_value){}

    /**
     * @brief Copy constructor
     * @param other Reference all'oggetto da copiare
     */


    //TODO: gestisci gli errori di memoria
    SparseMatrix(const SparseMatrix& other) : m_height(other.m_height), m_width(other.m_width), m_data(nullptr), m_default(other.m_default){
        Node* temp = other.m_data;
        while (temp != nullptr){
            set(temp->data.m_i, temp->data.m_j, temp->data.data);
            temp = temp->next;
        }
    }

    /**
     * @brief Distruttore
     */
    ~SparseMatrix() {
        Node* it = m_data;
        while (it != nullptr){
            Node* temp = it;
            it = it->next;
            delete temp;
        }
    }

    /**
     *
     * @param other Refernce all'oggetto da assegnare
     * @return Reference all'oggetto assegnato
     */
    SparseMatrix& operator=(const SparseMatrix<T>& other) {
        if (this != other){
            SparseMatrix temp(other);
            //TODO: controllare swap
            m_data = temp.m_data;
            m_height = temp.m_height;
            m_width = temp.m_width;
            m_default = temp.m_default;
        }
        return *this;
    }

    void set(size_type i, size_type j, const T& data){
        if(i > m_height || j > m_width || i < 0 || j < 0){
            return;
        }
        Node *found = get_node(i, j);
        if(found == nullptr){
            Node *new_node = new Node(i, j, data);
            new_node->next = m_data;
            m_data = new_node;
        }
        else {
            found->data.data = data;
        }
    }

    T& operator()(size_type i, size_type j) {
        if (i >= m_height || j >= m_width || i < 0 || j < 0){
            return m_default;
        }

        Node *found = get_node(i, j);
        if(found == nullptr){
            return m_default;
        }
        return found->data.data;
    }


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

        const Node *ptr;
        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class SparseMatrix;

        // Costruttore privato di inizializzazione usato dalla classe container
        // tipicamente nei metodi begin e end
        explicit const_iterator(const Node* ptr) : ptr(ptr) {}

        // !!! Eventuali altri metodi privati

    }; // classe const_iterator


    const_iterator begin() const {
        return const_iterator(m_data);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

private:



    struct Node{
        element data;
        Node *next;

        Node() : next(nullptr){}
        Node(const Node& other){
            data = other.data;
            next = other.next;
        }

        Node(size_type i, size_type j, const T& data) : data(element(i, j, data)), next(nullptr){}

        ~Node(){}

        Node& operator=(const Node& other){
            if (this != &other){
                Node temp = other;
                data = other.data;
                next = temp.next;
            }
            return *this;
        }
    };


    // La matrice vera e propria
    Node *m_data;

    // Gli attributi che memorizzano larghezza e altezza della matrice
    size_type m_width;
    size_type m_height;

    // Il valore di default nel caso venga richiesta una cella vuota
    T m_default;

    Node* get_node(size_type i, size_type j){
        Node* temp = m_data;
        while (temp != nullptr && temp->data.m_i != i && temp->data.m_j != j){
            temp = temp->next;
        }
        return temp;
    }

};


#endif // SPARSE_MATRIX_H
