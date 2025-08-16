// main.cpp: Entry point for the BTC/USDT trading system
// Purpose: Orchestrates data ingestion, strategy execution, backtesting, live trading, 
// performance analysis, and risk management for the trading system assignment

#include "data_manager.hpp"        // Manages market and alternative data ingestion
#include "backtest_engine.hpp"     // Handles backtesting of trading strategies
#include "live_engine.hpp"         // Simulates live shadow trading
#include "strategy_framework.hpp"  // Defines trading strategies (e.g., MovingAverage)
#include "performance_analytics.hpp" // Calculates performance metrics (Sharpe, Sortino)
#include "risk_manager.hpp"        // Monitors and manages trading risks
#include "order_matching.hpp"      // Matches orders with market data
#include "market_microstructure.hpp" // Simulates order book and market regimes
#include "analytics_ml.hpp"        // Applies machine learning for strategy analysis
#include <iostream>                // For console output
#include <thread>                  // For potential multithreading (not used currently)

// Entry point of the trading system
int main() {
    // Initialize DataManager to handle market and alternative data
    DataManager data_manager;
    
    // Initialize MovingAverage strategy with short=10, long=20 periods
    // Why: Generates BUY/SELL signals based on moving average crossovers for BTC/USDT
    MovingAverage strategy(10, 20);
    
    // Initialize BacktestEngine to simulate trading on historical data
    BacktestEngine backtest_engine(data_manager, strategy);
    
    // Initialize LiveEngine for real-time shadow trading simulation
    LiveEngine live_engine(data_manager, strategy);
    
    // Initialize PerformanceAnalytics to compute metrics (Sharpe, Sortino, MaxDD)
    PerformanceAnalytics performance_analytics;
    
    // Initialize RiskManager to monitor P&L, calculate VaR, and enforce limits
    RiskManager risk_manager;
    
    // Initialize OrderMatchingEngine to match orders and apply slippage/latency
    OrderMatchingEngine order_matching;
    
    // Initialize MarketMicrostructure to simulate order book and detect market regimes
    MarketMicrostructure market_microstructure;
    
    // Initialize MLAnalytics for strategy classification and regime detection
    MLAnalytics ml_analytics;

    // Ingest historical BTC/USDT data from file (BTC_USD.dat)
    // Why: Provides data for backtesting; file path is relative to project directory
    data_manager.ingest_historical_data("data/historical_data/btc_usd.dat", "BTC/USD");
    
    // Ingest alternative data (e.g., news sentiment) for enhanced analysis
    // Note: Currently placeholder; assumes "news" source
    data_manager.ingest_alternative_data("news");
    
    // Normalize ingested data to ensure consistency (e.g., handle missing values)
    data_manager.normalize_data();
    
    // Save ingested data to file for persistence and reuse
    data_manager.save_data("BTC/USD");

    // Run backtest on BTC/USDT data using MovingAverage strategy
    // Why: Simulates trading to generate historical trade performance
    backtest_engine.run_backtest("BTC/USD");
    
    // Connect to Binance WebSocket for real-time BTC/USDT data
    // Note: Uses placeholder URL; WebSocket integration in progress due to websocketpp issues
    data_manager.connect_websocket("wss://api.binance.com"); // here add websocket message handling
    
    // Simulate live shadow trading for BTC/USDT using MovingAverage strategy
    // Why: Tests strategy in real-time without risking capital
    live_engine.run_live("BTC/USD"); // Simulate live trading and new comment

    // Retrieve trades from backtesting for performance analysis
    auto backtest_trades = backtest_engine.get_trades();
    
    // Retrieve trades from live trading for comparison
    auto live_trades = live_engine.get_trades();
    
    // Calculate performance metrics (Sharpe, Sortino, MaxDD) for backtest trades
    performance_analytics.calculate_metrics(backtest_trades);
    
    // Compare live and backtest trade performance to evaluate consistency
    performance_analytics.compare_live_vs_backtest(live_trades, backtest_trades);
    
    // Monitor real-time P&L for live trades to manage risk
    risk_manager.monitor_realtime_risk(live_trades);
    
    // Calculate Value at Risk (VaR) for live trades to quantify potential losses
    risk_manager.calculate_var(live_trades);
    
    // Enforce risk limits (e.g., max loss 5%) to prevent excessive exposure
    risk_manager.enforce_risk_limits(live_trades);

    // Create sample market data for testing strategy execution
    MarketData sample_data;
    sample_data.asset = "BTC/USD";          // Set asset to BTC/USD
    sample_data.bid = 50000.0;              // Sample bid price
    sample_data.ask = 50010.0;              // Sample ask price
    sample_data.volume = 1000.0;            // Sample trading volume
    sample_data.timestamp = "2025-07-13 13:00:00"; // Sample timestamp
    
    // Execute MovingAverage strategy on sample data to generate an order
    Order order = strategy.execute(sample_data);
    
    // Match the generated order with market data (bid/ask prices)
    order_matching.match_order(order, sample_data);
    
    // Apply slippage and latency to simulate realistic trade execution
    order_matching.apply_slippage_and_latency(order);
    
    // Simulate order book dynamics for the order to model market impact
    market_microstructure.simulate_order_book(order, sample_data);
    
    // Detect market regime (e.g., trending, volatile) for BTC/USD
    market_microstructure.detect_regime("BTC/USD");

    // Classify strategy performance using machine learning techniques
    ml_analytics.classify_strategy(backtest_trades);
    
    // Detect market regimes in backtest trades for strategy optimization
    ml_analytics.detect_regime(backtest_trades);

    // Output confirmation of successful execution
    std::cout << "Backtester execution completed\n";
    
    return 0; // Exit program
}