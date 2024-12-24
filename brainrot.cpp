#include "compiler.h"


using namespace std;
int main(int argc, char** argv) {
    if (argc<2) {
        cout << "Too few arguments: provide a .bf file" << endl;
        return 1;
    }
    string filename;
    int outflag = -1;
    string outname;

    for (int i =1; i<argc; i++) {
        string prompt = argv[i];

        if (prompt[0] == '-'){
            // flags
            if (prompt == "-o") {
                outflag = i;
            }
        } else {
            if (outflag != -1) {
                outname = prompt;
                outflag = -1;
            } else {
                filename = prompt;
            }
        }
    }

    if (outname.empty()) {
        if (filename.ends_with(".bf")) {
            outname = filename.substr(0, filename.size()-3);
        } else {
            outname = filename + ".out";
        }
    }

    if (filename.empty()) {
        cout << "No .bf file provided" << endl;
        return 1;
    }

    ifstream infd(filename);
    string code;
    while (!infd.eof())
    {
        infd >> code;
    }
    infd.close();

    Compiler::compile(outname, code);

    cout << "Compilation finished" << endl;
    return 0;
}