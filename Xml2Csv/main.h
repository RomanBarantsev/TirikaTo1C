#pragma once
#include "warehouse.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <optional>
#include "xmlExtractor.h"
#include "datatypes.h"


int main() {
    xmlExtractor xml("C:/database-export.xml");
    dataTypes::attributes goodsAttributes = xml.extractAttributes("goods");
    dataTypes::attributes remainsAttributes = xml.extractAttributes("remainders");
    auto dataGoods = xml.extractData(goodsAttributes,"goods");
    auto dataGoods = xml.extractData(remainsAttributes,"remains");
    std::shared_ptr<dataTypes::data> shr_goodsAttr = make_shared<dataTypes::data>(dataGoods);
    auto warehousesList = xml.findWarhouses();
    std::map<size_t,warehouse> warehouses;
    for (const auto& wh : warehousesList)
    {        
        warehouse warh("1", shr_goodsAttr, remainsAttributes);
        warhouses.push_back()
    }
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

