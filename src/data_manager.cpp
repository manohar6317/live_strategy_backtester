// data_manager.cpp: Implementation of DataManager class for handling market and alternative data
// Purpose: Manages data ingestion, storage, and retrieval for the BTC/USDT trading system,
// supporting historical data (file or Binance API), alternative data (e.g., news sentiment),
// and real-time data processing

#include "data_manager.hpp"        // Header file defining DataManager class and data structures
#include <iostream>                // For console output (logging and errors)
#include <fstream>                 // For file input/output operations
#include <sstream>                 // For parsing CSV data lines
#include <filesystem>              // For directory and file path management
#include <algorithm>               // For string manipulation (e.g., std::replace)

// Constructor: Initializes DataManager and sets up storage directory
DataManager::DataManager() {
    // Log initialization for debugging and user feedback
    std::cout << "Initializing data manager...\n";
    // Create data/historical_data directory if it doesn't exist
    // Why: Ensures storage path exists for saving historical data files
    std::filesystem::create_directories("data/historical_data");
}

// Ingest historical data from a file for a specified asset (e.g., BTC/USD)
// source: File path (e.g., data/historical_data/btc_usd.dat)
// asset: Asset pair (e.g., BTC/USD)
// Why: Loads historical market data for backtesting the MovingAverage strategy
void DataManager::ingest_historical_data(const std::string& source, const std::string& asset) {
    // Lock mutex to ensure thread-safe data access
    std::lock_guard<std::mutex> lock(data_mutex_);
    
    // Replace '/' with '_' in asset string to create valid file names
    // Why: Prevents invalid file paths (e.g., BTC_USD instead of BTC/USD)
    std::string sanitized_asset = asset;
    std::replace(sanitized_asset.begin(), sanitized_asset.end(), '/', '_');
    
    // Construct file path for historical data (e.g., data/historical_data/BTC_USD.dat)
    std::filesystem::path file_path = std::filesystem::path("data/historical_data") / (sanitized_asset + ".dat");
    
    // Open input file for reading
    std::ifstream file(file_path);
    if (!file.is_open()) {
        // Log error if file cannot be opened
        std::cerr << "Failed to open data file for " << asset << " at " << file_path << "\n";
        return;
    }
    
    // Skip header line in CSV file (e.g., timestamp,asset,bid,ask,volume)
    std::string line;
    std::getline(file, line);
    
    // Read and parse each line of the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line); // Use stringstream to parse comma-separated values
        MarketData data;           // Structure to store market data (timestamp, asset, bid, ask, volume)
        std::string temp;          // Temporary string for parsing numbers
        
        // Extract fields from CSV line
        std::getline(ss, data.timestamp, ',');
        std::getline(ss, data.asset, ',');
        std::getline(ss, temp, ',');
        try {
            // Convert bid price from string to double
            data.bid = std::stod(temp);
            std::getline(ss, temp, ',');
            // Convert ask price from string to double
            data.ask = std::stod(temp);
            std::getline(ss, temp);
            // Convert volume from string to double
            data.volume = std::stod(temp);
            
            // Store parsed data in historical_data_ map
            historical_data_[asset].push_back(data);
            
            // Log successful ingestion for debugging
            std::cout << "Ingested historical data for " << asset << " at " << data.timestamp << "\n";
        } catch (const std::exception& e) {
            // Handle parsing errors (e.g., invalid number format)
            // Why: Ensures robustness by skipping malformed lines
            std::cerr << "Error parsing line: " << line << " (" << e.what() << ")\n";
        }
    }
    file.close(); // Close file to free resources
}

// Ingest alternative data (e.g., news sentiment) from a specified source
// source: Data source identifier (e.g., "news")
// Why: Enhances trading decisions with external data (placeholder implementation)
void DataManager::ingest_alternative_data(const std::string& source) {
    // Lock mutex for thread-safe data access
    std::lock_guard<std::mutex> lock(data_mutex_);
    
    // Create sample alternative data (e.g., news sentiment)
    // Note: Placeholder; real implementation would fetch from external source
    AlternativeData data;
    data.timestamp = "2025-07-13 13:00:00"; // Sample timestamp
    data.source = source;                   // Source identifier (e.g., "news")
    data.sentiment = "positive";            // Sample sentiment
    data.event = "Market news update";      // Sample event description
    
    // Store alternative data in alternative_data_ map
    alternative_data_[source].push_back(data);
    
    // Log ingestion for debugging
    std::cout << "Ingested alternative data from " << source << ": " << data.sentiment << ", " << data.event << "\n";
}

