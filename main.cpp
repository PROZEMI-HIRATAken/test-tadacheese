#include <bits/stdc++.h>
using namespace std;

// --- ここから先を実装してください ---
vector<string> split(const string &s, char delim);
bool isInteger(const string &s);

// 以下は変更不要
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input.csv>\n";
        return 1;
    }
    ifstream ifs(argv[1]);
    if (!ifs) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    // 省略：CSV→ARFF 変換処理
    return 0;
}
