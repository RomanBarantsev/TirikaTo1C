#pragma once
#include <vector>
#include <string>
#include <unordered_map>
namespace tables {

	struct good {
		size_t id;
		bool group_id;
		bool is_deleted;
		bool is_replicated;
		std::string product_code;
		bool is_sized;
		std::string manufacturer;
		bool is_discounted;
		bool is_set;
		std::string name;
		double price;
		double price1;
		double price2;
		double price3;
		double buy_price;
		double seller_bonus;
		double vat;
		size_t decimal_places;
		size_t good_type;
		size_t alco_type;
		double alco_amount;
		size_t currency_id;
		size_t currency_id1;
		size_t currency_id2;
		size_t currency_id3;
		size_t buy_currency_id;
		unsigned int price_change_date;
		bool is_alco_marked;
		bool is_tap_trade;
		double alco_strength;
		double alco_strength;
		bool is_serial_required;
		size_t tax_mode;
		double tax_percent;
		double price_advance;
		double price_advance1;
		double price_advance2;
		double price_advance3;
		size_t register_type;
		bool photo;
	};

	struct remainders {

		size_t shop_id;
		size_t good_id;
		bool is_deleted;
		bool is_replicated;
		double remainder;
		double min_amount;
		double reserved;
		double expected;
	};
}

namespace attributes {
	std::vector<std::string>{

	}
}