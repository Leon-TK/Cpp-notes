
//Notes:
//Use reference if you deny memory managment to user

class Class {};

//Creation
//Use raw pointer to indicate that this func returns lifetime object with no lifetime restricts
Class* getClass() { return new Class(); };


//Use reference to indicate that object cannot be deleted
class SomeClass1 {
    private:
    Class* m_Class = nullptr;
    public:
    Class& getClassUnmanaged() { return *m_Class; }; //Client code cannot manage lifetime of variable
};
class Relationship {
    class Association {
        class Composition {};
        class Aggregation {};
    };
};
namespace Generalization {
    class A {};
    class B : A {};
};
namespace Implementation
{
    class A { public: virtual void Do() = 0; };
    class B : public A { public: virtual void Do() override {}; };
};

//Class can manage lifetime
class Composition { 
    Class* cls = nullptr;
    public:
    ~Composition() { delete cls; };
};
//Class cannot manage lifetime
class Aggregation { 
    Class& cls;
    public:
    Aggregation(Class& cls) : cls(cls) {};
};

//Any relation between units
//But I perfer to restrict lifetime managing
//Class cannot manage lifetime
class Association { 
    public:
    void Do(Composition& comp) {};
};

//Creational patterns
class Creation {
    public:
    Class* create() { return new Class(); };
};