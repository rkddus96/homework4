#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}

    bool operator< (const Book& other) const
    {
        if (title != other.title)
        {
            return title < other.title;
        }
        return author < other.author;
    }
};

class BookDatabase
{
public:
    map<Book, int> bookStock;

public:
    

};

class BookManager {
public:
    BookDatabase& database; 

public:
    BookManager(BookDatabase& db) : database(db) {}
    // 책 추가 메서드
    void addBook(const string& title, const string& author, int quantity = 3) {
        Book book(title, author);
        if (database.bookStock.find(book) != database.bookStock.end())
        {
            cout << "이미 등록된 책입니다: " << title << " by " << author << endl;
        }
        else
        {
            database.bookStock[book] = quantity; // push_back 사용
            cout << "책이 추가되었습니다: " << title << " by " << author << " 재고 : " << quantity << endl;
        }
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (database.bookStock.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (auto& pair : database.bookStock) { // 일반적인 for문 사용
            cout << "- " << pair.first.title << " by " << pair.first.author << endl;
        }
    }

    pair<const Book, int>* findBookByTitle (string title)
    {
        for (auto& pair : database.bookStock)
        {
            if( pair.first.title == title)
            {
                return &pair;
            }
        }

        return nullptr;
    }

    pair<const Book, int>* findBookByAuthor(string author)
    {
        for (auto& pair : database.bookStock)
        {
            if (pair.first.author == author)
            {
                return &pair;
            }
        }

        return nullptr;
    }

};

class BorrowManager
{
private:
    BookManager& bookManager;

    
public:
    BorrowManager(BookManager& bm) : bookManager(bm) {}


    

    void borrowBookByTitle(string title)
    {
        pair<const Book, int>*  bookInfo = bookManager.findBookByTitle(title);
        if (bookInfo && bookInfo->second > 0)
        {
            cout << bookInfo->first.title << "을 대여하였습니다." << endl;
            bookInfo->second--;
        }
        else if (!bookInfo)
        {
            cout << "찾는 책이 없습니다." << endl;
        }
        else
        {
            cout << "수량이 부족하여 대여할 수 없습니다." << endl;
        }
    }

    void borrowBookByAuthor(string author)
    {
        pair<const Book, int>* bookInfo = bookManager.findBookByAuthor(author);
        if (bookInfo && bookInfo->second > 0)
        {
            cout << bookInfo->first.title << "을 대여하였습니다." << endl;
            bookInfo->second--;
        }
        else if (!bookInfo)
        {
            cout << "찾는 책이 없습니다." << endl;
        }
        else
        {
            cout << "수량이 부족하여 대여할 수 없습니다." << endl;
        }
    }

    void returnBook(string title)
    {
        pair<const Book, int>* bookInfo = bookManager.findBookByTitle(title);
        if (bookInfo)
        {
            if (bookInfo->second < 3)
            cout << "반납을 완료하였습니다." << endl;
            bookInfo->second++;
        }
        else
        {
            cout << "반납하지 않아도 됩니다." << endl;
        }
    }

    void displayStock()
    {
        if (bookManager.database.bookStock.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (auto& pair : bookManager.database.bookStock) { // 일반적인 for문 사용
            cout << "- " << pair.first.title << " by " << pair.first.author << " 재고 : " << pair.second << endl;
        }
    }


};

int main() {
    BookDatabase database;
    BookManager manager(database);
    BorrowManager borrower(manager);

    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl;       // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl;   // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 대여 (제목)" << endl; // 책 제목으로 대여
        cout << "4. 책 대여 (저자)" << endl; // 책 저자로 대여
        cout << "5. 책 반납" << endl;       // 책 제목으로 반납
        cout << "6. 재고 출력" << endl;     // 현재 책 재고 출력
        cout << "7. 종료" << endl;         // 프로그램 종료
        cout << "선택: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            string title, author;
            int quantity;
            cout << "책 제목: ";
            cin.ignore();
            getline(cin, title);
            cout << "책 저자: ";
            getline(cin, author);
            cout << "책 초기 재고: ";
            cin >> quantity;
            manager.addBook(title, author, quantity);
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 책 대여 (제목)
            string title;
            cout << "대여할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrower.borrowBookByTitle(title);
        }
        else if (choice == 4) {
            // 4번 선택: 책 대여 (저자)
            string author;
            cout << "대여할 책 저자: ";
            cin.ignore();
            getline(cin, author);
            borrower.borrowBookByAuthor(author);
        }
        else if (choice == 5) {
            // 5번 선택: 책 반납
            string title;
            cout << "반납할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrower.returnBook(title);
        }
        else if (choice == 6) {
            // 6번 선택: 재고 출력
            borrower.displayStock();
        }
        else if (choice == 7) {
            // 7번 선택: 종료
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            // 잘못된 입력 처리
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
