/*
Student Name:
Student Number:
Project Number: 5
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


int getMax(vector<int>* price, int N){
    int max= 0;
    for(int i=0; i<N; i++){
        if(max<(*price)[i]){
            max = (*price)[i];
        }
    }
    return max;
}


void countSort(int N, vector<int>* price, int exp){
    vector<int> output(N);
    vector<int> count(10,0);

    for(int i=0; i<N; i++){
        count[((*price)[i]/exp)%10]++;
    }
    for(int i=1; i<10; i++){
        count[i] += count[i-1];
    }
    for(int i= N-1; i>=0; i--){
        output[ count[ ((*price)[i]/exp)%10]-1] = (*price)[i];
        count[((*price)[i]/exp)%10]--;
    }
    for(int i=0; i<N; i++){
        (*price)[i] = output[i] ;
    }

}

void radixSort(int& N, vector<int>* price){
    int max = getMax(price,N);

    for(int i=1; max/i > 0; i*=10){
        countSort(N, price, i);
    }
}


int main(int argc, char* argv[]){
    int N, M;
    vector<int>* price;

    if(argc!=3){
        cout<<"there is a problem with arguments";
    }
    ifstream inFile(argv[1]);
    if (!inFile) { // operator! is synonymous to .fail(), checking if there was a failure
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        return 1;
    }

    inFile >> N;
    inFile >> M;

    price = new vector<int>(N);

    for(int i=0; i<N; i++){
        int a;
        inFile >> a;
        (*price)[i]= a;
    }
    radixSort(N,price);
    vector<long long int> table(N,0);

    for(int i=0; i<N; i++){
        long long int prev = 0;
        long long int plusPrev = 0;
        long long int minusPrev = 0;
        if(i>0){
            prev = table[i-1];
        }
        if(i>=M){
            plusPrev = table[i-M];
            if(i>M){
                minusPrev = table[i-M-1];
            }
        }

        table[i] = (*price)[i] + prev + plusPrev - minusPrev;


        outFile << table[i] <<" ";
    }




    return 0;
}