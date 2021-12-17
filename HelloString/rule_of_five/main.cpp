#include <iostream>
#include <memory>
#include <cstring>

class AAA {
private:
    std::string mStr;

public:
    AAA() {
        std::cout << "AAA() !" << std::endl;
    };

    ~AAA() {
        std::cout << "~~~AAA() !" << std::endl;
    }

    void testFunc(std::shared_ptr<AAA> p) {
        std::cout << "test Func Call From : " << &p << std::endl;
    }

    AAA* getAddress() {
        return this;
    }

    int sumFunc(int a, int b) {
        return a + b;
    }
};

// 5-CGF -> destructor, copy constructor, move constructor,
// copy assignment operator, move assignment operator
// CGF = Compiler-Generated Functions

// Rule of zero :
// 소멸자, 복사/이동 생성자, 복사/이동 할당연산자가 정의되어있는 class의 wrapper class는 다음의 꼴을 가진다.

class ruleOfZero {
private:
    int mValue;
public:
// 5-CGF
    ruleOfZero() = default;
    ruleOfZero(const ruleOfZero&) = default;
    ruleOfZero(ruleOfZero&&) = default;
    ruleOfZero& operator=(const ruleOfZero&) = default;
    ruleOfZero& operator=(ruleOfZero&&) = default;

    ruleOfZero(const int value) : mValue(value) { }

    void print() {
        std::cout << "ruleOfZero mValue : " << mValue << std::endl;
    }
};

// 얇은 복사
// class ruleOfThree {
// private:
//     int mValue;

// public:
//     ruleOfThree(const int value) : mValue(value) { }
//     ~ruleOfThree() {
//         std::cout << "~ruleOfThree()" << std::endl;
//     }
//     ruleOfThree(const ruleOfThree &other) {
//     }
//     ruleOfThree &operator=(const ruleOfThree &other) {
//         std::cout << "operator=" << std::endl;
//         mValue = other.mValue;
//         return *this;
//     }
//     void print() {
//         std::cout << "ruleOfThree mValue : " << mValue << std::endl;
//     }
// };

class ruleOfThree {
private:
    char* str;
public:
    ruleOfThree(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    ruleOfThree& operator=(const ruleOfThree& other) {
        delete[] str;
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
        return *this;
    }
    ~ruleOfThree() {
        delete[] str;
    }
    void print() {
        std::cout << "ruleOfThree str : " << str << std::endl;
    }
};

class ruleOfFive {
private:
    char* str;
public:
    ruleOfFive(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    ~ruleOfFive() {
        delete[] str;
    }

    ruleOfFive(const ruleOfFive& other) : ruleOfFive(other.str) {
        std::cout << "copy constructor" << std::endl;
    }

    ruleOfFive(ruleOfFive&& other) noexcept : str(std::exchange(other.str, nullptr)) {
        std::cout << "move constructor" << std::endl;
    }

    ruleOfFive& operator=(const ruleOfFive& other) {
        std::cout << "copy assignment" << std::endl;
        return *this = ruleOfFive(other);
    }

    ruleOfFive& operator=(ruleOfFive&& other) noexcept {
        std::swap(str, other.str);
        std::cout << "move assignment" << std::endl;
        return *this;
    }

    void print() {
        std::cout << "ruleOfThree str : " << str << std::endl;
    }
};

class Person {
private:
    int num;
public:
    Person() {
        std::cout << "Person()" << std::endl;
    }
    virtual ~Person() {
        std::cout << "~Person()" << std::endl;
    }
};

class TEST : public Person {
public:
    TEST() {
        std::cout << "TEST()" << std::endl;
    }
    ~TEST() {
        std::cout << "~TEST()" << std::endl;
    }
};

int main(void) {
    Person *abc = new TEST();
    delete abc;

    ruleOfZero zero(10);
    zero.print();

    ruleOfThree threeOne("one");
    ruleOfThree threeTwo("two");
    threeOne.print();
    threeTwo.print();

    threeOne = threeTwo;

    threeOne.print();

    ruleOfFive fiveOne("five1");
    ruleOfFive fiveTwo("five2");

    fiveOne.print();
    fiveTwo.print();

    fiveOne = fiveTwo;
    ruleOfFive tempFive(std::move(fiveOne));
    // 이동 생성자 (fiveOne 데이터를 tempFive로 모두 넘기고 fiveOne은 소멸하여 사용하면 프로그램이 죽음)

    // fiveOne.print();
    tempFive.print();

    ruleOfFive fiveThree("five3");
    ruleOfFive fiveFour("five4");

    fiveThree = std::move(fiveFour);
    // 이동 대입 연산자 fiveThree와 fiveFour의 데이터를 맞바꿈
    fiveThree.print();
    fiveFour.print();
    
    return 0;
}