#pragma once
#include "datatypes.h"
//class for non-unique data, which is exist for every warhouse.

class database
{
private:
	dataTypes::attributes m_goodsAttributes, m_remaindersAttributes;
	dataTypes::data m_goodsData;
public:
	database() = delete;
	database(dataTypes::attributes goodsAttributes, dataTypes::attributes remaindersAttributes, dataTypes::data goodsData) :
		m_goodsAttributes(goodsAttributes),
		m_remaindersAttributes(remaindersAttributes),
		m_goodsData(goodsData){

	};
	~database() {};
	database(database& other) {};
	dataTypes::attributes getGoodsAttrib() {
		return m_goodsAttributes;
	}
	dataTypes::attributes getRemaindersAttrib() {
		return m_remaindersAttributes;
	}
	dataTypes::data getGoodsData() {
		return m_goodsData;
	}
};

