/*
Name: Daniel Hinga,
Description:program should prompt for a value for 'n' and executes
    the recursive codes then outputs counts for all 4 codes
    and then prompts for a new n. Keep prompting the user for n until
    he enters a value of 0 and then terminate the program.
Input: prompt for a value for 'n' to get the numberof runs
Output: counts for all 4 codes and then prompts for a new n.
*/


#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

int Code1(int n){
    if (n==0){
       return 0; //The end number
    } else
    return 1 + Code1(n - 1); //The inner recursive
}

int Code2(int n,int j ){
    if (j== 2*n*n){
      return 0; //The end number
    } else
        return 1 + Code2(n,j + 1); //The inner recursive
}

int Code4(int n, int j){
    if (j == 3*n*n*n*n){
       return 0; //The end number
    } else
        return 1 + Code4(n, j + 1); //The inner recursive
}

int Code3(int n, int x){
    if (x == n){
      return 0; //The end number
    } else
        return 1 + Code3(n,x + 1); //The inner recursive
}


int main() {
      //Code
        int i, j, k, n;
        int count;
        /*keep track of counts */

// do while because i need it to rin
do {
    count = 0;
    cout << "Enter a value for n (0 to stop):  ";
    cin >> n;
    //cout << endl;

    if (n != 0) {


// this calls the Functions but does not store them just outputs
cout << "Code 1: count = " << Code1(n) << endl;
cout << "Code 2: count = " << Code2(n,0) << endl;
cout << "Code 3: count = " << Code3(n,0) << endl;
cout << "Code 4: count = " << Code4(n, 0) <<  endl;





}//else return 0;
        } while (n != 0);

        return (0);
    }
