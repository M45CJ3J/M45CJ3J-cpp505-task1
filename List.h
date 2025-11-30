#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>

struct Book {
    std::string title;
    std::string author;
    int version;
};

class List {
public:
    List();
    ~List();

    // Non-copyable for safety (simple rule of three)
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // classic linked-list API (adapted from original assignment)

    bool listIsEmpty() const;
    bool curIsEmpty() const;
    void toFirst();
    bool atFirst() const;
    void advance();
    void toEnd();
    bool atEnd() const;
    int  listSize() const;

    // get / update current node
    void updateData(const std::string &title, const std::string &author, int version);
    void retrieveData(std::string &title, std::string &author, int &version) const;
    void retrieveVersion(int &version) const;

    // insert operations (version treated as key)
    void insertFirst(const int &version, const std::string &title, const std::string &author);
    void insertAfter(const int &version, const std::string &title, const std::string &author);
    void insertBefore(const int &version, const std::string &title, const std::string &author);
    void insertEnd(const int &version, const std::string &title, const std::string &author);

    // delete
    void deleteNode(); 
    void deleteFirst();
    void deleteEnd();
    void makeListEmpty();

    // search / ordered insert
    bool search(const int &version);
    void orderInsert(const std::string &title, const std::string &author, const int &version);

    // traverse / utilities
    void traverse(std::ostream &os = std::cout) const;

    // exercises / algorithms
    int getMiddle();
    void reverse();
    bool Sortedlist();
    void selectionSort();
    void insertionSort();

    // recursion helpers
    int Recursive_List_Size() ;
    void DispalyList() ;

private:
    // internal node storing a book
    struct node
    {
        int key;               // version as key
        std::string dataTitle; // book title
        std::string dataAuthor;// book author
        node *next;
    };

    typedef node * NodePointer;

    // Pointers
    NodePointer head, cursor, prev;

    // recursion helpers
    int List_Size2( NodePointer h) ;
    void Display( NodePointer h);
};

#endif // LIST_H
