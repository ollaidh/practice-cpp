
#include <iostream>

using namespace std;

int main()
{
    string s1;
    string s2;
    string s3;
    cin >> s1 >> s2 >> s3;
    cout << min(min(s1, s2), s3);
}