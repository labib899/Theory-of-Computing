#include<bits/stdc++.h>
using namespace std;

#define pb          push_back
#define all(x)      x.begin(),x.end()
typedef vector<int> vi;


const int N=10;
int state[N];
vi fs; //final states
vector<vector<vi>> trans; //transition table for eNFA
vi closure(int s,vector<vector<vi>> v);
void print(vector<vi> st,vector<vector<vi>> dfaTable);


int main()
{
    //cout<<"Enter the number of states in ENFA table: "<<endl;
    int n; cin>>n;
    trans.resize(n);
    //cout<<"States: ("<<n<<" states, 1st one is the inital state)"<<endl;
    for(int i=0;i<n;i++) cin>>state[i];
    //cout<<"Number of final states:"<<endl;
    int f; cin>>f;
    for(int i=0;i<f;i++)
    {
        int x; cin>>x;
        fs.pb(x);
    }
    //cout<<"ENFA transition table:"<<endl;
    for(int i=0;i<n;i++)
    {
        trans[i].resize(3); // 2 symbols (0,1) + epsilon
        
        //cout<<"Number of states for input 0 in increasing order:"<<endl;
        int num; cin>>num;
        for(int j=0;j<num;j++)
        {
            int x; cin>>x;
            trans[i][0].pb(x);
        }
        
        //cout<<"Number of states for input 1 in increasing order:"<<endl;
        cin>>num;
        for(int j=0;j<num;j++)
        {
            int x; cin>>x;
            trans[i][1].pb(x);
        }
        
        //cout<<"Number of states for input epsilon in increasing order:"<<endl;
        cin>>num;
        for(int j=0;j<num;j++)
        {
            int x; cin>>x;
            trans[i][2].pb(x);
        }
    }
    
    vector<vector<vi>> dfaTable;
    vector<vi> st; // states column in dfatable
    st.pb(closure(0,trans)); // eclose of 0 (inital state)
    queue<vi> q;
    q.push(st[0]);
    while(!q.empty())
    {
        vi a=q.front(); q.pop();
        vector<vi> v; // rows in dfatable to push
        for(int i=0;i<2;i++)
        {
            vi t; // push in v
            set<int> s; // unique elements to push in t
            for(int j=0;j<a.size();j++) //each state in states vector
            {
                for(int k=0;k<trans[a[j]][i].size();k++)
                {
                    vi c=closure(trans[a[j]][i][k],trans);
                    for(int l=0;l<c.size();l++) s.insert(c[l]);
                }
            }
            for(auto x:s) t.pb(x);
            v.pb(t);
            if(find(all(st),t)==st.end())
            {
                st.pb(t);
                q.push(t);
            }
        }
        dfaTable.pb(v);
    }
    cout<<"DFA Table:"<<endl;
    print(st,dfaTable);
}

vi closure(int s,vector<vector<vi>> v)
{
    vi t;
    queue<int> q;
    t.pb(s);
    int x=v[s][v[s].size()-1].size();
    for(int i=0;i<x;i++)
    {
        t.pb(v[s][v[s].size()-1][i]);
        q.push(t[i]);
    }
    while(!q.empty())
    {
        int a=q.front(); q.pop();
        if(!v[a][v[a].size()-1].empty()) //if epsilon column is not empty
        {
            int u=v[a][v[a].size()-1].size();
            for(int i=0;i<u;i++) // traversing the epsilon column
            {
                int y=v[a][v[a].size()-1][i];
                if(find(all(t),y)==t.end())
                {
                    t.pb(y);
                    q.push(y);
                }
            }
        }
    }
    return t;
}

void print(vector<vi> st,vector<vector<vi>> dfaTable)
{
    cout<<"States"<<endl;
    for(int i=0;i<st.size();i++)
    {
        for(int j=0;j<st[i].size();j++)
        {
            cout<<st[i][j]<<" ";
        }
        cout<<"\t\t";
        for(int j=0;j<dfaTable[i].size();j++)
        {
            if(j==0) cout<<"for input 0: { ";
            else if(j==1)cout<<"for input 1: { ";
            for(int k=0;k<dfaTable[i][j].size();k++)
            {
                cout<<dfaTable[i][j][k]<<" ";
            }
            cout<<"}\t\t";
        }
        cout<<endl;
    }
}


/*
 3
 0 1 2
 1
 2
 2
 1 2
 1
 0
 1
 1
 0
 1
 1
 1
 2
 1
 2
 1
 2
 0 
*/


