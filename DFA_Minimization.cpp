#include<bits/stdc++.h>
using namespace std;


#define marked -1
#define unmarked 1
#define all(x)  x.begin(),x.end()
typedef vector<int> vi;


int total_state,total_symbol,initial_state;
int transition[10][10],m[10][10],arr[10];
vector<int> final_states,states(10,-1); // unreachable states are -1
vector<vi> equivalence;
map<int,set<int>> mp;


void dfs(int source)
{   
    states[source]=1;
    for(int i=0;i<total_symbol;i++)
    {   
        int x=transition[source][i];
        if(states[x]==-1) dfs(x);
    }
}

void store_dfa()
{
    cout<<"Enter total no. of states : ";
    cin>>total_state;
    cout<<"Enter total no. of symbols : ";
    cin>>total_symbol;
    cout<<"Enter initial state : ";
    cin>>initial_state;
    cout<<"Enter the no. of final states: "<<endl;
    int n; cin>>n;
    cout<<"Final states: ";
    final_states.resize(n);
    for(int i=0;i<n;i++) cin>>final_states[i];
    cout<<"Enter the transitions : "<<endl;
    for(int i=0;i<total_state;i++) // it will store initial transition table.
    {
        for(int j=0;j<total_symbol;j++)
        {
            cout<<endl<<i<< " ---> "<<char(j+97)<<" :";
            cin>>transition[i][j];
        }
    }
}

void show_dfa()
{
    cout<<endl<<endl;
    cout<<endl<<"Transition table of DFA: "<<endl<<endl;
    for(int i=0;i<total_symbol;i++) cout<<"\t"<<char(i+97);
    cout<<endl;
    for(int i=0;i<(total_symbol+1);i++) cout<<"-\t";
    for(int i=0;i<total_state;i++) //prints initial DFA
    {
        cout<<"\n"<<i<<"\t";
        for(int j=0;j<total_symbol;j++) cout<<transition[i][j]<<"\t";
    }
    cout<<endl<<endl<<"Total no. of states : "<<total_state;
    cout<<endl<<"Final states are : ";
    for(auto x:final_states) cout<<x<<" ";
    cout<<endl;
}

void mark_dfa()
{
    for(int i=0;i<total_state;i++)
    {
        for(int j=0;j<total_state;j++)
        {
            if(i<=j) m[i][j]=marked;
            else
            {   
                bool i_is_final=find(all(final_states),i)!=final_states.end();
                bool j_is_final=find(all(final_states),j)!=final_states.end();
                if(((i_is_final && !j_is_final) || (!i_is_final && j_is_final))) 
                    m[i][j]=marked;
                else m[i][j]=unmarked;
            }
        }
    }
    bool f=1;
    while(f)
    {   
        f=0;
        for(int i=0;i<total_state;i++)
        {
            for(int j=0;j<i;j++)
            {
                if(m[i][j]==unmarked)
                {
                    for(int k=0;k<total_symbol;k++)
                    {
                        int x=transition[i][k];
                        int y=transition[j][k];
                        int a=max(x,y),b=min(x,y);
                        if((m[a][b]==marked) && a!=b)
                        {   
                            f=1;
                            m[i][j]=marked;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void minimize_dfa()
{   
    for(int i=0;i<total_state;i++)
    {   
        set<int> s;
        s.insert(i);
        for(int j=0;j<total_state;j++)
        {
            if(equivalence[i][j]) s.insert(j);
        }
        mp[i]=s;
    }

    cout<<endl<<"Minimized DFA table: "<<endl<<endl;
    for(int i=0;i<total_state;i++)
    {   
        if(states[i]==-1) continue;
        bool f=0;
        for(int j=0;j<i;j++)
        {
            if(equivalence[i][j]) 
            {
                f=1;
                break;
            }
        }
        if(f) continue;
        for(auto x:mp[i]) cout<<x<<" ";
        for(int j=0;j<total_symbol;j++)
        {
            cout<<"\t";
            set<int> s=mp[transition[i][j]];
            for(auto x:s) cout<<x<<" "; 
        }
        cout<<endl;
    }
}



int main()
{   
    store_dfa();
    show_dfa();
    mark_dfa();
    cout<<"\nTable filling: "<<endl;
    for(int i=0;i<total_state;i++)
    {
        for(int j=0;j<total_state;j++)
        {
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\nEquivalent states: "<<endl;
    equivalence.resize(total_state,vi(total_state,0));
    dfs(initial_state);
    for(int i=0;i<total_state;i++)
    {
        for(int j=0;j<i;j++) 
        {   
            if(m[i][j]==unmarked) 
            {
                cout<<j<<"=="<<i<<endl;
                equivalence[j][i]=equivalence[i][j]=1;
            }
        }
    }
    minimize_dfa();
}