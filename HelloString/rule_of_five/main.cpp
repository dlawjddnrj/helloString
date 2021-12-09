#include <iostream>
#include <memory>
// 5-CGF -> destructor, copy constructor, move constructor,
// copy assignment operator, move assignment operator
// CGF = Compiler-Generated Functions


// Rule of zero :
// 소멸자, 복사/이동 생성자, 복사/이동 할당연산자가 정의되어있는 class의 wrapper class는 다음의 꼴을 가진다.

class ruleOfZero {
private:
    std::string str;
public:
// 5-CGF
    ruleOfZero() = default;
    ruleOfZero(const ruleOfZero&) = default;
    ruleOfZero(ruleOfZero&&) = default;
    ruleOfZero& operator=(const ruleOfZero&) = default;
    ruleOfZero& operator=(ruleOfZero&&) = default;

    ruleOfZero(const std::string &s) : str(s) { }
};

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

int main(void) {
    std::shared_ptr<AAA> a = std::make_shared<AAA>();
    std::cout << "a count : " << a.use_count() << std::endl;

    std::shared_ptr<AAA> b = a;
    std::cout << "b count : " << b.use_count() << std::endl;

    a->testFunc(a);
    b->testFunc(b);
    int result = b->sumFunc(3, 5);
    std::cout << "sumFunc result : " << result << std::endl;
    std::shared_ptr<AAA> c = a;
    c->testFunc(c);

    std::cout << "a count : " << a.use_count() << std::endl;
    std::cout << "b count : " << b.use_count() << std::endl;
    std::cout << "c count : " << c.use_count() << std::endl;

    std::cout << "a Address : " << a->getAddress() << std::endl;
    std::cout << "b Address : " << b->getAddress() << std::endl;
    std::cout << "c Address : " << c->getAddress() << std::endl;

    std::cout << "c count : " << b.use_count() << std::endl;
    c.reset();
    std::cout << "c count : " << b.use_count() << std::endl;

    std::cout << "b count : " << b.use_count() << std::endl;
    b.reset();
    std::cout << "b count : " << b.use_count() << std::endl;

    std::cout << "a count : " << a.use_count() << std::endl;
    a.reset();
    std::cout << "a count : " << a.use_count() << std::endl;
    
    return 0;
}