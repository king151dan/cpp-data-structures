/*
*Name: Daniel Hinga,
*Description:program that creates an array of linked list queues and then
        executes it accordingly.
*Input: nothing
*Output: expected output of the program.
*/


#include <iostream>

using namespace std;

template<typename T>
struct node{
    T data;// created a char data
    node *next;// created an object on node that is a pointer
};


template<typename T>
class Linkedlist{
public:



    node<T> *head;
    node<T> *current;
    node<T> *temp;

    Linkedlist(){
        head = NULL;// sets head to Null
        temp = NULL;// sets temp to Null
        current = NULL;// sets current to Null;
    }


    ~Linkedlist(){
        int count = 0;
        while(head != NULL){
            count++;
            cout << count;
            if(head->next != head){
                temp = head;
                head = head->next;

                delete temp;
            }
            else{
                delete head;
                head = NULL;
            }
        }
    }


    void createNode(T data1){
        node<T> *temp1 = new node<T>;
        temp1->data = data1;
        temp1->next = NULL;
        if(head != NULL){


            current = head;
            if(current->next != NULL){
                current = current->next;
            }

            current->next = temp1;
        }
        else{
            head = temp1;
        }
    }


    void deletelist(){
        node<T> *temp1;
        node<T> *temp2;
        temp1 = head;
        while(head != NULL){
            temp=head->next;
            delete temp1;
            temp1 = temp2;
        }
        head = NULL;
    }


    void printLinkedlist(){

        current = head;
        while(current != NULL){
           cout << current->data << ",";
            current = current->next;
        }
        cout << endl;
    }
};


class queue{
public:
    queue(int siz ){
        size = siz;
        front = 0;
        back = 0;
        list = new Linkedlist<char>[size];
    }


    ~queue(){
            delete [] list;// deletes the array of list
            list = NULL;//sets it to null
    }


    void enqueue(Linkedlist<char> temp) {
        while(size <= back){
            list[back+1] = temp;// the item infront of back gets the linkedlist
            count++;
            back++;
        }
    }


    void dequeue(){
        cout << " This item is leaving the queue" << endl;
        list[front].printLinkedlist();// prints the front of the list before it leaves
        list[front].deletelist();// deletes the list
        front++;
    }




    void enqueue(int index, char temp){
        if(back < index){
            cout << " this index is empty please add something " << endl;

        }else{

            list[index].createNode(temp);
        }
    }


    void enqueuenext(int index,  char temp){
        list[index].createNode(temp);
    }


    void createcircularqueue(int tsize){
    size = tsize;
    list = new Linkedlist<char>[size];

    }

    void resizequeue(){
     int temp = 2 * size;
     back = temp;
    }

    void createqueue(){
        if(back == size){
            cout << " The line is full "<< endl;
            cout << back << endl;
        }
        back++;//incrememts back
        Linkedlist<char> newList;
        enqueue(newList);// makes a new linked list
    }


    void print(){
        cout << " Circular Queue Size: " << size << endl;
        for(int i = 0;i < size; i++){
            if(list[i].head == NULL){
                cout << " Index " << " Empty: "<<endl;
            }
            else{
                cout << "Index: " << i << ": ";
                list[i].printLinkedlist();
            }
        }
    }



    int size;
    int front;
    int back;
    int count;
    Linkedlist<char> *list;

};


int main()
{
    queue q(10);
    q.createcircularqueue(7);
    q.createqueue();
    q.enqueue(0, 'd');
    q.resizequeue();
    q.enqueuenext(1,  'a');
    q.enqueuenext(2, 'n');
    q.enqueuenext(3 ,'i');
    q.enqueuenext(4, 'e');
    q.enqueuenext(5 ,'l');
    q.print();

    return 0;
}
