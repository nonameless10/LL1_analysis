/*
 * @Author       : czq
 * @Date         : 2021-03-23 14:17:51
 * @LastEditors  : czq
 * @LastEditTime : 2021-04-06 18:39:25
 */

#include <bits/stdc++.h>
using namespace std;


map<string, int> keywords, varNames, defValKeywords;
map<int, string> errors;

struct VAL {
    string name, val, type;
};

vector<VAL> vals;

bool CheckValName(string s) {
    while (s[s.size() - 1] == ' ') s.erase(s.end() - 1);
    int len = s.length();
    if (len > 256 || len == 0) return false;
    if (s[0] == '_' || (s[0] >= 'a' && s[0] <= 'z') || s[0] >= 'A' && s[0] <= 'Z');
    else return false;
    for (int i = 0; i < len; i ++) {
        if (s[i] == '_');
        else if (s[i] >= '0' && s[i] <= '9');
        else if (s[i] >= 'a' && s[i] <= 'z');
        else if (s[i] >= 'A' && s[i] <= 'Z');
        else return false;
    }

    if (keywords[s]) return false;
 
    if (varNames[s]) return false;
    return true;
}

bool CheckValType(string type, string s) {
    if (s[s.size() - 1] == ' ') s.erase(s.end() - 1);
    if (type == "string") {
        if (s[0] == '"' && s[s.size() - 1] == '"') return true;
        return false;
    }
    if (type == "char") {
        if (s.size() == 3 && s[0] == '\'' && s[2] == '\'') return true;
        return false;
    }
    if (type == "int" || type == "long" || type == "short") {
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] >= '0' && s[i] <= '9') continue;
            if (s[i] == '-' && i == 0) continue;
            return false;
        }
        return true;
    }
    if (type == "float" || type == "double") {
        int flag = 0;
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] == '-' && i == 0) continue;
            if (s[i] == '.') {
                if (i == s.size() - 1 || i == 0 || s[i - 1] == '-') return false;
                if (flag == 0) {
                    flag = 1;
                    continue;
                } else return false;
            }
            if (s[i] >= '0' && s[i] <= '9') continue;
            return false;
        }
        return true;
    }
    return false;
}

void Solve(string text) {
    int lenText = text.size();
    int idx = 0;
    int flag = 0;
    int error = 0;
    int errorIndex = 0;
    string tmpName = "", tmpVal = "", tmpType = "", type = "";
    while (idx < lenText) {
        if (flag == 0) {
            flag = 1;
            tmpType = "";
            errorIndex = idx;
            while (idx < lenText && text[idx] != ' ') tmpType += text[idx ++];
            if (defValKeywords[tmpType]) {
             
                if (tmpType == "const") {
                    while (idx < lenText && text[idx] == ' ') idx ++;
                    type = "";
                    errorIndex = idx;
                    while (idx < lenText && text[idx] != ' ') type += text[idx ++];
                    if (defValKeywords[type]) {
                        tmpType += " " + type;
                    } else {
                        error = 4;
                        break;
                    }
                } else {
                    type = tmpType;
                }
            }
            else{
                error = 4;
                break;
            }
        }
        while (idx < lenText && text[idx] == ' ') idx ++;
        errorIndex = idx;
        while (idx < lenText && text[idx] != ',' && text[idx] != ';' && text[idx] != '=') tmpName += text[idx ++];
        if (!CheckValName(tmpName)) {
            error = 1;
            break;
        }
        if (idx == lenText) break;
        if (text[idx] == '=') {
            idx ++;
            while (idx < lenText && text[idx] == ' ') idx ++;
            errorIndex = idx;
            while (idx < lenText && text[idx] != ',' && text[idx] != ';') tmpVal += text[idx ++]; // ????????
            if (!CheckValType(type, tmpVal)) {
                // cout << type << "-" << tmpVal << "-" << endl;
                error = 2;
                break;
            }
            if (idx == lenText) break;
            if (text[idx] == ';') flag = 0;
            idx ++;
            while (idx < lenText && text[idx] == ' ') idx ++;
            vals.push_back({tmpName, tmpVal, tmpType});
        } else {
            if (type != tmpType) {
                error = 5;
                break;
            }
            if (text[idx] == ';') flag = 0;
            idx ++;
            while (idx < lenText && text[idx] == ' ') idx ++;
            vals.push_back({tmpName, "NULL", tmpType});
        }
        varNames[tmpName] = 1;
        tmpName = "", tmpVal = "";
    }
    
    if (text[lenText - 1] != ';') {
        if (error == 0) {
            error = 3;
            errorIndex = lenText - 1;
        }
    }
    cout << text << endl;
    if (error) {
        for (int i = 0; i < errorIndex; i ++) cout << "-";
        cout << "^" << endl;
        cout << errors[error] << endl;
    } else {
        for (VAL it : vals) cout << it.name << "->[" << it.type << ", " << it.val << "]" << endl;
    }
    puts("");
}

int main() {

    {
        keywords["auto"] = 1; keywords["double"] = 1; keywords["int"] = 1; keywords["struct"] = 1;
        keywords["break"] = 1; keywords["else"] = 1; keywords["long"] = 1; keywords["switch"] = 1;
        keywords["case"] = 1; keywords["enum"] = 1; keywords["register"] = 1; keywords["char"] = 1;
        keywords["typedef"] = 1; keywords["extern"] = 1; keywords["return"] = 1; keywords["union"] = 1;
        keywords["const"] = 1; keywords["float"] = 1; keywords["short"] = 1; keywords["unsigned"] = 1;
        keywords["continue"] = 1; keywords["for"] = 1; keywords["signed"] = 1; keywords["void"] = 1;
        keywords["default"] = 1; keywords["goto"] = 1; keywords["sizeof"] = 1; keywords["volatile"] = 1;
        keywords["do"] = 1; keywords["if"] = 1; keywords["while"] = 1; keywords["static"] = 1;

        defValKeywords["const"] = 1;
        defValKeywords["int"] = 1;
        defValKeywords["long"] = 1;
        defValKeywords["double"] = 1;
        defValKeywords["short"] = 1;
        defValKeywords["char"] = 1;
        defValKeywords["float"] = 1;
        defValKeywords["string"] = 1;
    }
    

    {
        errors[1] = "变量名不合法";
        errors[2] = "变量值和其类型不匹配";
        errors[3] = "语句末尾没有分号";
        errors[4] = "变量类型不是一个关键字";
        errors[5] = "常量必须初始化";
    }
    
    
    string text1 = "int a = 1, b = 2; const  double x = 1.5; string s = \"hello world\"; char c = 'f';";
    string text2 = "int a = 1; intt b = 2;";
    string text3 = "const int t = 5, g;";
    string text4 = "int a = 1, b = 2";
    string text5 = "double a = 9; int a = 0.9";
    string text6 = "int 9s = 9;";
    Solve(text1);
    Solve(text2);
    Solve(text3);
    Solve(text4);
    Solve(text5);
    Solve(text6);
    return 0;
}