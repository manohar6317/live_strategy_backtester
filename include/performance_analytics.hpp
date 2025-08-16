#pragma once
#include <map>
#include <string>
#include <vector>
#include "types.hpp" // Include Trade

class PerformanceAnalytics {
public:
    void calculate_metrics(const std::vector<Trade>& trades);
    void compare_live_vs_backtest(const std::vector<Trade>& live_trades, const std::vector<Trade>& backtest_trades);
    std::map<std::string, double> get_metrics() const;

private:
    std::map<std::string, double> metrics_;
};