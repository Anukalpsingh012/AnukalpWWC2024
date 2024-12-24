#include<iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int ans;
    for(int i=1;i<=n;i++){
        ans = ans + i;
    }
    cout<< " sum is " << ans << endl;
}
