#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// Lớp giao diện Borrowable (có thể mượn)
class Borrowable {
public:
    virtual void borrow() = 0;
    virtual void returnItem() = 0;
    virtual bool isAvailable() const = 0;
    virtual ~Borrowable() = default;
};

// Lớp Book (Sách), kế thừa từ Borrowable
class Book : public Borrowable {
private:
    std::string title;
    std::string author;
    std::string ISBN;
    bool available;

public:
    // Constructor khởi tạo Book với tiêu đề, tác giả và ISBN
    Book(std::string t, std::string a, std::string i)
        : title(std::move(t)), author(std::move(a)), ISBN(std::move(i)), available(true) {}

    // Phương thức mượn sách
    void borrow() override {
        if (available) {
            available = false;
            std::cout << "Sách '" << title << "' đã được mượn." << std::endl;
        } else {
            std::cout << "Sách '" << title << "' không có sẵn để mượn." << std::endl;
        }
    }

    // Phương thức trả lại sách
    void returnItem() override {
        available = true;
        std::cout << "Sách '" << title << "' đã được trả lại." << std::endl;
    }

    // Kiểm tra xem sách có sẵn hay không
    bool isAvailable() const override {
        return available;
    }

    // Lấy tiêu đề của sách
    std::string getTitle() const { return title; }

    // Lấy tác giả của sách
    std::string getAuthor() const { return author; }

    // Lấy ISBN của sách
    std::string getISBN() const { return ISBN; }
};

// Lớp DVD, kế thừa từ Borrowable
class DVD : public Borrowable {
private:
    std::string title;
    std::string director;
    int duration;
    bool available;

public:
    // Constructor khởi tạo DVD với tiêu đề, đạo diễn và thời lượng
    DVD(std::string t, std::string d, int dur)
        : title(std::move(t)), director(std::move(d)), duration(dur), available(true) {}

    // Phương thức mượn DVD
    void borrow() override {
        if (available) {
            available = false;
            std::cout << "DVD '" << title << "' đã được mượn." << std::endl;
        } else {
            std::cout << "DVD '" << title << "' không có sẵn để mượn." << std::endl;
        }
    }

    // Phương thức trả lại DVD
    void returnItem() override {
        available = true;
        std::cout << "DVD '" << title << "' đã được trả lại." << std::endl;
    }

    // Kiểm tra xem DVD có sẵn hay không
    bool isAvailable() const override {
        return available;
    }

    // Lấy tiêu đề của DVD
    std::string getTitle() const { return title; }

    // Lấy đạo diễn của DVD
    std::string getDirector() const { return director; }

    // Lấy thời lượng của DVD
    int getDuration() const { return duration; }
};

// Lớp Library (Thư viện)
class Library {
private:
    std::vector<std::unique_ptr<Borrowable>> items;

public:
    // Phương thức thêm mục (sách hoặc DVD) vào thư viện
    void addItem(std::unique_ptr<Borrowable> item) {
        items.push_back(std::move(item));
    }

    // Phương thức mượn mục từ thư viện theo tiêu đề
    void borrowItem(const std::string& title) {
        auto it = std::find_if(items.begin(), items.end(), [&title](const auto& item) {
            if (auto book = dynamic_cast<Book*>(item.get())) {
                return book->getTitle() == title;
            }
            if (auto dvd = dynamic_cast<DVD*>(item.get())) {
                return dvd->getTitle() == title;
            }
            return false;
        });

        if (it != items.end()) {
            (*it)->borrow();
        } else {
            std::cout << "Không tìm thấy mục '" << title << "' trong thư viện." << std::endl;
        }
    }

    // Phương thức trả lại mục theo tiêu đề
    void returnItem(const std::string& title) {
        auto it = std::find_if(items.begin(), items.end(), [&title](const auto& item) {
            if (auto book = dynamic_cast<Book*>(item.get())) {
                return book->getTitle() == title;
            }
            if (auto dvd = dynamic_cast<DVD*>(item.get())) {
                return dvd->getTitle() == title;
            }
            return false;
        });

        if (it != items.end()) {
            (*it)->returnItem();
        } else {
            std::cout << "Không tìm thấy mục '" << title << "' trong thư viện." << std::endl;
        }
    }
};

// Hàm main để kiểm tra hệ thống thư viện
int main() {
    Library library;

    // Thêm một cuốn sách vào thư viện
    library.addItem(std::make_unique<Book>("Cuốn sách C++", "Tác giả A", "123456"));

    // Thêm một DVD vào thư viện
    library.addItem(std::make_unique<DVD>("DVD về Lập trình", "Đạo diễn B", 120));

    // Mượn sách
    library.borrowItem("Cuốn sách C++");

    // Mượn DVD
    library.borrowItem("DVD về Lập trình");

    // Trả lại sách
    library.returnItem("Cuốn sách C++");

    // Trả lại DVD
    library.returnItem("DVD về Lập trình");

    return 0;
}
