Copy code
#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <string.h>
#include <unistd.h>
using namespace std;

void list_files(string dir, string tab, ofstream &out) {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(dir.c_str());
    if (dp == NULL) {
        out << "Error opening " << dir << endl;
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                list_files(dir + "/" + entry->d_name, tab + "  ", out);
            }
        }
        else {
            out << "<tr>" << endl;
            out << "<td>" << entry->d_name << "</td>" << endl;
            string path = dir;
            size_t found = path.find_last_of("/\\");
            out << "<td>" << path.substr(0,found) << "</td>" << endl;
            out << "</tr>" << endl;
        }
    }
    closedir(dp);
}

int main() {
    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);
    string dir(buffer);
    string output_file;

    cout << "Enter the output file name (with .html extention):";
    cin >> output_file;

    ofstream out;
    out.open(output_file);

    if(!out) {
        cout << "Error opening " << output_file;
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
    list_files(dir, "", out);

    out << "</table>" << endl;
    out << "...";
    out.close();
    return 0;
}
