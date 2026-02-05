/*
Name: Daniel Hinga, 
Description:create a program that will simulate the fleet’s navigation
  system to be guided by either the local navigation tower or a Resurgent-class
  Star Destroyer as back-up *
Input: linux redirection of the shipsname txt with arays vectors and linked lists  *
Output: expected output of the program.
*/


//Build as: g++ ast01.cpp -g -std=c++17
//Execute as: ./a.out shipnames.txt
//Debug as: 'gdb a.out' and then type 'r shipnames.txt'
//Check for memory leaks with valgrind ./a.out shipnames.txt
#include <iostream> //cout
#include <fstream>  //ifstream
#include <cstdlib>  //rand()
#include <string>   //stringz
#include <vector> // vectors
#include <ctype.h>
using namespace std;

class RNGnamer{
public:
    RNGnamer(string filename = "shipnames.txt") : size(0) {
        //Your Code Here:
        ifstream infile;
        // temporary string to store anywords needed
        string temp;

        //Read the file once the end of it to count the number of ships.
        infile.open(filename);
        if (infile.is_open()) {
            for (int i = 0; i < 3; i++) {
                getline(infile, temp);
            }
        }
        // this will keep count of how may ships there are
        while ( getline(infile, temp)) {
            size++;
        }
        infile.close();

        //reopen file and now place it into the vector
        infile.open(filename);
        if (infile.is_open()) {
            for (int i = 0; i < 3; i++) {
                getline(infile, temp);
            }
        }
        for (int i = 0; i < size; i++) {
            //grab a line and store that line in vector
            getline(infile, temp);
            names.push_back(temp);
        }
        infile.close();

    }
    ~RNGnamer(){
    }

    void printAllPossibleNames(){
        cout << "All Possible Ship Names:" << endl;
        for(int i=0; i < size; i++){
            cout << i << ": " << names[i] << endl;
        }
        cout << endl;
    }

    string generateName(){
        return names[rand() % size];
    }

private:
    int size;
    vector<string> names;
};


class entity_t {
public:
    entity_t() : id(ent_cnt++){}
    //Your Code Here: Virtual Function whatamI() that returns a string
    virtual string whatamI()=0;
    //Your Code Here: function getName that returns a string with the name
    string getName(){
        return name;
    }
protected:
    //Your Code Here: static integer variable called ent_cnt that keeps track of how many entities there are
    static int ent_cnt;
    int id; //individual entity id
    string name;
};


//Your Code Here: Initalize ent_cnt static variable with 0.
int entity_t::ent_cnt = 0;

class navigation_tower : public entity_t{
public:
    navigation_tower(){
        name = "Exegol Navigation Tower #" + to_string(id);
    }
    string whatamI(){
        return "Navigation_Tower";
    }
};

//Your Code Here for the Xyston_class_StarDestroyer class that inherits from entity_t
//entity_t type pointer to create  navigation power class and resurgence class
class Xyston_class_StarDestroyer : public entity_t{
public:
    Xyston_class_StarDestroyer(RNGnamer& temp){
        name = temp.generateName() + " # " + to_string(id);
    }

    void setNavSource(entity_t* temp2){
        temp1 = temp2;
        name1=temp2->getName();
        name2=temp2->whatamI();
    }

    void printNavSource(){
        cout << "Current Navigation Source is a" << " "  << name2 << ":" << name1 << endl;
    }

    string whatamI(){
        return "Xyston_class_StarDestroyer";
    }

    string name1;
    string name2;
private:
    entity_t* temp1;
};


class Resurgent_class_StarDestroyer : public entity_t{
public:
    Resurgent_class_StarDestroyer(string name = "Capital Ship Steadfast") {
        this->name = name;
    }
    string whatamI(){
        return "Resurgent_StarDestroyer";
    }
};


class Linkedlist{
public:
    //node for link list
    struct Node{
        Xyston_class_StarDestroyer data;// to keep thr string data
        Node *next; // made an object pointer node for the linked list
        Node(Xyston_class_StarDestroyer ship): data(ship){
        }
    };

    Linkedlist(){
        head = NULL;
        current = head;
    }

    void generatelist(Xyston_class_StarDestroyer s){
        Node *temp;
        temp = new Node(s);

        temp->next = head;
        head = temp;
    }

    void listLoop(Xyston_class_StarDestroyer list){

        current->next = new Node(list);
        current = current->next;

    }


    ~Linkedlist(){
        //this will dealocate everything
        while(head != NULL){
            current = head;
            head = head->next;

            delete current;
            current = NULL;
        }
        delete head;
        head = NULL;
    }

    Node *current;
    Node *head;
};


