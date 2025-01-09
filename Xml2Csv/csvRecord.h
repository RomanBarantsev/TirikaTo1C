#pragma once
#include <fstream>
#include <vector>
#include <iostream>

class csvRecord
{
private:
	std::string m_path;
	std::ofstream csv_file;
public:
	csvRecord(std::string path) : m_path(path) 
    {
        csv_file.open(m_path);
        if (!csv_file.is_open()) {
            std::cerr << "Failed to open the file: " << m_path << std::endl;            
        }
    };
	~csvRecord() 
    {
        csv_file.close();
    };
	void addingLine(std::vector<std::string> line) {
    for (auto it = line.begin(); it!= line.end();it++)
    {
        
        if (it != line.begin()) {
            csv_file << ",";
        }
        csv_file << *it;
    }
    csv_file << "\n";
	}
};

