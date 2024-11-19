#include <iostream>
#include <queue>
using namespace std;
// priority 0 is low, 9 is high
class Process
{
    private: 
        string pID;
        int arrivalTime = 0, burstTime, waitingTime = -1, turnATime = -1, responseTime = -1, remainT, priority = 0;
        
    public: 
        Process(string pID, int burstTime, int arrivalTime, int priority) {
            this->pID = pID;
            this->arrivalTime = arrivalTime;
            this->burstTime = burstTime;
            this->remainT = burstTime;
            this->priority = priority;
        }
        Process (string pID, int burstTime) {
            this->pID = pID;
            this->burstTime = burstTime;
        }
        
        int getRemain() {return remainT;}
        int getP() {return priority;}
        int getBT() {return burstTime;}
        int getAT() {return arrivalTime;}
        int getWT() {return waitingTime;}
        int getTAT() {return turnATime;}
        int getRT() {return responseTime;}

        void setResponseTime(int responseTime) {
            this->responseTime = responseTime;
        }

        void setTurnAroundTime(int turnATime) {
            this->turnATime = turnATime - this->arrivalTime;
        }

        void setWaitingTime() {
            waitingTime = turnATime - burstTime;
        }

        void decrementRemainTime() {
            this->remainT--;
        }

        friend ostream& operator << (ostream& os, Process& process) {
            os << process.pID << "\t" << process.burstTime << "\t" << process.arrivalTime << "\t" << process.priority << "\t" << process.waitingTime << "\t" << process.turnATime << "\t" << process.responseTime << "\n";

            return os;
         }
};


void findAverageTime(int size, Process* arrOfProcess) {

    float averageWT = 0, averageTAT = 0, averageRT = 0;

    for (int i = 0; i < size; i++) {
        averageWT += arrOfProcess[i].getWT();
        averageTAT += arrOfProcess[i].getTAT();
        averageRT += arrOfProcess[i].getRT();
    }

    cout << "\nAverage Waiting Time: \t" << averageWT/size;
    cout << "\nAverage Turn Around Time: \t" << averageTAT/size;
    cout << "\nAverage Response Time: \t" << averageRT/size;
}

struct CompareByPriority{
    bool operator()(Process* p1, Process * p2) {
        return p1->getP() < p2->getP();
    }
};

int main () {

    auto compareByArrival = [] (Process *p1, Process *p2) -> bool {
        return p1->getAT() > p2->getAT();
    };
    int clk = 0;
    Process * pointer;
    priority_queue<Process*, vector<Process*>, decltype(compareByArrival)> readyQA(compareByArrival);
    priority_queue<Process*, vector<Process*>, CompareByPriority> readyQR;
    //queue<Process*> readyQA;

    Process processArr[5] = {
        Process("P0",6,2,3),
        Process("P1",4,1,6),
        Process("P2",9,1,2),
        Process("P3",2,3,7),
        Process("P4",3,4,9)
    };


    for (int i = 0; i < 5; i++) {
        readyQA.push(&processArr[i]);
    }

    cout << readyQA.top()->getAT();
    while(!readyQR.empty() || !readyQA.empty()) {
        if( !readyQA.empty() && clk == readyQA.top()->getAT()) {
            pointer = readyQA.top();
            readyQR.push(pointer);
            readyQA.pop();
            continue;
        }
        if (!readyQR.empty() && readyQR.top()->getRT() == -1){
            readyQR.top()->setResponseTime(clk);
        }
        clk++;
        if (!readyQR.empty()){readyQR.top()->decrementRemainTime();}
        if ((!readyQR.empty()) && (readyQR.top()->getRemain() == 0)){
            readyQR.top()->setTurnAroundTime(clk);
            readyQR.top()->setWaitingTime();
            readyQR.pop();
        }
    }
    cout << "\nPID\tCBT\tAT\tPr\tWT\tTAT\tRT\n";
    for (Process i : processArr) {
        cout << i;
    }

    findAverageTime(5,processArr);

    cout << "\nCPU exited at " << clk;

    return 0;
}