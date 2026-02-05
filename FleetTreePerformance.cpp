/*
Name: Daniel Hinga, 
Description:create binary tree and avl tree
Input: linux redirection of the shipsname txt binaryTree standard or binaryTree AVL
Output: output hte ships in a certain order
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

//return 0 for equal, -1 for a being less and 1 for b being less.
template <class T>
int compare1(const T& a, const T& b){

    if( a == b) return 0;
    int min = a.length() <= b.length() ? a.length() : b.length(); //min function
    int i;
    for(i=0; i < min; i++){
        if(isdigit(a[i]) || isdigit(b[i])) break;
        if(tolower(a[i]) < tolower(b[i])) return -1;
        if(tolower(a[i]) > tolower(b[i])) return 1;
        if(tolower(a[i]) == tolower(b[i])) continue;
        cout << "wat" << endl;
    }
    if(isdigit(a[i]) && !isdigit(b[i])) return -1;
    if(!isdigit(a[i]) && isdigit(b[i])) return 1;
    if(!isdigit(a[i]) && !isdigit(b[i])) cout << "We dun gufd"<< endl;

    //Copy numbers to their own strings:
    string anum = "";
    string bnum = "";
    for(int j=i; j < a.length(); j++){
        anum += a[j];
    }
    for(int j=i; j < b.length(); j++){
        bnum += b[j];
    }
    //convert em to ints
    int numa = stoi(anum);
    int numb = stoi(bnum);

    if(numa < numb) return -1;
    if(numa > numb) return 1;
    if(numa == numb) return 0;

    return 42; // we dun guffd

    //return (a == b) ? 0 : ((a < b) ? -1 : 1);
}

template < class T>
class node {
public:
    //Your Code Here: Default Constructor
    node(){
        data = NULL;// makes a new data T
        left = NULL;// sets left to null
        right = NULL;// sets the right to null
    }

    node(const T var) : left(NULL), right(NULL) {
        data = new T;//m makes a  new  object data T
        *data = var;// copies var
    }

    //Your Code Here for Destructor
    ~node(){
        if(data != NULL){
            delete data;
            data = NULL;
        }
    }

    //Your Code Here to Overlaod Copy Constructor so you can make a node(node)
    node(const node& temp){
        // makes a new data T
        data = new T;
        //makes a  deep copy of data
        *data = *(temp.data);
        //copies left
        this->left = temp.left;
        //copies right
        this->right = temp.right;

    }

    //Your Code Here for Assignment Operator Overload to assign node to a node  (Part of Rule of 3)
    const node & operator=(const node& temp){

        *data = *(temp.data);
        // makes a deep copy of temp data
        this->left =temp.left;
        //copies the left side
        this->right=temp.right;
        // copies the right side

    }

    void operator=(const T &var){  //Assignment Operator Overload to take literals
        *data = var; //copies the data of var
    }

    void setData(T var) {
        *data = var;//sets the data
    }

    T getData() const {
        //Your Code Here
        return *data;//returns the data
    }

    friend std::ostream& operator<<(std::ostream& out, const node& n){
        out << *n.data;
        return out;
    }

    //Your Code Here for >> operator overloading to read into n.data of a node&n. Make it inline
    friend std::istream& operator>>(std::istream& in, const node& n){
        in >> *n.data;// overloads the instream
    }

protected:
    int height;
    T    *data;
    node *left;
    node *right;
    template <class U> friend class BinaryTree; //<--Don't you dare to @#$%$ touch this.
};

template <class T>
class BinaryTree{
public:
    BinaryTree() : root(NULL), count(0), rotations(0), size(0){}

    virtual ~BinaryTree(){                //Destructor                    (Part of Rule of 3)
#ifdef DEBUG
        cout << "De-allocating Tree here" << endl;
#endif
        DeleteTree(&root);
        root = NULL;
    }

    BinaryTree(const BinaryTree &b2){     //Copy Constructor Overload     (Part of Rule of 3)
#ifdef DEBUG
        cout << "Manually copying tree in copy constructor" << endl;
#endif
        //Your Code Here (Should call copyTree)
        copyTree(b2.root, &root);
    }

    int copyTree(node<T>* currOG, node<T>** currNEW){
        //Your Code Here
        if(currOG == NULL){
            *currNEW = NULL;// this will create a new tree
            return 0;
        }
        else{
            *currNEW = new node<T> (*currOG->data);// makes a  new node
            int temp = copyTree(currOG->left,&((*currNEW)->left));// will copy the left side of tree recursively
            int temp1 =copyTree(currOG->right,&((*currNEW)->right));// will copy the right side of the tree recursively
            return temp + temp1; // adds temp and temp1 and returns it
        }

    }

    node<T> *&getRoot(){
        return root;
    }

    //overload | operator to act as mirror :D
    BinaryTree operator|(const BinaryTree& OG){
#ifdef DEBUG
        cout << "Mirroring Tree!" << endl;
#endif
        if(OG.root == NULL) return OG;
        DeleteTree(&root);
        this->root = NULL;
        this->size = mirrorTree(OG.root, &(this->root));
        return OG;
    }

    int mirrorTree(node<T>* currOG, node<T>** currNEW){
        //Your Code Here
        int temp = 0;
        int temp1 = 0;
        if(currOG == NULL)// checks if the node currOG  NULL
        {
            *currNEW = NULL;// this will create a new tree
            return 0;
        }
        else
        {
            *currNEW = new node<T> (*currOG->data);// makes a  new node
            int temp = mirrorTree(currOG->left,&((*currNEW)->right));//will copy the tree recursively but flipped like a mirror
            int temp1 = mirrorTree(currOG->right,&((*currNEW)->left));//will copy  the tree recursively
            return temp + temp1; // adds the  temp and temp1 and returns it
        }

    }

    void operator=(const BinaryTree &b2){ //Assignment Operator Overload  (Part of Rule of 3)
#ifdef DEBUG
        cout << "Manually copy tree in assignment operator" << endl;
#endif
        DeleteTree(&root);
        this->root = NULL;
        this->size = copyTree(b2.root, &(this->root));
    }

    void readnGenerate(const T a[], int arr_size){
        if(arr_size <= 0) return; //empty
#ifdef DEBUG
        cout << "Generating From: '" << a << "'\nOG Length: 00" << arr_size << endl;
#endif
        DeleteTree(&root);
        this->size = recInsert(a, arr_size, &root, 1);
#ifdef DEBUG
        cout << "Total Inserted: "  << this->size << endl;
#endif

    }

    int recInsert(const T *a, int arrSize, node<T>**curr, int currIndex){
        //Your Code Here
        int x = 0;
        int temp = currIndex-1;// temp value so that we get the index bfore

        if(temp == 0)// check if the indes is 0
        {
            x= 0;//gives x th value of 0
        }
        if (temp >= arrSize)//checks if the temp value is bigger than the size if it is return x
        {
            return x;//return x
        }
        if(a[temp] == '%')
        {
            *curr = new node<T>('\0');// makes a new node of 0
        }
        else
        {
            *curr = new node<T>(a[temp]);// makes a new object if T array
            x++;
        }
        x += recInsert(a, arrSize, &(*curr)->left, currIndex * 2);// recursively calls the recinsert functiom
        x += recInsert(a, arrSize, &(*curr)->right, currIndex * 2 + 1); 		// recursively calls the recinsert functiom
        return x;
    }

    void genFromINandPRE(const T *preOrderArray,const T *inOrderArray, int level, int arrSize, node<T> **curr)
    {
        int i = level;
        static int temp;
        static int temp1;
        //static int x = level ;

        if(temp1 == 0)//checks if it is 0
        {
            DeleteTree(&root);// delete root
            temp1++;//increment temp1
        }
        if(level >= arrSize)
        {
            return;
        }
        while( i < arrSize)
        {
            if(inOrderArray[i] == preOrderArray[temp])
            {
                *curr = new node<T>(preOrderArray[temp]);
                temp++;
                break;
            }
            i++;
        }
        genFromINandPRE(preOrderArray, inOrderArray, level, i, &(*curr)->left);
        genFromINandPRE(preOrderArray, inOrderArray, i+1, arrSize, &(*curr)->right);

    }

    void genFromINandPOST(const T *postOrderArray,const T *inOrderArray, int level,int arrSize, node<T> **curr)
    {
        int i = arrSize-1;
        static int index = arrSize-1;
        static int  temp1 = 0;
        // static int x = 0 ;

        //genFromINandPOST(inOrderArray, postOrderArray, level, i, &(*curr)->left);
        //genFromINandPOST(inOrderArray, postOrderArray, i+1, arrSize, &(*curr)->right);
        if(level >= arrSize)
        {
            //     cout << " boom "<< endl;
            return;
        }

        if(temp1 == 0)//checks if it is 0
        {
            //       cout << " hi " << endl;
            DeleteTree(&root);// delete root
            temp1++;//increment temp1
        }
        /*if(level >= arrSize)
        {
                cout << " boom "<< endl;
		return;
        }*/
        //genFromINandPOST(inOrderArray, postOrderArray, level, i, &(*curr)->right);
        //genFromINandPOST(inOrderArray, postOrderArray, i+1, arrSize-1, &(*curr)->left);
        // for( i = arrSize-1 ; i >= level ; i--)
        //{
        while( i >= level)
        {
            if(postOrderArray[index] == inOrderArray[i])
            {
                //cout << " bammmm " << endl;
                *curr = new node<T>(postOrderArray[index]);
                index--;
                break;
            }
            i--;
        }
        //cout << " great" << endl;
        genFromINandPOST(postOrderArray, inOrderArray, i+1, arrSize, &(*curr)->right);
        //cout << " amazing " << endl;
        genFromINandPOST(postOrderArray, inOrderArray, level, i, &(*curr)->left);
        //genFromINandPOST(inOrderArray, postOrderArray, i-1, arrSize, &(*curr)->right);

        //cout  << " good bye " << endl;
    }

    void BinaryTree_Insert(node<T> *&curr, T *data) { // curr is the root, data is the ships

        if(curr == NULL){

            (curr) = new node<T>;
            (curr)->data = data;
        }
        else if(compare1(data->getName(), curr->data->getName()) == -1){
            BinaryTree_Insert(curr->left, data);
            count++;
        }
        else{
            BinaryTree_Insert(curr->right, data);
            //count++;
        }
        //  cout << "comparisons = " << count<< endl;
    }

    // difference between left and right children
    int Balance(node<T> *curr){
        if(curr == NULL){
            return 0;
        }
        else {
            return getHeight(curr->left) - getHeight(curr->right);//if the total is 0 then its balance
        }
    }

    int maxreturning(int a , int b){
        int temp;
        if(a > b){
            temp = a;
        }
        else if (a < b){
            temp = b;
        }
        return temp ;
    }

    node<T> *rightRotate(node<T> *curr){
        //right rotate
        node<T> *temp = curr->left;
        node<T> *swap = temp->right;

        temp->right = curr;
        curr->left = swap;
        rotations++;
        return temp;
    }

    node<T> *leftRotate(node<T> *curr)  {
        //left rotate
        node<T> *temp = curr->right;
        node<T> *swap = temp->left;

        temp->left = curr;
        curr->right = swap;
        rotations++;
        return temp;
    }

    void BST_AVL_insert(T* data){
        root = BST_AVL_insert(root, data);
    }

    node<T> *AVLtree(node<T> *&curr, T *data){
        if(curr == NULL){
            (curr) = new node<T>(*data);
        }
        else if(compare1(data->getName(), curr->data->getName()) == -1){
            curr->left=AVLtree(curr->left, data);
        }
        else{
            curr->right = AVLtree(curr->right, data);
        }

        if(Balance(curr) > 1 ){//left left rotation

            if (compare1(data->getName() , curr->left->data->getName()) == -1){
                count++;
                return rightRotate(curr);
            } else if (compare1(data->getName() , curr->left->data->getName()) == 1){
                count++;
                curr->left = leftRotate(curr->left);
                return rightRotate(curr);
            }
        }
        else if(Balance(curr) < -1 ){//right right rotation
            if(compare1(data->getName() , curr->right->data->getName()) == 1){
                // count++;
                return leftRotate(curr);
            } else if (compare1(data->getName() , curr->right->data->getName()) == -1){//right left case
                count++;
                curr->right = rightRotate(curr->right);
                return leftRotate(curr);
            }
        }

        return curr;
    }

    void inOrderTraversal(node<T>* curr){
        //Your Code Here

        if(curr == NULL)// checks if curr is NULL if it is give it back to the root
        {
            curr = root;
        }
        if( curr == NULL)// if root is NULL return the value
        {
            return ;
        }
        //cout << *curr->data << "," << flush;// outputs the value
        if(curr->left != NULL)// checks if the left side is NULL if not  call the function recursively for the left side
        {
            inOrderTraversal(curr->left);
        }
        cout << curr->data->getName() << endl;// outputs the value
        if(curr->right != NULL)//checks if the left side is NULL if not  call the function recursively for the right side
        {
            //cout << *curr->data << "," << flush;
            inOrderTraversal(curr->right);
        }

    }

    void preOrderTraversal(node<T>* curr){
        //Your Code Here
        if(curr == NULL)// if curr is null copy the value of root
        {
            curr = root;
        }
        else if( curr == NULL)// if its still null then return
        {
            return ;
        }
        cout << *curr->data << flush;//out puts the value
        if(curr->left != NULL)// checks of the curr left is null
        {
            //cout << *curr->data << "," << flush;
            preOrderTraversal(curr->left);
        }
        if(curr->right != NULL)//checks if curr right is null
        {
            preOrderTraversal(curr->right);
        }
    }

    void postOrderTraversal(node<T>* curr){
        //Your Code Here
        if(curr == NULL)//checks if curr is NULL if it  copy the value of root
        {
            curr = root;
        }
        if( curr == NULL)// if it is null still return
        {
            return ;
        }
        //cout << *curr->data << "," << flush;
        if(curr->left != NULL)//checks if curr left is null
        {
            postOrderTraversal(curr->left);
        }
        //cout << *curr->data << "," << flush;
        if(curr->right != NULL)// checks if curr right is null
        {
            postOrderTraversal(curr->right);
            //cout << *curr->data << "," << flush;
        }
        cout << *curr->data << flush;// outputs the value of  curr data
    }

    int getHeight(node<T> *curr){
        //Compute Height of both subtrees and keep the larger one
        if(curr == NULL) return 0; //base case
        else{
            int lheight = getHeight(curr->left);
            int rheight = getHeight(curr->right);
            if  (lheight > rheight) return lheight+1;
            else return rheight+1;
        }
    }

    void printSpecificLevel(node<T> *root, int level){
        if(root == NULL) return;
        if(level == 1) cout << *root;
        else if(level > 1){
            printSpecificLevel(root->left, level-1);
            printSpecificLevel(root->right, level-1);
        }
    }

    void printLevelOrderTraversal(){
        for(int i=0; i <= getHeight(root); i++){
            //Your Code Here. Should be one line of code,
            //a fucntion call to printSpecificLevel with root and i as parameters
            printSpecificLevel(root,i);
        }
    }
    int rotationsc(){
        return rotations;
    }

    int counter(){
        return count;
    }

