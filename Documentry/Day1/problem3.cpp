#include<iostream>
using namespace std;

int main(){
    int n;
    int count = 0;
    cout<<"enter the number ";
    cin>>n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            count++;
        }
    }
    if(count>0){
        cout<<"its not a prime number"<<endl;
    }
    else{
        cout<<"its a prime number"<<endl;
    }
}
