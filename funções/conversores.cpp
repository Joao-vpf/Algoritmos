string hextobin(string a)
{
	bitset<4> bis;//bitset
	string res;
	for (char x : a)
	{
		x=toupper(x);//cctype
		int b=x;
		if (b<=int ('9'))
		{
			bis=b-48;
			res+=bis.to_string();
		}
		else
		{
			bis=b-55;
			res+=bis.to_string();
		}
	}
	return res;
}

int s_int(string a) //String em inteiro
{
	int c=a.size()-1;
	int y=0;
	for (char x : a)
	{
		y+=(x-'0')*pow(10,c);
		c--;
	}
	return y;
}
