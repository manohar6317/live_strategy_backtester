#include "live_engine.hpp"
#include <iostream>

LiveEngine::LiveEngine(DataManager& data_manager, Strategy& strategy)
    : data_manager_(data_manager), strategy_(strategy), pnl_(0.0) {}

void LiveEngine::run_live(const std::string& asset) {
    MarketData data;
    data.asset = asset;
    data.bid = 50000.0; // Simulated real-time data
    data.ask = 50010.0;
    data.volume = 1000.0;
    data.timestamp = "2025-07-13 13:00:00";
    data_manager_.process_realtime_data(data);
    Order order = strategy_.execute(data);
    Trade trade;
    trade.asset = order.asset;
    trade.price = order.price;
    trade.volume = order.volume;
    trade.type = order.type;
    trade.timestamp = order.timestamp;
    trades_.push_back(trade);
    pnl_ = trade.price * trade.volume;
    std::cout << "Shadow trade executed: " << trade.asset << " at " << trade.price << "\n";
    std::cout << "Live P&L: " << pnl_ << "\n";
}

std::vector<Trade> LiveEngine::get_trades() const {
    return trades_;
}

double LiveEngine::get_pnl() const {
    return pnl_;
}