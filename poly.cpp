// poly: p[i]x^i
template<typename T>
void rem_red(vector<T> &v) {
    while(!v.empty()  && v.back() == 0)
        v.pop_back();
}
template<typename T> // O(A.size()*B.size())
pair<vector<T>, vector<T>> operator / (vector<T> A, vector<T> B) {
    rem_red(A);
    rem_red(B);
    assert(!B.empty());
    if(A.size() < B.size())
        return {{0}, A};
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    T norm = B[0];
    for(int i=0 ; i<=A.size()-B.size() ; i++) {
        A[i] /= norm;
        T coef = A[i];
        if(coef != 0)
            for(int j=1 ; j<B.size() ; j++)
                A[i+j] += -1 * coef * B[j];
    }
    reverse(A.begin(), A.end());
    vector<T> q, r;
    for(int i=0 ; i<B.size()-1 ; i++)
        r.push_back(A[i]);
    for(int i=B.size()-1 ; i<A.size() ; i++)
        q.push_back(A[i]);
    rem_red(r);
    rem_red(q);
    return {q, r}; // quotient, remainder
}
