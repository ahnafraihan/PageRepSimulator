#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int numPageAccesses = 10000;

double FIFO (int arr[10000], int size) {
    double hits = 0;
    double misses = 0;
    vector <int> cache(size);
    fill(cache.begin(), cache.end(), -1);
    
    for (int i = 0; i < numPageAccesses; i++) { // Access
        bool accFlag = false;
        for (int j = 0; j < size; j++) {
            if ((cache.at(j) == -1 || cache.at(j) == arr[i]) && accFlag == false) { // hit
                cache.at(j) = arr[i];
                hits++;
                accFlag = true;
                
            }
            else if (accFlag == false && j == size-1) { // miss
                cache.erase(cache.begin());
                cache.push_back(arr[i]);
                misses++;
                accFlag = true;
                break;
            }
        }
    }
    hits = hits - size;
    if (hits == 0 && misses == 0)
        return 0;
    return (hits / (hits + misses))*100;
}

double Rand (int arr[10000], int size) {
    double hits = 0;
    double misses = 0;
    vector <int> cache(size);
    fill(cache.begin(), cache.end(), -1);
    
    for (int i = 0; i < numPageAccesses; i++) { // Access
        bool accFlag = false;
        for (int j = 0; j < size; j++) {
            if ((cache.at(j) == -1 || cache.at(j) == arr[i]) && accFlag == false) { // hit
                cache.at(j) = arr[i];
                hits++;
                accFlag = true;
                
            }
            else if (accFlag == false && j == size-1) { // miss
                int evict = 0 + (rand() % (size -1 -0 + 1 ));
                cache.at(evict) = arr[i];
                misses++;
                accFlag = true;
                break;
            }
        }
    }
    if (hits == 0 && misses == 0)
        return 0;
    hits = hits - size;
    return (hits / (hits + misses))*100;
}

double LRU (int arr[10000], int size) {
    double hits = 0;
    double misses = 0;
    vector <int> cache(size);
    fill(cache.begin(), cache.end(), -1);
    
    for (int i = 0; i < numPageAccesses; i++) { // Access
        bool accFlag = false;
        for (int j = 0; j < size; j++) {
            if ((cache.at(j) == -1 || cache.at(j) == arr[i]) && accFlag == false) { // hit
                cache.erase(cache.begin() + j);
                cache.push_back(arr[i]);
                hits++;
                accFlag = true;
                
            }
            else if (accFlag == false && j == size-1) { // miss
                cache.erase(cache.begin());
                cache.push_back(arr[i]);
                misses++;
                accFlag = true;
                break;
            }
        }
        /*   cout << arr[i] << " - ";
         for (int k = 0; k < size; k++) {
         cout << cache.at(k) << " ";
         }
         cout << endl; */
    }
    if (hits == 0 && misses == 0)
        return 0;
    hits = hits - size;
    return (hits / (hits + misses))*100;
}

double OPT (int arr[10000], int size) {
    double hits = 0;
    double misses = 0;
    vector <int> cache(size);
    fill(cache.begin(), cache.end(), -1);
    
    for (int i = 0; i < numPageAccesses; i++) { // Access
        bool accFlag = false;
        for (int j = 0; j < size; j++) {
            if ((cache.at(j) == -1 || cache.at(j) == arr[i]) && accFlag == false) { // hit
                //cout << "Hit! ";
                cache.at(j) = arr[i];
                hits++;
                accFlag = true;
                
            }
            else if (accFlag == false && j == size-1) { // miss
                //cout << "Miss! ";
                int opt = 0;
                int recCounter[100];
                fill_n(recCounter, 100, -1);
                for (int k = i+1; k < numPageAccesses; k++) {
                    if (recCounter[arr[k]] == -1) {
                        recCounter[arr[k]] = k;
                    }
                }
                for (int k = 0; k < size; k++) {
                    if (recCounter[cache.at(k)] == -1) {
                        opt = cache.at(k);
                        break;
                    }
                    else {
                        if (recCounter[cache.at(k)] > recCounter[opt])
                            opt = cache.at(k);
                    }
                }
                
                for (int k = 0; k < size; k++) {
                    if (cache.at(k) == opt)
                        cache.at(k) = arr[i];
                    
                }
                misses++;
                accFlag = true;
                //break;
            }
        }
        /* cout << arr[i] << " - ";
         for (int k = 0; k < size; k++) {
         cout << cache.at(k) << " ";
         }
         cout << endl; */
    }
    
    if (hits == 0 && misses == 0)
        return 0;
    hits = hits - size;
    return (hits / (hits + misses))*100;
}

