#include "SymbolTable.h"
#include "SymbolTable.cpp"
using namespace std;

void test(string filename)
{
    SymbolTable *st = new SymbolTable();
    try
    {
        st->run(filename);
    }
    catch (exception &e)
    {
        cout << e.what();
    }
    delete st;
}

int main(int argc, char **argv)
{
    //if (argc < 2)
        //return 1;
        //hmmm, tìm hiểu qua cái lệnh này, khó hiểu quá
        test("D:\\CLionProjects\\asm\\asm1\\asm0\\test1.txt");
    return 0;
}
