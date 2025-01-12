#pragma once
#include "src/pugixml.hpp"
#include "warehouse.h"
#include "datatypes.h"
#include <iostream>
#include <vector>
#include <map>
#include <optional>

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

     
     std::map<size_t,tables::good> extractGoods() {
        int counter = 0;
        std::map<size_t, tables::good> data;
        for (pugi::xml_node record = docIn.child("data").child("tables").child("goods").child("record"); record; record = record.next_sibling("record")) {
            std::vector<std::string> values;
            size_t key;
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

