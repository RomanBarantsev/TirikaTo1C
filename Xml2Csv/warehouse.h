#pragma once
#include <string>
#include <vector>
#include "datatypes.h"

class warehouse {
private:
    std::string m_name;
    dataTypes::attributes m_goodsAttributes,m_remainsAttribute;
    dataTypes::data m_remains;
    std::shared_ptr<dataTypes::data> m_goods;
public:
    warehouse(std::string name, dataTypes::attributes goodsAttributes, dataTypes::attributes remainsAttribute) :
        m_name(name),
        m_goodsAttributes(goodsAttributes)
    {

    };
    ~warehouse() {};
    warehouse(warehouse& other) {};
};
