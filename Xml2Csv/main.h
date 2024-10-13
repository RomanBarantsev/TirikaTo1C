#pragma once
#include "src/pugixml.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <QFileInfo>

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

void convertXmlToCsv(const std::string& inputFile, const std::string& outputFile = "") {
    // Load XML file
    pugi::xml_document docIn;
    pugi::xml_parse_result result = docIn.load_file(inputFile.c_str());
    if (!result) {
        std::cerr << "Error parsing XML: " << result.description() << std::endl;
        return;
    }

    // Extract the directory from the input file path
    QFileInfo fileInfo(QString::fromStdString(inputFile));
    QString outputFilePath;

    // If output file is not provided, save CSV with the same name as the XML file but with a .csv extension
    if (outputFile.empty()) {
        outputFilePath = fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + ".csv";
    } else {
        outputFilePath = QString::fromStdString(outputFile);
    }

    std::ofstream csv_file(outputFilePath.toStdString());
    std::unordered_map<long long, std::vector<std::string>> dataVector;

    // Extract attributes from <goods>
    for (pugi::xml_node record = docIn.child("data").child("tables").child("goods").child("record"); record; record = record.next_sibling("record")) {
        std::vector<std::string> values;
        for (const auto& row : rows) {
            values.push_back(record.attribute(row.c_str()).value());
        }
        dataVector[record.attribute("id").as_uint()] = values;
    }

    // Write CSV headers
    for (const auto& row : rows) {
        csv_file << row << ",";
    }
    csv_file.seekp(-1, std::ios_base::end); // Remove last comma
    csv_file << "\n";

    // Write CSV data
    for (const auto& [key, stringVec] : dataVector) {
        for (const auto& value : stringVec) {
            csv_file << value << ",";
        }
        csv_file.seekp(-1, std::ios_base::end); // Remove last comma
        csv_file << "\n";
    }

    csv_file.close();
    std::cout << "CSV file saved at: " << outputFilePath.toStdString() << std::endl;
}