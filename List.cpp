#include "List.h"

using std::cout;

// Constructor / Destructor
List::List()
{
    head = nullptr; cursor = nullptr; prev = nullptr;
}

List::~List()
{
    makeListEmpty();
}

// Basic checks and movement
bool List::listIsEmpty() const { return head == nullptr; }
bool List::curIsEmpty() const { return cursor == nullptr; }

void List::toFirst()
{
    cursor = head; prev = nullptr;
}

bool List::atFirst() const { return (cursor == head); }

void List::advance()
{
    prev = cursor;
    if (cursor) cursor = cursor->next;
}

void List::toEnd()
{
    toFirst();
    if (!listIsEmpty())
        while (cursor->next != nullptr) advance();
}

bool List::atEnd() const
{
    if (listIsEmpty()) return true;
    else if (curIsEmpty()) return false;
    else return (cursor->next == nullptr);
}

// Size
int List::listSize() const
{
    NodePointer q = head;
    int count = 0;
    while (q != nullptr) { ++count; q = q->next; }
    return count;
}

// Update / retrieve
void List::updateData(const std::string &title, const std::string &author, int version)
{
    if (!cursor) throw std::logic_error("updateData: cursor is null");
    cursor->dataTitle = title;
    cursor->dataAuthor = author;
    cursor->key = version;
}

void List::retrieveData(std::string &title, std::string &author, int &version) const
{
    if (!cursor) throw std::logic_error("retrieveData: cursor is null");
    title = cursor->dataTitle;
    author = cursor->dataAuthor;
    version = cursor->key;
}

void List::retrieveVersion(int &version) const
{
    if (!cursor) throw std::logic_error("retrieveVersion: cursor is null");
    version = cursor->key;
}

// Insertions
void List::insertFirst(const int &k, const std::string &title, const std::string &author)
{
    NodePointer pnew = new node;
    pnew->key = k; pnew->dataTitle = title; pnew->dataAuthor = author;
    pnew->next = head;
    head = pnew;
    cursor = head;
    prev = nullptr;
}

void List::insertAfter(const int &k, const std::string &title, const std::string &author)
{
    if (curIsEmpty()) { // behave like insertEnd if cursor empty
        insertEnd(k, title, author);
        return;
    }
    NodePointer pnew = new node;
    pnew->key = k; pnew->dataTitle = title; pnew->dataAuthor = author;
    pnew->next = cursor->next;
    cursor->next = pnew;
    prev = cursor;
    cursor = pnew;
}

void List::insertBefore(const int &k, const std::string &title, const std::string &author)
{
    if (cursor == head || prev == nullptr) { // insert at head
        insertFirst(k, title, author);
        return;
    }
    NodePointer pnew = new node;
    pnew->key = k; pnew->dataTitle = title; pnew->dataAuthor = author;
    pnew->next = cursor;
    prev->next = pnew;
    cursor = pnew;
}

void List::insertEnd(const int &k, const std::string &title, const std::string &author)
{
    if (listIsEmpty()) insertFirst(k, title, author);
    else { toEnd(); insertAfter(k, title, author); }
}

// Deletion
void List::deleteNode()
{
    NodePointer q;
    if (!curIsEmpty()) {
        if (atFirst()) { // delete head
            q = cursor;
            cursor = cursor->next;
            head = cursor;
            delete q;
            prev = nullptr;
        } else {
            q = cursor;
            cursor = cursor->next;
            prev->next = cursor;
            delete q;
        }
    }
}

void List::deleteFirst()
{
    if (!listIsEmpty()) { toFirst(); deleteNode(); }
}

void List::deleteEnd()
{
    if (!listIsEmpty()) { toEnd(); deleteNode(); }
}

void List::makeListEmpty()
{
    toFirst();
    while (!listIsEmpty()) deleteNode();
}

// search
bool List::search(const int &k)
{
    bool found = false;
    toFirst();
    while ((!found) && (cursor != nullptr)) {
        if (k == cursor->key) found = true;
        else advance();
    }
    return found;
}

// ordered insert by key (version)
void List::orderInsert(const std::string &title, const std::string &author, const int &k)
{
    toFirst();
    while ((cursor != nullptr) && (k > cursor->key)) advance();
    if (prev == nullptr) insertFirst(k, title, author);
    else insertBefore(k, title, author);
}

// traverse
void List::traverse(std::ostream &os) const
{
    NodePointer p = head;
    while (p != nullptr) {
        os << p->dataTitle << " | " << p->dataAuthor << " | " << p->key << '\n';
        p = p->next;
    }
}

// exercises
int List::getMiddle()
{
    if (listIsEmpty()) return -1;
    NodePointer slow = head, fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->key;
}

void List::reverse()
{
    NodePointer next = nullptr;
    prev = nullptr;
    toFirst();
    while (!curIsEmpty()) {
        next = cursor->next;
        cursor->next = prev;
        prev = cursor;
        cursor = next;
    }
    head = prev;
    // reset cursor/prev
    cursor = nullptr; prev = nullptr;
}

bool List::Sortedlist()
{
    if (listIsEmpty()) return true;
    toFirst();
    while (cursor != nullptr && cursor->next != nullptr) {
        int a = cursor->key;
        advance();
        int b = cursor->key;
        if (a > b) return false;
    }
    return true;
}

// selection sort by key (version)
void List::selectionSort()
{
    node *p, *smallptr, *q;
    p = head;

    while (p != nullptr) {
        smallptr = p;
        int smallest = p->key;
        q = p->next;
        while (q != nullptr) {
            if (q->key < smallest) {
                smallptr = q;
                smallest = q->key;
            }
            q = q->next;
        }

        // swap data
        if (smallptr != p) {
            std::swap(smallptr->key, p->key);
            std::swap(smallptr->dataTitle, p->dataTitle);
            std::swap(smallptr->dataAuthor, p->dataAuthor);
        }
        p = p->next;
    }
}

// insertion sort by key (version) - rebuild a new ordered list
void List::insertionSort()
{
    if (head == nullptr || head->next == nullptr) return;

    node *sorted = nullptr; // new list
    node *current = head;

    while (current != nullptr) {
        node *next = current->next;

        // insert current into sorted list by key
        if (sorted == nullptr || current->key < sorted->key) {
            current->next = sorted;
            sorted = current;
        } else {
            node *it = sorted;
            while (it->next != nullptr && it->next->key <= current->key) it = it->next;
            current->next = it->next;
            it->next = current;
        }
        current = next;
    }

    head = sorted;
    cursor = nullptr; prev = nullptr;
}

// recursion helpers
int List::Recursive_List_Size()
{
    return List_Size2(head);
}

int List::List_Size2(NodePointer h)
{
    if (h == nullptr) return 0;
    return 1 + List_Size2(h->next);
}

void List::DispalyList()
{
    Display(head);
}

void List::Display(NodePointer h)
{
    if (h == nullptr) return;
    cout << h->key << " " << h->dataTitle << " " << h->dataAuthor << std::endl;
    Display(h->next);
}
