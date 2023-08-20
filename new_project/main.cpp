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

string names[MAX_SPECIALIZATION_LEN][MAX_QUEUE_LEN];//name of patient and number of its queue in each specialization
int status[MAX_SPECIALIZATION_LEN][MAX_QUEUE_LEN];//status => regular or urgent
int cnt_queue[MAX_SPECIALIZATION_LEN];//to know queue length for each specialization

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "Enter your choice: " << endl;
        cout << "1) Add patient " << endl;
        cout << "2) Print patient " << endl;
        cout << "3) Get next patient " << endl;
        cout << "4) Exit " << endl;
        cin >> choice;
        if (!(choice >= 1 && choice <= 4)) {
            cout << "Invalid input ,please renter" << endl;
            choice = -1;
        }
    }
    return choice;
}

void add_in_begin(int spec, string name[], int st[]) {
    int size = cnt_queue[spec];
    for (int i = size - 1; i >= 0; --i) {
        name[i + 1] = name[i];
        st[i + 1] = st[i];
    }
    cnt_queue[spec]++;
}
void remove_from_begin(int spec,string name[],int st[]){
    //remove from the beginning of the queue ,so we shift left
    int size=cnt_queue[spec];
    for (int i = 1; i <size ; ++i) {
        name[i-1]=name[i];
        st[i-1]=st[i];
    }
    cnt_queue[spec]--;
}

void add_patient() {
    string name;
    int spec;
    int st;
    cout << "Enter specialization,name,status: ";
    cin >> spec >> name >> st;
    int pos = cnt_queue[spec];
    if (pos >= MAX_QUEUE_LEN) {
        cout << "no more queues , please wait" << endl;
        return ;
    }
    if (st == 0) {
        names[spec][pos] = name;
        status[spec][pos] = st;
        cnt_queue[spec]++;
    } else {
        add_in_begin(spec, names[spec], status[spec]);
        names[spec][0] = name;
        status[spec][0] = st;
    }

}

void print_one_patient(int spec, string name[], int st[]) {
    int size = cnt_queue[spec];
    if (size == 0) {
        return;
    }
    cout << "There are " << size << " patients in specialization " << spec << endl;
    for (int i = 0; i < size; ++i) {
        cout << name[i] << " ";
        if (st[i] == 0) {
            cout << "regular" << endl;
        } else {
            cout << "urgent " << endl;
        }
    }
    cout << endl;
}

void print_patients() {
    //iterate all specializations
    cout << "**************************************" << endl;
    for (int spec = 0; spec < MAX_SPECIALIZATION_LEN; ++spec) {
        print_one_patient(spec, names[spec], status[spec]);
    }
}
void get_next_patient(){
    cout<<"Enter specialization: ";
    int spec;
    cin>>spec;
    int size=cnt_queue[spec];
    if(size==0){
        cout<<"No patients at this moment "<<endl;
    }
    else{
        cout<<endl<<names[spec][0]<<" your turn "<<endl;
        remove_from_begin(spec,names[spec],status[spec]);
    }
}

void hospital_system() {
    while (true) {
        int choice = menu();
        if (choice == 1) {
            add_patient();
        } else if (choice == 2) {
            print_patients();
        }
        else if (choice==3){
            get_next_patient();
        }
        else {
            break;
        }
    }
}

int main() {
    hospital_system();

    return 0;
}
