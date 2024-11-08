using namespace std;

#include <iostream>
#include <string>
#include <cctype>


bool Keyword(const string& token) {
    return token == "int" || token == "char" || token == "float" || token == "double" || token == "void" || token == "bool" ||
           token == "if" || token == "else" || token == "while" || token == "for" || token == "do" || token == "switch" ||
           token == "case" || token == "break" || token == "continue" || token == "return" ||
           token == "public" || token == "private" || token == "protected" || token == "class" ||
           token == "try" || token == "catch" ||token == "throw" || token == "static";
}

bool Number(const string& token) {
    bool hasDecimal = false;
    for (int i = 0; i < token.length(); i++) {
        if (token[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool Identifier(const string& token) {
    if (isalpha(token[0]) || token[0] == '_') {
        for (int i = 1; i < token.length(); i++) {
            if (!isalnum(token[i]) && token[i] != '_') return false;
        }
        return true;
    }
    return false;
}

bool SpecialCharacter(const string& token) {

     if ( token == "==" || token == "!=" || token == "++" || token == "--" || token == "+=" || token == "-=" || token == "*=" || token == "/=") {
        return true;
    }

    return token == "+" || token == "-" || token == "*" || token == "/" ||
           token == ";" || token == "," || token == "(" || token == ")" ||
           token == "[" || token == "]" || token == "{" || token == "}" ||
           token == ":" || token == "." || token == "!" || token == "&" ||
           token == "|" || token == "^" || token == "<" ||
           token == ">" || token == "=";
}

void skipLineComment(const string& expression, int& i) {
    while (i < expression.length() && expression[i] != '\n') {
        i++;
    }
}

void skipMultipleLineComment(const string& expression, int& i) {
    i+2;
    while (i < expression.length()) {
        if (expression[i] == '*' && expression[i + 1] == '/') {
            i += 2;
            break;
        }
        i++;
    }
}

int main() {
    string line;

    cout << "Enter : ";

    while (getline(cin, line)) {
        int i = 0;
        bool isEmptyLine = true;

        while (i < line.length()) {
            if (isspace(line[i])) {
                i++;
                continue;
            }

            if (i < line.length() - 1 && line[i] == '/' && line[i + 1] == '/') {
                skipLineComment(line, i);
                continue;
            }
            else if (i < line.length() - 1 && line[i] == '/' && line[i + 1] == '*') {
                skipMultipleLineComment(line, i);
                continue;
            }

            string token = "";

            if (isalpha(line[i]) || line[i] == '_') {
                while (i < line.length() && (isalnum(line[i]) || line[i] == '_')) {
                    token += line[i];
                    i++;
                }
                if (Keyword(token)) {
                    cout <<token << " is keyword" <<endl;
                } else if (Identifier(token)) {
                    cout << token << " is id"<<endl;
                }
                isEmptyLine = false;
            }
            else if (isdigit(line[i]) || line[i] == '.') {
                while (i < line.length() && (isdigit(line[i]) || line[i] == '.')) {
                    token += line[i];
                    i++;
                }
                cout << token << " is number"<<endl;
                isEmptyLine = false;
            }
            else {
                token += line[i];
                i++;

                if (i < line.length() && (line[i] == '=' || line[i] == '+' || line[i] == '*' || line[i] == '-' || line[i] == '/' || line[i] == '(' || line[i] == ')')) {
                    token += line[i];
                    i++;
                }

                if (SpecialCharacter(token)) {
                    cout  << token << " is special character" <<endl;
                } else {
                    cout  << token << " is unknown token"<<endl;
                }
                isEmptyLine = false;
            }
        }

        if (isEmptyLine) {
            cout << "Empty Line"<<endl;
        }
    }

    return 0;
}
