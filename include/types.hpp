#pragma once
#include <string>

struct Order {
    std::string asset;
    double price;
    double volume;
    std::string type; // "BUY" or "SELL"
    std::string timestamp;
};

struct Trade {
    std::string asset;
    double price;
    double volume;
    std::string type; // "BUY" or "SELL"
    std::string timestamp;
};

struct MarketData {
    std::string timestamp;
    std::string asset;
    double bid;
    double ask;
    double volume;
};

struct AlternativeData {
    std::string timestamp;
    std::string source;
    std::string sentiment;
    std::string event;
};