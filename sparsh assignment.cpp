#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
string current_date() {
  std::time_t currentTime = std::time(nullptr);
  char buffer[80]; 
  std::strftime(buffer, sizeof(buffer), "%d-%m-%Y",
                std::localtime(&currentTime));
  return string(buffer);
}
int num_days(string date1_str, string date2_str) {
  std::tm date1 = {};
  std::tm date2 = {};
  std::istringstream date1_stream(date1_str);
  std::istringstream date2_stream(date2_str);
  date1_stream >> std::get_time(&date1, "%d-%m-%Y");
  date2_stream >> std::get_time(&date2, "%d-%m-%Y");
  if (date1_stream.fail() || date2_stream.fail()) {
    std::cerr << "Error parsing dates." << std::endl;
    return 1;
  }
  auto time_point1 =
      std::chrono::system_clock::from_time_t(std::mktime(&date1));
  auto time_point2 =
      std::chrono::system_clock::from_time_t(std::mktime(&date2));
  auto duration =
      std::chrono::duration_cast<std::chrono::hours>(time_point2 - time_point1);
  int days = duration.count() / 24; 
  return days;
}

class Books {
public:
  string Title;
  string Author;
  int year_published;
  int available_copies;
  int total_copies;
  bool is_reserved = false;
  Books(string Title, string Author, int year_published, int available_copies,
        int total_copies) {
    this->Title = Title;
    this->Author = Author;
    this->year_published = year_published;
    this->available_copies = available_copies;
    this->total_copies = total_copies;
  }

public:
  void CheckOut(string name) {
    if (available_copies > 0 && is_reserved == false) {
    cout<<"\""<<this->Title <<"\""<< " "<< "Checked Out"<<endl;
      available_copies -= 1;
    } else if (available_copies > 0 && is_reserved == true) {
      cout <<"\""<<this->Title << "\""<<" IS RESERVED, CANNOT CHECK OUT" << endl;
      is_reserved = false;
    } else {
      cout << "Book Not Available" << endl;
    }
  }
  void CheckIn(string name) {
    if (available_copies < total_copies) {
    cout<<"\""<<this->Title <<"\""<<" "<<"CHECKED IN"<<endl;
      available_copies += 1;
    } else {
      cout << "BOOK IN EXCESS" << endl;
    }
  }
};

class LibraryPatron {

public:
  int patron_ID;
  string name;
  vector<pair<Books *, string>> CheckedOutBooks;
  LibraryPatron(int patron_ID, string name) {
    this->patron_ID = patron_ID;
    this->name = name;
  }

public:
  void CheckOutBook(Books *book, string date_CheckOut,string name_) {
    //   book here is pointer
    CheckedOutBooks.push_back({book, date_CheckOut});
    book->CheckOut(name_);
  }
  void CheckInBook(Books *book, string date_checkOut, string date_submission,string name_) {
    pair<Books *, string> target_pair = {book, date_checkOut};
    auto iter =
        std::find(CheckedOutBooks.begin(), CheckedOutBooks.end(), target_pair);
    if (iter != CheckedOutBooks.end()) {
      int days = num_days(date_checkOut, date_submission);
      if (days <= 15) {
        CheckedOutBooks.erase(iter);
        book->CheckIn(name_);
      } else {
        cout <<"\""<< book->Title<<"\""<<" "<<"crossed due date"
             << " : "
             << "IMPOSED FINE = " << (days - 15) * 5 << "$" << endl;
        CheckedOutBooks.erase(iter);
        book->CheckIn(name);
      }
    } else {
      cout << book->Title << " "
           << "WAS NEVER CHECKED OUT" << endl;
    }
  }
  void checked_out_BookTitle() {
    for (int i = 0; i < CheckedOutBooks.size(); i++) {
      cout << CheckedOutBooks[i].first->Title << endl;
    }
  }
};
class LibraryTransaction {
public:
  string patron_name;
  string book_name;
  string date;
  LibraryTransaction(LibraryPatron *patron, Books *book, string date) {
    this->patron_name = patron->name;
    this->book_name = book->Title;
    this->date = date;
  }
  void statement_CheckOut(Books *book) {
    cout <<"\""<< book->Title<<"\"" << " "
         << "was CHECKED OUT on"
         << " " << this->date <<" by "<<" patron "<<"\""<<patron_name<<"\""<< endl;
  }
  void statement_CheckIn(Books *book,string date_) {
    cout <<"\""<<book->Title<<"\""<< " "
         << "is "<<"CHECKED IN on"
         << " " << date_ <<" by "<<" patron "<<"\""<<patron_name<<"\""<< endl;
  }
};

