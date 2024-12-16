#include <iostream>
using namespace std;

struct Hole{
    string name;
    int size, remain;
};

struct Process{
    string name, hole = "\0";
    int size;

};

void firstFit(struct Hole memory[], int h, struct Process p[], int n){
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < h; j++){
            if (memory[j].remain >= p[i].size){
                memory[j].remain -= p[i].size;
                p[i].hole = memory[j].name;
                break;
            }
        }
    }
    return;
}

void bestFit(struct Hole memory[], int h, struct Process p[], int n) {
    int min, minIndex, d;
    for (int i = 0; i < n; i++) {
        min = INT_MAX; 
        minIndex = -1;
        for (int j = 0; j < h; j++) {
            d = memory[j].remain - p[i].size;
            if (d >= 0 && d < min && memory[j].remain > p[i].size) {
                min = d; minIndex = j;
            }
        }
        if (minIndex != -1) {
            memory[minIndex].remain -= p[i].size;
            p[i].hole = memory[minIndex].name;
        }
    }
    return;
}

void worstFit (struct Hole memory[], int h, struct Process p[], int n) {
    int max, maxIndex;
    for (int i = 0; i < n; i++) {
        max = 0; 
        maxIndex = -1;
        for (int j = 0; j < h; j++) {
            if (memory[j].remain > max && memory[j].remain >= p[i].size) {
                max = memory[j].remain;
                maxIndex = j;
            }
        }
        if (maxIndex != -1) {
            memory[maxIndex].remain -= p[i].size;
            p[i].hole = memory[maxIndex].name;
        }
    }
    return;
}

void nextFit(struct Hole memory[], int h, struct Process p[], int n){
    int next = 0;
    for (int i = 0; i < n; i++) {
        for (int j = next; j < h; j++){
            if (memory[j].remain >= p[i].size) {
                memory[j].remain -= p[i].size;
                p[i].hole = memory[j].name;
                next = j;
                break;
            }
        }
        if (p[i].hole == "\0" && next != 0) {
            for (int j = 0; j < next; j++) {
                if (memory[j].remain >= p[i].size) {
                    memory[j].remain -= p[i].size;
                    p[i].hole = memory[j].name;
                    next = j;
                    break;
                }
            }
        }
    }
    return;
}


int main() {
    int h, n, totalRemain = 0, flag, unAllocated = 0;
    string name;
    cout << "\nEnter no. of holes: ";
    cin >> h;
    struct Hole memory[h];
    cout << "\nEnter hole size sequentially (in KB): ";
    for (int i = 0; i < h; i++) {
        memory[i].name = "H" + to_string(i);
        cout << "\nSize of " << memory[i].name << ": ";
        getchar();
        cin >> memory[i].size;
        memory[i].remain = memory[i].size;
    }

    cout << "\nMemory setup complete";
    cout << "\nEnter no. of Processes in system: ";
    cin >> n;
    struct Process p[n];
    cout << "\nEnter process size sequentially (in KB): ";
    for (int i = 0; i < n; i++) {
        p[i].name = "P" + to_string(i);
        cout << "\nSize of " << p[i].name << ": ";
        cin >> p[i].size;
    }
    
    system("cls");
    STRATEGY:
    cout << "\nSelect Strategies for Contiguous Allocation:\n1 First Fit\n2 Best Fit\n3 Worst Fit\n4 Next Fit\nEnter Number of Strategy: ";
    cin >> flag;

    switch(flag){
        case 1: firstFit(memory,h,p,n); break;
        case 2: bestFit(memory,h,p,n); break;
        case 3: worstFit(memory,h,p,n); break;
        case 4: nextFit(memory,h,p,n); break;
        default: 
            cout << "\nInvalid Input, choose again\n";
            goto STRATEGY;
    }
    
    system("cls");
    cout << "Memory Status\n";
    for (auto i : memory){
        cout << i.name << "\tSize: " << i.size << " KB"<< endl;
        totalRemain += i.remain;
    }

    cout << "\nProcess allocated in memory are : \n";
    for (auto i : p) {
        if (i.hole != "\0") {
            cout << i.name << "\tSize: " << i.size << " KB\tHole: " << i.hole << endl;
        }
        else {
            unAllocated++;
        }
    }

    if (unAllocated != 0) {
        cout << "\nProcesses which are not allocated any memory are:\n";
        for (auto i : p) {
            if (i.hole == "\0") {
                cout << i.name << "\tSize: " << i.size << " KB"<< endl;
            }
        }
    }

    cout << "\n\nTotal Memory remaining after allocation to processes is " << totalRemain << " KB"; 
      

    return 0;
}