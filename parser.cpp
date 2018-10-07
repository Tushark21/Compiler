#include<bits/stdc++.h>

using namespace std;

void pop();
void push(char token);

int size=100000,top=-1;
vector<char> parseStack(size);

int main(){
    
    vector<vector<char>> parseTable(7,vector<char> (5,'-'));
    vector<vector<char>> dParseTable(7,vector<char> (5,'-'));
/*
    parseTable[0][1]='a';
    parseTable[0][2]='b';
    parseTable[0][3]='$';
    parseTable[0][4]='A';
    parseTable[0][5]='S';

    parseTable[1][0]='0';
    parseTable[2][0]='1';
    parseTable[3][0]='2';
    parseTable[4][0]='3';
    parseTable[5][0]='4';
    parseTable[6][0]='5';
    parseTable[7][0]='6';
*/

    parseTable[0][0]='s';
    parseTable[0][1]='s';
    parseTable[2][0]='s';
    parseTable[2][1]='s';
    parseTable[3][0]='s';
    parseTable[3][1]='s';

    parseTable[4][0]='r';
    parseTable[4][1]='r';
    parseTable[4][2]='r';
    parseTable[5][0]='r';
    parseTable[5][1]='r';
    parseTable[5][2]='r';
    parseTable[6][0]='r';
    parseTable[6][1]='r';
    parseTable[6][2]='r';

    parseTable[0][3]='2';
    parseTable[0][4]='1';
    parseTable[2][3]='5';
    parseTable[3][3]='6';
    
    parseTable[1][2]='!';       //Accept State  :   !
    
    //dParseTable
    dParseTable[0][0]='3';
    dParseTable[0][1]='4';
    dParseTable[2][0]='3';
    dParseTable[2][1]='4';
    dParseTable[3][0]='3';
    dParseTable[3][1]='4';

    dParseTable[4][0]='3';
    dParseTable[4][1]='3';
    dParseTable[4][2]='3';
    dParseTable[5][0]='1';
    dParseTable[5][1]='1';
    dParseTable[5][2]='1';
    dParseTable[6][0]='2';
    dParseTable[6][1]='2';
    dParseTable[6][2]='2';


    /*
    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            cout<<parseTable[i][j]<<dParseTable[i][j]<<" ";
        }
        cout<<"\n";
    }
    */

    string str;
    cin>>str;
    str+='$';

    push('0');

    //Parsing Loop
    int j,n=str.length();
    for(int i=0;i<n;){
        if(str[i]=='a'){
            j=0;
        }
        else if(str[i]=='b'){
            j=1;
        }
        else if(str[i]=='$'){
            j=2;
        }
        else if(str[i]=='A'){
            j=3;
        }
        else if(str[i]=='S'){
            j=4;
        }

        if(parseTable[parseStack[top]-'0'][j]=='-'){
            cout<<"Error\n";
            break;
        }
        if(parseTable[parseStack[top]-'0'][j]=='s'){
            push(str[i]);
            push(dParseTable[parseStack[top-1]-'0'][j]);
            i++;
        }
        else if(parseTable[parseStack[top]-'0'][j]=='r'){
            int len=0,l;
            char pushSymbol;
            if(dParseTable[parseStack[top]-'0'][j]=='1'){
                len=4;
                pushSymbol='S';
                l=4;
            }
            else if(dParseTable[parseStack[top]-'0'][j]=='2'){
                len=4;
                pushSymbol='A';
                l=3;
            }
            else if(dParseTable[parseStack[top]-'0'][j]=='3'){
                len=2;
                pushSymbol='A';
                l=3;
            }

            for(int k=0;k<len;k++){
                pop();
            }
            push(pushSymbol);
            push(parseTable[parseStack[top-1]-'0'][l]);
        }
        else if(parseTable[parseStack[top]-'0'][j]=='!'){
            cout<<"Accepted\n";
            break;
        }
    }

    return 0;
}

void pop(){
    if(top<0){
        cout<<"Underflow\n";
    }
    else{
        top--;
    }
}

void push(char token){
    if(top==size){
        cout<<"Overflow\n";
    }
    else{
        top++;
        parseStack[top]=token;
    }
}