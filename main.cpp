#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 文字か数字かどうかを判定する関数
bool is_digit(const string &str) {
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// カンマで区切られた文字列を分割してvectorに格納する関数
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream ifs("lesson3.csv"); // 入力ファイル名を適宜変更
    ofstream ofs("sample3-1.arff"); // 出力ファイル名を適宜変更

    if (!ifs.is_open() || !ofs.is_open()) {
        cout << "ファイルを開けませんでした" << endl;
        return 1;
    }

    vector<vector<string>> vec;

    // CSVファイルの読み込み
    string line;
    while (getline(ifs, line)) {
        vec.push_back(split(line, ','));
    }

    // データが空でないことを確認する
    if (vec.empty()) {
        cout << "データがありません" << endl;
        return 1;
    }

    // ARFF形式への変換
    ofs << "@relation Kadai3" << endl << endl;
    for (size_t i = 0; i < vec[0].size(); ++i) {
        vector<string> unique_values;
        for (const auto &row : vec) {
            if (find(unique_values.begin(), unique_values.end(), row[i]) == unique_values.end()) {
                unique_values.push_back(row[i]);
            }
        }
        // unique_values.erase(unique(unique_values.begin(), unique_values.end()), unique_values.end());
        sort(unique_values.begin(), unique_values.end());
        if (unique_values.size() == 1) { // 1つの要素しかない場合
            if (!is_digit(unique_values[0])) {
                ofs << "@attribute No" << i+1 << " integer" << endl;
            } else {
                ofs << "@attribute No" << i+1 << " {" << unique_values[0] << "}" << endl;
            }
        }
        if (all_of(vec.begin(), vec.end(), [i](const vector<string> &row) { return is_digit(row[i]); })) {
            ofs << "@attribute No" << i+1 << " integer" << endl;
        } else {
            if(unique_values.size() != 1) {
                ofs << "@attribute No" << i+1 << " {" << unique_values[0];
                for (size_t j = 1; j < unique_values.size() ; ++j) {
                    ofs << ", " << unique_values[j];
                }
            ofs << "}" << endl;
            }
        }
    }
    ofs << endl << "@data" << endl;
    for (const auto &row : vec) {
        for (size_t i = 0; i < row.size(); ++i) {
            ofs << row[i];
            if (i != row.size() - 1)
                ofs << ", ";
        }
        ofs << endl;
    }
    
    vec.clear();
    ifs.close();
    ofs.close();

    return 0;
}
