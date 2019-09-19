#include <iostream>
#include <vector>
using namespace std;
/*
 * Benjamin Raiford
 * MergeSort
 * September 19, 2019
 */

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


    //unit test for mergeSortedLists
    cout << "Testing mergeSortedLists\n" << endl;

    vector<int> testTemp{0, 0, 0, 0};//tempVector for testing

    //test case: "normal"
    vector<int> test1{1, 6, 4, 5};
    vector<int> test1Solution{1, 4, 5, 6};
    mergeSortedLists(test1, testTemp, 0, 1, 3);
    cout << "Test 1: general case." << endl;
    assert(test1 == test1Solution);

    //test case: contains duplicates
    vector<int> test2{2, 3, 2, 2};
    vector<int> test2Solution{2, 2, 2, 3};
    mergeSortedLists(test2, testTemp, 0, 1, 3);
    cout << "Test 2: contains duplicates." << endl;
    assert(test2 == test2Solution);

    //test case: already sorted
    vector<int> test3{6, 22, 55, 99};
    vector<int> test3Solution{6, 22, 55, 99};//note that this isn't perfectly sorted, that's why we need mergeSort
    mergeSortedLists(test3, testTemp, 0, 1, 3);
    cout << "Test 3: already sorted list." << endl;
    assert(test3 == test3Solution);

    //test case: reversed list
    vector<int> test4{24, 12, 6, 3};
    vector<int> test4Solution{6, 3, 24, 12};
    mergeSortedLists(test4, testTemp, 0, 1, 3);
    cout << "Test 4: reversed list." << endl;
    assert(test4 == test4Solution);

    //test case: odd vector length
    vector<int> test5{22, 11, 5};
    vector<int> test5Solution{5, 22, 11};//again, this isn't perfectly sorted, but it will be with mergeSort
    testTemp.resize(test5.size());//resize temp from 4 to 3
    mergeSortedLists(test5, testTemp, 0, 1, 2);
    cout << "Test 5: odd vector length" << endl;
    assert(test5 == test5Solution);

    //test case: empty vector
    vector<int> test6{};
    vector<int> test6Solution{};
    mergeSortedLists(test6, testTemp, 0, 0, 0);
    cout << "Test 6: empty vector." << endl;
    assert(test6 == test6Solution);

    cout << "\nTesting complete. No errors in mergeSorted List.\n\n" << endl;


    //initialize and print input
    cout << "Unsorted list" << endl;
    for(int & i : v) {
        i = rand() % 100;
        cout << i << '\t';
    }
    cout << endl;

    //call mergeSort to order the vector
    mergeSort(v,t,0,v.size()-1);

    //print output
    cout << "\nSorted list" << endl;
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
    //base is implicit:
    // because of the if statement and void function type, vectors sized 0 and 1 will fall through
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
    //mergeSort shouldn't pass empty vectors to mergeSortedLists, but user might call mergeSortedLists with an empty vector
    if(a.empty()){
        return;
    }

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


