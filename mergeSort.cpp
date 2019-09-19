#include <iostream>
#include <vector>
using namespace std;

// function declarations
void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right);
void mergeSortedLists(vector<int>& a, vector<int>& tmp, int left, int middle, int right);

int main() {
    int seed;   //user-defined seed
    int length; //vector length

    //get input
    cout << "Enter any number and the length of vector, separated by a space." << endl;
    cin >> seed >> length;
    srand(seed);

    vector<int> v(length);  //vector to be sorted
    vector<int> t(length);  //temporary workspace prevents the program being too memory intensive

    //initialize and print input
    for(int & i : v) {
        i = rand() % 100;
        cout << i << '\t';
    }
    cout << endl;

    //FIXME: Add unit test
    //unit test for mergeSortedLists

    //call mergeSort to order the vector
    mergeSort(v,t,0,v.size()-1);

    //print output
    for(int i : v) {
        cout << i << '\t';
    }
    cout << endl;

    //check output to make sure it's sorted
    for(int i = 1; i < v.size(); i++) {
        assert(v.at(i-1) <= v.at(i));
    }

    return 0;
}

void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right){
    if(left < right){
        //break the vector down recursively (only shifting indices)
        int midpoint = (left + right - 1)/2;
        mergeSort(a, tmp, left, midpoint);
        mergeSort(a, tmp, midpoint + 1, right);

        //run the merge operation on each part
        mergeSortedLists(a, tmp, left, midpoint, right);
    }
}

void mergeSortedLists(vector<int>& a, vector<int>& tmp, int left, int middle, int right){
    //These indices split the section of the vector into two parts
    int i = left;           //start first part
    int j = middle + 1;     //start second part
    int tmpIndex = left;    //index of temp to which values will be copied


    //While loop to compare entries in the first and second half, copying the smaller entry into tmp
    while (i <= middle && j <= right){
        //lesser value is in the first section
        if (a.at(i) <= a.at(j)) {
            tmp.at(tmpIndex) = a.at(i);     //copy to tmp
            i++;                            //increment i
        }
        //lesser value is in the second section
        else {
            tmp.at(tmpIndex) = a.at(j);     //copy to tmp
            j++;                            //increment j
        }
        tmpIndex++;
    }

    //If i or j have not iterated over their respective sections, make them finish
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

    //Copy ONLY the values changed by this call...
    //Using (i = 0; i < a.size(); i++) can potentially remove data by copying null values from tmp to a
    for(i = left; i <= right; i++){
        a.at(i) = tmp.at(i);
    }
}


