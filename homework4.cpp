#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std; // namespace std ���

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
    // å �߰� �޼���
    void addBook(const string& title, const string& author, int quantity = 3) {
        Book book(title, author);
        if (database.bookStock.find(book) != database.bookStock.end())
        {
            cout << "�̹� ��ϵ� å�Դϴ�: " << title << " by " << author << endl;
        }
        else
        {
            database.bookStock[book] = quantity; // push_back ���
            cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << " ��� : " << quantity << endl;
        }
    }

    // ��� å ��� �޼���
    void displayAllBooks() const {
        if (database.bookStock.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (auto& pair : database.bookStock) { // �Ϲ����� for�� ���
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
            cout << bookInfo->first.title << "�� �뿩�Ͽ����ϴ�." << endl;
            bookInfo->second--;
        }
        else if (!bookInfo)
        {
            cout << "ã�� å�� �����ϴ�." << endl;
        }
        else
        {
            cout << "������ �����Ͽ� �뿩�� �� �����ϴ�." << endl;
        }
    }

    void borrowBookByAuthor(string author)
    {
        pair<const Book, int>* bookInfo = bookManager.findBookByAuthor(author);
        if (bookInfo && bookInfo->second > 0)
        {
            cout << bookInfo->first.title << "�� �뿩�Ͽ����ϴ�." << endl;
            bookInfo->second--;
        }
        else if (!bookInfo)
        {
            cout << "ã�� å�� �����ϴ�." << endl;
        }
        else
        {
            cout << "������ �����Ͽ� �뿩�� �� �����ϴ�." << endl;
        }
    }

    void returnBook(string title)
    {
        pair<const Book, int>* bookInfo = bookManager.findBookByTitle(title);
        if (bookInfo)
        {
            if (bookInfo->second < 3)
            cout << "�ݳ��� �Ϸ��Ͽ����ϴ�." << endl;
            bookInfo->second++;
        }
        else
        {
            cout << "�ݳ����� �ʾƵ� �˴ϴ�." << endl;
        }
    }

    void displayStock()
    {
        if (bookManager.database.bookStock.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (auto& pair : bookManager.database.bookStock) { // �Ϲ����� for�� ���
            cout << "- " << pair.first.title << " by " << pair.first.author << " ��� : " << pair.second << endl;
        }
    }


};

int main() {
    BookDatabase database;
    BookManager manager(database);
    BorrowManager borrower(manager);

    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl;       // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl;   // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å �뿩 (����)" << endl; // å �������� �뿩
        cout << "4. å �뿩 (����)" << endl; // å ���ڷ� �뿩
        cout << "5. å �ݳ�" << endl;       // å �������� �ݳ�
        cout << "6. ��� ���" << endl;     // ���� å ��� ���
        cout << "7. ����" << endl;         // ���α׷� ����
        cout << "����: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            string title, author;
            int quantity;
            cout << "å ����: ";
            cin.ignore();
            getline(cin, title);
            cout << "å ����: ";
            getline(cin, author);
            cout << "å �ʱ� ���: ";
            cin >> quantity;
            manager.addBook(title, author, quantity);
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3�� ����: å �뿩 (����)
            string title;
            cout << "�뿩�� å ����: ";
            cin.ignore();
            getline(cin, title);
            borrower.borrowBookByTitle(title);
        }
        else if (choice == 4) {
            // 4�� ����: å �뿩 (����)
            string author;
            cout << "�뿩�� å ����: ";
            cin.ignore();
            getline(cin, author);
            borrower.borrowBookByAuthor(author);
        }
        else if (choice == 5) {
            // 5�� ����: å �ݳ�
            string title;
            cout << "�ݳ��� å ����: ";
            cin.ignore();
            getline(cin, title);
            borrower.returnBook(title);
        }
        else if (choice == 6) {
            // 6�� ����: ��� ���
            borrower.displayStock();
        }
        else if (choice == 7) {
            // 7�� ����: ����
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        }
        else {
            // �߸��� �Է� ó��
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}
