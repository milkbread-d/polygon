#include <iostream>
#include <fstream>
#include <string>
using namespace std;


bool coro(const string& str){
  int state = 0;
  for(int i = 0; i < str.length(); i++){
    char current = str[i];
    if (current == '('){
      state++;
    }
    else if (current == ')'){
    state--;
    }

  }
  return state != 0;
}


int main(){
  string str;
  ifstream fin("lab3.txt");
  fin>>str;

  ofstream fout("lab3_out.txt");
  fout << coro(str);
  cout<< coro(str);
  fout.close();
  fin.close();
}