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
        bookId=-1;
        quantity=borrowed=0;
    }
    void read(){
        cout<<"Enter id,name,quantity: ";
        cin>>bookId>>bookName>>quantity;
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
    bool borrow(){
        if(quantity-borrowed==0)
        {
            cout<<"There are no available copies"<<endl;
            return false;
        }
        borrowed++;
        return true;
    }
    void return_book(){
       borrowed--;
    }

};
bool cmp_by_name(book &b1,book &b2){
    return b1.bookName<b2.bookName;
}
bool cmp_by_id(book &b1,book &b2){
    return b1.bookId<b2.bookId;
}
struct user{
    int id{};
    string userName;
    int borrowedBooks[MAX_BOOKS];
    int len{};
    user(){
        id=-1;
        len=0;
    }
    void read(){
        cout<<"Enter your name and your national-ID: ";
        cin>>userName>>id;
    }
    void borrow(int book_id,int user_id){
        borrowedBooks[len++]=book_id;
//        userBorrow[len]=user_id;
    }

    bool is_borrowed(int book_id){
        for (int i = 0; i <len ; ++i) {
            if(book_id==borrowedBooks[i]){
                return true;
            }
        }
        return false;
    }
    void return_book(int book_id){
        int flag=0;
        for (int i = 0; i <len ; ++i) {
            if(borrowedBooks[i]==book_id){
                for (int j = i+1; j <len ; ++j) {
                    borrowedBooks[j-1]=borrowedBooks[j];
                }
                len--;
                flag=1;
                break;
            }
        }
        if(!flag){
            cout<<"This user: "<<userName<<" didn't borrow this book: "<<book_id<<endl;
        }
    }
    void print()
    {
        cout<<"user: "<<userName<<" id: "<<id<<" ";
        if(len==0){
            cout<<"borrowed books ids: NONE"<<endl;
            return ;
        }
        sort(borrowedBooks,borrowedBooks+len);
        for (int i = 0; i <len ; ++i) {
            cout<<"borrowed books ids: "<<borrowedBooks[i];
        }
        cout<<endl;
    }


};

struct library{
    book books[MAX_BOOKS];
    user users[MAX_USERS];
    int num_of_books{};
    int num_of_users{};
    library(){
         num_of_books=0;
         num_of_users=0;
    }
    void add_book(){
        books[num_of_books++].read();
    }
    void search_book(){
        string name;
        cout<<"enter book name: ";
        cin>>name;
        int flag=0;
        for (int i = 0; i <num_of_books ; ++i) {
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

        sort(books,books+num_of_books,cmp_by_name);
        for (int i = 0; i <num_of_books ; ++i) {
            cout<<endl<<"id= "<<books[i].bookId<<" name= "<<books[i].bookName<<" quantity= "<<books[i].quantity<<" total_borrowed= "<<books[i].borrowed<<endl;
        }
    }
    void list_books_by_id(){
        sort(books,books+num_of_books, cmp_by_id);
        for (int i = 0; i <num_of_books ; ++i) {
            cout<<endl<<"id= "<<books[i].bookId<<" name= "<<books[i].bookName<<" quantity= "<<books[i].quantity<<" total_borrowed= "<<books[i].borrowed<<endl;        }
    }
    void add_user(){
        users[num_of_users++].read();
    }
    int check_books_name(string name){
        for (int i = 0; i <num_of_books ; ++i) {
            if(name==books[i].bookName){
                return i;
            }
        }
        return -1;
    }
    int check_users_name(string name){
        for (int i = 0; i <num_of_users ; ++i) {
            if(name==users[i].userName){
                return i;
            }
        }
        return -1;
    }
    bool check_user_books_names(int &usrIdx,int &bookIdx,int numOfTrials=4){
        string usrName,bookName;
        while(numOfTrials--){
            cout<<"Enter your name and book name: ";
            cin>>usrName>>bookName;
            bookIdx= check_books_name(bookName);
            if(bookIdx==-1){
                cout<<"There are no books with that name"<<endl;
                continue;
            }
            usrIdx= check_users_name(usrName);
            if(usrIdx==-1){
                cout<<"There are no users with that name "<<endl;
                continue;
            }
            return true;
        }
        cout<<"You entered so many trials ,please try later"<<endl;
        return false;

    }
    void borrow_book() {
        int user_idx, book_idx;
        if (!check_user_books_names(user_idx, book_idx))
            return;

        int user_id = users[user_idx].id;
        int book_id = books[book_idx].bookId;

        if (!books[book_idx].borrow())
            cout << "No more copies available right now\n";
        else
            users[user_idx].borrow(book_id,user_id);

    }
    void print_users_borrowed_book(){
        string book_name;
        cout<<"Enter book name: ";
        cin>>book_name;
        int book_idx= check_books_name(book_name);
        if(book_idx==-1){
            cout<<"There are no books with that name"<<endl;
            return ;
        }
        int bookId=books[book_idx].bookId;
        if(books[book_idx].borrowed==0){
            cout<<"There are no borrowed copies"<<endl;
            return;
        }
        for (int i = 0; i <num_of_users ; ++i) {
            if(users[i].is_borrowed(bookId)){
                cout<<users[i].userName<<endl;
            }
        }


    }
    void user_return_book(){
        string book_name,user_name;
        int userIdx,bookIdx;
        if(!check_user_books_names(userIdx,bookIdx)){
            return;
        }
        int book_id=books[bookIdx].bookId;
        books[bookIdx].return_book();
        users[userIdx].return_book(book_id);
    }
    void print_users(){
        for (int i = 0; i <num_of_users ; ++i) {
            users[i].print();
        }
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
            else if (choice==5){
                add_user();
            }
            else if (choice==6){
                borrow_book();
            }
            else if (choice==7){
                print_users_borrowed_book();
            }
            else if (choice==8){
                user_return_book();
            }
            else if (choice==9){
                print_users();
            }
            else{
                break;
            }
        }
    }

};
int main() {
    library lib=library() ;
    lib.library_system();
    return 0;
}
