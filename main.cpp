#include<iostream>
#include<string>
using namespace std;

static int lib_count=0;
class library;
class book{
    int book_id;
    string name_of_author;
    string name_of_book;
    int published_year;
    bool is_issued;
    public:
    book(){
        book_id=0,name_of_author="",name_of_book="",published_year=0,is_issued=false;
    }

    book(int a, string b, string c, int d){
        book_id=a,name_of_author=b,name_of_book=c,published_year=d,is_issued=false;
    }

    book (book &b){
        book_id=b.book_id;
        name_of_author=b.name_of_author;
        name_of_book=b.name_of_book;
        published_year=b.published_year;
        is_issued=b.is_issued;
    }

    friend ostream& operator<<(ostream &print, const book &b){
        print <<"\nBook ID : "<<b.book_id<<"\nTitle : "<<b.name_of_book<<"\nAuthor Name : "<<b.name_of_author
        <<"\nPublished Year : "<<b.published_year<<"\nAvailable Status : "<<(!(b.is_issued)?"Yes" : "No")<<endl;
        return print;
    }

    friend class library;
};

 

class library{
    book *set_of_books;
    int tot_books;
    int max_slot;
    public:
    library(){
        tot_books=0;
        max_slot=10;
        set_of_books = new book[max_slot];
    }

    void include_book(const book &b){
        if(tot_books>=max_slot){
            increase_slot();
        }
        set_of_books[tot_books++]=b;
        lib_count++;
    }

    void remove_book(int bookid){
        for(int i=0;i<tot_books;i++){
            if(set_of_books[i].book_id==bookid){
                for(int j=i;j<tot_books-1;j++){
                    set_of_books[j]=set_of_books[j+1];
                }
                tot_books--;
                lib_count--;
                cout<<"Book with book id : "<<bookid<<" has been removed!"<<endl;
                return;
            }
        }
        cout<<"Book with book id : "<<bookid<<" is not found!"<<endl;
    }

    void issue_book(int bookid){
        for(int i=0;i<tot_books;i++){
            if(set_of_books[i].book_id==bookid){
                if(!set_of_books[i].is_issued){
                    cout<<"Book with book id : "<<bookid<<" has been issued!"<<endl;
                    set_of_books[i].is_issued=true;
                    return;
                }
                else{
                    cout<<"Book with book id : "<<bookid<<" is currently unavailable because it has already been issued!"<<endl;
                    return;
                }
            }
        }
        cout<<"Book with book id : "<<bookid<<" is not available!"<<endl;
    }

    void return_book(int bookid){
        for(int i=0;i<tot_books;i++){
            if(set_of_books[i].book_id==bookid && set_of_books[i].is_issued){
                cout<<"Book with book id : "<<bookid<<" has been returned!"<<endl;
                set_of_books[i].is_issued=false;
                return;
            }
        }
        cout<<"Book with book id :"<<bookid<<" is either already returned or it doesn't belong to this library!"<<endl;
    }

    void display_books(){
        for(int i=0;i<tot_books;i++){
            cout<<set_of_books[i]<<endl;
        }
    }

    static int get_total_book_count(){
        return lib_count;
    }

    ~library(){
        delete[] set_of_books;
    }

    private:
    void increase_slot(){
        max_slot*=2;
        book *t;
        t=new book[max_slot];
        for(int i=0;i<max_slot;i++){
            t[i]=set_of_books[i];
        }
        delete[] set_of_books;
        set_of_books=t;
    }
    
};

int main(){
    library L;

    //adding books to the library
    L.include_book(book(121,"JK Rowling","Harry Potter",1972));
    L.include_book(book(122,"Stanlee","The Marvels",1951));
    L.include_book(book(123,"Abdul Kalam","The Wings of Fire",1942));
    L.include_book(book(124,"William Shakesphere","Romeo and Juliet",1967));
    L.include_book(book(125,"Toni Morrison","Beloved",1987));

    L.display_books();

    //removing a book
    L.remove_book(124);
    L.remove_book(125);
    
    L.display_books();

    //issuing and returning books
    L.issue_book(121);
    L.issue_book(123);
    L.issue_book(124);

    L.return_book(121);
    L.return_book(122);
    L.display_books();

    //getting the total books count
    cout<<"Books count in the library is : "<<lib_count<<endl;

}