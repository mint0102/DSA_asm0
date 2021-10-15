#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

class Node{
public:
    string data;
    string type;
    int level;
    Node *next = nullptr;
    Node():next(nullptr){};
    Node(string data, string type,int level): data(data), type(type), level(level), next(nullptr) {};
    ~Node();
};
class Link{
public:
    Node* head;
    Link():head(nullptr){};
    ~Link();
};
int Space(string input){
    int size;
    size = input.length();
    int count = 0;
    int i = 0;
    while(i < size) {
        if(input[i] == ' ') count++;
        if(input[i] == 39){
            string st = input.substr(i+1, size - i -1);
            int k;
            k = st.find(39);
            i = i + k + 2;
        }
        else i++;
    }
    return count;
}
bool identifier(string data){
    int size;
    size = data.length();
    for (int i = 1; i < size; ++i) {
        if(!((data[i] <= 'z' && data[i] >= 'a') || (data[i] <= 'Z' && data[i] >= 'A') || (data[i] =='_')|| (data[i] <='9' && data[i]>='0')))
            return false;
    }
    return true;
}
bool insert(Link*& List, const string& data, const string& type, int level){
    Node *temp = new Node(data, type, level);
    if(List->head == nullptr){
        List->head = temp;
        return true;
    }
    Node* pre = List->head;
    Node* tp = new Node();
    while (pre){
        if((pre->data == data) && (pre->level == level))
            return false;
        tp = pre;
        pre = pre->next;
    }
    tp->next = temp;
    return true;
}
bool rinsert(Link*& List, string data, string type, int level){
    Node *temp = new Node(data, type, level);
    if(List->head == nullptr)
        List->head = temp;
    else{
        temp->next = List->head;
        List->head = temp;
    }
    return true;
}
bool constNumber(string val){
    int size;
    size = val.length();
    for (int i = 0; i < size; i++) {
        if(val[i] <'0' || val[i] >'9') return false;
    }
    return true;
}
bool key(char k){
    if((k >= '0' && k <= '9') || (k >= 'a' && k <= 'z') ||(k >= 'A' && k <= 'Z') || (k == ' '))
        return true;
    return false;
}
bool constString(string val){
    int size;
    size = val.length();
    if(val[0] != 39 || val[size-1] != 39) return false;
    for (int i = 1; i < size-1 ; i++) {
        if(!key(val[i]))
            return false;
    }
    return true;
}
bool Val(const string& value){
    if(identifier(value) || constNumber(value) || constString(value)) return true;
    return false;
}
string Typeval(Link* List, const string& value){
    if(constString(value)) return "string";
    if(constNumber(value)) return "number";
    Node *pre = List->head;
    int k = 0;
    string type;
    while (pre){
        if(pre->data == value && pre->level >= k){
            type = pre->type;
        }
        pre = pre->next;
    }
    return type;
}
string Typedata(Link* List, const string& data){
    Node *pre = List->head;
    int k = 0;
    string type = "";
    while (pre){
        if(pre->data == data && pre->level >= k){
            type = pre->type;
            k++;
        }
        pre = pre->next;
    }
    return type;
}
int assign(Link*& List, const string& data, const string& value){
    if(List->head == nullptr || Typedata(List, data) == "") return -1;
    if(Typeval(List,value) != Typedata(List, data)) return 0;
    return 1;
}
void print(Link* List){
    if(List->head == nullptr) return;
    Node* pre = List->head;
    Link *LIST = new Link();
    while (pre){
        rinsert(LIST, pre->data, pre -> type, pre -> level);
        pre = pre -> next;
    }
    pre = LIST->head;
    Link *LISTT = new Link();
    bool k = false;
    while (pre){
        Node* tp;
        tp = LISTT->head;
        while (tp){
            if(tp->data == pre -> data)
                k = true;
            tp = tp->next;
        }
        if(!k) rinsert(LISTT, pre->data, pre -> type, pre -> level);
        pre = pre -> next;
        k = false;
    }
    pre = LISTT->head;
    while(pre->next){
        cout << pre->data << "//" << pre->level << " ";
        pre = pre->next;
    }
    cout << pre->data << "//" << pre->level << endl;
}
void rprint(Link* List){
    if(List->head == nullptr) return;
    Node* pre = List->head;
    Link *LIST = new Link();
    while (pre){
        rinsert(LIST, pre->data, pre -> type, pre -> level);
        pre = pre -> next;
    }
    pre = LIST->head;
    Link *LISTT = new Link();
    bool k = false;
    while (pre){
        Node* tp;
        tp = LISTT->head;
        while (tp){
            if(tp->data == pre -> data)
                k = true;
            tp = tp->next;
        }
        if(!k) rinsert(LISTT, pre->data, pre -> type, pre -> level);
        pre = pre -> next;
        k = false;
    }
    pre = LISTT->head;
    Link *RLIST = new Link();
    while (pre){
        rinsert(RLIST, pre->data, pre -> type, pre -> level);
        pre = pre -> next;
    }
    pre = RLIST->head;
    while(pre->next){
        cout << pre->data << "//" << pre->level << " ";
        pre = pre->next;
    }
    cout << pre->data << "//" << pre->level << endl;

}
int look(Link* List, const string& data){
    if(List->head == nullptr){
        return -1;
    }
    Node *pre = List->head;
    int k = -1;
    while (pre){
        if(pre->data == data && k < pre->level) k = pre->level;
        pre = pre->next;
    }
    return k;
}
void remove(Link*& List, int level){
    if(List->head == nullptr) return;
    if(List->head->level == level){
        Node* tp;
        tp = List->head;
        List->head = nullptr;
        free(tp);
        return;
    }
    Node* pre;
    Node* tp = new Node();
    bool k = true;
    pre = List->head;
    while (k && pre->next){
        if(pre->next->level == level){
            k = false;
        }
        tp = pre;
        pre = pre->next;
    }
    if(k)
        return;
    if(!pre)
        return;
    else{
        Node *temp;
        temp = tp->next;
        tp->next = nullptr;
        while(!temp){
            Node * t = temp;
            temp = temp->next;
            free(t);
            //free(t) ????
        }
    }
}
class SymbolTable {
public:
    SymbolTable() {}
    void run(string filename);
    ~SymbolTable(){}
    // tac dung cua class nay la gi?
    //
};
#endif
