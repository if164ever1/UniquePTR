// UniquePTR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
class CUniqueptr {
private:
    T* ppointer;
public:
    CUniqueptr() {};
    CUniqueptr(T* pointer)
        : ppointer(pointer) 
    {}
    CUniqueptr(CUniqueptr&& robject)
        : ppointer{ robject.ppointer } {
        robject.ppointer = nullptr;
    }

    CUniqueptr(const CUniqueptr&) = delete;
    CUniqueptr& operator = (const CUniqueptr&) = delete;

    CUniqueptr& operator=(CUniqueptr&& robject){
        if (ppointer)
            delete ppointer;
        ppointer = robject.ppointer;
        robject.ppointer = nullptr;
        return *this;
    }

    ~CUniqueptr() {
        if (ppointer)
            delete ppointer;
    }

    T* Getptr() { return ppointer; }
};


class CTestClass {
    const char* m_pname;
public:
    CTestClass():m_pname("") {};
    CTestClass(const char* n) :m_pname(n) {
        std::cout << "Konstruktor <CTestClass> name : " << m_pname << "\n";
    }
    ~CTestClass() {
        std::cout << "Destruktor <CTestClass> name : " << m_pname << "\n";
    }
};

void ThirdTestShow(CUniqueptr<CTestClass> thirdp) {
    std::cout << "void ThirdTestShow name : " << thirdp.Getptr() << "\n";
}

void SecondTestShow(CUniqueptr<CTestClass> secondp) {
    std::cout << "void SecondTestShow name : " << secondp.Getptr() << "\n";
    std::cout << "\n\nWe created new object and moved him to third fucntion\n";
    CTestClass* b = new CTestClass("ptr-2");
    secondp = b;
    ThirdTestShow(std::move(secondp));
}

void FirstTestShow(CUniqueptr<CTestClass> firstp) {
    std::cout << "void FirstTestShow name : " << firstp.Getptr() << "\n";
    SecondTestShow(std::move(firstp));
    std::cout << "AFRER A MOVED PTR to another function <void SecondTestShow> name : " << firstp.Getptr() << "\n";
}



int main()
{
    CTestClass*pa = new CTestClass("ptr");
    auto ptr = CUniqueptr<CTestClass>(pa);
    std::cout << "<Main function> ptr : " << ptr.Getptr() << "\n";
    FirstTestShow(std::move(ptr));
    std::cout << "<Main function> ptr : " << ptr.Getptr() << "\n";
}