protected:
    int rotations ;
    int count;
    node<T> *root;
    int size;
private:
    void DeleteTree(node<T>** curr){
        //Your Code Here
        if(*curr == NULL)// checks if its null return
        {
            return;
        }
        else
        {
            DeleteTree(&((*curr)->left));// deletes the left side of the tree
            DeleteTree(&((*curr)->right));// deletes the right side of the tee
            delete *curr;//deletes curr pointer
            *curr = NULL;// sets curr to null
        }
    }
};

class RNGnamer{
public:
    RNGnamer(string filename = "shipnames.txt") : size(0){
        //Your Code Here:
        //oopen the file with shipnames.
        ifstream infile;
        infile.open(filename);

        string temp;// temporary string

        //Read the file once the end of it to count the number of ships.
        if(infile.is_open()){
            for(int i = 0; i < 3;i++)
            {
                getline(infile, filename);
            }
        }
        while(!infile.eof()){
            infile >> temp;// this will bring in the names of the ships
            names.push_back(temp);// this will keep count of how may ships there are
            size++;
        }

        //Close file.
        infile.close();


    }
    ~RNGnamer(){
        //Your Code Here:
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
    //void operator =(entity_t const &r)
    //{
    //  this->name = r.name;
    //this->id=r.id;
    //}
    string getName()
    {
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
    Xyston_class_StarDestroyer(){};
    Xyston_class_StarDestroyer(RNGnamer &temp){
        name = temp.generateName() + " # " + to_string(id);
    }
    void setNavSource(entity_t*);
    void printNavSource();
    string whatamI(){
        return "Xyston_class_StarDestroyer";
    }
    string name1;
    string name2;
private:
    entity_t* temp1;
};

void Xyston_class_StarDestroyer::setNavSource(entity_t* temp2){
    temp1 = temp2;
    name1=temp2->getName();
    name2=temp2->whatamI();
}

void Xyston_class_StarDestroyer::printNavSource(){
    cout << "Current Navigation Source is a" << " "
         << name2 << ":" << name1 << endl;
}

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
    string temp;
    RNGnamer nameList(argv[1]);
    int fleet_size = 10000;
    //srand(time(NULL));

    if(argc != 4){
        cout << "Error: Missing command line input" << endl;
        return 1;
    }
    else if(argc == 4){

        temp = argv[3];
        for(int i = 0; i < temp.size(); i++) {
            temp.at(i) = tolower(temp.at(i));
        }
        if(temp == "standard"){
            BinaryTree<Xyston_class_StarDestroyer> tree;
            node<Xyston_class_StarDestroyer> *temp;
            for(int i = 0; i < fleet_size; i++)
            {

                Xyston_class_StarDestroyer *temp1;
                temp1 = new Xyston_class_StarDestroyer(nameList);
                tree.BinaryTree_Insert(tree.getRoot(),temp1);


            }
            tree.inOrderTraversal(NULL);
            cout << "\n# of comparisons "<<tree.counter()<< endl;
            cout << "\n# of rotations "<<tree.rotationsc()<< endl;
        }
        if(temp == "avl" ){

            BinaryTree<Xyston_class_StarDestroyer> tree;
            node<Xyston_class_StarDestroyer> *temp;

            for(int i = 0; i < fleet_size; i++){

                Xyston_class_StarDestroyer temp1(nameList);
                tree.AVLtree(tree.getRoot(),&temp1);

            }
            tree.inOrderTraversal(NULL);
            cout << "\n# of comparisons "<<tree.counter()<< endl;
            cout << "\n# of rotations "<<tree.rotationsc()<< endl;

        }
        else{
            cout << " invalid input " << endl; }
    }
    // srand(time(NULL)); //Seed Rand!
    cout << "\n\nSimulation Terminated." << endl;
    return 0;
}

/*
int main(){
    //string temp;
    RNGnamer nameList("shipnames.txt");
    int fleet_size = 10000;


    BinaryTree<Xyston_class_StarDestroyer> tree;
    node<Xyston_class_StarDestroyer> *temp;

    for(int i = 0; i < fleet_size; i++){


        Xyston_class_StarDestroyer *temp1;
        temp1 = new Xyston_class_StarDestroyer(nameList);
        tree.BinaryTree_Insert(tree.getRoot(),temp1);
    }

    tree.inOrderTraversal(NULL);
    cout << "\n# of comparisons "<<tree.counter()<< endl;

    cout << "\n# of rotations "<<tree.rotationsc()<< endl;

    // srand(time(NULL)); //Seed Rand!
    cout << "\n\nSimulation Terminated." << endl;
    return 0;
}*/
