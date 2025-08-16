#pragma once
#include <vector>
#include <string>
#include "types.hpp" // Include Trade

class MLAnalytics {
public:
    void classify_strategy(const std::vector<Trade>& trades);
    void detect_regime(const std::vector<Trade>& trades);
};