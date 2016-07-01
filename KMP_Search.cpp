size_t KMP_Search(const string& str, const string& exp) {
    /* this part gets the KMP code from 'exp': */
    size_t *code = new size_t[exp.size()];
    code[0] = code[1] = 0;
    for (size_t i = 1; i < exp.size()-1; ++i) {
        size_t cnt = 0;
        for (size_t n = 1; n <= i; ++n)
            if (string(exp.begin(), exp.begin()+n) == string(exp.begin()+(i-n)+1, exp.begin()+i+1))
                cnt = n;
        code[i+1] = cnt;
    }
    /**    starting search in 'str'   **/
    for (size_t i = 0, j = 0; i < str.size();) {

        if (str[i] == exp[j])
            ++j, ++i;
        else if (j == 0 && str[i] != exp[j])
            ++i;
        else
            j = code[j];
        if (j == exp.size()) {
            delete []code;
            return i - j;
        }
    }
    delete []code;
    return size_t(0-1);
}