int main(int argc, char **argv){
    string temp;
    RNGnamer nameList(argv[1]);
    int fleet_size = 10000;
    srand(time(NULL));

    if(argc != 3){
        cout << "Error: Missing command line input" << endl;
        return 1;
    }
    else if(argc == 3){

        temp = argv[2];

        for(int i = 0; i < temp.size(); i++) {
            temp.at(i) = tolower(temp.at(i));
        }

        if(temp == "vector" ){
            cout << "Vector "<< endl;
            Resurgent_class_StarDestroyer Steadfast_flagship;
            //Xyston_class_StarDestroyer Sith_Eternal_Fleet[fleet_size](nameList);
            vector<Xyston_class_StarDestroyer> Sith_Eternal_Fleet; //modified version for vector on how to declare an object
            for(int i=0; i < fleet_size; i++)
                Sith_Eternal_Fleet.push_back(Xyston_class_StarDestroyer(nameList));// using the push back function for vector to bring in the list of the names

            navigation_tower Exogol_Tower;

            cout << "\nAt last the work of generations is complete. "
                 << "The great error is corrected. The day of victory is at hand. "
                 << "The day of revenge. The day of the Sith.\n" << endl;

            for(int i = 0; i < fleet_size; ++i ){
                Sith_Eternal_Fleet[i].setNavSource(&Exogol_Tower);// modified version vector so that the fleet will be connected to the tower
            }

            // prints out every ships navi source to make sure pointing correctly
            cout << "Nav Source for fleet:" << endl;
            for (auto ship : Sith_Eternal_Fleet)
                ship.printNavSource();

            cout << "\nThe Resistance is targetting the Navigation Tower. "
                 << "Transfer the signal to the Steadfast. "
                 << "We'll guide the fleet ourselves." << endl;

            // printNavSource displays/prints what ship
            cout << "\nSwitching Nav Source to Steadfast." << endl;
            for(int i = 0; i < fleet_size; ++i ){
                Sith_Eternal_Fleet[i].setNavSource(&Steadfast_flagship);// modified version on traversing through the whole thing  instead of using the arrow  fucntion
                cout << Sith_Eternal_Fleet[i].getName() << ": ";
                Sith_Eternal_Fleet[i].printNavSource();
            }
            //for(int i=0; i < fleet_size; i++){
            //delete Sith_Eternal_Fleet[i];
            //Did you ever hear the tragedy of Darth Plagueis the wise?


        }
        else if(temp == "linked" ){
            cout << "linked list" << endl;
            Resurgent_class_StarDestroyer Steadfast_flagship;
            //Xyston_class_StarDestroyer Sith_Eternal_Fleet[fleet_size](nameList);
            Linkedlist  Sith_Eternal_Fleet;
            Sith_Eternal_Fleet.generatelist(Xyston_class_StarDestroyer(nameList));
            Sith_Eternal_Fleet.current = Sith_Eternal_Fleet.head;
            for(int i=0; i < fleet_size; i++)
                Sith_Eternal_Fleet.listLoop(Xyston_class_StarDestroyer(nameList));


            Sith_Eternal_Fleet.current->next = NULL;
            navigation_tower Exogol_Tower;

            cout << "\nAt last the work of generations is complete. "
                 << "The great error is corrected. The day of victory is at hand. "
                 << "The day of revenge. The day of the Sith.\n" << endl;



            // prints out every ships navi source to make sure pointing correctly
            cout << "Nav Source for fleet:" << endl;

            Sith_Eternal_Fleet.current = Sith_Eternal_Fleet.head;
            while(Sith_Eternal_Fleet.current != NULL)
            {
                //Sith_Eternal_Fleet.current = Sith_Eternal_Fleet.head;
                Sith_Eternal_Fleet.current->data.setNavSource(&Exogol_Tower);
                Sith_Eternal_Fleet.current->data.printNavSource();
                Sith_Eternal_Fleet.current = Sith_Eternal_Fleet.current->next;
            }


            cout << "\nThe Resistance is targetting the Navigation Tower. "
                 << "Transfer the signal to the Steadfast. "
                 << "We'll guide the fleet ourselves." << endl;

            // printNavSource displays/prints what ship
            Sith_Eternal_Fleet.current = Sith_Eternal_Fleet.head;
            cout << "\nSwitching Nav Source to Steadfast." << endl;
            while(Sith_Eternal_Fleet.current != NULL)
            {
                Sith_Eternal_Fleet.current->data.setNavSource(&Steadfast_flagship);
                cout << Sith_Eternal_Fleet.current->data.getName() << ": ";
                Sith_Eternal_Fleet.current->data.printNavSource();
                Sith_Eternal_Fleet.current = Sith_Eternal_Fleet.current->next;
            }

        }
        else if(temp == "array"){

            cout << " You picked Array" << endl;
            Resurgent_class_StarDestroyer Steadfast_flagship;

            Xyston_class_StarDestroyer *Sith_Eternal_Fleet[fleet_size];
            for(int i=0; i < fleet_size; i++)
                Sith_Eternal_Fleet[i] = new Xyston_class_StarDestroyer(nameList);

            navigation_tower Exogol_Tower;

            cout << "\nAt last the work of generations is complete. "
                 << "The great error is corrected. The day of victory is at hand. "
                 << "The day of revenge. The day of the Sith.\n" << endl;

            for(int i = 0; i < fleet_size; ++i ){
                Sith_Eternal_Fleet[i]->setNavSource(&Exogol_Tower);
            }

            // prints out every ships navi source to make sure pointing correctly
            cout << "Nav Source for fleet:" << endl;
            for (auto ship : Sith_Eternal_Fleet)
                ship->printNavSource();

            cout << "\nThe Resistance is targetting the Navigation Tower. "
                 << "Transfer the signal to the Steadfast. "
                 << "We'll guide the fleet ourselves." << endl;

            // printNavSource displays/prints what ship
            cout << "\nSwitching Nav Source to Steadfast." << endl;
            for(int i = 0; i < fleet_size; ++i ){
                Sith_Eternal_Fleet[i]->setNavSource(&Steadfast_flagship);
                cout << Sith_Eternal_Fleet[i]->getName() << ": ";
                Sith_Eternal_Fleet[i]->printNavSource();
            }
            for(int i=0; i < fleet_size; i++){
                delete Sith_Eternal_Fleet[i];
            } //Did you ever hear the tragedy of Darth Plagueis the wise?


        }
    }

    srand(time(NULL)); //Seed Rand!
    cout << "\n\nSimulation Terminated." << endl;
    return 0;
}
