#include <iostream>
#include <climits>

using namespace std;

class travar
{
   int vet2[1000];
   public:
   travar();
};

travar::travar()
{
   register int vet[1000];
   for (int i=0; i<1000; i++)
   {
      vet[i]=INT_MAX;
      vet2[i]=INT_MAX;
      new char;
      new int;
   }
}

int main()
{
   for (int i=0; i<INT_MAX; i++)
   {
      new travar;
      new int;
      new char;
   }
}
