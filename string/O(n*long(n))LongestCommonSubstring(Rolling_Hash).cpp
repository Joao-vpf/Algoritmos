#rpuneet

const int P1 = 31;
const int mod1 = 1e9 + 9;
const int P2 = 53;
const int mod2 = 1e9 + 7;
const int N = 1e5 + 5;
const int invP1 = 838709685;
const int invP2 = 56603774;


long long pow1[N] , pow2[N];

long long addAtEnd1(long long hash , char c , int n){
	return (hash + (int)(c - 'a' + 1) * pow1[n]) % mod1;
}

long long eraseFromBeg1(long long hash ,char c , int n){
	return ((hash - (int)(c - 'a' + 1) + mod1) * invP1) % mod1;
}

long long addAtEnd2(long long hash , char c , int n){
	return (hash + (int)(c - 'a' + 1) * pow2[n]) % mod2;
}

long long eraseFromBeg2(long long hash ,char c , int n){
	return ((hash - (int)(c - 'a' + 1) + mod2) * invP2) % mod2;
}


bool check(int m , string a , string b){
	set< pair<long long , long long> > substringHashA1;

	long long hash1 = 0;
	long long hash2 = 0;
	int n = 0;

	for(int i = 0 ; i < m ; ++i){
		hash1 = addAtEnd1(hash1 , a[i] , n);
		hash2 = addAtEnd2(hash2 , a[i] , n);
		n++;
	}

	substringHashA1.insert({hash1 , hash2});

	for(int i = m ; i < a.size() ; ++i){
		hash1 = addAtEnd1(hash1 , a[i] , n);
		hash1 = eraseFromBeg1(hash1 , a[i - m] , n);

		hash2 = addAtEnd2(hash2 , a[i] , n);
		hash2 = eraseFromBeg2(hash2 , a[i - m] , n);

		substringHashA1.insert({hash1 , hash2});
	}

	hash1 = 0;
	hash2 = 0;

	n = 0;
	for(int i = 0 ; i < m ; ++i){
		hash1 = addAtEnd1(hash1 , b[i] , n);
		hash2 = addAtEnd2(hash2 , b[i] , n);

		n++;
	}

	if(substringHashA1.find({hash1 , hash2}) != substringHashA1.end()){
		return true;
	}

	for(int i = m ; i < b.size() ; ++i){
		hash1 = addAtEnd1(hash1 , b[i] , n);
		hash1 = eraseFromBeg1(hash1 , b[i - m] , n);

		hash2 = addAtEnd2(hash2 , b[i] , n);
		hash2 = eraseFromBeg2(hash2 , b[i - m] , n);

		if(substringHashA1.find({hash1 , hash2}) != substringHashA1.end()){
			return true;
		}
	}
	return false;
}

int longestCommonSubstring(string a , string b){
	int start = 0 , end = min(a.size() , b.size());

	while((end - start) > 5){
		int m = (start + end) / 2;
		if(check(m , a , b)){
			start = m;
		}else{
			end = m;
		}
	}
	int ans = start;

	for(int l = start ; l <= end ; ++l){
		if(check(l , a , b)){
			ans = l;
		}
	}
	return ans;
}


pow1[0] = pow2[0] = 1;

for(int i = 1 ; i < N ; ++i){
		pow1[i] = (pow1[i-1] * P1) % mod1;
		pow2[i] = (pow2[i-1] * P2) % mod2;
	}
