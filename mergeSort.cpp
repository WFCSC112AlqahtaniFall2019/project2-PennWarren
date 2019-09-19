#include <iostream>
#include <vector>
using namespace std;

// function declarations
void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right);
void mergeSortedLists(vector<int>& a, vector<int>& tmp, int left, int middle, int right);

int main() {
    // get input: first is random seed, second is vector length
    int seed, length;

    cout << "Enter any number and the length of vector, separated by a space." << endl;
    cin >> seed >> length;
    srand(seed);


    vector<int> v(length);  // vector to be sorted
    vector<int> t(length);  // temporary workspace

    // initialize and print input
    for(int i = 0; i < v.size(); i++) {
        v.at(i) = rand() % 100;
        cout << v.at(i) << '\t';
    }
    cout << endl;

    // print output
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << '\t';
    }
    cout << endl;

    mergeSort(v,t,0,v.size()-1);


    // unit test for merge
    //FIXME: add unit test

    // print output
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << '\t';
    }
    cout << endl;

    // check output, make sure it's sorted
    for(int i = 1; i < v.size(); i++) {
        assert(v.at(i-1) <= v.at(i));
    }


    return 0;
}

void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right){
    if(a.size() <= 1){
        return;
    }
    if(left < right){
        int midpoint = (left + right - 1)/2;

        mergeSort(a, tmp, left, midpoint);
        mergeSort(a, tmp, midpoint + 1, right);

        mergeSortedLists(a, tmp, left, midpoint, right);
    }
}

void mergeSortedLists(vector<int>& a, vector<int>& tmp, int left, int middle, int right){
    int i = left;
    int j = middle + 1;
    int tmpIndex = left;

    while (i <= middle && j <= right)
    {
        if (a.at(i) <= a.at(j)) {
            tmp.at(tmpIndex) = a.at(i);
            i++;
        }
        else {
            tmp.at(tmpIndex) = a.at(j);
            j++;
        }
        tmpIndex++;
    }

    while (i <= middle){
        tmp.at(tmpIndex) = a.at(i);
        i++;
        tmpIndex++;
    }

    while (j <= right){
        tmp.at(tmpIndex) = a.at(j);
        j++;
        tmpIndex++;
    }

    for(i = 0; i < tmp.size(); i++){
        a.at(i) = tmp.at(i);
    }
}


