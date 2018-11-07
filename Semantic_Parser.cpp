#include <bits/stdc++.h>

using namespace std;

struct LRItem{
    int prevState;
    string gotoSymbol;
    vector<string> leftOfProd;
    vector<string> rightOfProd;
    vector<int> pointerPos;
};

//parsing table
vector<vector<string>> parseTable(1000,vector<string>(1000,"-"));

/*
//vectors to store productions
vector<string> lhs={"S'","S","A","A"};
vector<string> rhs={"S,$","A,A,$","a,A,$","b,$"};
*/

vector<string> lhs={"S'","S","PN","FN","LN"};
vector<string> rhs={"S,$","PN,$","FN,LN,$","tushar,$","gautam,$"};

//vector to for indices of terminals and non-terminals
vector<string> index;
vector<string> terminals;
vector<string> nonTerminals;

/*
//vectors to indicate terminals and non-terminals are in index vector or not
vector<bool> gotoPushed(26,false);
vector<bool> actionPushed(26,false);
*/

//stack for parsing strings
int size=100000,top=-1;
vector<string> parseStack(size);

//Functions
//string parsing stack's push and pop function
void pop();
void push(string token);

//function to fill index vector
void fillIndex(){
    //Index for Action part of Parsing Table
    for(int i=0;i<terminals.size();i++){
        index.push_back(terminals[i]);
    }

    index.push_back("$");
    
    //Index for Goto part of Parsing Table
    for(int i=0;i<nonTerminals.size();i++){
        index.push_back(nonTerminals[i]);
    }
}

//function to find index of terminals and non-terminals indicating
//columns in parse table
int findIndex(string str){
    for(int i=0;i<index.size();i++){
        if(index[i]==str){
            return i;
        }
    }
    return -1;
}

//function to convert integer to string
string toString(int x){
    string str="";
    char a;
    while(x>0){
        a=(x%10)+'0';
        str=a+str;
        x/=10;
    }
    return str;
}

//function to convert string to integers
int toInteger(string str){
    int i=0;
    //need to change
    if(str[0]=='r' || str[0]=='s'){
        i=1;
    }

    int n=str.length(),a,num=0;
    for(;i<n;i++){
        a=str[i]-'0';
        num=(num*10)+a;
    }
    return num;
}

//function to find the production number
int findProductionNumber(string l,string r){
    for(int i=0;i<lhs.size();i++){
        if(l==lhs[i] && r==rhs[i]){
            return i;
        }
    }
    return -1;
}

//funtion to check weather string is Non-terminal or not
bool isNonTerminal(string str){
    for(int i=0;i<nonTerminals.size();i++){
        if(str==nonTerminals[i]){
            return true;
        }
    }
    return false;
}

