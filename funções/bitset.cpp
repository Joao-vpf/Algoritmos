// -------operação com bitsets ------- 
bool fullAdder(bool b1, bool b2, bool& carry)// faz operacão de soma com bitset
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}
bitset<17> bitsetAdd(bitset<17>& x)
{
    bool carry = false;
    bitset<17> ans, oi(1);//oi esta somando 1 por vez
    for (int i = 0; i < 17; i++) {
        ans[i] = fullAdder(x[i],oi[i], carry);
    }
    return ans;
}
//faz diferenca entre dois bitsets
bool fullSubtractor(bool b1, bool b2, bool& borrow)
{
    bool diff;
    if (borrow) {
        diff = !(b1 ^ b2);
        borrow = !b1 || (b1 && b2);
    }
    else {
        diff = b1 ^ b2;
        borrow = !b1 && b2;
    }
    return diff;
}

bitset<33> bitsetSubtract(bitset<32> x, bitset<32> y)
{
    bool borrow = false;
    bitset<33> ans;//resultado
    for (int i = 0; i < 32; i++) {
        ans[i] = fullSubtractor(x[i], y[i], borrow);
    }
    return ans;
}

