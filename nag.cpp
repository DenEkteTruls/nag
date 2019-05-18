#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

string saved;

void save(string name, string value) {
  string final = ";;" + name + ";" + value;
  saved += final;
}

// IF MATCHES

void if_match_equals() {
  cout << "equal" << endl;
  // working here ...
}
void if_match_over() {
  cout << "over" << endl;
  // working here ...
}
void if_match_under() {
  cout << "under" << endl;
  // working here ...
}
void if_match_overEquals() {
  cout << "overEquals" << endl;
  // working here ...
}
void if_match_underEquals() {
  cout << "underEquals" << endl;
  // working here ...
}

// THE MAIN CODE

int main(int argc, char* argv[]) {
  string line;
  ifstream file(argv[1]);
  if(file.is_open()) {
    while(getline(file, line)) {

      // Printing process

      // Normal print string
      if(line.find("print") != string::npos) {
        // Checks for the normal printing option
        int start_par = 5;
        int value_par = 6;
        int end_par = line.size();
        int checking_par = 6;
        if(line[checking_par] == '$') {
          // Printing a saved string
          string stringValue; // Check
          string stringName; // Check
          for(int i = value_par + 1; i < end_par; i++) {
            if(line[i] == ')') {
              break;
            }
            stringName += line[i];
          }
          for(int i = 0; i < saved.size(); i++) {
            if(saved.find(";;" + stringName) != string::npos) {
              stringValue += saved[i + stringName.size() + 3];
            }
          }
          if(line[line.size()] == '.') {
            cout << stringValue; break;
          } else { cout << stringValue << endl; break; }
        }
        if(line[start_par] == '(') {
          string print_value; // Check
          int end_pos; // Check
          for(int i = value_par; i < end_par; i++) {
            if(line[i] == ')') {
              end_pos = i;
              break;
            }
            print_value += line[i];
          }
          if(line[end_pos + 1] == '.') {
            cout << print_value;
          } else { cout << print_value << endl; }
        }
      }

      // Writing process

      // Normal single write operation
      if(line.find("write") != string::npos) {
        // Checks for the normal writing option
        int start_par = 5;
        int value_par = 6;
        int end_par = line.size();
        if(line[start_par] == '(') {
          string writeName; // Check
          string writeValue; // Check
          string finalWriting; // Check
          for(int i = value_par; i < end_par; i++) {
            if(line[i] == ')') {
              // save the writing in memory
              getline(cin, writeValue);
              save(writeName, writeValue);
            }
            writeName += line[i];
          }
        }
      }

      // Variables process

      // Normal string var
      if(line.find("$var") != string::npos) {
        int start_pos = 3; // Check
        int value_pos; // Check
        string varName; // Check
        string varValue; // Check
        for(int i = start_pos; i < line.size(); i++) {
          if(line[i] == '=') {
            value_pos = i + 1;
            break;
          }
        }
        for(int s = start_pos + 2; s < value_pos - 2; s++) {
          varName += line[s];
        }
        if(line[value_pos] == ' ') {
          value_pos += 1;
        }
        for(int a = value_pos; a < line.size(); a++) {
          varValue += line[a];
        }
        // save the variable in the memory
        if(varValue[0] == 'w' & varValue[1] == 'r' & varValue[2] == 'i' & varValue[3] == 't' & varValue[4] == 'e' & varValue[5] == '(' & varValue[6] == ')') {
          string var_writeValue;
          getline(cin, var_writeValue);
          save(varName, var_writeValue);
        } else {
          save(varName, varValue);
        }
      }

      // if statements

      if(line.find("if($(") != string::npos) {
        string variable;
        string raw_string;
        string operation;
        for(int i = 5; i < line.size(); i++) {
          if(line[i] == ')') {
            break;
          }
          variable += line[i];
        }
        for(int i = 5 + variable.size() + 1; i < line.size(); i++) {
          if(line[i] == '>') {
            operation = ">"; break;
          } else if(line[i] == '<') {
            operation = "<"; break;
          } else if(line[i] == '=' & line[i+1] == '>') {
            operation = "=>"; break;
          } else if(line[i] == '=' & line[i+1] == '<') {
            operation = "=<"; break;
          } else if(line[i] == '=') {
            operation = "="; break;
          }
        }
        for(int i = 5 + variable.size() + operation.size() + 2; i < line.size(); i++) {
          if(line[i] == ' ') {
            i += 1;
          }
          if(line[i] == ')') {
            break;
          }
          raw_string += line[i];
        }

        // deconverting the variableName
        string deconverted;
        for(int i = 0; i < saved.size(); i++) {
          if(saved.find(";;" + variable) != string::npos) {
            deconverted += saved[i + variable.size() + 3];
          }
        }

        // Prints things
        cout << "variable: " + variable << endl;
        cout << "operation: " + operation << endl;
        cout << "raw_string: " + raw_string << endl;
        cout << "deconverted: " + deconverted << endl;
        cout << endl;

        const char *final_deconverted = deconverted.c_str();

        if(operation == "=") {
          if(final_deconverted == raw_string) {
            if_match_equals();
          }
        } if(operation == ">") {
          if(final_deconverted > raw_string) {
            if_match_over();
          }
        } if(operation == "<") {
          if(final_deconverted < raw_string) {
            if_match_under();
          }
        } if(operation == "=>") {
          if(final_deconverted >= raw_string) {
            if_match_overEquals();
          }
        } if(operation == "=<") {
          if(final_deconverted <= raw_string) {
            if_match_underEquals();
          }
        }
      }
    }
  }
  return 0;
}
