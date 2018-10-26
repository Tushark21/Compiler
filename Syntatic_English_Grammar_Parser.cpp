//Parser for Productions:
//s->AA
//A->aA/b
#include<bits/stdc++.h>

using namespace std;

void pop();
void push(string token);

int size=10000,top=-1;
vector<string> parseStack(size);

int findIndex(char);

int toInt(string str){
    int n=str.length(),a=0;
    for(int i=0;i<n;i++){
        a=(a*10)+(str[i]-'0');
    }
    return a;
}

char findTerminal(string str){

}

int main(){
    
    vector<vector<string>> parseTable(17,vector<string> (13,"-"));
    //vector<vector<char>> dParseTable(17,vector<char> (13,'-'));
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
    9 States
    10 columns:
    s,v,c,o,$
    Subject,Connecting Verbs,Verbs,Objects
*/

    parseTable[0][0]="s5";
    parseTable[0][1]="s4";
    parseTable[2][3]="s16";
    parseTable[3][2]="s8";
    parseTable[6][4]="s9";
    parseTable[10][0]="s14";
    parseTable[10][5]="s13";
    parseTable[12][5]="s15";

    parseTable[4][3]="r3";
    parseTable[5][2]="r4";
    parseTable[7][3]="r2";
    parseTable[8][3]="r5";
    parseTable[9][0]="r7";
    parseTable[9][5]="r7";
    parseTable[9][6]="r4";
    parseTable[11][5]="r1";
    parseTable[13][6]="r9";
    parseTable[14][5]="r4";
    parseTable[15][6]="r8";
    parseTable[16][4]="r6";

    parseTable[0][7]="3";
    parseTable[0][8]="1";
    parseTable[0][9]="2";
    parseTable[2][10]="6";
    parseTable[6][11]="10";
    
    parseTable[1][6]="!";       //Accept State  :   !

    /*
    for(int i=0;i<17;i++){
        for(int j=0;j<13;j++){
            cout<<parseTable[i][j]<<"   ";
        }
        cout<<"\n";
    }
    */

    string str,temp="",newString="";
    cin>>str;
/*
    for(int i=0;i<str.length();i++){
        if(str[i]==' '){
            temp+=findTerminal(newString);
        }
        else{
            newString+=str[i];
        }
    }
    temp+=findTerminal(newString);

    str=temp;*/
    str+='$';

    push("0");

    //Parsing Loop
    int j,n=str.length();
    for(int i=0;i<n;){
        j=findIndex(str[i]);

        //cout<<parseStack[top]<<"\n";
        int row=toInt(parseStack[top]);
        //cout<<row<<","<<j<<":"<<parseTable[row][j]<<"\n";
        if(parseTable[row][j]=="-"){
            cout<<"Error\n";
            break;
        }
        if(parseTable[row][j][0]=='s'){
            push(str[i]+"");
            string pushSymbol="";
            for(int i1=1;i1<parseTable[row][j].length();i1++){
                pushSymbol+=parseTable[row][j][i1];
            }
            push(pushSymbol);
            i++;
        }
        else if(parseTable[row][j][0]=='r'){
            int len=0,l;
            string pushSymbol="";
            for(int i1=1;i1<parseTable[row][j].length();i1++){
                pushSymbol+=parseTable[row][j][i1];
            }

            if(pushSymbol=="1"){
                len=8;
                pushSymbol="S";
                l=8;
            }
            else if(pushSymbol=="2"){
                len=4;
                pushSymbol="Q";
                l=9;
            }
            else if(pushSymbol=="3"){
                len=2;
                pushSymbol="Q";
                l=9;
            }
            else if(pushSymbol=="4"){
                len=2;
                pushSymbol="T";
                l=7;
            }
            else if(pushSymbol=="5"){
                len=2;
                pushSymbol="P";
                l=4;///////////
            }
            else if(pushSymbol=="6"){
                len=2;
                pushSymbol="V";
                l=10;
            }
            else if(pushSymbol=="7"){
                len=2;
                pushSymbol="C";
                l=11;
            }
            else if(pushSymbol=="8"){
                len=4;
                pushSymbol="O";
                l=12;
            }
            else if(pushSymbol=="9"){
                len=2;
                pushSymbol="O";
                l=12;
            }

            for(int k=0;k<len;k++){
                pop();
            }
            push(pushSymbol);
            row=toInt(parseStack[top-1]);
            push(parseTable[row][l]);

            //Print Reduced String
            cout<<"Reduced String:";
            for(int m=1;m<top;m+=2){
                cout<<parseStack[m];
            }
            for(int m=i;m<n-1;m++){
                cout<<str[m];
            }
            cout<<"\n";
        }
        else if(parseTable[row][j]=="!"){
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

void push(string token){
    if(top==size){
        cout<<"Overflow\n";
    }
    else{
        top++;
        parseStack[top]=token;
    }
}

int findIndex(char ch){

    switch(ch){
        case 't':
        return 0;
        break;

        case 's':
        return 1;
        break;
        
        case 'p':
        return 2;
        break;
        
        case 'v':
        return 3;
        break;
        
        case 'c':
        return 4;
        break;
        
        case 'o':
        return 5;
        break;
        
        case '$':
        return 6;
        break;
        
        case 'T':
        return 7;
        break;
        
        case 'S':
        return 8;
        break;

        case 'Q':
        return 9;
        break;
        
        case 'V':
        return 10;
        break;
        
        case 'C':
        return 11;
        break;
        
        case 'O':
        return 12;
        break;

        default:
        return 12;
    }
}