/*
The structure to each node of the list.
The constructor is one parameter and initializes
the val and sets both the next and prev pointer
to null
*/
struct ListNode {
    int val;
    ListNode* next;
    ListNode* prev;
    ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
};

/*
In a doubley linked list we need both the head and tail of the list.
This also includes the size of the list
*/
class MyLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;

public:
    MyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Get function that gets the value at a specific index
    int get(int index) {
        // Ensures the index is valid
        if (index < 0 || index >= size) return -1;
        // Our pointer for iterating through the list
        ListNode* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->val;
    }

    /*
    To add at the head the function takes in the val we are adding at 
    a specific node. A new node is then created and initialized with
    that value. If the list is empty, the newNode becomes both the head
    and the tail of the list. Else new node points to head, head prev points
    to the new node and finally newnode is the new head. Increment size.
    */
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    /*
    Same idea as above
    */
    void addAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    /*
    To add at a specific index, the function takes the index and the val. Ensure the index exists.
    Condition for if we are adding that the head. Condition for if we are adding at the tail. 
    Create a curr pointer to iterate through the list to get to the desired index. Then create 
    the newNode that we will be adding to the list. Since we are adding before the previous index
    newNode->next points to curr, newNode->prev points to curr->previous and so on. Relinking the
    nodes. Increment size
    */
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        if (index == 0) {
            addAtHead(val);
            return;
        }
        if (index == size) {
            addAtTail(val);
            return;
        }
        ListNode* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        ListNode* newNode = new ListNode(val);
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        ++size;
    }

    /*
    To delete a node, same condtions apply. Ensure the index exists.
    If the list only has one node delete it, head and tail set to nullptr.
    If the head is the node to delete with the list containing other node, create temp
    that points to head. The new head is the head->next. Delink head->prev. Then delete
    that "head" node through temp. Decrement the size.
    If its the last one, same method as if deleting head.
    If all the initial conditions fail we have a list with multiple values and the node is
    somewhere inbetween the list. Increment to it and then unlink the pieces.
    */
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        if (size == 1) {
            delete head;
            head = tail = nullptr;
            --size;
            return;
        }
        if (index == 0) {
            ListNode* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
            --size;
            return;
        }
        if (index == size - 1) {
            ListNode* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            --size;
            return;
        }
        ListNode* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        --size;
    }
};
