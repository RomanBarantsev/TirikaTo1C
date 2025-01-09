#pragma once
#include "warhouse.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <optional>
#include "xmlExtractor.h"


int main() {
    xmlExtractor xml("C:/database-export.xml");
    using Attrib = std::vector<std::string>;
    Attrib goods = xml.extractAttributes("goods");
    Attrib remains = xml.extractAttributes("remainders");
    auto data = xml.extractGoods(goods);
    /*for (auto& i : dataVector)
    {
        auto stringVec = i.second;
        for (auto it = stringVec.begin();it!= stringVec.end();it++)
        {
            if (it != stringVec.begin()) {
                csv_file << ",";
            }
            csv_file << *it;
        }
        csv_file << "\n";
    }
    std::cout << "обработано:" << counter << " позиций";
    csv_file.close();
    std::cout << "CSV файл успешно создан." << std::endl;*/
 }

