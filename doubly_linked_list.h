// Copyright 2016 Thomas Machado

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Uma classe
    /*!
    Descreve comportamento de uma lista duplamente encadeada
*/
template<typename T>
class DoublyLinkedList {
 public:
    //! Contrutor
    /*!
        Construtor default
    */
    DoublyLinkedList() {
        size_ = 0;
        head = nullptr;
    }

    //! Destrutor
    /*!
        Destrutor default
    */
    ~DoublyLinkedList() {
        clear();
    }

    //! Um método
    /*!
        Limpa a lista deletando todos os nodes
    */
    void clear() {
        Node* current = head;
        Node* previous;
        head = nullptr;
        size_ = 0;
        while (current != nullptr) {
            previous = current;
            current = current->next();
            delete previous;
        }
    }

    //! Um método
    /*!
        \param data
        Adiona elemento no fim da fila
    */
    void push_back(const T& data) {  // insere no fim
        insert(data, size_);
    }

    //! Um método
    /*!
        \param data
        Adiona elemento no início da fila
    */
    void push_front(const T& data) {  // insere no início
        Node* newNode = new Node(data, head);
        newNode->prev(nullptr);
        if (newNode == nullptr) {
            throw std::out_of_range("Full List");
        } else {
            head = newNode;
            if (newNode->next() != nullptr) {
                newNode->next()->prev(newNode);
            }
            size_ = size_ + 1;
        }
    }

    //! Um método
    /*!
        \param data
        \param index
        Adiona elemento na posição indicada por index
    */
    void insert(const T& data, std::size_t index) {  // insere na posição
        if (index < 0 || index > size_) {
            throw std::out_of_range("Out of bounds");
        } else if (index == 0) {
            push_front(data);
        } else {
            Node* newNode = new Node(data);
            if (newNode == nullptr) {
                throw std::out_of_range("Full list");
            }
            Node* current = head;
            for (int i = 0; i < index -1; ++i) {
                current = current->next();
            }
            newNode->next(current->next());
            if (newNode->next() != nullptr) {
                newNode->next()->prev(newNode);
            }
            current->next(newNode);
            newNode->prev(current);
            size_ = size_ + 1;
        }
    }

    //! Um método
    /*!
        \param data
        Adiona elemento em ordem crescente
    */
    void insert_sorted(const T& data) {   // insere em ordem
        Node* current;
        int position;
        if (empty()) {
            push_front(data);
        } else {
            current = head;
            position = 0;
            while (current->next() != nullptr && data > current->data()) {
                current = current->next();
                ++position;
            }
            if (data > current->data()) {
                return insert(data, position + 1);
            } else {
                return insert(data, position);
            }
        }
    }

     //! Um método
    /*!
        \param index
        \return T
        Retira elemento da posição index e o retorna
    */
    T pop(std::size_t index) {  // retira da posição
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (index < 0 || index > size_-1) {
            throw std::out_of_range("Out of bounds");
        } else if (index == 0) {
            return pop_front();
        } else {
            Node* deleteNode;
            Node* previous = head;
            for (int i = 0; i < index -1; ++i) {
                previous = previous->next();
            }
            deleteNode = previous->next();
            T back = deleteNode->data();
            previous->next(deleteNode->next());
            if (previous->next() != nullptr) {
                previous->next()->prev(previous);
            }
            delete deleteNode;
            size_ = size_ -1;
            return back;
        }
    }

    //! Um método
    /*!
        \param index
        \return T
        Retira elemento do fim da lista e o retorna
    */
    T pop_back() {  // retira do fim
        return pop(size_ -1);
    }

    //! Um método
    /*!
        \param index
        \return T
        Retira elemento do início da lista e o retorna
    */
    T pop_front() {  // retira do início
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else {
            Node* deleteNode = head;
            T back = deleteNode->data();
            head = head->next();
            if (head != nullptr) {
                head->prev(nullptr);
            }
            delete deleteNode;
            size_ = size_ -1;
            return back;
        }
    }

    //! Um método
    /*!
        \param data
        Retira elemento data da lista
    */
    void remove(const T& data)  {  // retira específico
        pop(find(data));
    }

    //! Um método constante
    /*!
        \return bool
        Indica se a lista está vazia ou não
    */
    bool empty() const {  // lista vazia
        return size_ == 0;
    }

    //! Um método constante
    /*!
        \param data
        \return bool
        Indica se a lista possui elemento data ou não
    */
    bool contains(const T& data) const {  // contém
        Node* current = head;
        while (current != nullptr) {
            if (current->data() == data) {
                return true;
            } else {
                current = current->next();
            }
        }
        return false;
    }

    //! Um método
    /*!
        \param index
        Acessa elemento na posição index
    */
    T& at(std::size_t index)  {  // acesso a um elemento (checando limites)
        if (index < 0 || index > size_ - 1) {
            throw std::out_of_range("Out of bounds");
        } else {
            size_t i = 0;
            Node* current = head;
            while (i < index) {
                current = current->next();
                ++i;
            }
            return current->data();
        }
    }
    //! Um método constante
    /*!
        \param index
        Acessa elemento na posição index
    */
    const T& at(std::size_t index) const {  // getter constante a um elemento
        return at(index);
    }

    //! Um método
    /*!
        \param data
        \return size_t
        Indica posição do elemento data
    */
    std::size_t find(const T& data) const {  // posição de um dado
        size_t i = 0;
        Node* current = head;
        while (current != nullptr) {
            if (current->data() == data) {
                return i;
            } else {
                current = current->next();
                ++i;
            }
        }
        return i;
    }

    //! Um método constante
    /*!
        \return size_t
        Indica posição tamanho da lista
    */
    std::size_t size() const {  // tamanho
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {  // setter: anterior
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head;
    std::size_t size_;
};

}  // namespace structures

#endif
