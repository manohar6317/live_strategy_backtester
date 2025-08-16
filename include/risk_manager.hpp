#pragma once
#include <vector>
#include <mutex>
#include <string>
#include "types.hpp" // Include Trade

class RiskManager {
public:
    void monitor_realtime_risk(const std::vector<Trade>& trades);
    void calculate_var(const std::vector<Trade>& trades);
    void enforce_risk_limits(const std::vector<Trade>& trades);

private:
    std::mutex risk_mutex_;
};