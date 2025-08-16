#pragma once
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <filesystem>
#include <fstream>
#include "types.hpp" // Include Trade, Order, MarketData, and AlternativeData

class DataManager {
public:
    DataManager();
    void ingest_historical_data(const std::string& source, const std::string& asset);
    void ingest_alternative_data(const std::string& source);
    void process_realtime_data(const MarketData& data);
    void connect_websocket(const std::string& endpoint); // Placeholder
    void normalize_data();
    void save_data(const std::string& asset);
    void load_data(const std::string& asset);
    std::vector<MarketData> get_historical_data(const std::string& asset) const;
    std::vector<AlternativeData> get_alternative_data(const std::string& source) const;

private:
    mutable std::mutex data_mutex_;
    std::map<std::string, std::vector<MarketData>> historical_data_;
    std::map<std::string, std::vector<AlternativeData>> alternative_data_;
};