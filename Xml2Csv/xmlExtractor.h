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
        pugi::xml_parse_result result = docIn.load_file("h:\database-export.xml");
        if (!result) {
            std::cerr << "Error parsing XML: " << result.description() << std::endl;            
        } 
    };
    ~xmlExtractor() {};
    std::vector<std::string> extractGoodAttributes() {
        std::vector<std::string> goodsAttributes;
        pugi::xml_node goods = docIn.child("data").child("tables").child("goods"); //root node
        if (goods) {
            auto firstGood = *goods.children("record").begin(); // extrude from first good all attributes
            for (pugi::xml_attribute attr : firstGood.attributes()) {
                goodsAttributes.push_back(attr.name());
            }
        }
        else {
            std::cerr << "No 'goods' node found!" << std::endl;
        }
        return goodsAttributes;
    };

    std::vector<std::string> extractRemaindersAttributes(){
        std::vector<std::string> remaindersAttributes;
        pugi::xml_node remainders = docIn.child("data").child("tables").child("remainders"); //root node
        if (remainders) {
            auto firstRemainders = *remainders.children("record").begin(); // extrude from first good all attributes
            for (pugi::xml_attribute attr : firstRemainders.attributes()) {
                remaindersAttributes.push_back(attr.name());
            }
        }
        else {
            std::cerr << "No 'remainders' node found!" << std::endl;
        }
        return remaindersAttributes;
    };

    void findWarhouses() {        
        std::map<size_t, std::string> warehouses;
        for (pugi::xml_node record = docIn.child("data").child("tables").child("settings").child("record"); record; record = record.next_sibling("record")) {
            auto firstAttribute = record.first_attribute();
            auto secondAttribute = record.first_attribute().next_attribute();
            std::string firstValue = firstAttribute.value();
            std::string secondValue = secondAttribute.value();
            if (firstValue.find("SHOP")!=-1) {
                if (extractShopDetails(secondValue)!=std::nullopt)
                {
                    auto res = extractShopDetails(secondValue);
                    warehouses.emplace(res.value().first, res.value().second);
                }
                std::cout << std::endl;
            }
        }
    }
};

