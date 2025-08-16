// backtest_engine.cpp: Implementation of BacktestEngine class for simulating trading
// Purpose: Executes the trading strategy on historical data to generate trades,
// supporting backtesting for the BTC/USDT trading system assignment

#include "backtest_engine.hpp"  // Header file defining BacktestEngine class and dependencies
#include <iostream>             // For console output (logging trades and errors)

// Constructor: Initializes BacktestEngine with references to DataManager and Strategy
// data_manager: Provides access to historical market data
// strategy: Trading strategy (e.g., MovingAverage) to generate orders
// Why: Sets up dependencies for backtesting BTC/USDT trades
BacktestEngine::BacktestEngine(DataManager& data_manager, Strategy& strategy)
    : data_manager_(data_manager), strategy_(strategy) {}

// Run backtest on historical data for a specified asset
// asset: Asset pair (e.g., BTC/USD)
// Why: Simulates trading using the MovingAverage strategy to evaluate performance
void BacktestEngine::run_backtest(const std::string& asset) {
    // Retrieve historical data for the asset from DataManager
    auto historical_data = data_manager_.get_historical_data(asset);
    
    // Check if data is available; exit if empty to avoid invalid backtesting
    if (historical_data.empty()) {
        std::cerr << "No historical data available for backtest of " << asset << "\n";
        return;
    }
    
    // Iterate through each historical data point
    for (const auto& data : historical_data) {
        // Execute the strategy (e.g., MovingAverage) to generate an order
        // Why: Converts market data into BUY/SELL/HOLD orders
        Order order = strategy_.execute(data);
        
        // Create a trade from the order (ignores HOLD orders implicitly)
        Trade trade;
        trade.asset = order.asset;       // Set trade asset (e.g., BTC/USD)
        trade.price = order.price;       // Set execution price (bid for SELL, ask for BUY)
        trade.volume = order.volume;     // Set trade volume
        trade.type = order.type;         // Set trade type (BUY/SELL)
        trade.timestamp = order.timestamp; // Set trade timestamp
        
        // Store the trade in the trades_ vector
        trades_.push_back(trade);
        
        // Log trade execution for debugging and user feedback
        std::cout << "Executed trade: " << trade.asset << " at " << trade.price << "\n";
    }
    
    // Log completion of backtest for the MovingAverage strategy
    std::cout << "Backtest completed for strategy: MovingAverage\n";
}

// Retrieve the list of trades generated during backtesting
// Returns: Vector of Trade structs
// Why: Provides trade data for performance analysis (e.g., Sharpe, Sortino)
std::vector<Trade> BacktestEngine::get_trades() const {
    return trades_; // Return the stored trades
}