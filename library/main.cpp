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

const int MAX_BOOKS=10;
const int MAX_USERS=10;

struct book{
    string bookName;
    int bookId{};
    int quantity{};
    int borrowed{};
    book(){
        bookId=0;
        quantity=0;
        borrowed=0;
    }
    void read(){
        cout<<"Enter id,name,quantity: ";
        cin>>bookId>>bookName>>quantity;
        quantity++;
    }
    bool isPrefix(string pre){
        if(bookName.size()<pre.size())
            return false;
        for (int i = 0; i <pre.size() ; ++i) {
            if(bookName[i]!=pre[i])
                return false;
        }
        return true;
    }

};
bool cmp_by_name(book &b1,book &b2){
    return b1.bookName<b2.bookName;
}
bool cmp_by_id(book &b1,book &b2){
    return b1.bookId<b2.bookId;
}

struct library{
    book books[MAX_BOOKS];
    int idx=0;
    void add_book(){
        books[idx++].read();
    }
    void search_book(){
        string name;
        cout<<"enter book name: ";
        cin>>name;
        int flag=0;
        for (int i = 0; i <idx ; ++i) {
            if(books[i].isPrefix(name)){
                cout<<books[i].bookName<<endl;
                flag++;
            }
        }
        if(!flag){
            cout<<"There are not books with this prefix"<<endl;
        }

    }
    void list_books_by_name(){

        sort(books,books+idx,cmp_by_name);
        for (int i = 0; i <idx ; ++i) {
            cout<<endl<<"id= "<<books[i].bookId<<" name= "<<books[i].bookName<<" quantity= "<<books[i].quantity<<" total_borrowed= "<<books[i].borrowed<<endl;
        }
    }
    void list_books_by_id(){
        sort(books,books+idx, cmp_by_id);
        for (int i = 0; i <idx ; ++i) {
            cout<<endl<<"id= "<<books[i].bookId<<" name= "<<books[i].bookName<<" quantity= "<<books[i].quantity<<" total_borrowed= "<<books[i].borrowed<<endl;        }
    }

    int menu(){
        int choice=-1;
        while(choice==-1){
            cout<<"Your menu choice [1-10]: ";
            cin>>choice;
            if(!(choice>=1&&choice<=10)){
                cout<<"Invalid Input,please renter"<<endl;
                choice=-1;
            }
        }
        return choice;

    }
    void library_system(){
        while(true){
            int choice=menu();
            if(choice==1){
                add_book();
            }
            else if (choice==2){
                search_book();
            }
            else if (choice==3){
                list_books_by_name();
            }
            else if (choice==4){
                list_books_by_id();
            }
            else{
                break;
            }
        }
    }

};
int main() {
    library lib;
    lib.library_system();
    return 0;
}
