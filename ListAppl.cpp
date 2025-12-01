#include <iostream>
#include "List.h"

int main()
{
    List books;

    // initial 4 books
    books.insertEnd(1, "cs504 book", "dr fatma ellithy");
    books.insertEnd(1, "cs505 book", "dr.haidy");
    books.insertEnd(1, "cs506 book", "dr.zainab");
    books.insertEnd(1, "cs507 book", "dr ashraf");

    std::cout << "Initial book list:\n"; 
    books.traverse();

    // Basic info
    std::cout << "\nSize: " << books.listSize() << " (recursive: " << books.Recursive_List_Size() << ")\n";
    std::cout << "Middle version: " << books.getMiddle() << "\n";

    // Insert a few more nodes to exercise insertFirst/After/Before
    books.insertFirst(0, "Intro book", "dr starter");
    books.toFirst(); books.advance(); // move cursor to second node
    books.insertAfter(5, "experimental book", "dr extra");
    books.toFirst(); books.advance(); books.advance(); // move cursor a bit
    books.insertBefore(2, "inserted before", "dr b");

    std::cout << "\nAfter some inserts:\n";
    books.traverse();

    // Search then delete a node
    if (books.search(5)) {
        std::cout << "\nFound node with version 5, deleting it...\n";
        books.deleteNode();
    }

    std::cout << "\nAfter delete (version 5 removed):\n";
    books.traverse();

    // Demonstrate deletion at ends
    books.deleteFirst();
    books.deleteEnd();
    std::cout << "\nAfter deleteFirst & deleteEnd:\n";
    books.traverse();

    // Add a few unordered nodes and sort
    books.insertEnd(9, "book9", "a");
    books.insertEnd(3, "book3", "b");
    books.insertEnd(7, "book7", "c");

    std::cout << "\nBefore selectionSort:\n";
    books.traverse();

    books.selectionSort();
    std::cout << "\nAfter selectionSort (by version):\n";
    books.traverse();

    // reverse
    books.reverse();
    std::cout << "\nAfter reverse:\n";
    books.traverse();

    // insertion sort then display result
    books.insertionSort();
    std::cout << "\nAfter insertionSort (by version):\n";
    books.traverse();

    std::cout << "\nIs sorted? " << (books.Sortedlist() ? "yes" : "no") << "\n";

    std::cout << "\nRecursive display (version title author):\n";
    books.DispalyList();

    // cleanup
    books.makeListEmpty();
    std::cout << "\nAfter makeListEmpty(): size=" << books.listSize() << "\n";

    return 0;
}
