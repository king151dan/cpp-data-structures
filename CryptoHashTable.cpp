/*
Name: Daniel Hinga, 
Description:program will open and read (use filestreams) two files and output text to the stdout (screen).
Input: The name of the files will be given by the command line as the second argument and third argument
Output: text to the stdout (screen).
*/


#include<iostream>  //cin, cout
#include<cmath>     //pow
#include<fstream>   //filestreams
#include<string>    //strings
using namespace std;

struct hashNode;
//typedef hashNode * hashNodePtr;

struct hashNode{ //Node to store data in linked list
    int password;
    string username;
    hashNode *next;
};

class cryptohashtable {
public:
    cryptohashtable(int size=23){ //Constructor
        htable = new hashNode*[size]; //Array of pointers :D
        for(int i=0;i<size;i++){
            htable[i] = NULL;
        }
        this->size = size;
    }

    ~cryptohashtable(){ //Destructor
        // Your Code Here

        // Declare variables
        hashNode* temp;

        // Loop to linearly go through the hash table
        for (int i = 0; i < size; i++){
            // Make sures an element is present
            if (htable[i] != NULL){
                // Loop to clear htable[i]
                do{

                    temp = htable[i] -> next;

                    delete htable[i];
                    htable[i] = temp;

                }while (temp != NULL);

                // Clear temp
                delete temp;
                temp = NULL;
            }

            // Clear htable[i]
            delete htable[i];
            htable[i] = NULL;
        }

        // Clear htable
        delete[] htable;
        htable = NULL;
    }

    cryptohashtable(const cryptohashtable &h2){ //Copy constructor
        size = h2.size;
        htable = htable; //Shallow Copy
    }

    void printTable(){ //Prints table out nicely
        for(int i=0;i<size;i++) {
            cout << "Index " << i << ":";
            printChain(htable[i]);
            cout << "." << endl;
        }
        cout << endl;
    }

    void printChain(hashNode* entry){
        if(entry != NULL){
            cout << " " << entry->username << " (" << entry->password << ")";
            printChain(entry->next);
        }
    }

    int hashFunction(int x){
        //h(x) = x mod 23
        //Normal Modulus is ok
        //Your Code Here
       // int temp = x % 23;
        return (x % 23);
    }

    int hashPassword(string p){ //plaintext->hash
        //g(m) = m^e mod n
        //g(m) = m^7 mod 80543327

        //Used for the HashPassword
        const int n = 80543327;

        //First convert string to a number:
        double m = 0;
        for(int i=0; i<p.length();i++){
            m += p[i];
        }

        //Now Compute m^7;
        m = pow(m,7); //loses precision but we kinda have to in order to keep it simple and just use a double
        //Next compute the mod n. For this we use math function fmod(double, double) since % is only for integers.
        if(m < 0){
            m = -m;
        } //fixes any overflows
        return fmod(m,n);
    }

    bool authenticate(string usr, string pass){
        //Your Code Here

        int HshPassword = hashPassword(pass);
        hashNode* curr;

        // Loop to search for member linearly
        for (int i = 0; i < size; i++){
            curr = htable[i];

            // Checks if htable at i is present
            if (curr != NULL){
                // Loop to check if the member is present at the linked list at htable[i]
                do{
                    // Checks if it finds the equal member
                    if (curr -> password == HshPassword && curr -> username == usr){
                        curr = NULL;
                        delete curr;
                        return true;
                    }

                    curr = curr -> next;
                }
                while (curr != NULL);
            }
        }

        // Clear memory space used by curr
        curr = NULL;
        delete curr;

        return false;
    }

    bool authenticatedelete(string usr, string pass){
        //Your Code Here
        //Delete Node:
        //Tips: Check if it's first item, if so check if it is only item, or if there are items after
        //Otherwise check if its middle element or last element.

        // Declare variables
        int HshPassword = hashPassword(pass);

        // Loop to search for member linearly
        for (int i = 0; i < size; i++){
            // Checks if htable at i is present
            if (htable[i] != NULL){
                // Checks if the member is the first element
                if (htable[i] -> password == HshPassword && htable[i] -> username == usr){
                    // Checks if it's the only element
                    if (htable[i] -> next == NULL){
                        delete htable[i];
                        htable[i] = NULL;
                    }else{
                        // Creates a temp pointer to store the next element of htable[i]
                        hashNode *temp = htable[i] -> next;

                        delete htable[i];
                        htable[i] = temp;
                    }

                    return true;
                }else {
                    // Not the first element of htable[i]

                    // Creates a curr pointer for searching through htable[i]
                    hashNode *curr = htable[i];

                    // Loop to check if it's present in htable[i]
                    do{
                        // Make sures there's another element, else exit the loop
                        if (curr -> next == NULL){
                            break;
                        }
                            // The next element is the element for deletion
                        else if (curr -> next -> password == HshPassword && curr -> next -> username == usr){
                            // Checks if it's the last element in htable
                            if (curr -> next -> next == NULL){
                                delete (curr -> next);
                                htable[i] -> next = NULL;
                            }
                            else{
                                // Creates a temp pointer to store the next element of curr
                                hashNode *temp = curr -> next -> next;

                                delete (curr -> next);
                                curr -> next = temp;
                            }

                            return true;
                        }

                        curr = curr -> next;
                    }
                    while (curr != NULL);
                }
            }
        }

        return false;

    }

    void plaintext_insert(string usr, string pass){
        //Your Code Here

        // Declare variables
        int HshPassword = hashPassword(pass), location = hashFunction(HshPassword);

        // Create a temp pointer for the hashNode
        hashNode* temp = new hashNode;

        temp -> password = HshPassword;

        temp -> username = usr;

        // Checks if htable at location is empty
        if (htable[location] == NULL){

            temp -> next = NULL;
        }

        else{
            // Insert as first element of htable at location and points to the previous first element
            temp -> next = htable[location];
        }
        htable[location] = temp;
    }

private:
    hashNode** htable;
    int size;

};

//Client Code
int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "Usage: " << argv[0] << " inputFileName searchFileName" << endl;
        return 0;
    }
    cryptohashtable *HashTable = new cryptohashtable(23); //create our hash table
    string user, pass, mode;
    ifstream inf;
    //First we will insert to hash table. (input file)
    inf.open(argv[1]);
    while(inf >> user >> pass){ //Read Username //Read Password in plaintext
        HashTable->plaintext_insert(user, pass);
    }
    inf.close();
    cout << "\nCrypto Hash Table" << endl;
    HashTable->printTable(); //Print our beautiful table :)
    //Next let's query it with some search and delete (search file)
    inf.open(argv[2]);
    while(inf >> user >> pass >> mode){ //Read Username //Read Password in plaintext
        cout << "Searching for '" << user << "'... ";
        if(mode == "s"){
            if(HashTable->authenticate(user, pass)){
                cout << "Found! AUTHENTICATED." << endl;
            }
            else {
                cout << "Not found! ACCESS DENIED." << endl;
            }

        }
        else if(mode == "d"){
            if(HashTable->authenticatedelete(user, pass)){
                cout << "Found! DELETED." << endl;
            }
            else {
                cout << "Not found! NO CHANGES." << endl;
            }

        }
        else{
            cout << "Error: Invalid Argument. Must Enter 's' or 'd'" <<endl;
        }
    }
    inf.close();
    cout << "\nPost Query Crypto Hash Table" << endl;
    HashTable->printTable(); //Print our beautiful table :)

    return 0;
}