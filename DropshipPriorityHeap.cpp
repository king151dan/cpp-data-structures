/*
* Name: Daniel Hinga, 
* Description: create a heap and a way to fix it
* Input:n/a
*Output: ship names according to priority
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

class dropship{
public:
    dropship(string n = randname(), int p = rand() % 20 + 1){
        id = count++;
        name = new string;
        *name = n;
        priority = p;
    }
    dropship operator=(dropship const &og){
        id = og.id;
        if(name == NULL)
            name = new string;
        *name = *og.name;
        priority = og.priority;
    }
    ~dropship(){
        delete name;
        name = NULL;
    }

    friend ostream & operator<< (ostream &out, const dropship *d){
        out << "Dropship #" << d->id << ", Carries: " << *d->name << " Priority " << d->priority;
        return out;
    }
    string *name;
    int priority;
private:
    static string randname(){
        string name = "";
        static const char str[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        for(int i = 0; i < 6; i++){
            name += str[rand() % 62];
        }
        return name + " squad!";
    }
    int id;
    static int count;
};

int dropship::count = 0;

void heapify(dropship **arr, int size, int index){
    int biggest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < size and arr[left]->priority < arr[biggest]->priority){
        biggest = left;
    }
    if(right < size and arr[right]->priority < arr[biggest]->priority){
        biggest = right;
    }
    if(biggest != index){
        swap(arr[index]->priority, arr[biggest]->priority);
        heapify(arr, size, biggest);
    }
}

void heapfix(dropship **arr, int size, int index){
    int parent = (index - 1) / 2;

    if(index == 0){
        return;
    }
    if(arr[index]->priority < arr[parent]->priority){
        swap(arr[index]->priority, arr[parent]->priority);
        heapfix(arr, size, parent);
    }
}


int main(){
    srand(time(0));
    cout << "Master Sergeant Farell: Itâ€™s a new day people. Destiny calls.\n"
         << "                         The world expects only one thing from us:\n"
         << "                         that we will win.\n" << endl;

    dropship* UDF[1002];
    for(int i=0; i<1000; i++){
        UDF[i] = new dropship;
    }
    UDF[1000] = NULL;
    UDF[1001] = NULL;

    dropship j("J SQUAD", 1);
    dropship fmb("Full Metal B***h!",1);
    cout << &j << endl;
    cout << &fmb << endl;

    //My code automatically assign a priority to each dropship randomly: 1-20
    for(int i=0; i<1000; i++){
        cout << UDF[i] << endl;
    }

    //Heapify the array.
    //Your Code Here
    for(int i = (1000/2)-1 ; i >= 0; i--){
        heapify(UDF, 1000, i);
    }

    //Insert the two VIP squads.
    UDF[1000] = &j;
    //Fix Heap after insertion of J SQUAD.
    //Your Code Here
    heapfix(UDF,1001,1000);

    UDF[1001] = &fmb;
    //Fix Heap after insertion of FMB.
    //Your Code Here
    heapfix(UDF, 1002, 1001);

    //Now launch each ship by removing it from the heap. Print to screen as each ship launches.
    //e.g:  Launching Ship:
    //Your Code Here
    for(int i = 1002; i > 0; i--){
        dropship *temp = UDF[0];
        cout << UDF[0] << endl;
        //take very last element of the tree move him to the root and heapify it from to the root
        temp = UDF[i-1];
        UDF[i-1] = UDF[0];
        UDF[0] = temp;
        heapify(UDF, i - 1, 0);
    }


    cout << "Master Sergeant Farell: Itâ€™s alright to be scared.\n"
         << "There is no courage without fear." << endl;

    //De-allocate to avoid memory leaks.
    //Your Code Here
    //  delete [] UDF;
    for (int i = 1002; i >= 0; i--) {
        delete UDF[i];
    }

    return 0;
}
