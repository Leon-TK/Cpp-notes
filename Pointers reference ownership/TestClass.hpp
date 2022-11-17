#pragma once

template <typename Public, typename Private>
class TestClass {
    private:
    Private priv;
    public:
    TestClass(Public pub, Private priv) : priv(priv), pub(pub) {};
    TestClass(TestClass&& other) {
        this->priv = other.priv;
        this->pub = other.pub;
        other.priv = Private();
        other.pub = Public();
    };
    TestClass& operator=(TestClass&& other) {
        this->priv = other.priv;
        this->pub = other.pub;
        other.priv = Private();
        other.pub = Public();
    };
    Public pub;
    void Func() {};
};