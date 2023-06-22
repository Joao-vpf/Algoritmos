/*-----------------Chinese Remainder-----------*/

long long CRT_weak(vector<long long>A, vector<long long>B)
{
    ll X=0;
    ll N=1;
    ll y,z;
   for(int i=0; i<SZ(B); i++)
        N*=B[i];
    for(int i=0; i<SZ(A); i++)
   {
       y=N/B[i];
        z=modInv(y,B[i]);
        X+=(A[i]*y*z);
        X%=N;
    }
    return (X+N)%N;
}
