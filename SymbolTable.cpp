#include "SymbolTable.h"

void SymbolTable::run(string filename) {
    fstream testcase;
    testcase.open(filename, ios:: in);
    string input;
    Link* List = new Link();
    int level = 0;
    while (!testcase.eof()){
        getline(testcase, input);
        int space = Space(input);
        if(space > 2)
            throw InvalidInstruction(input);
        int k = input.find(' ');
        string task = input.substr(0, k);
        if(space == 2){
            if(task == "INSERT"){
                string st = input.substr(k+1, input.length());
                int t = st.find(' ');
                string data = st.substr(0, t);
                string type = st.substr(t+1, st.length());
                if(type != "string"){
                    if(type != "number")
                        throw InvalidInstruction(input);
                }
                if(!identifier(data))
                    throw InvalidInstruction(input);
                if( !insert(List, data, type, level))
                    throw Redeclared(input);
                cout << "success" << endl;
            }
            else if(task == "ASSIGN"){
                string st = input.substr(k+1, input.length());
                int t = st.find(' ');
                string data = st.substr(0, t);
                string value = st.substr(t+1, st.length());
                if(!identifier(data))
                    throw InvalidInstruction(input);
                if( !Val( value))
                    throw InvalidInstruction(input);
                if(assign(List, data, value) == -1)
                    throw Undeclared(input);
                if(assign(List, data, value) == 0)
                    throw TypeMismatch(input);
                if(assign(List, data, value) == 1)
                    cout << "success" << endl;
            }
            else throw InvalidInstruction(input);
        }
        if(space == 1){
            if(task == "LOOKUP"){
                string data = input.substr(k+1, input.length());
                if(!identifier(data))
                    throw InvalidInstruction(input);
                if(look(List,data) == -1)
                    throw  Undeclared(input);
                cout << look(List, data) << endl;
            }
            else throw InvalidInstruction(input);
        }
        if(space == 0){
            if(task == "BEGIN") level++;
            else if(task == "END"){
                if(level == 0)
                    throw  UnknownBlock();
                remove(List, level);
                level--;
            }
            else if(task == "PRINT") print(List); // forget "phot lo tam vuc"
            else if(task == "RPRINT") rprint(List);
            else throw InvalidInstruction(input);
        }
    }
    testcase.close();
    if(level > 0)
        throw UnclosedBlock(level);
}