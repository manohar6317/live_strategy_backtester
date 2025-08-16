// strategy_framework.cpp: Implementation of the MovingAverage strategy class
// Purpose: Defines the MovingAverage strategy for generating BUY/SELL/HOLD orders
// based on market data, used in the BTC/USDT trading system for backtesting and live trading

#include "strategy_framework.hpp"  // Header file defining Strategy and MovingAverage classes
#include <iostream>                // For console output (logging, not used in this file)

// Constructor: Initializes MovingAverage strategy with short and long window periods
// short_window: Number of periods for short moving average (e.g., 10)
// long_window: Number of periods for long moving average (e.g., 20)
// Why: Sets up parameters for calculating moving averages to detect price trends
MovingAverage::MovingAverage(int short_window, int long_window)
    : short_window_(short_window), long_window_(long_window) {}

// Execute the MovingAverage strategy on market data to generate a trade order
// data: MarketData struct containing timestamp, asset, bid, ask, volume
// Returns: Order struct with asset, price, volume, type (BUY/SELL/HOLD), timestamp
// Why: Generates trading signals for BTC/USDT based on moving average crossovers
// Note: Current implementation is a placeholder, always returning BUY; needs crossover logic
Order MovingAverage::execute(const MarketData& data) {
    // Calculate mid-price (average of bid and ask) and store in prices_ vector
    // Why: Mid-price used for moving average calculation (currently not utilized)
    prices_.push_back((data.bid + data.ask) / 2.0);
    
    // Initialize order with default values
    Order order;
    order.asset = data.asset;       // Set order asset to match input (e.g., BTC/USD)
    order.price = data.ask;        // Set price to ask for BUY orders
    order.volume = 1.0;            // Set fixed volume (1 unit for simplicity)
    order.type = "BUY";            // Set order type to BUY (placeholder logic)
    order.timestamp = data.timestamp; // Set order timestamp to match data
    
    // Note: Missing moving average crossover logic; should compare short and long MAs
    // Bug: Always returns BUY order, needs fix to implement MA crossover for BUY/SELL/HOLD
    return order;
}