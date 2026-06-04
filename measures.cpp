#include<iostream>
#include <sstream>
#include <string>
using namespace std;

const int N = 100;
const int INF = 1000;

int n, f, mark[N];
int measureSum[N]; //length, parsimony, ambiguity, disambiguation, entropy
vector<int> features[N];
int mapping[N][N];

void getInput(){
    cin >> n >> f;
    string line = "";
    getline(cin, line);
    for(int i = 0; i < n; i++){
        getline(cin, line);
        istringstream iss(line);
        string word;
        while(iss >> word){
            features[i].push_back(stoi(word));
        }
    }
}

void checkInput(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < features[i].size(); j++){
            cout << features[i][j] << " ";
        }
        cout << endl;
    }
}

void clearVars(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < f; j++){
            mapping[i][j] = 0;
        }
    }
    fill(begin(measureSum), end(measureSum), 0);
}

double getAvgLen(){
    int len = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < f; j++){
            if(mapping[i][j]){
                len++;
            }
        }
    }
    double avgLen = (double)len/n;
    return avgLen;
}

double getParsimony(){
    for(int i = 0; i < n; i++){
        
    }
}

double getAvgAmb(){
    double amb = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            bool consistent = 1;
            for(int k = 0; k < f; k++){
                if(mapping[i][k]){
                    bool flag = 0;
                    for(int m = 0; m < features[j].size(); m++){
                        if(features[j][m] == k){
                            flag = 1;
                        }
                    }
                    if(!flag){
                        consistent = 0;
                    }
                }
            }
            if(consistent){
                amb++;
            }
        }
    }
    return double(amb/n);
}

double getAvgDis(){
    double dis = 0;
    for(int i = 0; i < n; i++){
        int itemMappingLen = 0;
        for(int j = 0; j < f; j++){
            itemMappingLen += mapping[i][j];
        }
        dis += features[i].size() - itemMappingLen;
    }
    return (double)dis/n;
}

void updateAvg(){
    measureSum[0] += getAvgLen(); // length
    measureSum[2] += getAvgAmb(); // ambiguity
    measureSum[3] += getAvgDis(); // disambiguation
}

// we assume number of items <= 2 * number of features
void createMappings(int curI, int curF){
    //cout << "create mapping " << cur << endl;
    if(curI <= 0){
        updateAvg();
        return;
    }
    mapping[curI][curF] = 0;
    if(curF-1 == 0){
        createMappings(curI-1, f);
    }
    else{
        createMappings(curI, curF-1);
    }
    for(int i = 0; i < features[curI].size(); i++){
        if(features[curI][i] == curF){
            mapping[curI][curF] = 1;
            if(curF-1 == 0){
                createMappings(curI-1, f);
            }
            else{
                createMappings(curI, curF-1);
            }
            break;
        }
    }
}

int main(){
    getInput();
    //checkInput();
    clearVars();
    //cout << "vars cleared" << endl;
    createMappings(n, f);
    //cout << "mappings created" << endl;
}