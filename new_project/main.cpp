#include <bits/stdc++.h>
#include <algorithm>
#include<iostream>
#include<string>

using namespace std;

void fast() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

#define endl "\n"
#define ll long long

const int MAX_SPECIALIZATION_LEN = 20;
const int MAX_QUEUE_LEN = 5;

struct hospital_queue {
    int spec{};
    int len{};
    int status[MAX_QUEUE_LEN]{};
    string names[MAX_QUEUE_LEN];

    hospital_queue() {
        len = 0;
        spec = -1;
    }

    hospital_queue(int spec) {
        len = 0;
        this->spec = spec;
    }

    void add_end(string name, int st) {
        names[len] = name;
        status[len] = st;
        len++;
    }

    void add_front(string name,int st) {
        for (int i = len - 1; i >= 0; --i) {
            names[i + 1] = names[i];
            status[i + 1] = status[i];
        }
        names[0]=name;
        status[0]=st;
        len++;
    }

    void remove_front() {
        if (!len) {
            cout << "There are no patients at this moment.Have rest,dr" << endl;
            return;
        }
        cout << names[0] <<" please,go with dr" << endl;
        for (int i = 1; i < len; ++i) {
            names[i - 1] = names[i];
            status[i - 1] = status[i];
        }
        len--;
    }

    void print_queue() {
        if (!len) {
            return;
        }
        cout << "There are " << len << " in specialization: " << spec << endl;
        for (int i = 0; i < len; ++i) {
            cout << names[i] << " ";
            if (status[i] == 0) {
                cout << "regular" << endl;
            } else {
                cout << "urgent" << endl;
            }
        }
        cout << endl;
    }
};

struct hospital_system {
    hospital_queue queues[MAX_SPECIALIZATION_LEN];

    hospital_system() {
        for (int i = 0; i < MAX_SPECIALIZATION_LEN; ++i) {
            queues[i] = hospital_queue(i);
        }

    }

    void add_patient() {
        int spec, st;
        string name;
        cout << "Enter specialization,name,status: ";
        cin >> spec >> name >> st;
        cout<<endl;
        if (queues[spec].len >= MAX_QUEUE_LEN) {
            cout << "Sorry,there are no more queues" << endl;
            return;
        }
        if (st == 0) {
            queues[spec].add_end(name, st);
        } else {
            queues[spec].add_front(name,st);

        }
    }

    void print_patients() {
        cout << "***********************" << endl;
        for (int spec = 0; spec < MAX_SPECIALIZATION_LEN; ++spec) {
            queues[spec].print_queue();
        }
    }

    void get_nex_patient() {
        int spec;
        cout << "Enter specialization: ";
        cin >> spec;
        queues[spec].remove_front();
    }

    int menu() {
        int choice = -1;
        while (choice == -1) {
            cout << "1)Add patient " << endl;
            cout << "2)Print patients " << endl;
            cout << "3)Get next patient " << endl;
            cout << "4)Exit " << endl;
            cin >> choice;
            if (!(choice >= 1 && choice <= 4)) {
                cout << "Invalid input,please renter a valide one" << endl;
                choice = -1;
            }
        }
        return choice;
    }

    void run_hos_system() {
        while (true) {
            int choice = menu();
            if (choice == 1) {
                add_patient();
            } else if (choice == 2) {
                print_patients();
            } else if (choice == 3) {
                get_nex_patient();
            } else {
                cout<<"You terminated the program "<<endl;
                break;
            }
        }
    }
};

int main() {
    hospital_system hospital = hospital_system();
    hospital.run_hos_system();

    return 0;
}
