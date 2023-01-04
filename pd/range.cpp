maxrange(vector<long long> a)
{
  long long maxatual = a[0];
  long long minatual = a[0];
  long long maior = a[0];
  for (int i = 1; i < n; i++) 
  {
      long long temp = max({ a[i], a[i] * maxatual, a[i] * minatual});
      minatual = min({ a[i], a[i] * maxatual, a[i] * minatual});
      maxatual = temp;
      maior = max(maior, maxatual);
  }
  return maior
}
