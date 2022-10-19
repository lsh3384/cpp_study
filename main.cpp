#include <iostream>
#include <memory>

using namespace std;

class Person
{
private:
    string name_;
    int age_;
public:
    Person(const string& name, int age)
    : name_(name), age_(age)
    {
        cout << "initialzer called!" << endl;
    };

    ~Person() {
        cout << "closed!" << endl;
        cout << this->name_ << this->age_ << endl;
    }
    void print_info() {
        cout << "name: " << this->name_ << "age: " << this->age_ << endl;
    }
};

void unique_ptr_test() {
    std::cout << "start of unique_ptr_test" << std::endl;
    std::unique_ptr<Person> u1 = std::make_unique<Person>("hello", 1);
    std::cout << "end of unique_ptr_test" << std::endl;  // 끝나는 시점에 u1의 소멸자가 호출이 되고 힙영역에 할당되었던 메모리가 해제됨
}

void shared_ptr_test() {
    std::cout << "start of shared_ptr_test" << std::endl;
    std::shared_ptr<int> s1 = std::make_shared<int>(22);
    std::cout << "end of shared_ptr_test" << std::endl;  // 끝나는 시점에 u1의 소멸자가 호출이 되고 힙영역에 할당되었던 메모리가 해제됨
}

int main() {

    unique_ptr_test();

    shared_ptr_test();

    std::shared_ptr<int> s1 = std::make_shared<int>(10);
    std::cout << s1.use_count() << std::endl;

    auto s2(s1);  // 복사 생성자 초기화
    std::cout << s2.use_count() << std::endl;

    std::shared_ptr<Person> s5 = std::make_shared<Person>("kim", 22);

    {
        std::shared_ptr<int> s3 = s1;
        std::cout << s1.use_count() << " " << s3.use_count() << std::endl;

        std::shared_ptr<Person> person01 = std::make_shared<Person>("gildong", 29);
        std::cout << person01.use_count() << std::endl;  // 블록 스코프를 만나서 스택영역에서 사라질 때 소멸자 호출
    }

    std::cout << s1.use_count() << " " << s2.use_count() <<  std::endl;
    s1.reset();
    std::cout << s1.use_count() << " " << s2.use_count() <<  std::endl;


    auto weak1 = std::make_shared<int>(77);
    std::cout << "weak1: " << weak1.use_count() <<  std::endl;


    std::weak_ptr<int> weak2 = weak1;
    std::cout << "weak2: " << weak2.use_count() <<  std::endl;  // (5)

    return 0;
}