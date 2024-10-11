#pragma once
#include "src/pugixml.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>

std::vector<std::string> rows{
    "id",
    "group_id",
    "is_deleted",
    "is_deleted",
    "barcode",
    "is_replicated",
    "product_code",
    "is_sized",
    "manufacturer",
    "is_discounted",
    "is_set",
    "name",
    "price",
    "price1",
    "price2",
    "price3",
    "buy_price",
    "seller_bonus",
    "vat",
    "decimal_places",
    "good_type",
    "alco_type",
    "currency_id",
    "currency_id",
    "currency_id",
    "currency_id",
    "currency_id1",
    "currency_id2",
    "currency_id3",
    "buy_currency_id",
    "price_change_date",
    "is_tap_trade",
    "alco_strength",
    "is_serial_required",
    "tax_mode",
    "tax_percent",
    "price_advance",
    "price_advance1",
    "price_advance2",
    "price_advance3",
    "register_type"
};

int main() {
    pugi::xml_document docIn;
    pugi::xml_parse_result result = docIn.load_file("database.xml");
    if (!result) {
        std::cerr << "Error parsing XML: " << result.description() << std::endl;
        return 1;
    }
    std::ofstream csv_file("output.csv");
    std::unordered_map<long long,std::vector<std::string>> dataVector;
    int counter=0;
    // Extract attributes from <goods>
    for (pugi::xml_node record = docIn.child("data").child("tables").child("goods").child("record"); record; record = record.next_sibling("record")) {
        
        std::vector<std::string> values;
        for (auto& i : rows)
        {
            values.push_back(record.attribute(i.c_str()).value());
        }
        dataVector[record.attribute("id").as_uint()]=values;
        counter++;        
    }
    // Extract attributes from <>
    /*for (pugi::xml_node record = docIn.child("data").child("tables").child("goods").child("record"); record; record = record.next_sibling("record"))
    {
        if (record.attribute("id").value());
    }*/
    //csv file 
    for (auto it = rows.begin(); it!=rows.end();it++)
    {
        if (it != rows.begin()) {
            csv_file << ",";
        }
        csv_file << *it;
    }
    csv_file << "\n";
    for (auto& i : dataVector)
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
    std::cout << "CSV файл успешно создан." << std::endl;
 }

