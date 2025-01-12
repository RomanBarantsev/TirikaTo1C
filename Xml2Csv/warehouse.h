#pragma once
#include <string>
#include <vector>
#include "datatypes.h"

class warehouse {
private:
    std::string m_name;
    dataTypes::data m_remains;
public:
    warehouse(std::string name) :
        m_name(name)
    {

    };
    ~warehouse() {};
    warehouse(warehouse& other) 
    {
        m_name=other.m_name;
        m_remains = other.m_remains;
    };
    std::string getName() {
        return m_name;
    }
    
    dataTypes::data getRemains() {
        return m_remains;
    }

    void addRemains(size_t key,dataTypes::attributes data) {
        m_remains.emplace(key,data);
    }
};
