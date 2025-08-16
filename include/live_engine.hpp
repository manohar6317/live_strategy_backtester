#pragma once
#include <string>
#include <vector>
#include "data_manager.hpp"
#include "strategy_framework.hpp"
#include "types.hpp" // Include Trade

class LiveEngine {
public:
    LiveEngine(DataManager& data_manager, Strategy& strategy);
    void run_live(const std::string& asset);
    std::vector<Trade> get_trades() const; // Add get_trades
    double get_pnl() const; // Add get_pnl

private:
    DataManager& data_manager_;
    Strategy& strategy_;
    std::vector<Trade> trades_;
    double pnl_;
};