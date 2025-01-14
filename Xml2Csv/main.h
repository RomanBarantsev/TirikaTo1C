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


int main() {
    xmlExtractor xml("C:/database-export.xml");
    dataTypes::attributes goodsAttributes = xml.extractAttributes("goods");
    dataTypes::attributes remaindersAttributes = xml.extractAttributes("remainders");
    dataTypes::data remaindersData = xml.extractData(remaindersAttributes,"remainders");
    dataTypes::data goodsData = xml.extractData(remaindersAttributes,"remainders");

    database DB(goodsAttributes, remaindersAttributes, goodsData);
    auto warehousesList = xml.findWarhouses();
    std::map<size_t,warehouse> warehouses;
    for (const auto& wh : warehousesList)
    {   
        warehouse warh(wh.second);
        warehouses.emplace(wh.first,warh);
    }
    //put remainders in warhouses
    for (const auto& remain : remaindersData)
    {
        //size_t shopNumber = std::stoi(remain[0]);
        //auto& wh = warehouses.at(shopNumber);
        //wh.addRemains(remain);
    }

    //adding header to csv
    
 }

