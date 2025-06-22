#include<iostream>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int ml,cl=1;
    for(size_t i=1;i<s.size();i++)
    {

        if(s[i]==s[i-1])
        {
            cl++;
        }
        else{
            cl=1;
        }
        ml=max(ml,cl);
        
    }
    cout<<ml<<endl;
    
    return 0;
    
}