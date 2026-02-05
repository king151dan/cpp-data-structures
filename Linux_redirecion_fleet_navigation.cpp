/*
Name: Daniel Hinga, *
Description:create a program that will simulate the fleet’s navigation
  system to be guided by either the local navigation tower or a Resurgent-class
  Star Destroyer as back-up *
Input: linux redirection of the shipsname txt  *
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

using namespace std;

class RNGnamer{
public:
    RNGnamer(string filename = "shipnames.txt") : size(0){
        //Your Code Here:
        //Using filestream open the file with shipnames.
        string trashname;
        ifstream ifile;
while (filename != "shipnames.txt"){
  cout << "error wrong file opened, reenter file : shipnames.txt"<< endl;
  cin.clear();
  cin.ignore(100);
  cin >> filename;
}

        ifile.open(filename);
        //Read the file once the end of it to count the number of ships.
        if (ifile.is_open()){

            for (int i = 0; i < 3; i++) {
              getline(ifile, trashname);
            }
          //  getline(ifile, testname);
            while (getline(ifile, trashname)){
              //Keep that value in size class variable.
                size++;
            }
        }
        //Close file.
        ifile.close();

        //Use new to dynamically allocate an array of strings called names.
        //For the size use the number you just read into the size class variable.
        names = new string [size];

        //Open file again.
        ifile.open(filename);

        //Note that the first 3 lines will always be a header so you want to skip
                //them when reading into the array.
        for (int i = 0; i < 3; i++) {
          getline(ifile, trashname);
        }

        //Read in all ship names into the names array you just made.
        for (int i = 0; i < size; i++) {
        getline(ifile, names[i]);
        }

        //close file.
        ifile.close();

      cout << "\nTotal Number of Possible Ship Names Read: "<< size<< "\n"<<endl;
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


    ~RNGnamer(){
        //Your Code Here:
        delete [] names;
        names = NULL;
        //use delete to de-allocate your name array.
        //No memory leaks allowed or you will lose points.
    }

private:
    int size;
    string *names;
};

class entity_t {
public:
    entity_t() : id(ent_cnt++){}
    //Your Code Here: Virtual Function whatamI() that returns a string
    virtual string whatamI(){
      return "This is what i am";
    }
    //Your Code Here: function getName that returns a string with the name
    string getName(){
      return name;
    }
protected:
    //Your Code Here: static integer variable called ent_cnt that
    //keeps track of how many entities there are
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
class Xyston_class_StarDestroyer :public navigation_tower{
public:

  string name1; // to store what kind of ship it is
  string name2; // to store the name of the ship

//to store initial pointer to null
Xyston_class_StarDestroyer(){
entity = NULL;
}

//destructor to delete pointer and set it to null
//~Xyston_class_StarDestroyer(){
  //delete entity;
//entity = NULL;
//}

// passes a pointer of entity type
    void setNavSource(entity_t* temp){
      // sets poth pointer to point to the same adress
      entity = temp;
      // store name of the kind of ship
      name1=temp->getName();
      // to store the name of the ship
      name2=temp->whatamI();
    }

// print the name of the ship and the name of the kind of ship
    void printNavSource(){
  	cout << "Current Navigation Source is a " << name2
          << " : " << name1 << endl;
    }

// constructor that requires a variable from the RNGnamer to use its functions
    Xyston_class_StarDestroyer(RNGnamer& temp){
        name = temp.generateName() +" # "+ to_string(id);
       }

// returns the kind of ship it is
    string whatamI(){
        return "Xyston_StarDestroyer";
    }

  private:
  entity_t* entity;
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

int main(int argc, char **argv){
    if(argc != 2){
        cout << "Error: Missing shipnames.txt!" << endl;
        return 1;
    }
    srand (time(NULL)); //Seed Rand!
    RNGnamer nameList(argv[1]);
    int fleet_size = 10000;
//#define DEBUG
#ifdef DEBUG
    fleet_size = 10; //for small tests (sample output given is with this size)
#endif
    Resurgent_class_StarDestroyer Steadfast_flagship;
    //Xyston_class_StarDestroyer Sith_Eternal_Fleet[fleet_size](nameList); //old
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

    cout << "Nav Source for fleet:" << endl;
    for (auto ship : Sith_Eternal_Fleet)
        ship->printNavSource();

    cout << "\nThe Resistance is targetting the Navigation Tower. "
         << "Transfer the signal to the Steadfast. "
         << "We'll guide the fleet ourselves." << endl;

    cout << "\nSwitching Nav Source to Steadfast." << endl;
    for(int i = 0; i < fleet_size; ++i ){
        Sith_Eternal_Fleet[i]->setNavSource(&Steadfast_flagship);
        cout << Sith_Eternal_Fleet[i]->getName() << ": ";
        Sith_Eternal_Fleet[i]->printNavSource();
    }

    for(int i=0; i < fleet_size; i++){
        delete Sith_Eternal_Fleet[i];
    } //Did you ever hear the tragedy of Darth Plagueis the wise?

#ifdef DEBUG
    nameList.printAllPossibleNames(); //Test if read successfully.
    cout << "RNG Test: " << nameList.generateName() << endl; //Test RNG of names (should be different each run)
    cout << "RNG Test: " << nameList.generateName() << endl; //Test RRG of names (should be different each run)

    Xyston_class_StarDestroyer ship1(nameList);
    Xyston_class_StarDestroyer ship2(nameList);

    navigation_tower test_tower;
    Resurgent_class_StarDestroyer flagship;

    ship1.printNavSource(); //No Nav Set

    //ship1.setNavSource(dynamic_cast<entity_t*>(&test_tower));
    ship1.setNavSource(&test_tower);
    ship2.setNavSource(dynamic_cast<entity_t*>(&flagship));
    //ship2.setNavSource(&flagship);

    ship1.printNavSource();
    ship2.printNavSource();

#endif
    cout << "\n\nSimulation Terminated." << endl;
    return 0;
}
