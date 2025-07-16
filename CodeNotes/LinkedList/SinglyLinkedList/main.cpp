class MyLinkedList {
public:
    struct Node {
        int val;
        Node *next;
        Node(int value){
            val = value;
            next = nullptr;
        }
    };
    
    Node *head;
    
    MyLinkedList() {
        head = nullptr;
    }
    
    int get(int index) {
        // For an empty list
        if (head == nullptr) return -1;
        
        // Tracking the current node and
        // creating the counter
        Node *currNode = head;
        int counter = 0;
        
        // List traversal
        while (counter < index && currNode != nullptr) {
            currNode = currNode->next;
            counter++;
        }
        
        // Incase we make it to the end of the list
        if (currNode == nullptr) return -1;
        // Return the value at the index
        return currNode->val;
    }
    
    void addAtHead(int val) {
        // Conditions for adding at the head?

        // We take in the value to add

        // This new value will be the new head and the
        // next pointer will have to point the the prev
        // head

        // Lets start by creating that new head?
        // create the new head node
        Node *newHead = new Node(val);

        // Next have it point to the head
        newHead->next = head;
        
        // head ptr should equal this newly created
        // node
        head = newHead;
        
    }
    
    void addAtTail(int val) {
        // The condition for this is to traverse the whole list,
        // keeping track of the prev ptr?

        // No need to keep track of prev
        // We do need a currPtr
        Node *currPtr = head;

        // Conditions for an empty list?
        if(currPtr==nullptr){
            Node *newHead = new Node(val);
            head = newHead;            
        }
        // If not empty traverse
        else{
            while(currPtr->next!=nullptr){
                currPtr = currPtr->next;
            }
            Node *newNode = new Node(val);
            currPtr->next = newNode;
            newNode->next = nullptr;
        }
    }
    
    /*
    void addAtIndex(int index, int val) {
        // Traverse until we find the index?
        // When found add before the index'th position
        // example: index = 4; add before [0'th], [1'th], [2'th], [3'th], (add here), [4'th]

        // Variables
        Node    *currPtr = head,
                *prevPtr = head;
        int count = 1;
        // Empty list?
        if(currPtr==nullptr)
            cout << "List empty" << endl;
        else{
            // First start by finding the length of the list?
            // Feel like I can incorporate the else part of the statment
            // in this...
            while(currPtr->next!=nullptr){
                count++;
            }
            if(count==index)
                addAtTail(val);
            else if(index > count)
                cout << "Index greater than size of list, no insertion" << endl;
            else{
                // traverse the list
                while(currPtr->next!=nullptr && count<index){
                    prevPtr = currPtr;
                    currPtr = currPtr->next;
                    count++;
                }
                // After this loop the currPtr will be the index after insertion?
                Node *newNode = new Node(val);
                prevPtr->next = newNode;
                newNode->next = currPtr;
            }
        }

        

        // Condition for if index equals the length of the list,
        // append to the end


        // Condition if the index is greater than the length of the list

        // If the index isnt found 
    }
    
    */
    
    void addAtIndex(int index, int val) {
        // Case where index is less than 0..... ooookaaaayyyy
        if (index < 0) return;
        
        // If the value needs to be added to the front of the list
        // makes sense, totally missed this
        if (index == 0) {
            addAtHead(val);
            return;
        }
        
        // prevPtr is null instead of the head like you thought originally
        Node *currPtr = head;
        Node *prevPtr = nullptr;
        int counter = 0;
        
        // Traverse the list like you originally planned
        while (counter < index && currPtr != nullptr) {
            prevPtr = currPtr;
            currPtr = currPtr->next;
            counter++;
        }
        
        // && prevPtr != nullptr
        // takes care of an empty list
        if (counter == index && prevPtr != nullptr) {
            Node *newNode = new Node(val);
            prevPtr->next = newNode;
            newNode->next = currPtr;
        }
    }

    void deleteAtIndex(int index) {
        // create a counter variable
        // prev ptr and current pointer

        // traverse the list until you find the index
        // or reach the end

        // If currptr==nullptr && counter!=index
            // return
        // else
            // counter == index
            // prev ptr = cur ptr->next
            // that easy

        // ACTUAL CODE
        // empty list or invalid index
        if (index < 0 || head == nullptr) return;
        
        // If you have to delete the head, didnt think
        // about this tbh, you would need to redirect that
        // new head position
        if (index == 0) {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        // Now your thoughts, kinda
        Node *currPtr = head;
        Node *prevPtr = nullptr;
        int counter = 0;
        
        while (counter < index && currPtr != nullptr) {
            prevPtr = currPtr;
            currPtr = currPtr->next;
            counter++;
        }
        
        // Nothing happend in the case where the index is 
        // greater than the list....
        if (currPtr != nullptr && prevPtr != nullptr) {
            prevPtr->next = currPtr->next;
            delete currPtr;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
