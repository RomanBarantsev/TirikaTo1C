#pragma once
#include <string>
#include <vector>

class warehouse {
private:
    using good = std::vector<std::string>;
    std::string m_name;
    std::vector<std::string> m_goodsAttributes;
    std::vector<good> m_goods;
public:
    warehouse(std::string name, std::vector<std::string> goodsAttributes) :
        m_name(name),
        m_goodsAttributes(goodsAttributes) {
    };
    ~warehouse() {};
    warehouse(warehouse& other) {};
    void addGood(good goods) {
        m_goods.push_back(goods);
    }
    std::vector<good> getGood() {
        return m_goods;
    }
};
