/*
* Name: Daniel Hinga, 
* Description: create a program that represents the entire enemy’s network as a graph where each mimic
 is a vertex and the connections between them are the edges with the weight representing the distance between them.
* Input:txt file or 3 arguments that specify the Alien Population and
 two numbers representing the range of the degree a node can have
*Output: printed graph 
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>


using namespace std;

class Graph{

public:
    enum Roles{Alpha,Omega,You,Drones};

    int ** array;

    int meNode;

    int omegaNode;

    int Vertex;

    vector<int> tempath;

    vector<int> savdpath;

    void visitCheck(){
        int pathsize = savdpath.size();
        bool *check = new bool[Vertex];

        for(int i = 0; Vertex > i; i++){

            check[i]= false;
        }

        DFS(meNode, check, omegaNode);

        cout << "Path to Omega is: ";

        for(int i = 0; pathsize > i; i++) {

            cout << savdpath[i] + 1 << ' ';
        }
        cout << endl;
    }

    void DFS(int visitor, bool *check, int destination){
        tempath.push_back(visitor);

        if (visitor == destination) {

            savdpath = tempath;
        }
        check[visitor] = true;

        for(int i = 0; Vertex > i; i++){

            if(!check[i] && array[visitor][i] != 0){

                DFS(i,check,omegaNode);
            }
        }
        tempath.pop_back();

        return;
    }

    void printGraph(){

        cout << "  ";
        for (int i = 0; i <= Vertex; i++) {
            cout << i << ' ';
        }
        cout << endl;

        for (int i = 0; i < Vertex; i++) {

            cout << i+1 << ' ';

            for (int j = 0; j < Vertex; j++) {

                if(array[i][j] == 0) {

                    cout << "  ";
                } else {

                    cout << array[i][j] << ' ';
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void calculateMST(Graph &pr){

        int mother[Vertex];

        int keyValue[Vertex];

        bool set[Vertex];

        for(int i = 0; i < Vertex; i++){

            keyValue[i] = INT_MAX;

            set[i] = false;
        }

        keyValue[0] = 0;
        mother[0] = -1;

        for(int j = 0; j < Vertex - 1; j++){

            int temp_key = minimum_Key(keyValue, set);

            set[temp_key] = true;

            for(int k = 0 ; k < Vertex ; k++){

                if(array[temp_key][k] && set[k] == false && array[temp_key][k] < keyValue[k]){

                    mother[k] = temp_key;

                    keyValue[k] = array[temp_key][k];
                }
            }
        }

        for (int i = 1; i < Vertex; i++){

            pr.array[mother[i]][i]=array[i][mother[i]];

            pr.array[i][mother[i]]=array[i][mother[i]];
        }
        pr.printGraph();

    }

    void makeMatrix(fstream& infile){

        string line;
        int start = 0;
        int end = 0;
        int weight = 0;

        while(getline(infile, line)) {

            stringstream in(line);
            in >> start;
            start--;

            while(in >> end) {

                end--;
                in >> weight;
                array[start][end] = weight;
                array[end][start] = weight;

            }
        }
    }

    int minimum_Key(int var[], bool numVisit[]){

        int index = 0;

        int minimumvalue = INT_MAX;

        for(int i = 0 ; i < Vertex ; i++){

            if(numVisit[i] == false && var[i] < minimumvalue){

                minimumvalue = var[i];

                index = i;
            }
        }

        return index;
    }

    Graph(int vertex){

        int minimum;
        int maximum;
        int weight;
        Vertex = vertex;
        array = new int*[vertex];

        for(int i = 0; i < vertex; i++){

            array[i] = new int[vertex];

            for(int j = 0; j < vertex; j++){

                array[i][j] = 0;
                if(i == j){

                    // sets the diagonal
                    array[i][j] = 1;

                }else{

                    array[i][j] = 0;
                }
            }
        }
    }

    Roles *roles;

    Graph( int min, int max,int vertex, int weight){

        roles = new Roles[vertex];

        Vertex = vertex;

        array = new int*[vertex];

        for(int i = 0; i < vertex; i++){

            roles[i] = Roles::Drones;
            array[i] = new int[vertex];

            for(int j = 0; j < vertex; j++){

                array[i][j] = 0;
                if(i == j){

                    array[i][j] = 1;
                }else{

                    array[i][j] = 0;
                }
            }
        }

        int connection[vertex] = {0};

        for(int i = 0; i < Vertex ; i++){

            if(i % 20 == 0){
                int random = rand() % Vertex;

                while(Roles::Alpha == roles[random]){

                    random = rand() % Vertex;

                }
                roles[random] = Roles::Alpha;
                cout << "Alphas: " << random+1 << endl;
            }

            int nodeDegree = rand() % (max + min + 1) - min;

            for(int numNeighbor = 0; numNeighbor < nodeDegree ; numNeighbor++){

                if (connection[i] < max) {

                    int newNodeConnect = rand() % vertex;

                    if (newNodeConnect == i or array[i][newNodeConnect] != 0 or connection[newNodeConnect] == max){
                        numNeighbor--;

                        continue;

                    } else {

                        int randWeight = rand() % 9 + 1;

                        array[i][newNodeConnect] = randWeight;

                        array[newNodeConnect][i] = randWeight;

                        connection[i]++;

                        connection[newNodeConnect]++;
                    }
                }
                else{

                    break;
                }
            }
        }


        int temp = rand() % Vertex;

        while(roles[temp] == Roles::Alpha){

            temp = rand() % Vertex;
        }

        roles[temp] = Roles::Omega;

        cout << "Omega :" << " " << temp + 1 << endl;

        int temp2 = rand() % Vertex;

        while(roles[temp2] != Roles::Drones){

            temp2 = rand() % Vertex;


        }
        roles[temp2] = Roles::You;
        omegaNode = temp;
        meNode = temp2;
        cout << "You :" << " " << temp2 + 1 << endl;
    }

    ~Graph(){
        for(int i = 0 ; i < Vertex; i++){
            delete [] array[i];
        }
        delete [] array;
        array = NULL;
    }
};

int main(int argc, char **argv){
    srand(time(NULL));
    int argv1, argv2, argv3 ,argv4;

    if(argc == 5){

        argv1 = atoi(argv[1]);

        argv2 = atoi(argv[2]);

        argv3 = atoi(argv[3]);

        argv4 = atoi(argv[4]);

        Graph map(argv1, argv2, argv3, argv4); // Get these from argc


        Graph m2(map.Vertex);

        cout << " RANDOM GRAPH" << endl;

        map.printGraph();

        cout << " MIN SPANNING TREE" << endl;

        map.calculateMST(m2);

        map.visitCheck();
    }
    else if(argc == 2){
        string filename, temp;
        fstream infile;

        int count = 0;

        infile.open(argv[1]);
        while(getline(infile, temp)) {

            count++;
        }

        Graph map2(count);
        infile.close();

        infile.open(argv[1]);

        map2.makeMatrix(infile);

        Graph mst(count);
        map2.printGraph();
        map2.calculateMST(mst);


    }
    else{
        cout << " Error invalid input: Enter a text file, or 3 command line arguments" << endl;
    }
    return 0;
}