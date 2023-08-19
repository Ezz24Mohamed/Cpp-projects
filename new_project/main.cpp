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

const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

string names[MAX_SPECIALIZATION][MAX_QUEUE];
int status[MAX_SPECIALIZATION][MAX_QUEUE];
int queue_len[MAX_SPECIALIZATION];

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "Enter your choice: " << endl;
        cout << "1) Add new patient" << endl;
        cout << "2) Print all patients" << endl;
        cout << "3) Get next patient" << endl;
        cout << "4) Exit" << endl;
        cin >> choice;
        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid number ,Please renter" << endl;
            choice = -1;
        }
    }
    return choice;
}

void add_in_begin(int spec, string name[], int st[]) {
    //shift right
    int size = queue_len[spec];
    for (int i = size - 1; i >= 0; --i) {
        name[i + 1] = name[i];
        st[i + 1] = st[i];
    }
    queue_len[spec]++;
}
void remove_from_begin(int spec,string name[],int st[]){
    //shift left
    int size=queue_len[spec];
    for (int i = 1; i <size ; ++i) {
        name[i-1]=name[i];
        st[i-1]=st[i];
    }
    queue_len[spec]--;
}

bool add_patient() {
    int spec;
    string name;
    int st;
    cout << "Enter specialization , name, status: ";
    cin >> spec >> name >> st;
    int pos = queue_len[spec];
    if (pos >= MAX_QUEUE) {
        cout << "Sorry,there is no more queues" << endl;
        return false;
    }

    if (st == 0) {
        names[spec][pos] = name;
        status[spec][pos] = st;
        queue_len[spec]++;
    } else {
        add_in_begin(spec, names[spec], status[spec]);
        names[spec][0] = name;
        status[spec][0] = st;

    }

    return true;


}

void print_one_patient(int spec, string name[], const int st[]) {
    int size = queue_len[spec];
    if(!size){
        return ;
    }
    cout << "There are " << size << " in specialization " << spec << endl;
    for (int i = 0; i < size; ++i) {
        cout << name[i];
        if (st[i] == 0) {
            cout << " regular" << endl;
        } else {
            cout << " urgent" << endl;
        }
    }
    cout<<endl;
}

void print_patients() {
    cout << "**********************************************" << endl;
    for (int spec = 0; spec < MAX_SPECIALIZATION; ++spec) {
        print_one_patient(spec, names[spec], status[spec]);
    }
}
void getPatient(){
    int spec;
    cout<<"Enter specialization: ";
    cin>>spec;
    int size=queue_len[spec];
    if(!size){
        cout<<endl <<"No patients at moment "<<endl;
        return ;
    }
    cout<<names[spec][0]<<" please go with Dr "<<endl;
    remove_from_begin(spec,names[spec],status[spec]);
}


void hospital_system() {
    while (true) {
        int choice = menu();
        if (choice == 1)
            add_patient();
        else if (choice==2){
            print_patients();
        }
        else if(choice==3){
            getPatient();
        }
        else
            break;
    }
}

int main() {
    hospital_system();
    return 0;
}