double Clock (int arr[10000], int size) {
    int currPos = 0;
    double hits = 0;
    double misses = 0;
    vector <int> cache(size);
    fill(cache.begin(), cache.end(), -1);
    int pages [2][size];
    for (int i = 0; i < size; i++) {
        pages[0][i] = -1;
        pages [1][i] = 0;
    }
    
    
    for (int i = 0; i < numPageAccesses; i++) { // Access
        bool accFlag = false;
        for (int j = 0; j < size; j++) {
            if ((pages[0][j] == -1 || pages[0][j] == arr[i]) && accFlag == false) { // hit
                //cout<< "Hit " ;
                pages[0][j] = arr[i];
                if (pages[1][j] == 0)
                    pages[1][j] = 1;
                else if (pages[1][j] == 1)
                    pages[1][j] = 0;
                hits++;
                accFlag = true;
            }
            else if (accFlag == false && j == size-1) { // miss
                //cout<< "Miss " ;
                while (accFlag == false) {
                    if (pages[1][currPos] == 0) {
                        pages[0][currPos] = arr[i];
                        pages[1][currPos] = 1;
                        accFlag = true;
                        misses++;
                        if (currPos == size -1)
                            currPos = 0;
                        else
                            currPos++;
                        break;
                    }
                    
                    else {
                        pages[1][currPos] = 0;
                        if (currPos == size -1)
                            currPos = 0;
                        else
                            currPos++;
                        
                    }
                }
            }
        }
        /* cout << arr[i] << " - ";
         for (int k = 0; k < size; k++) {
         cout << "[" << pages[0][k] << "]" << " (" << pages[1][k] << ") ";
         }
         cout << endl; */
    }
    if (hits == 0 && misses == 0)
        return 0;
    hits = hits - size;
    return (hits / (hits + misses))*100;
}



