#include<bits/stdc++.h>

using namespace std;

string extract(string str){
    int n=str.length();
    string tokenString="",temp="";

    for(int i=0;i<n;i++){
        if(str[i]!=' '){
            temp+=str[i];
        }
        else if(temp!=""){
            tokenString+=temp+'`';
            temp="";
        }
    }

    return tokenString+temp+'`';
}
int main(){
    
    string input;
    getline(cin,input);
    
    string tokens=extract(input);

    int n=tokens.length(),count=0;

    for(int i=0;i<n;i++){
        if(tokens[i]!='`'){
            cout<<tokens[i];
        }
        else{
            cout<<"\n";
            count++;
        }
    }
    cout<<"Total Numbers of Tokens are:"<<count;

    return 0;
}