#include <bits/stdc++.h> 
using namespace std;

int glob=0;
int glob2;

bool findParity(int x) 
{ 
    int y = x ^ (x >> 1); 
    y = y ^ (y >> 2); 
    y = y ^ (y >> 4); 
    y = y ^ (y >> 8); 
    y = y ^ (y >> 16); 
  
 
    if (y & 1) 
        return 1; 
    return 0; 
} 

int convertToASCII(string letter)
{
  cout<<"\n";
    for (int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
      glob+=int(x);
      glob2=int(x);
      cout << letter.at(i)<< " - " <<int(x);
      (findParity(glob)==0)?cout<<" Even Parity\n":cout<<" Odd Parity\n"; 

      cout<<"\n";
    }
  return 0;
}
int main()
{
  string plainText;
cout << "Enter word to convert to ASCII: ";
 //plainText="dsgt";
  cin>>plainText;
convertToASCII(plainText);
  cout<<" \n Sum of Ascii code of entered word is "<<glob<<"\n it is an ";
     (findParity(glob)==0)?cout<<"Even Parity\n":cout<<"Odd Parity\n"; 
  return 0;
}


/*
OUTPUT


Enter word to convert to ASCII: dsgt
d - 100 Odd Parity

s - 115 Even Parity

g - 103 Even Parity

t - 116 Odd Parity



*/
