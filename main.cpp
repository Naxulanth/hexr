#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/filesystem.hpp>


using namespace std;
namespace fs = boost::filesystem;

int main() {


    fs::path path = ".";

    fs::directory_iterator end;

    for (fs::directory_iterator iter(path); iter != end; ++iter) {
        if (is_regular_file(iter->path())) {
        string file_name = iter->path().filename().string();

    char* filename = &file_name[0u];
    string res = "hexdump_" + string(filename) + ".txt";
    cout << file_name + " -> " + res << endl;
    char* r_filename = &res[0u];
    unsigned long addr = 0;
    fstream file(filename, fstream::binary | fstream::in);
    fstream result(r_filename, fstream::out);

    while (file.good())
    {

        char buf[16];

        int rd;

        for (rd = 0; rd < 16 && file.get(buf[rd]); rd++); // fill buffer

        if (rd == 0) break; // end if there are nothing to get in the file

        result << hex << setfill('0') << setw(8) << addr; // print address in 8 char form

        for (int i = 0; i < 16; i++)
        {
            if (i % 8 == 0) result << " ";
            if (i < rd) // check if buffer contains a value
                result << " " << setw(2) << (unsigned int)(unsigned char)buf[i]; // cast into unsigned char to avoid sign extension
            else
                result << "   "; // insert 3 spaces if there's nothing in buffer
        }

        result << "  "; // separator

        for (int i = 0; i < rd; i++)
        {
            if (buf[i] < 32) result << '.'; // print . if the buffer doesn't contain a printable char
            else result << buf[i];
        }

        result << "\n";
        addr += 16;
        }
    }
    cout << "done" << endl;
    }
    return 0;
}