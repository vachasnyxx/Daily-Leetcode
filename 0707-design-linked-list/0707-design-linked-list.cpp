class Node {
public:
    int val;
    Node *next;
    Node(int val) {
        this->val = val;
        this->next = NULL;
    }
};

class MyLinkedList {
private:
    Node *head;
    Node *tail;
    int size;
    
public:
    MyLinkedList() {
        head = tail = NULL;
        size = 0;
    }
    
    int get(int index) {
        if(index < 0 || index >= size) {
            return -1;
        }
        else if(index == 0) return head->val;
        else if(index == size - 1) return tail->val;
        else {
            Node* temp = head;
            for(int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->val;
        }
    }
    
    void addAtHead(int val) {
        Node *temp = new Node(val);
        if (size == 0)
            head = tail = temp;
        else {
            temp->next = head;
            head = temp;
        }
        size++;
    }
    
    void addAtTail(int val) {
        Node *temp = new Node(val);
        if (size == 0)
            head = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index > size) {
            return;
        }
        else if(index == 0) addAtHead(val);
        else if(index == size) {
            addAtTail(val);
        }
        else {
            Node *t = new Node(val);
            Node* temp = head;
            for(int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            t->next = temp->next;
            temp->next = t;
            size++;
        }
    }
    
    void deleteAtIndex(int index) {
        if(size == 0 || index < 0 || index >= size) {
            return;
        }
        else if(index == 0) {
            // deleteAtHead
            head = head->next;
            if(size == 1) {
                tail = NULL;
            }
            size--;
        }
        else if(index == size - 1) {
            // deleteAtTail
            Node* temp = head;
            while(temp->next != tail) {
                temp = temp->next;
            }
            temp->next = NULL;
            tail = temp;
            size--;
        }
        else {
            Node* temp = head;
            for(int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            temp->next = temp->next->next;
            size--;
        }
    }
};