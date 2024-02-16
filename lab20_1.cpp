#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f, vector<string> &n, vector<int> &s, vector<char> &g){
  ifstream ns(f);
  string l;
  while (getline(ns, l)) {
    char name[100];
    int a, b, c;
    sscanf(l.c_str(), "%[^:]: %d %d %d", name, &a, &b, &c);
    int total = a + b + c;
    n.push_back(name);
    s.push_back(total);
    g.push_back(score2grade(total));
  }
}

void getCommand(string &c, string &k){
  string l;
  cout << "Please input your command: ";
  getline(cin, l);
  int i = l.find(' ');
  c = l;
  if (i != -1) {
    c = l.substr(0, i);
    k = l.substr(i+1);
  }
}

void searchName(vector<string> n, vector<int> s, vector<char> g, string k){
  printf("---------------------------------\n");
  for (unsigned int i = 0; i < n.size(); i++) {
    if (toUpperStr(k) == toUpperStr(n[i])) {
      printf("%s's score = %d\n%s's grade = %c\n", n[i].c_str(), s[i], n[i].c_str(), g[i]);
      printf("---------------------------------\n");
      return;
    }
  }
  printf("Cannot found.\n");
  printf("---------------------------------\n");
}

void searchGrade(vector<string> n, vector<int> s, vector<char> g, string k){
  bool f = false;
  printf("---------------------------------\n");
  for (unsigned int i = 0; i < n.size(); i++) {
    if (toupper(k[0]) == toupper(g[i])) {
      printf("%s (%d)\n", n[i].c_str(), s[i]);
      f = true;
    }
  }
  if (!f) printf("Cannot found.\n");
  printf("---------------------------------\n");
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
