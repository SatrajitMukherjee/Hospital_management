#include <bits/stdc++.h>
using namespace std;

// ---------------- PATIENT STRUCT ----------------
struct Patient {
    int id;
    string name;
    int priority; // 1-5
    string issue;
};

// Comparator for max heap (higher priority treated first)
struct ComparePriority {
    bool operator()(Patient const &a, Patient const &b) {
        return a.priority < b.priority; // max heap
    }
};

// ---------------- HOSPITAL MANAGEMENT ----------------
class Hospital {
private:
    priority_queue<Patient, vector<Patient>, ComparePriority> emergencyHeap;
    queue<Patient> opdQueue;

    int patientCounter = 1;

public:

    void addPatient(string name, int priority, string issue) {
        Patient p = { patientCounter++, name, priority, issue };

        if (priority >= 3) {       // 3,4,5 → emergency
            emergencyHeap.push(p);
            cout << "Added to Emergency: " << p.name << " (Priority " << p.priority << ")\n";
        } 
        else {                    // 1,2 → normal OPD
            opdQueue.push(p);
            cout << "Added to OPD Queue: " << p.name << " (Priority " << p.priority << ")\n";
        }
    }

    void showNextPatient() {
        if (!emergencyHeap.empty()) {
            Patient p = emergencyHeap.top();
            cout << "\nNext Critical Patient:\n";
            cout << "ID: " << p.id << " | Name: " << p.name 
                 << " | Priority: " << p.priority << " | Issue: " << p.issue << "\n";
        } 
        else if (!opdQueue.empty()) {
            Patient p = opdQueue.front();
            cout << "\nNext OPD Patient:\n";
            cout << "ID: " << p.id << " | Name: " << p.name 
                 << " | Priority: " << p.priority << " | Issue: " << p.issue << "\n";
        } 
        else {
            cout << "\nNo patients waiting.\n";
        }
    }

    void treatPatient() {
        if (!emergencyHeap.empty()) {
            Patient p = emergencyHeap.top();
            emergencyHeap.pop();
            cout << "\nTreated EMERGENCY Patient: " << p.name << " (Priority " << p.priority << ")\n";
        } 
        else if (!opdQueue.empty()) {
            Patient p = opdQueue.front();
            opdQueue.pop();
            cout << "\nTreated OPD Patient: " << p.name << " (Priority " << p.priority << ")\n";
        } 
        else {
            cout << "\nNo patients to treat!\n";
        }
    }

    void showAllPatients() {
        cout << "\n--- EMERGENCY PATIENTS (HEAP) ---\n";

        auto tempHeap = emergencyHeap;
        if (tempHeap.empty()) cout << "No emergency patients.\n";
        while (!tempHeap.empty()) {
            Patient p = tempHeap.top();
            tempHeap.pop();
            cout << p.id << ". " << p.name << " | Priority: " << p.priority 
                 << " | Issue: " << p.issue << "\n";
        }

        cout << "\n--- OPD PATIENTS (QUEUE) ---\n";
        queue<Patient> tempQueue = opdQueue;
        if (tempQueue.empty()) cout << "No OPD patients.\n";
        while (!tempQueue.empty()) {
            Patient p = tempQueue.front();
            tempQueue.pop();
            cout << p.id << ". " << p.name << " | Priority: " << p.priority
                 << " | Issue: " << p.issue << "\n";
        }
    }
};

// ---------------- MAIN MENU ----------------
int main() {
    Hospital H;
    int choice;

    while (true) {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Show Next Patient\n";
        cout << "3. Treat Patient\n";
        cout << "4. Show All Waiting Patients\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, issue;
            int priority;

            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, name);

            cout << "Enter Issue: ";
            getline(cin, issue);

            cout << "Enter Severity (1-5): ";
            cin >> priority;

            H.addPatient(name, priority, issue);
        } 
        else if (choice == 2) {
            H.showNextPatient();
        } 
        else if (choice == 3) {
            H.treatPatient();
        } 
        else if (choice == 4) {
            H.showAllPatients();
        } 
        else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } 
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}

