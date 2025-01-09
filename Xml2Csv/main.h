#pragma once
#include "warhouse.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <optional>


int main() {
   
    std::ofstream csv_file("output.csv");
    

    

    /*int counter = 0;
    for (pugi::xml_node record = docIn.child("data").child("tables").child("goods").child("record"); record; record = record.next_sibling("record")) {        
        std::vector<std::string> values;
        for (auto& i : goodsAttributes)
        {
            values.push_back(record.attribute(i.c_str()).value());
        }
        dataVector[record.attribute("id").as_uint()]=values;
        counter++;        
    }    */

    ////csv file goodAttributes to header 
    //for (auto it = goodsAttributes.begin(); it!= goodsAttributes.end();it++)
    //{
    //    if (it != goodsAttributes.begin()) {
    //        csv_file << ",";
    //    }
    //    csv_file << *it;
    //}
    //csv_file << "\n";


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