//function to find length of production
int getProductionLength(string str){
    int count=0,n=str.length();
    for(int i=0;i<n;i++){
        if(str[i]==','){
            count++;
        }
    }
    return count;
}
//
string getRHSVariable(string str,int index){
    int n=str.length(),count=0;
    string temp="";
    for(int i=0;i<n;i++){
        if(str[i]==',' && count<index){
            temp="";
            count++;
        }
        else if(str[i]==',' && count==index){
            return temp;
        }
        else{
            temp+=str[i];
        }
    }
    return temp;
}
//main function
int main(){

    string lhs1,rhs1;
    //cin>>lhs1>>rhs1;
    //rhs1+='$';
    
    //lhs.push_back(lhs1);
    //rhs.push_back(rhs1);
/*
    terminals.push_back("a");
    terminals.push_back("b");
    
    nonTerminals.push_back("S");
    nonTerminals.push_back("A");
*/
    terminals.push_back("tushar");
    terminals.push_back("gautam");
    
    nonTerminals.push_back("S");
    nonTerminals.push_back("PN");
    nonTerminals.push_back("FN");
    nonTerminals.push_back("LN");

    fillIndex();

    //Printing all productions
    for(int i=0;i<lhs.size();i++){
        cout<<lhs[i]<<"->"<<rhs[i]<<"\n";
    }
    cout<<"\n";

    vector<LRItem> LRI;

    LRItem ptr;
    ptr.leftOfProd.push_back("S'");
    ptr.rightOfProd.push_back("S,$");
    ptr.pointerPos.push_back(0);

    LRI.push_back(ptr);
    
    for(int nodeNo=0;nodeNo<LRI.size();nodeNo++){
        ptr=LRI[nodeNo];
        vector<bool> added(lhs.size(),false);
        for(int i=0;i<ptr.leftOfProd.size();i++){
            for(int j=0;j<lhs.size();j++){
                if(ptr.leftOfProd[i]==lhs[j] && ptr.rightOfProd[i]==rhs[j]){
                    added[j]=true;
                }
            }
        }
        
        //Loop for traversing productions in the Node
        for(int i=0;i<ptr.rightOfProd.size();i++){
            //Loop for Traversing lhs for adding productions
            //Clouser
            for(int j=0;j<lhs.size();j++){
                string currentVar="";
                currentVar=getRHSVariable(ptr.rightOfProd[i],ptr.pointerPos[i]);
                if(currentVar==lhs[j] && !added[j]){
                    ptr.leftOfProd.push_back(lhs[j]);
                    ptr.rightOfProd.push_back(rhs[j]);
                    ptr.pointerPos.push_back(0);
                    added[j]=true;
                }
            }
        }
        LRI[nodeNo]=ptr;
        
        //Goto
        for(int j=0;j<ptr.leftOfProd.size();j++){
            if(getRHSVariable(ptr.rightOfProd[j],ptr.pointerPos[j])!="$"){
                vector<bool> addedGoto(lhs.size(),false);
                bool formed=false;
                LRItem newItem;

                for(int k=0;k<ptr.leftOfProd.size();k++){
                    int prodNo=findProductionNumber(ptr.leftOfProd[k],ptr.rightOfProd[k]);
                    if(getRHSVariable(ptr.rightOfProd[k],ptr.pointerPos[k])==getRHSVariable(ptr.rightOfProd[j],ptr.pointerPos[j]) && !addedGoto[prodNo] && getRHSVariable(ptr.rightOfProd[k],ptr.pointerPos[k])!="$"){
                        newItem.leftOfProd.push_back(ptr.leftOfProd[k]);
                        newItem.rightOfProd.push_back(ptr.rightOfProd[k]);
                        newItem.pointerPos.push_back((ptr.pointerPos[k])+1);
                        newItem.prevState=nodeNo;
                        newItem.gotoSymbol=getRHSVariable(ptr.rightOfProd[k],ptr.pointerPos[k]);
                        addedGoto[prodNo]=true;
                        formed=true;
                    }
                }
                if(formed){
                    //find Weather same item is already in the item set or not
                    LRI.push_back(newItem);
                }
            }
        }
    }

    
    for(int i=0;i<LRI.size();i++){
        cout<<"State:"<<i<<"\n";
        for(int j=0;j<LRI[i].leftOfProd.size();j++){
            cout<<LRI[i].leftOfProd[j]<<"->"<<LRI[i].rightOfProd[j]<<":"<<LRI[i].pointerPos[j]<<"\n"<<LRI[i].gotoSymbol<<","<<LRI[i].prevState<<"\n";
        }
        cout<<"\n";
    }
    

    //Generation of Parsing Table
    cout<<"Parsing Table:\n";
    int tableIndex=findIndex("$");
    parseTable[1][tableIndex]="*";

    for(int state=1;state<LRI.size();state++){
        int row,col,prodNo;

        //Entries crossponding to final items (reduce entries)
        if(getRHSVariable(LRI[state].rightOfProd[0],LRI[state].pointerPos[0])=="$" && state!=1){
            row=state;
            col=findIndex("$");
            prodNo=findProductionNumber(LRI[state].leftOfProd[0],LRI[state].rightOfProd[0]);
            string concat=toString(prodNo);
            for(int i1=0;i1<=col;i1++){
                parseTable[row][i1]="r"+concat;
            }
        }
        //Entries crossponding to state numbers
        if(isNonTerminal(LRI[state].gotoSymbol)){
            row=LRI[state].prevState;
            col=findIndex(LRI[state].gotoSymbol);
            string concat=toString(state);
            parseTable[row][col]=concat;
        }

        //Entries crossponding to shift
        else{
            row=LRI[state].prevState;
            col=findIndex(LRI[state].gotoSymbol);
            string concat=toString(state);
            parseTable[row][col]="s"+concat;
        }
    }

    for(int i=0;i<index.size();i++){
        cout<<" "<<index[i]<<" ";
    }

    cout<<"\n";
    for(int i=0;i<LRI.size();i++){
        cout<<i<<" ";
        for(int j=0;j<index.size();j++){
            cout<<parseTable[i][j]<<"  ";
        }
        cout<<"\n";
    }

    //Parsing starts here
    vector<string> parseStr;
    string str,temp="";
    cout<<"Enter String:\n";
    getline(cin,str);

    //cout<<str<<"\n";
    
    for(int i=0;i<str.length();i++){
        if(str[i]==' '){
            parseStr.push_back(temp);
            temp="";
        }
        else{
            temp+=str[i];
        }
    }
    parseStr.push_back(temp);
    //cout<<parseStr[parseStr.size()-1]<<"\n";
    parseStr.push_back("$");

    push("0");

    //Parsing Loop
    int n=parseStr.size();
    for(int i=0;i<n;){
        int row,col;
        string var="";
        var+=parseStr[i];
        col=findIndex(var);
        if(col==-1){
            cout<<"ERROR\n";
            break;
        }
        //cout<<parseTable[toInteger(parseStack[top])][col]<<",";
        //cout<<"Stack:"<<parseStack[top]<<"\n";
        //cout<<toInteger(parseStack[top])<<","<<col<<"\n";
        if(parseTable[toInteger(parseStack[top])][col][0]=='-'){
            cout<<"ERROR\n";
            break;
        }
        if(parseTable[toInteger(parseStack[top])][col][0]=='s'){
            string pushSymbol="";
            pushSymbol+=parseStr[i];
            push(pushSymbol);
            //cout<<"parse table:"<<toInteger(parseTable[toInteger(parseStack[top-1])][col])<<",";
            pushSymbol=toString(toInteger(parseTable[toInteger(parseStack[top-1])][col]));
            push(pushSymbol);
            //cout<<toString(toInteger(parseTable[toInteger(parseStack[top])][col]))<<"\n";
            i++;
        }
        else if(parseTable[toInteger(parseStack[top])][col][0]=='r'){
            int prodToReduce=toInteger(parseTable[toInteger(parseStack[top])][col]);
            int len,l;
            string pushSymbol=lhs[prodToReduce];
            len=getProductionLength(rhs[prodToReduce]);
            len*=2;
            l=findIndex(pushSymbol);

            for(int k=0;k<len;k++){
                pop();
            }
            push(pushSymbol);
            push(parseTable[toInteger(parseStack[top-1])][l]);

            //Print Reduced String
            cout<<"Reduced String:";
            for(int m=1;m<top;m+=2){
                cout<<parseStack[m]<<" ";
            }
            for(int m=i;m<n-1;m++){
                cout<<parseStr[m]<<" ";
            }
            cout<<"\n";
        }
        else if(parseTable[toInteger(parseStack[top])][col][0]=='*'){
            cout<<"Accepted\n";
            break;
        }
    }
    /////////
    return 0;
}

//push and pop function defination
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