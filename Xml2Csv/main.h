#pragma once
#include "warehouse.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <optional>
#include "xmlExtractor.h"
#include "datatypes.h"
#include "database.h"
#include "csvRecord.h"


int main() {
    //init database
    xmlExtractor xml("C:/database-export.xml");
    auto warehousesList = xml.findWarhouses();
    dataTypes::attributes goodsAttributes = xml.extractAttributes("goods");
    dataTypes::attributes remaindersAttributes = xml.extractAttributes("remainders");
    dataTypes::data remaindersData = xml.extractData(remaindersAttributes,"remainders","shop_id");
    dataTypes::data goodsData = xml.extractData(goodsAttributes,"goods","id");
    database DB(goodsAttributes, remaindersAttributes, goodsData);

    //make warehouses map 
    std::map<size_t,warehouse> warehouses;
    for (const auto& wh : warehousesList)
    {   
        warehouse warh(wh.second);
        warehouses.emplace(wh.first,warh);        
    }

    //put remainders in warhouses
    for (const auto& remain : remaindersData)
    {
        size_t shopNumber = remain.first;
        auto& wh = warehouses.at(shopNumber);
        wh.addRemains(remain.first,remain.second);
    }

    //adding header to csv
    csvRecord csvRec("D:/");
    dataTypes::attributes newLine;
    for (auto& rmAtr : remaindersAttributes)
    {
        if (rmAtr == "good_id")
        {
            for (auto& goodAtr : goodsAttributes)
            {
                newLine.push_back(goodAtr);
            }
        }
        else
        {
            newLine.push_back(rmAtr);
        }
    }
    csvRec.addingLine(newLine);
 }

