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
 * @tparam T Il tipo di dato da memorizzare all'interno della mtrice
 */

template<typename T>
class SparseMatrix {

public:
    /**
     * @typedef size_type
     * @brief Un wrapper per mascherare il vero tipo di dati che rappresenta la dimensione della matrice
     */
    typedef unsigned long size_type;


    /**
     * @brief Costruttore di default. Istanzia una matrice vuota e ha come dato di default il risultato del costruttore
     * di default del tipo T.
     */

    SparseMatrix() : m_width(0), m_height(0), m_data(nullptr), m_default(T()){
    }


    /**
     * @brief Copy constructor
     * @param other Reference all'oggetto da copiare
     */


    //TODO: gestisci gli errori di memoria
    SparseMatrix(const SparseMatrix<T>& other) : m_height(0), m_width(0), m_data(nullptr), m_default(T()){
        m_data = new T**[other.m_height];

        for (int i = 0; i < other.m_height; i++){
            m_data[i] = new T*[other.m_width];

            for(int j = 0; j < other.m_width; j++){
                if(other.m_data[i][j] != nullptr){
                    m_data[i][j] = new T(*other.m_data[i][j]);
                }
                else {
                    m_data[i][j] = nullptr;
                }
            }
        }

        m_height = other.m_height;
        m_width = other.m_width;
        m_default = other.m_default;
    }

    /**
     * @brief Distruttore
     */
    ~SparseMatrix() {
    }

    /**
     *
     * @param other Refernce all'oggetto da assegnare
     * @return Reference all'oggetto assegnato
     */
    SparseMatrix& operator=(const SparseMatrix<T>& other) {
        if (this != other){
            SparseMatrix<T> temp(other);
            //TODO: controllare swap
            m_data = temp.m_data;
            m_height = temp.m_height;
            m_width = temp.m_width;
            m_default = temp.m_default;
        }
        return *this;
    }

    void set(size_type i, size_type j){

    }

    struct element{
        size_type m_i;
        size_type m_j;
        T data;

        element() : m_i(-1), m_j(-1), data(T()) {}
        element() :
    };

private:



    // La matrice vera e propria
    element *m_data;

    // Gli attributi che memorizzano larghezza e altezza della matrice
    size_type m_width;
    size_type m_height;

    // Il valore di default nel caso venga richiesta una cella vuota
    T m_default;

};


#endif // SPARSE_MATRIX_H
