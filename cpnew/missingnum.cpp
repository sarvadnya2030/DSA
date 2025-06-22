#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int mn=0;
    int num=0;
    long long sum1=0;
    
    
    for(int i=0;i<n-1;i++)
    {
        cin>>num;
        sum1+=num;

    }
    long long sum=((long long)n*(n+1))/2;
    cout<<sum-sum1<<endl;
    return 0;


}