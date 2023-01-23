#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <string.h>
#include <unistd.h>
using namespace std;

void list_files(string dir, ofstream &out) {
    DIR *dp = opendir(dir.c_str());
    if (dp == nullptr) {
        cerr << "Error opening " << dir << endl;
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dp)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            string name = entry->d_name;
            if (name != "." && name != "..") {
                list_files(dir + '/' + name, out);
            }
        }
        else {
            out << "<tr>" << endl;
            out << "<td>" << entry->d_name << "</td>" << endl;
            out << "<td>" << dir << "</td>" << endl;
            out << "</tr>" << endl;
        }
    }
    closedir(dp);
}

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        cerr << "Error getting current working directory" << endl;
        return -1;
    }
    string dir = cwd;
    string output_file;

    cout << "Enter the output file name (with .html extention):";
    cin >> output_file;

    ofstream out(output_file);
    if (!out) {
        cerr << "Error opening " << output_file << endl;
        return -1;
    }

    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title> Directory Listing </title>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<h1> Directory Listing </h1>" << endl;
    out << "<table border='1'>" << endl;
    out << "<tr>" << endl;
    out << "<th> File Name </th>" << endl;
    out << "<th> File Path </th>" << endl;
    out << "</tr>" << endl;
    list_files(dir, out);

    out << "</table>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;
    out.close();
    cout << "Directory listing saved to " << output_file << endl;

    return 0;
}
