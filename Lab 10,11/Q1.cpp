#include <iostream>
#include <string>
using namespace std;

struct Incident {
    int severity;
    long long timestamp;
    string description;
};

Incident heapArr[1000];
int heapSize = 0;

bool higher(const Incident& a, const Incident& b) {
    if (a.severity == b.severity) return a.timestamp < b.timestamp;
    return a.severity > b.severity;
}

void pushHeap(Incident x) {
    heapArr[++heapSize] = x;
    int i = heapSize;
    while (i > 1 && higher(heapArr[i], heapArr[i/2])) {
        Incident t = heapArr[i];
        heapArr[i] = heapArr[i/2];
        heapArr[i/2] = t;
        i /= 2;
    }
}

Incident popHeap() {
    Incident top = heapArr[1];
    heapArr[1] = heapArr[heapSize--];
    int i = 1;
    while (true) {
        int l = i*2, r = i*2+1, best = i;
        if (l <= heapSize && higher(heapArr[l], heapArr[best])) best = l;
        if (r <= heapSize && higher(heapArr[r], heapArr[best])) best = r;
        if (best == i) break;
        Incident t = heapArr[i];
        heapArr[i] = heapArr[best];
        heapArr[best] = t;
        i = best;
    }
    return top;
}

int main() {
    string cmd;
    while (cin >> cmd) {
        if (cmd == "ADD") {
            Incident x;
            cin >> x.severity >> x.timestamp;
            getline(cin, x.description);
            if (x.description.size() > 0 && x.description[0] == ' ')
                x.description.erase(0, 1);
            pushHeap(x);
        } 
        else if (cmd == "DISPATCH") {
            if (heapSize == 0) {
                cout << "NO INCIDENTS\n";
            } else {
                Incident x = popHeap();
                cout << x.severity << " " << x.timestamp << " " << x.description << "\n";
            }
        }
    }
}

