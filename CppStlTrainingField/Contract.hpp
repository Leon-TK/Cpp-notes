namespace Contract
{
    //TODO: or use just one argument of bool? That is caleer must make expression
    template<bool... bls>
    bool Expects(bls...) { 
        if (...) {
            return true; }
        return false;
    };
    bool ExpectsExpr(bool val) {
        //static_assert(val);
        return val;
    };
    void Test() {
        ExpectsExpr(1 > 0 && 1 < 0);
    };
} // namespace Contract
