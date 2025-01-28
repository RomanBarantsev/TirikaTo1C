#pragma once
#include "src/pugixml.hpp"
#include "warehouse.h"
#include "datatypes.h"
#include <iostream>
#include <vector>
#include <map>
#include <optional>

//this class purpose to extract all data from xml file, which can be unloaded from Tirika shop through vygruzka-dannyh.bat file

class xmlExtractor
{
private:
    pugi::xml_document docIn;

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

public:
    xmlExtractor(std::string path) {
        pugi::xml_parse_result result = docIn.load_file(path.c_str());
        if (!result) {
            std::cerr << "Error parsing XML: " << result.description() << std::endl;
        } 
    };

    ~xmlExtractor() {};

    std::map<const size_t, std::string> findWarhouses() {
        std::map<const size_t, std::string> warehouses;
        for (pugi::xml_node record = docIn.child("data").child("tables").child("settings").child("record"); record; record = record.next_sibling("record")) {
            auto firstAttribute = record.first_attribute();
            auto secondAttribute = record.first_attribute().next_attribute();
            std::string firstValue = firstAttribute.value();
            std::string secondValue = secondAttribute.value();
            if (firstValue.find("SHOP") != -1) {
                if (extractShopDetails(secondValue) != std::nullopt)
                {
                    auto res = extractShopDetails(secondValue);
                    warehouses.emplace(res.value().first, res.value().second);
                }
                std::cout << std::endl;
            }
        }
        return warehouses;
    }

    dataTypes::attributes extractAttributes(std::string table){
        dataTypes::attributes Attributes;
        pugi::xml_node remainders = docIn.child("data").child("tables").child(table.c_str()); //root node
        if (remainders) {
            auto firstRemainders = *remainders.children("record").begin(); // extrude from first good all attributes
            for (pugi::xml_attribute attr : firstRemainders.attributes()) {
                Attributes.push_back(attr.name());
            }
        }
        else {
            std::cerr << "No " << table << " node found!" << std::endl;
        }
        return Attributes;
    };
    
    dataTypes::data extractData(const std::vector<std::string>& attributes, std::string table,std::string keyAttribute) {
        int counter = 0;
        dataTypes::data data;
        for (pugi::xml_node record = docIn.child("data").child("tables").child(table.c_str()).child("record"); record; record = record.next_sibling("record")) {
            std::vector<std::string> values;
            size_t key=0;
            for (auto& i : attributes)
            {
                if (i == keyAttribute) {
                    key = std::stoi(record.attribute(i.c_str()).value());
                }
                values.push_back(record.attribute(i.c_str()).value());
            }
            data.emplace(key,values);
            counter++;
        }    
        return data;
    }


};

