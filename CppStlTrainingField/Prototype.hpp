namespace Prototype
{
    //TODO: todo note
    //FO. future optimization note suggestion or assumption
    //Q. Question note. Prototype question. 
    //Q. This is a call of a function. What to usse for function definition? A macros?

    class SpmeClass {};
    using ProtoClass = SpmeClass;
    // SomeClass2<ProtoClass> ...
    template<typename Func>
    class ProtoFunction {
        public:
        static void Exec(Func func) {
            func();
        };
    };
    //past this instead of fucntion\
    must be declared by macro or ???
    template<typename T>
    class ProtoComment {
        public:
        static void Comment(std::string comment) { //(type, reason, )

        };
        static void Uncomment() {

        };
    };
    template<typename T>
    class ProtoStatement {
        public:
        static void Statement(std::string statement) {
            
        };
    };
    void Test() {
        /* auto lamb = []() { std::cout << std::format("Hello\n")};
        ProtoFunction::Exec(lamb); */
    };

    namespace TestSpace
    {
        template<typename Ret, typename... Args>
        Ret func(Args... args) {

        };

        #define STATIC_DEF(name, b) constexpr bool name##IsStatic = b;
        #define INIT_TYPE(name, type) \
            void InitType() {\
                if constexpr (!name##IsStatic) {\
                    name = type();\
                }\
            };
        
        #define STATIC_VAR static
        #ifdef STATIC_VAR
        STATIC_DEF(var, true)
        #else
        STATIC_DEF(var, false)
        #endif

        #define ACCESS1 public:
        #define ACCESS2 private:

        template<typename T, class... Parents>
        class Temp : public Parents... {
            ACCESS1
            STATIC_VAR T var;
            Temp() {
                InitType();
            };
            INIT_TYPE(var, T)
        };
        struct A { int a = 1; };
        struct B { int b = 2; };
        void Test() {
            Temp<short, A, B> tmp;
            tmp.a;
            tmp.b;
        };
    } // namespace TestSpace
    
} // namespace Prototype
