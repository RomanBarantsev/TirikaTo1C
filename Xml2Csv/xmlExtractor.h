#pragma once
#include "src/pugixml.hpp"
#include "warhouse.h"
#include <iostream>
#include <vector>
#include <map>
#include <optional>

class xmlExtractor
{
private:
    pugi::xml_document docIn;
    using dataType = std::vector<std::vector<std::string>>;

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

    std::map<size_t, std::string> findWarhouses() {
        std::map<size_t, std::string> warehouses;
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

    std::vector<std::string> extractAttributes(std::string table){
        std::vector<std::string> Attributes;
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
    
    dataType extractGoods(const std::vector<std::string>& goodAtr){
        int counter = 0;
        dataType data;
        for (pugi::xml_node record = docIn.child("data").child("tables").child("goods").child("record"); record; record = record.next_sibling("record")) {
            std::vector<std::string> values;
            for (auto& i : goodAtr)
            {
                values.push_back(record.attribute(i.c_str()).value());
            }
            data[record.attribute("id").as_uint()]=values;
            counter++;
        }    
        return data;
    }


};

