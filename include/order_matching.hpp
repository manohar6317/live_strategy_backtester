#pragma once
#include <string>
#include "data_manager.hpp"
#include "types.hpp" // Include Order and MarketData

class OrderMatchingEngine {
public:
    void match_order(const Order& order, const MarketData& market_data);
    void apply_slippage_and_latency(Order& order) const;
};