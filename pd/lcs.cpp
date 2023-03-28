
// Function to find the Longest Common
// Subsequence between the two arrays
int LCS(vector<int>& firstArr,vector<int>& secondArr)
{//O(nlogn)

	// Maps elements of firstArr[]
	// to their respective indices
	unordered_map<int, int> mp;
	int size=firstArr.size();
	// Traverse the array firstArr[]
	for (int i = 0; i < size ; i++) {
		mp[firstArr[i]] = i + 1;
	}

	// Stores the indices of common elements
	// between firstArr[] and secondArr[]
	vector<int> tempArr;
	size=secondArr.size();
	// Traverse the array secondArr[]
	for (int i = 0; i <size ; i++) {

		// If current element exists in the Map
		if (mp.find(secondArr[i]) != mp.end()) {

			tempArr.push_back(mp[secondArr[i]]);
		}
	}

	// Stores lIS from tempArr[]
	vector<int> tail;

	tail.push_back(tempArr[0]);
	size=tempArr.size();
	for (int i = 1; i < size; i++) {

		if (tempArr[i] > tail.back())
			tail.push_back(tempArr[i]);

		else if (tempArr[i] < tail[0])
			tail[0] = tempArr[i];

		else {
			auto it = lower_bound(tail.begin(),
								tail.end(),
								tempArr[i]);
			*it = tempArr[i];
		}
	}
	return (int)tail.size();
}
