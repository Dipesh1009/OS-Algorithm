#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

class Process {
    public:
    string name;
    short state, priority, clock;


    void set(string name, int priority, int clock) {
        this->name = name;
        state = -1;
        this->priority = priority;
        this->clock = clock;
    } 

    friend ostream& operator << (ostream &os, Process &p) {
        os << "\nName: " << p.name << "\tPriority: " << p.priority << "\tTime: " << p.clock;
        return os;     
    }
};

bool wait(int &s) {
    if (s <= 0) {
        return false;
    }
    s--;
    return true;
}

void signal(int &s) {
    s++;
}
int main() {
    srand(time(0));
    int n, s,  clk = 0;
    cout << "\nEnter number of instances of Resource R: ";
    cin >> s;
    cout << "\nEnter number of processes: ";
    cin >> n;

    Process p[n];
    string name = "P";
    for (int i = 1; i <= n; i++){
        name += to_string(i);
        p[i-1].set(name, rand() % 10, (rand() % 3) + 1);
        name = "P";
    }

    for (auto a : p) {
        cout << a;
    }

    sort(p, p+n, [](const Process& p1, const Process& p2) {
        return p1.priority < p2.priority;
    });
    int i = 0;
    do{
        cout << "\n\nClock Cycle: " << clk++ << "\n";
        while(wait(s) && i < n) {
            p[i++].state++;
        }
        
        for (auto &a : p) {
            switch(a.state) {
                case -1: cout << "\n" << a.name << " is waiting"; break;
                case 0: cout << "\n" << a.name << " is in Critical Section"; a.clock--; break;
                case 1: cout << "\n" << a.name << " is completed"; break; 
            }
            if (a.clock == 0 && a.state < 1) {
                a.state++; 
                signal(s);
            }
        }
    }while(p[n-1].state != 1);

    cout << "\nProcess Exited at Clock: " << clk;

    return 0;
}