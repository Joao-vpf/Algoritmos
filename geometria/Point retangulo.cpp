struct Point
{
	ill x, y;
};

ill func(ill x1, ill y1, ill x2, ill y2, ill x3, ill y3)
{
	ill  res= x3*(y2-y1)+y1*(x2-x1) - (y2-y1)*x1;
	ill l  = y3 * (x2-x1);
	if(res<l)
	{
		return 1;
	}
	if(res>l)
	{
		return -1;
	}
	return 0;
}

int main() 
{
	ios
	//freop
	ill d, n;
	cin>> n >>d;
	int m;
	cin>> m;
	rep(i, 0, m)
	{
		ill x, y;
		cin >> x>> y;
		ill p1 = func(0, d, d, 0, x, y);//baixo
		ill p2 = func(0, d, n-d,n, x, y);//esquerda
		ill p3 = func(n, n-d, d, 0, x, y);//direita
		ill p4 = func(n, n-d, n-d,n, x, y);//cima
		cout << p1 << " "<< p2 << " " << p3 << " " << p4 <<endl;
		if(!p1 ||  !p2 || !p3 || !p4)
		{
			cout << "YES" <<endl;
			continue;
		}
		if(p1>0 && p2<0 && p3<0 && p4>0) 
		{
			cout << "YES" <<endl;
			continue;
		}
		cout << "NO" <<endl;
	}
	
}
