#include <iostream>
using namespace std;


int main()
{
 int no_of_states;
 cout<<"Enter no. of states:";
 cin>>no_of_states;

 int input_symbol;
 cout<<"Enter no. of input symbol:";
 cin>>input_symbol;
 int states[no_of_states][input_symbol];
 cout<<"Enter states:";
 for(int i=0;i<no_of_states;i++)
 {
     for(int j=0;j<input_symbol;j++)
     {
        cin>>states[i][j];
     }
 }
 for(int i=0;i<no_of_states;i++)
 {
     for(int j=0;j<input_symbol;j++)
     {
        cout<<states[i][j]<<" ";
     }

     cout<<endl;
 }
 int length;
 cout<<"Enter string length:";
 cin>>length;
 char input[length];
 cout<<"Enter String:";
 cin>>input;

 int state_count=0;

 for(int i=0;i<length;i++)
 {

     if(input[i]=='a')
     {
         state_count=states[state_count][0];

     }
     else
    {
        state_count=states[state_count][1];

     }
 }
cout<<state_count<<endl;
 if(state_count==1)
 {
     cout<<"Accepted";
 }
 else
{
    cout<<"Rejected";
 }
}