class LibraryBranch {
public:
  Books *book_type;
  LibraryPatron *patron;

public:
  LibraryBranch(Books *book_type, LibraryPatron *patron) {
    this->book_type = book_type;
    this->patron = patron;
  }
};

class reservation_by_patrons {
public:
  Books *book;
  LibraryPatron *patron;

public:
  reservation_by_patrons(Books *book, LibraryPatron *patron) {
    this->book = book;
    this->patron = patron;
  }
  void reserve() {
    if (book->available_copies > 0) {
      cout <<"\""<< book->Title <<"\""<< " IS AVAILABLE, NO NEED TO RESERVE" << endl;
    } else {
      book->is_reserved = true;
      cout <<"\""<< book->Title<<"\""<< " "
           << "IS RESERVED BY " << patron->name << endl;
    }
  }
};
bool check_authenticity(string name,int roll_number){
    vector<pair<int,string>> studentsData = {
        {230001, "Sophie"},
        {230002, "Noah"},
        {230003, "Avery"},
        {230004, "Liam"},
        {230005, "Ella"},
        {230006, "Oliver"},
        {230007, "Sophia"},
        {230008, "Emma"},
        {230009, "Logan"},
        {230010, "Amelia"},
        {230011, "Olivia"},
        {230012, "William"},
        {230013, "Grace"},
        {230014, "Daniel"},
        {230015, "Lily"},
        {230016, "Henry"},
        {230017, "Ava"},
        {230018, "Samuel"},
        {230019, "Sophie"},
        {230020, "Mason"},
        {230021, "Emily"},
        {230022, "Ethan"},
        {230023, "Isabella"},
        {230024, "Liam"},
        {230025, "Mia"},
        {230026, "Alexander"},
        {230027, "Aiden"},
        {230028, "Ella"},
        {230029, "Chloe"},
        {230030, "Logan"},
        {230031, "Grace"},
        {230032, "Sophie"},
        {230033, "Jackson"},
        {230034, "Avery"},
        {230035, "Lucas"},
        {230036, "Layla"},
        {230037, "Benjamin"},
        {230038, "Emma"},
        {230039, "Zoe"},
        {230040, "Caleb"},
        {230041, "Madison"},
        {230042, "Elijah"},
        {230043, "Abigail"},
        {230044, "Gabriel"},
        {230045, "Aria"},
        {230046, "Jackson"},
        {230047, "Scarlett"},
        {230048, "Nathan"},
        {230049, "Hannah"},
        {230050, "Isaac"},
        {230051, "Ava"},
        {230052, "Carter"},
        {230053, "Evelyn"},
        {230054, "Owen"},
        {230055, "Amelia"},
        {230056, "Wyatt"},
        {230057, "Victoria"},
        {230058, "Leo"},
        {230059, "Peyton"},
        {230060, "Mila"}};
    bool presence=false;
    for(int i=0;i<80;i++){
        pair<int ,string> expected_data={roll_number,name};
        if(expected_data==studentsData[i]){
            presence=true;
            break;
        }
    }
    return presence;
}
void check_out_book(LibraryBranch* type, Books* book_,string date){
    int roll_number;
    string name;
    cout<<"PLEASE ENTER YOUR ROLL NO. : ";
    cin>>roll_number;
    cout<<endl;
    cout<<"PLEASE ENTER YOUR NAME : ";
    cin>>name;
    cout<<endl;
    if(check_authenticity(name,roll_number)){
        type->patron->CheckOutBook(book_ , date,name);
        LibraryTransaction transaction(type->patron,book_,date);
        transaction.statement_CheckOut(book_);
    }
    else{
        cout<<"USER IS NOT AUTHENTICATED :("<<endl;
    }
}
void check_in_book(LibraryBranch* type, Books* book_,string date_CheckOut,string date_CheckIn){
    int copies = book_->available_copies;
    int roll_number_;
    string name_;
    cout<<"PLEASE ENTER YOUR ROLL NO. TO CHECK IN: ";
    cin>>roll_number_;
    cout<<endl;
    cout<<"PLEASE ENTER YOUR NAME TO CHECK IN : ";
    cin>>name_;
    cout<<endl;
    if(check_authenticity(name_,roll_number_)){
        type->patron->CheckInBook(book_, date_CheckOut, date_CheckIn,name_);
        if(copies<book_->available_copies){
            LibraryTransaction transaction2(type->patron,book_,date_CheckOut);
            transaction2.statement_CheckIn(book_,date_CheckIn);
        }
        cout<<"THANK YOU "<<endl;
    }
    else{
        cout<<"USER IS NOT AUTHENTICATED :("<<endl;
    }
}
int main() {
  LibraryPatron patron_comedy = {1011, "Alexa"};
Books book_comedy[10] = {
       {"Laugh Out Loud", "Jane Doe", 2010, 30, 50},
       {"Hilarious Times", "John Smith", 2015, 25, 40},
       {"Comic Relief", "Alice Johnson", 2012, 15, 30},
       {"Witty Jokes", "Bob Anderson", 2018, 20, 35},
       {"Giggle Fest", "Emily White", 2009, 10, 20},
       {"Funny Business", "Tom Brown", 2014, 18, 25},
       {"Humor Haven", "Sara Miller", 2017, 22, 40},
       {"Chuckling Charm", "Chris Taylor", 2011, 28, 45},
       {"Comedy Carousel", "David Clark", 2019, 12, 30},
       {"Jovial Tales", "Jessica Davis", 2016, 24, 38}};
  LibraryBranch comedy(book_comedy, &patron_comedy);
  LibraryPatron patron_horror = {1015, "Emily"};
  Books book_horror[10] = {
    {"Spooky Shadows", "Michelle Dark", 2013, 20, 30},
    {"Haunted Encounters", "Elijah Shadow", 2016, 15, 25},
    {"Eerie Tales", "Isabella Moonlight", 2011, 30, 45},
    {"Whispering Nightmares", "Lucas Fear", 2018, 10, 18},
    {"Secrets of Darkness", "Ava Midnight", 2015, 25, 40},
    {"Silent Screams", "Liam Raven", 2012, 18, 30},
    {"Ghostly Chronicles", "Sophie Bloodmoon", 2017, 8, 15},
    {"Dreadful Dreams", "Christopher Haunter", 2014, 22, 35},
    {"Height of Horrors", "Emma Haunt", 2019, 12, 22},
    {"Mysterious Midnight", "Alexander Blackwood", 2020, 28, 50}
};

  LibraryBranch horror(book_horror, &patron_horror);
  LibraryPatron patron_romance = {1013, "Sarah"};
  Books book_romance[10] = {
      {"Love in Bloom", "Emma Rose", 2012, 20, 35},
      {"Hearts Entwined", "David Sparks", 2016, 15, 25},
      {"Passionate Promises", "Sophie Lovejoy", 2010, 25, 40},
      {"Eternal Embrace", "Ryan Evergreen", 2015, 18, 30},
      {"Sweet Serendipity", "Lily Harmony", 2018, 22, 38},
      {"Cupid's Arrow", "Alexandra Bliss", 2013, 12, 20},
      {"Enchanting Moments", "Oliver Moonlight", 2017, 28, 45},
      {"Romantic Rendezvous", "Isabella Dreamer", 2011, 30, 50},
      {"Whispers of Love", "Christopher Rosewood", 2014, 10, 15},
      {"Destined Hearts", "Madison Rivers", 2019, 24, 42}};
  LibraryBranch romance(book_romance, &patron_romance);
  check_out_book(&comedy, &book_comedy[6],"23-01-2024");
  check_out_book(&horror, &book_horror[7],"24-01-2024");
  check_in_book(&comedy, &book_comedy[6],"23-01-2024","30-03-2024");
  check_in_book(&horror, &book_horror[7],"24-01-2024","30-01-2024");
  return 0;
}