#include<bits/stdc++.h>
using namespace std;


void left(string s);
void right(string s);


int main()
{
    string str; cin>>str;
    left(str);
    right(str);
}


void left(string s)
{   
    cout<<"Leftmost Derivation:"<<endl;
    int n=s.size();

    string x="A1B";
    cout<<"Applying S-> A1B: "<<x<<endl;
    // ind is for tracking x, firstOne is for handling the first 1 in the string
    int ind=0,firstOne=0; 
    bool A=true; // to check if A is done
    for(int i=0;i<n;i++)
    {   
        if(s[i]=='0')
        {   
            if(A) cout<<"Applying A->  0A: ";
            else cout<<"Applying B->  0B:";
            x.insert(ind,"0");
            ind++;
        }
        else
        {   
            firstOne++; 
            if(x[ind]=='A') 
            {   
                cout<<"Applying A-> eps: ";
                x.erase(x.begin()+ind); // removing A
                ind++;
                A=false; // A is done
            }
            else if(x[ind]=='B')
            {
                if(firstOne>1) // don't do anything if it is the first 1 in the string
                {
                    cout<<"Applying B->  1B: ";
                    x.insert(ind,"1");
                    ind++;
                }
            }
        }
        cout<<x<<endl;
    }
    if(A) 
    {
        cout<<"Applying A-> eps: ";
        x.erase(x.begin()+ind);
        cout<<x<<endl;
        cout<<"Can not be derived..."<<endl;
    }
    else
    {
        cout<<"Applying B-> eps: ";
        x.erase(x.end()-1);
        cout<<x<<endl;
        cout<<"Can be derived..."<<endl;
    } 
    cout<<endl;
}

void right(string s)
{   
    cout<<"Rightmost Derivation:"<<endl;
    int n=s.size();

    string x="A1B";
    cout<<"Applying S-> A1B: "<<x<<endl;
    // ind is for tracking x, firstOne is for handling the first 1 in the string
    int ind=2,firstOne=-1; 
    //bool B=true; // to check if B is done
    for(int i=0;i<n;i++)
    {
        if(s[i]=='1') 
        {
            firstOne=i;
            break;
        }
    }
    for(int i=firstOne+1;i<n;i++)
    {   
        if(s[i]=='0')
        {   
            cout<<"Applying B->  0B: ";
            x.insert(ind,"0");
            ind++;
        }
        else
        {   
            cout<<"Applying B->  1B: ";
            x.insert(ind,"1"); 
            ind++;
        }
        cout<<x<<endl;
    }
    cout<<"Applying B-> eps: ";
    x.erase(x.end()-1);
    cout<<x<<endl;
    
    ind=0;
    for(int i=0;i<firstOne;i++)
    {
        cout<<"Applying A->  0A: ";
        x.insert(ind,"0");
        ind++;
        cout<<x<<endl;
    }

    x.erase(x.begin()+ind);
    cout<<"Applying A-> eps: ";
    cout<<x<<endl;

    if(x==s) cout<<"Can be derived..."<<endl;
    else cout<<"Can not be derived..."<<endl;
}