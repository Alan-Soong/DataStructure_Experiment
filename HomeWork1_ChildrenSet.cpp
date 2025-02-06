#include <iostream>
#include<vector>
using namespace std;

void print(int n, int index, vector<char> re) {
	if (index == n) {
		if (!re.empty()) {
			for (int i = 0; i < re.size(); i++) {
				cout << re[i];
				if (i != re.size() - 1) {
					cout << " ";
				}
			}
			cout << endl;
		}
		else {
			cout << endl;
		}
		return;
	}
	print(n, index + 1, re);
	
	char a = 'a' + index;
	re.push_back(a);
	print(n, index + 1, re);

}
 
int main(){
	int n = 0, index = 0;
	cin >> n;
	vector<char> str;
	print(n, index, str);
}