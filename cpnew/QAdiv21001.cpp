#include<bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> arr1(N);
        for (int i = 0; i < N; i++) {
            cin >> arr1[i];
        }
        vector<int> arr2(N);
        for (int i = 0; i < N; i++) {
            cin >> arr2[i];
        }

      
        sort(arr1.begin(), arr1.end());
       
        sort(arr2.begin(), arr2.end(), greater<int>());

        
        vector<int> arr3(N);
        for (int i = 0; i < N; i++) {
            arr3[i] = arr1[i] + arr2[i];
        }

        
        set<int> mySet(arr3.begin(), arr3.end());
        if (mySet.size() >= 3) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}