#pragma once
#include <string>
#include "data_manager.hpp"
#include "types.hpp" // Include Order and MarketData

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual Order execute(const MarketData& data) = 0;
};

class MovingAverage : public Strategy {
public:
    MovingAverage(int short_window, int long_window);
    Order execute(const MarketData& data) override;

private:
    int short_window_;
    int long_window_;
    std::vector<double> prices_;
};