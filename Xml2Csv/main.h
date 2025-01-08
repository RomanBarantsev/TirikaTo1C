#pragma once
#include "warhouse.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <optional>

std::optional<std::pair<size_t, std::string>> extractShopDetails(const std::string& settingsValue) {
    size_t commaPos = settingsValue.find(',');
    if (commaPos != std::string::npos) {
        // Extract the shop number (substring before the comma)
        std::string shopNumber = settingsValue.substr(0, commaPos);

        // Extract the shop name (substring after the comma)
        std::string shopName = settingsValue.substr(commaPos + 1);
        return std::make_pair(std::stoi(shopNumber), shopName);
    }
    else 
        return std::nullopt;
}

int main() {
   
    std::ofstream csv_file("output.csv");
    

    ////find all shops
    //std::map<size_t, warehouse> warehouses;
    //for (pugi::xml_node record = docIn.child("data").child("tables").child("settings").child("record"); record; record = record.next_sibling("record")) {
    //    auto firstAttribute = record.first_attribute();
    //    auto secondAttribute = record.first_attribute().next_attribute();
    //    std::string firstValue = firstAttribute.value();
    //    std::string secondValue = secondAttribute.value();
    //    if (firstValue.find("SHOP")!=-1) {
    //        if (extractShopDetails(secondValue)!=std::nullopt)
    //        {
    //            auto res = extractShopDetails(secondValue);
    //            warehouse wH(res.value().second, goodsAttributes);
    //            warehouses.emplace(res.value().first, wH);
    //        }
    //        std::cout << std::endl;
    //    }
    //}

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