// Process real-time market data and store it
// data: MarketData struct containing real-time data
// Why: Simulates real-time data ingestion for live trading
void DataManager::process_realtime_data(const MarketData& data) {
    // Lock mutex for thread-safe data access
    std::lock_guard<std::mutex> lock(data_mutex_);
    
    // Append real-time data to historical_data_ for consistency
    historical_data_[data.asset].push_back(data);
    
    // Log processing for debugging
    std::cout << "Processed real-time data for " << data.asset << "\n";
}

// Connect to a WebSocket endpoint for real-time data
// endpoint: WebSocket URL (e.g., wss://api.binance.com)
// Why: Placeholder for real-time data streaming (currently uses cpprestsdk for HTTP)
void DataManager::connect_websocket(const std::string& endpoint) {
    // Log placeholder message; WebSocket integration in progress due to websocketpp issues
    std::cout << "WebSocket connection placeholder for " << endpoint << "\n";
}

// Normalize stored data to ensure consistency
// Why: Placeholder for handling missing values or outliers (not fully implemented)
void DataManager::normalize_data() {
    // Log normalization step for debugging
    std::cout << "Normalizing data...\n";
}

// Save historical data to a file for persistence
// asset: Asset pair (e.g., BTC/USD)
// Why: Stores ingested data for reuse in backtesting or analysis
void DataManager::save_data(const std::string& asset) {
    // Lock mutex for thread-safe data access
    std::lock_guard<std::mutex> lock(data_mutex_);
    
    // Replace '/' with '_' in asset string for valid file names
    std::string sanitized_asset = asset;
    std::replace(sanitized_asset.begin(), sanitized_asset.end(), '/', '_');
    
    // Construct file path for saving data (e.g., data/historical_data/BTC_USD_saved.dat)
    std::filesystem::path file_path = std::filesystem::path("data/historical_data") / (sanitized_asset + "_saved.dat");
    
    // Open output file for writing
    std::ofstream file(file_path);
    if (!file.is_open()) {
        // Log error if file cannot be opened
        std::cerr << "Failed to save data for " << asset << " at " << file_path << "\n";
        return;
    }
    
    // Write CSV header
    file << "timestamp,asset,bid,ask,volume\n";
    
    // Write each MarketData entry to the file
    for (const auto& data : historical_data_[asset]) {
        file << data.timestamp << "," << data.asset << "," << data.bid << "," << data.ask << "," << data.volume << "\n";
    }
    
    file.close(); // Close file to free resources
    
    // Log successful save for debugging
    std::cout << "Saved data for " << asset << " to " << file_path << "\n";
}

// Load historical data for an asset by calling ingest_historical_data
// asset: Asset pair (e.g., BTC/USD)
// Why: Reuses ingestion logic for loading saved data
void DataManager::load_data(const std::string& asset) {
    // Delegate to ingest_historical_data with empty source (assumes default path)
    ingest_historical_data("", asset);
}

// Retrieve historical data for a specified asset
// asset: Asset pair (e.g., BTC/USD)
// Returns: Vector of MarketData entries
// Why: Provides data for backtesting or analysis
std::vector<MarketData> DataManager::get_historical_data(const std::string& asset) const {
    // Lock mutex for thread-safe data access
    std::lock_guard<std::mutex> lock(data_mutex_);
    
    try {
        // Return historical data for the asset
        return historical_data_.at(asset);
    } catch (const std::out_of_range&) {
        // Handle case where no data exists for the asset
        std::cerr << "No historical data found for " << asset << "\n";
        return {}; // Return empty vector
    }
}

// Retrieve alternative data for a specified source
// source: Data source (e.g., "news")
// Returns: Vector of AlternativeData entries
// Why: Provides external data for enhanced trading analysis
std::vector<AlternativeData> DataManager::get_alternative_data(const std::string& source) const {
    // Lock mutex for thread-safe data access
    std::lock_guard<std::mutex> lock(data_mutex_);
    
    try {
        // Return alternative data for the source
        return alternative_data_.at(source);
    } catch (const std::out_of_range&) {
        // Handle case where no data exists for the source
        std::cerr << "No alternative data found for " << source << "\n";
        return {}; // Return empty vector
    }
}