//Parser for Present Indefinite Tense:

#include<bits/stdc++.h>

using namespace std;

vector<string> s={"s","I","He","She","they"};
vector<string> T={"t","the"};
vector<string> places={"p","rain","Himalayas"};
vector<string> verbs={"v","pours","plays","work","run","goes","study"};
vector<string> connectors={"c","into","with"};
vector<string> objects={"o","ball","pot"};

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
    int n=s.size();
    for(int i=0;i<n;i++){
        if(str==s[i]){
            return 's';
        }
    }
    n=T.size();
    for(int i=0;i<n;i++){
        if(str==T[i]){
            return 't';
        }
    }
    n=places.size();
    for(int i=0;i<n;i++){
        if(str==places[i]){
            return 'p';
        }
    }
    n=verbs.size();
    for(int i=0;i<n;i++){
        if(str==verbs[i]){
            return 'v';
        }
    }
    n=connectors.size();
    for(int i=0;i<n;i++){
        if(str==connectors[i]){
            return 'c';
        }
    }
    n=objects.size();
    for(int i=0;i<n;i++){
        if(str==objects[i]){
            return 'o';
        }
    }

    return '*';
}

int main(){
    
    vector<vector<string>> parseTable(17,vector<string> (14,"-"));
    //vector<vector<char>> dParseTable(17,vector<char> (13,'-'));

    parseTable[0][0]="s5";
    parseTable[0][1]="s4";
    parseTable[2][3]="s7";
    parseTable[3][2]="s9";
    parseTable[6][4]="s10";

    parseTable[11][0]="s5";
    parseTable[11][5]="s14";
    parseTable[13][5]="s15";

    parseTable[4][3]="r3";
    parseTable[5][2]="r4";
    parseTable[5][5]="r4";
    parseTable[7][4]="r6";
    parseTable[8][3]="r2";
    parseTable[9][3]="r5";
    parseTable[10][0]="r7";
    parseTable[10][5]="r7";
    //
    //parseTable[10][6]="r7";
    //
    parseTable[12][6]="r1";
    parseTable[14][6]="r9";
    parseTable[15][6]="r8";
///////
    parseTable[15][5]="r4";
    parseTable[13][6]="r9";

    //May Needed to change
    //parseTable[11][6]="r1";


    parseTable[0][7]="3";
    parseTable[0][8]="1";
    parseTable[0][9]="2";
    parseTable[2][10]="6";
    parseTable[3][13]="8";
    parseTable[6][11]="11";
    parseTable[11][7]="13";
    parseTable[11][12]="12";
    
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
    getline(cin,str);

    for(int i=0;i<str.length();i++){
        if(str[i]==' '){
            char ch=findTerminal(newString);
            if(ch=='*'){
                cout<<"Error\n";
                break;
            }
            temp+=ch;
            //cout<<newString<<",";
            newString="";
        }
        else{
            newString+=str[i];
        }
    }
    temp+=findTerminal(newString);

    str=temp;
    //cout<<str<<"\n";
    cout<<"S:Sentence\nQ:Subject\nV:Verb\nC:Connectors\nO:Objects\n\n";
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
                l=13;
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
            cout<<"Reduced String: ";
            for(int m=1;m<top;m+=2){
                cout<<parseStack[m]<<" ";
            }
            for(int m=i;m<n-1;m++){
                cout<<str[m]<<" ";
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

        case 'P':
        return 13;
        break;

        default:
        return 13;
    }
}