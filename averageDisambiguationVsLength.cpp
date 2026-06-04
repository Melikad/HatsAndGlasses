#include<iostream>
#include <sstream>
#include <string>
using namespace std;

const int N = 100;
const int INF = 1000;

int n, f, mark[N];
double minAvgLen;
double minAvgDis;
vector<int> features[N];
vector<int> mapping[N];
vector<vector<pair<int, int>>> minLenMappings, minDisMappings;

void getInput(){
    cin >> n >> f;
    string line = "";
    getline(cin, line);
    for(int i = 0; i < n; i++){
        getline(cin, line);
        istringstream iss(line);
        string word;
        while(iss >> word){
            features[i].push_back(stoi(word)-1);
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
        while(mapping[i].size() > 0){
            mapping[i].pop_back();
        }
        mark[i] = 0;
    }
    minAvgLen = INF;
    minAvgDis = INF;
}

double getAvgLen(){
    int len = 0;
    for(int i = 0; i < n; i++){
        len += mapping[i].size();
    }
    double avgLen = (double)len/n;
    return avgLen;
}

double getAvgDis(){
    double dis = 0;
    for(int i = 0; i < n; i++){
        dis += features[i].size();
        for(int j = 0; j < mapping[i].size(); j++){
            //if(*find(features[i].begin(), features[i].end(), mapping[i][j]) != 0){
            for(int k = 0; k < features[i].size(); k++){
                if(features[i][k] == mapping[i][j]){
                    dis--;
                    // if(mapping[0].size() + mapping[1].size() + mapping[2].size() == 6 && mapping[0][0] == 0 && mapping[0][1] == 1 && mapping[1][0] == 1 && mapping[1][1] == 2 && mapping[2][0] == 0 && mapping[2][1] == 2){
                    //     cout << "## item: " << i << " mapping: " << mapping[i][j] << endl;
                    //     cout << "$$ features: " << features[i][0] << " " << features[i][1] << endl;
                    //     cout << "dis: " << dis << endl;
                    // }
                    break;
                    //cout << "### decresing dis from mapping: " << dis << endl;
                    // for(int k = 0; k < n; k++){
                    //     for(int m = 0; mapping[k].size(); m++){
                    //         cout << mapping[k][m] << " ";
                    //     }
                    //     cout << ",";
                    // }
                    // cout << endl;
                }
            }
        }
    }
    // if(mapping[0].size() + mapping[1].size() + mapping[2].size() == 6 && mapping[0][0] == 0 && mapping[0][1] == 1 && mapping[1][0] == 1 && mapping[1][1] == 2 && mapping[2][0] == 0 && mapping[2][1] == 2){
    //     cout << "--------------- dis: " << dis << " " << (double)dis/n << endl;
    // }
    return (double)dis/n;
}

void checkAvg(){
    double avgLen = getAvgLen();
    //cout << "avg len " << avgLen << endl;
    double avgDis = getAvgDis();
    // if(mapping[0].size() + mapping[1].size() + mapping[2].size() == 6 && mapping[0][0] == 0 && mapping[0][1] == 1 && mapping[1][0] == 1 && mapping[1][1] == 2 && mapping[2][0] == 0 && mapping[2][1] == 2){
    //     cout << "?1 avg dis: " << avgDis << " min avg dis: " << minAvgDis << endl;
    // }
    //cout << "avg dis " << avgDis << endl;
    if(avgLen < minAvgLen){
        minAvgLen = avgLen;
        minLenMappings.clear();
    }
    if(avgDis < minAvgDis){
        minAvgDis = avgDis;
        minDisMappings.clear();
    }
    if(avgLen <= minAvgLen){
        vector<pair<int, int>> newMinMapping;
        for(int i = 0; i < n; i++){
            //cout << "adding new min len mapping  for item" << i << " with mapping size " << mapping[i].size() << endl;
            if(mapping[i].size() == 1){
                newMinMapping.push_back(make_pair(mapping[i][0], INF));
            }
            else{
                newMinMapping.push_back(make_pair(mapping[i][0], mapping[i][1]));
            }
        }
        minLenMappings.push_back(newMinMapping);
        newMinMapping.clear();
    }
    if(avgDis <= minAvgDis){
        vector<pair<int, int>> newMinMapping;
        for(int i = 0; i < n; i++){
            //cout << "adding new min dis mapping for item" << i << " with mapping size " << mapping[i].size() << endl;
            if(mapping[i].size() == 1){
                newMinMapping.push_back(make_pair(mapping[i][0], INF));
            }
            else{
                newMinMapping.push_back(make_pair(mapping[i][0], mapping[i][1]));
            }
        }
        minDisMappings.push_back(newMinMapping);
        newMinMapping.clear();
    }
    // if(mapping[0].size() + mapping[1].size() + mapping[2].size() == 6 && mapping[0][0] == 0 && mapping[0][1] == 1 && mapping[1][0] == 1 && mapping[1][1] == 2 && mapping[2][0] == 0 && mapping[2][1] == 2){
    //     cout << "?2 avg dis: " << avgDis << " min avg dis: " << minAvgDis << endl;
    // }
}

// we assume number of items <= 2 * number of features
void createMappings(int cur){
    //cout << "create mapping " << cur << endl;
    if(cur == 0){
        // cout << "current mapping: ";
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < mapping[i].size(); j++){
        //         cout << mapping[i][j]+1 << " ";
        //     }
        //     cout << ", ";
        // }
        // cout << endl;
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < mapping[i].size(); j++){
        //         cout << "@ " << mapping[i][j] << "@ ";
        //         if(*find(features[i].begin(), features[i].end(), mapping[i][j]) != 0){
        //             cout << "is in features : " << *find(features[i].begin(), features[i].end(), mapping[i][j]) << " ";
        //             cout << "### " << features[i][0] << " " << features[i][1] << " ### " << mapping[i][j]+1 << " $$$$$ "; 
        //         }
        //         cout << ", ";
        //     }
        // }
        // cout << endl;
        checkAvg();
        return;
    }
    for(int i = 0; i < f; i++){
        if(!mark[i]){
            mark[i] = 1;
            mapping[cur-1].push_back(i);
            createMappings(cur-1);
            mark[i] = 0;
            mapping[cur-1].clear();
        }
    }
    for(int i = 0; i < f; i++){
        for(int j = i+1; j < f; j++){
            if(!mark[i*f+j]){
                mark[i*f+j] = 1;
                mapping[cur-1].push_back(i);
                mapping[cur-1].push_back(j);
                createMappings(cur-1);
                mark[i*f+j] = 0;
                mapping[cur-1].clear();
            }
        }
    }
}

void minMappingsOutput(){
    cout << "min avg len: " << minAvgLen << endl;
    cout << "min avg len mappings: " << minLenMappings.size() << endl;
    for(int i = 0; i < minLenMappings.size(); i++){
        for(int j = 0; j < n; j++){
            cout << minLenMappings[i][j].first+1;
            if(minLenMappings[i][j].second != INF){
                cout << " " << minLenMappings[i][j].second+1;
            }
            cout << ", ";
        }
        cout << endl;
    }

    cout << "min avg dis: " << minAvgDis << endl;
    cout << "min avg dis mappings: " << minDisMappings.size() << endl;
    for(int i = 0; i < minDisMappings.size(); i++){
        for(int j = 0; j < n; j++){
            cout << minDisMappings[i][j].first+1;
            if(minDisMappings[i][j].second != INF){
                cout << " " << minDisMappings[i][j].second+1;
            }
            cout << ", ";
        }
        cout << endl;
    }
}

void sharedMinMappings(){
    int minLenInDis = 0;
    int minDisInLen = 0;
    for(int i = 0; i < minLenMappings.size(); i++){
        bool foundTheSame = 0;
        for(int j = 0; j < minDisMappings.size() && !foundTheSame; j++){
            if(minLenMappings[i].size() == minDisMappings[j].size()){
                bool flag = 0;
                for(int k = 0; k < minLenMappings[i].size(); k++){
                    if(minLenMappings[i][k] != minDisMappings[j][k]){
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    minLenInDis++;
                    foundTheSame = 1;
                }
            }
        }
    }
    cout << "min len in min dis " << minLenInDis << endl;
    for(int i = 0; i < minDisMappings.size(); i++){
        bool foundTheSame = 0;
        for(int j = 0; j < minLenMappings.size() && !foundTheSame; j++){
            if(minLenMappings[i].size() == minDisMappings[j].size()){
                bool flag = 0;
                for(int k = 0; k < minDisMappings[i].size(); k++){
                    if(minDisMappings[i][k] != minLenMappings[j][k]){
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    minDisInLen++;
                    foundTheSame = 1;
                }
            }
        }
    }
    cout << "min dis in min len " << minDisInLen << endl;
}

int main(){
    getInput();
    //checkInput();
    clearVars();
    //cout << "vars cleared" << endl;
    createMappings(n);
    //cout << "mappings created" << endl;
    minMappingsOutput();
    sharedMinMappings();
}
