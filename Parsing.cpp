#include<bits/stdc++.h>

using namespace std;

typedef string Token;

string str;

string tokanize(){
    int n=str.length();
    Token tokanizeStr="";

    for(int i=0;i<n;i++){
        if(str[i]!=' '){
            tokanizeStr+=str[i];
        }
        else if(tokanizeStr[tokanizeStr.length()-1]!='`'){
            tokanizeStr+='`';
        }
    }

    return tokanizeStr+"`END`";
}

Token getNextToken(){
    Token temp="";
    int i=0;

    while(str[i]!='`'){
        temp+=str[i];
        i++;
    }

    str.erase(0,temp.length()+1);

    return temp;
}

int main(){
    
    getline(cin,str);

    str=tokanize();

    Token token=getNextToken();

    //cout<<str;
    while(token!="END"){
        cout<<token<<"\n";//<<str<<"\n";
        token=getNextToken();
    }

    return 0;
}