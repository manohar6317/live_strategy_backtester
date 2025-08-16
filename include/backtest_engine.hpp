#pragma once
#include <string>
#include <vector>
#include "data_manager.hpp"
#include "strategy_framework.hpp"
#include "types.hpp" // Include Trade

class BacktestEngine {
public:
    BacktestEngine(DataManager& data_manager, Strategy& strategy);
    void run_backtest(const std::string& asset);
    std::vector<Trade> get_trades() const; // Add get_trades

private:
    DataManager& data_manager_;
    Strategy& strategy_;
    std::vector<Trade> trades_;
};