int main(int argc, const char * argv[]) {
    
    
    /* ---------- NO LOCALITY WORKLOAD ------------*/
    
    int NLArray[numPageAccesses];
    srand((unsigned)time(0));
    for (int i = 0; i < numPageAccesses; i++) {
        NLArray[i] = 0 + (rand() % (99 - 0 + 1 ));
    }
    
    /* -------------- 80/20 WORKLOAD --------------*/
    int ETArray [numPageAccesses];
    for (int i = 0; i < numPageAccesses; i++) {
        if (i >= 0 && i < 8000) {
            ETArray[i] = 0 + (rand() % (19 - 0 + 1 ));
        }
        else {
            ETArray[i] = 20 + (rand() % (99 - 20 + 1 ));
        }
    }
    
    random_shuffle(begin(ETArray), end(ETArray));
    for (int i = 0; i < numPageAccesses; i++) {
    }
    
    /* -------------- LOOPING WORKLOAD -------------*/
    
    int LArray [numPageAccesses];
    int count = 0;
    for (int i = 0; i < numPageAccesses; i++) {
        if (count == 49) {
            LArray[i] = count;
            count = 0;
        }
        else {
            LArray[i] = count;
            count++;
        }
    }
    
    /* -------------- TESTING: FIFO -------------*/
    
    
    double NL_FIFO[21];
    int NL_FIFO_Count = 0;
    for (int i = 0; i < 21; i++) {
        NL_FIFO[i] = FIFO(NLArray, NL_FIFO_Count);
        cout << "NL_FIFO " << NL_FIFO_Count << ": " << NL_FIFO[i] << endl;
        NL_FIFO_Count += 5;
    }
    
    cout << endl;
    
    double ET_FIFO[21];
    int ET_FIFO_Count = 0;
    for (int i = 0; i < 21; i++) {
        ET_FIFO[i] = FIFO(ETArray, ET_FIFO_Count);
        cout << "ET_FIFO " << ET_FIFO_Count << ": " << ET_FIFO[i] << endl;
        ET_FIFO_Count += 5;
    }
    
    cout << endl;
    
    double L_FIFO[21];
    int L_FIFO_Count = 0;
    for (int i = 0; i < 21; i++) {
        L_FIFO[i] = FIFO(LArray, L_FIFO_Count);
        cout << "L_FIFO " << L_FIFO_Count << ": " << L_FIFO[i] << endl;
        L_FIFO_Count += 5;
    }
    
    /* -------------- TESTING: RANDOM -------------*/
    
    cout << endl;
    
    double NL_RAND[21];
    int NL_RAND_Count = 0;
    for (int i = 0; i < 21; i++) {
        NL_RAND[i] = Rand(NLArray, NL_RAND_Count);
        cout << "NL_RAND " << NL_RAND_Count << ": " << NL_RAND[i] << endl;
        NL_RAND_Count += 5;
    }
    
    cout << endl;
    
    double ET_RAND[21];
    int ET_RAND_Count = 0;
    for (int i = 0; i < 21; i++) {
        ET_RAND[i] = Rand(ETArray, ET_RAND_Count);
        cout << "ET_RAND " << ET_RAND_Count << ": " << ET_RAND[i] << endl;
        ET_RAND_Count += 5;
    }
    
    cout << endl;
    
    double L_RAND[21];
    int L_RAND_Count = 0;
    for (int i = 0; i < 21; i++) {
        L_RAND[i] = Rand(LArray, L_RAND_Count);
        cout << "L_RAND " << L_RAND_Count << ": " << L_RAND[i] << endl;
        L_RAND_Count += 5;
    }
    
    /* -------------- TESTING: LRU -------------*/
    
    cout << endl;
    
    double NL_LRU[21];
    int NL_LRU_Count = 0;
    for (int i = 0; i < 21; i++) {
        NL_LRU[i] = LRU(NLArray, NL_LRU_Count);
        cout << "NL_LRU " << NL_LRU_Count << ": " << NL_LRU[i] << endl;
        NL_LRU_Count += 5;
    }
    
    cout << endl;
    
    double ET_LRU[21];
    int ET_LRU_Count = 0;
    for (int i = 0; i < 21; i++) {
        ET_LRU[i] = LRU(ETArray, ET_LRU_Count);
        cout << "ET_LRU " << ET_LRU_Count << ": " << ET_LRU[i] << endl;
        ET_LRU_Count += 5;
    }
    
    cout << endl;
    
    double L_LRU[21];
    int L_LRU_Count = 0;
    for (int i = 0; i < 21; i++) {
        L_LRU[i] = LRU(LArray, L_LRU_Count);
        cout << "L_LRU " << L_LRU_Count << ": " << L_LRU[i] << endl;
        L_LRU_Count += 5;
    }
    
    /* -------------- TESTING: OPT -------------*/
    
    cout << endl;
    double NL_OPT[21];
    int NL_OPT_Count = 0;
    for (int i = 0; i < 21; i++) {
        NL_OPT[i] = OPT(NLArray, NL_OPT_Count);
        cout << "NL_OPT " << NL_OPT_Count << ": " << NL_OPT[i] << endl;
        NL_OPT_Count += 5;
    }
    
    cout << endl;
    
    double ET_OPT[21];
    int ET_OPT_Count = 0;
    for (int i = 0; i < 21; i++) {
        ET_OPT[i] = OPT(ETArray, ET_OPT_Count);
        cout << "ET_OPT " << ET_OPT_Count << ": " << ET_OPT[i] << endl;
        ET_OPT_Count += 5;
    }
    
    cout << endl;
    
    double L_OPT[21];
    int L_OPT_Count = 0;
    for (int i = 0; i < 21; i++) {
        L_OPT[i] = OPT(LArray, L_OPT_Count);
        cout << "L_OPT " << L_OPT_Count << ": " << L_OPT[i] << endl;
        L_OPT_Count += 5;
    }
    
    /* -------------- TESTING: Clock -------------*/
    
    cout << endl;
    double NL_Clock[21];
    int NL_Clock_Count = 0;
    for (int i = 0; i < 21; i++) {
        NL_Clock[i] = Clock(NLArray, NL_Clock_Count);
        cout << "NL_Clock " << NL_Clock_Count << ": " << NL_Clock[i] << endl;
        NL_Clock_Count += 5;
    }
    
    cout << endl;
    
    double ET_Clock[21];
    int ET_Clock_Count = 0;
    for (int i = 0; i < 21; i++) {
        ET_Clock[i] = Clock(ETArray, ET_Clock_Count);
        cout << "ET_Clock " << ET_Clock_Count << ": " << ET_Clock[i] << endl;
        ET_Clock_Count += 5;
    }
    
    cout << endl;
    
    double L_Clock[21];
    int L_Clock_Count = 0;
    for (int i = 0; i < 21; i++) {
        L_Clock[i] = Clock(LArray, L_Clock_Count);
        cout << "L_Clock " << L_Clock_Count << ": " << L_Clock[i] << endl;
        L_Clock_Count += 5;
    }
    
    return 0;
}
