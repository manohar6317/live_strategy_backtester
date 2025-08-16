#pragma once
#include <string>
#include "data_manager.hpp"
#include "types.hpp" // Include Order and MarketData

class MarketMicrostructure {
public:
    void simulate_order_book(const Order& order, const MarketData& market_data);
    void detect_regime(const std::string& asset);
};