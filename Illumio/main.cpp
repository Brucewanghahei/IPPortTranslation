#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class IPPortTranslation {
    unordered_map<string, string> ip_port_map;
    unordered_map<string, string> ip_map;
    unordered_map<string, string> port_map;

    void readNAT(string NAT_file) {
        ifstream nat(NAT_file);
        if (!nat.is_open()) {
            cout << "Unable to open NAT file" << endl;
            return;
        }
        string line;
        while (getline(nat, line)) {
            string s1 = line.substr(0, line.find(','));
            string s2 = line.substr(line.find(',') + 1);
            if (s1.find('*') == s1.npos) {
                ip_port_map[s1] = s2;
                continue;
            }
            string ip = s1.substr(0, s1.find(':'));
            string port = s1.substr(s1.find(':') + 1);
            if (ip == "*") {
                port_map[port] = s2;
            } else {
                ip_map[ip] = s2;
            }
        }
        nat.close();
    }

    void clearMap() {
        ip_port_map.clear();
        port_map.clear();
        ip_map.clear();
    }

public:
    void translate(string NAT_file, string FLOW_file);
};

void IPPortTranslation::translate(string NAT_file, string FLOW_file) {
    clearMap();
    readNAT(NAT_file);
    ofstream output;
    output.open("../OUTPUT.txt");
    if (!output.is_open()) {
        cout << "Unable to open OUTPUT file" << endl;
        return;
    }
    ifstream flow(FLOW_file);
    if (!flow.is_open()) {
        cout << "Unable to open FLOW file" << endl;
        return;
    }
    string line;
    while (getline(flow, line)) {
        if (ip_port_map.count(line)) {
            output << line << " -> " << ip_port_map[line] << "\n";
            continue;
        }
        string ip = line.substr(0, line.find(':'));
        string port = line.substr(line.find(':') + 1);
        if (ip_map.count(ip)) {
            output << line << " -> " << ip_map[ip] << "\n";
        } else if (port_map.count(port)) {
            output << line << " -> " << port_map[port] << "\n";
        } else {
            output << "No nat match for " << line << "\n";
        }
    }
    flow.close();
    output.close();
}

int main() {
    IPPortTranslation test;
    //test.translate("../Tests/NAT.txt", "../Tests/FLOW.txt");
    test.translate("../Tests/NAT2.txt", "../Tests/FLOW2.txt");
}