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

void importDataFromFile(string filename, vector<string> &name,vector<int> &score,vector<char> &grade){
    ifstream file;
    file.open(filename);
    string text;
    while(getline(file,text)) {
        char tempN[99];
        int s1,s2,s3;
        sscanf(text.c_str(),"%99[^:]: %d %d %d",tempN,&s1,&s2,&s3);
        name.push_back(tempN);
        score.push_back(s1+s2+s3);
        grade.push_back(score2grade(s1+s2+s3));
    }
    file.close();
}

void getCommand(string &text,string &ky){
    cout << "Please input your command:\n";
    getline(cin,text);
    text = toUpperStr(text);
    if (text.substr(0,4) == "NAME"){
        ky = text.substr(5,sizeof(text)/sizeof(text[0]));
        text = text.substr(0,4);
    }else if (text.substr(0,5) == "GRADE") {
        ky = text.substr(6,sizeof(text)/sizeof(text[0]));
        text = text.substr(0,5);
    }
}

void searchName(vector<string> name,vector<int> score,vector<char> grade,string key){
    bool state=false;
    for (unsigned int i=0;i<name.size();i++) {
        if (key == toUpperStr(name[i])) {
            state = true;
            cout << "---------------------------------\n";
            cout << name[i] << "'s score = " << score[i] << endl; 
            cout << name[i] << "'s grade = " << grade[i] << endl; 
            cout << "---------------------------------\n";
            break;
        }
    }
    if (!state) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> name,vector<int> score,vector<char> grade,string key){
    int state=0;
    cout << "---------------------------------\n";
    for (unsigned int i=0;i<name.size();i++) {
        if (key[0] == grade[i]) {
            cout << name[i] << " (" << score[i] << ")" << endl; 
            state += 1;
        }
    }
    if (state <= 0) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
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