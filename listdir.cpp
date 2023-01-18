#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

// Funcion para listar los archivos en un directorio de forma recursiva
void list_files(string dir, string tab, ofstream &out) {
    // Estructura para acceder al contenido de un directorio
    struct dirent *entry;
    // Puntero para abrir un directorio
    DIR *dp;

    // Abre el directorio especificado
    dp = opendir(dir.c_str());
    // Si no se puede abrir, muestra un error
    if (dp == NULL) {
        out << "Error opening " << dir << endl;
        return;
    }

    // Lee el contenido del directorio
    while ((entry = readdir(dp)) != NULL) {
        // Si es un directorio
        if (entry->d_type == DT_DIR) {
            // Si no es el directorio actual o el directorio padre
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                // Imprime el nombre del directorio y llama recursivamente a la funcion
                out << tab << entry->d_name << "/" << endl;
                list_files(dir + "/" + entry->d_name, tab + "  ", out);
            }
        }
        // Si es un archivo
        else {
            // Imprime el nombre del archivo
            out << tab << entry->d_name << endl;
        }
    }
    // Cierra el directorio
    closedir(dp);
}

int main() {
    // Directorio por defecto es el directorio actual
    string dir;
    // Nombre del archivo de salida
    string output_file;

    cout << "Enter the directory to list files:"<<endl;
    cin >> dir;
    DIR* checkdir = opendir(dir.c_str());
    if (!checkdir) {
      cout << "Invalid directory"<<endl;
      return -1;
    }
    closedir(checkdir);

    cout << "Enter the output file name (with .html extention):";
    cin >> output_file;

    // Flujo de salida para escribir en un archivo
ofstream out;
// Abre el archivo especificado
out.open(output_file);
if(!out) {
    cout << "Error opening " << output_file;
    return -1;
}

// Escribe la estructura básica de un documento html en el archivo de salida
out << "<html>" << endl;
out << "<head>" << endl;
out << "<title> Directory Listing </title>" << endl;
out << "</head>" << endl;
out << "<body>" << endl;
out << "<h1> Directory Listing </h1>" << endl;
out << "<table>" << endl;
out << "<tr>" << endl;
out << "<th> File Name </th>" << endl;
out << "<th> File Path </th>" << endl;
out << "</tr>" << endl;

// Llama a la funcion para listar los archivos y escribir los resultados en el archivo de salida
list_files(dir, "", out);

// Cierra la estructura de la tabla y del documento html
out << "</table>" << endl;
out << "</body>" << endl;
out << "</html>" << endl;
// Cierra el archivo de salida
out.close();
cout << "Directory listing saved to " << output_file << endl;
return 0;
}