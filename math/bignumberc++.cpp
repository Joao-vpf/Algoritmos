string multiply(string a, string b) {
    int n1 = a.size(), n2 = b.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    string res(n1 + n2, '0');
    int i_n1 = 0, i_n2 = 0;

    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0, n1 = a[i] - '0';
        i_n2 = 0;

        for (int j = n2 - 1; j >= 0; j--) {
            int n2 = b[j] - '0';
            int sum = n1 * n2 + (res[i_n1 + i_n2] - '0') + carry;

            carry = sum / 10;
            res[i_n1 + i_n2] = (sum % 10) + '0';
            i_n2++;
        }

        if (carry > 0)
            res[i_n1 + i_n2] += carry;

        i_n1++;
    }

    while (res.size() > 1 && res.back() == '0')
        res.pop_back();

    reverse(res.begin(), res.end());
    return res;
}

string sub(string a, string b) {
    bool negative = false;
    if (a.size() < b.size() || (a.size() == b.size() && a < b)) {
        swap(a, b);
        negative = true;
    }
    int n1 = a.size(), n2 = b.size();

    int carry = 0;
    string res = "";
    for (int i = 0; i < n1; i++) {
        int x = a[n1 - 1 - i] - '0';
        int y = i < n2 ? b[n2 - 1 - i] - '0' : 0;
        int sub = x - y - carry;

        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        res.push_back(sub % 10 + '0');
    }

    while (res.size() > 1 && res.back() == '0')
        res.pop_back();

    if (negative) {
        res.push_back('-');
    }

    reverse(res.begin(), res.end());
    return res;
}



string add(string a, string b) {
    int signA = 1, signB = 1;

    // verifica o sinal de a
    if (a[0] == '-') {
        signA = -1;
        a = a.substr(1);
    }

    // verifica o sinal de b
    if (b[0] == '-') {
        signB = -1;
        b = b.substr(1);
    }

    // se os sinais forem diferentes, faz a subtração
    if (signA != signB) {
        if (signA == -1) {
            return sub(b, a);
        } else {
            return sub(a, b);
        }
    }

    int n1 = a.size(), n2 = b.size();
    if (n1 < n2)
        swap(a, b), swap(n1, n2);

    int carry = 0;
    string res = "";
    for (int i = 0; i < n1; i++) {
        int x = a[n1 - 1 - i] - '0';
        int y = i < n2 ? b[n2 - 1 - i] - '0' : 0;
        int sum = x + y + carry;

        carry = sum / 10;
        res.push_back(sum % 10 + '0');
    }

    if (carry > 0) {
        res.push_back(carry + '0');
    }

    // adiciona o sinal se necessário
    if (signA == -1) {
        res.push_back('-');
    }

    reverse(res.begin(), res.end());
    return res;
}
