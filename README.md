# Live Strategy Backtester – C++ Trading System

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](./)
[![License](https://img.shields.io/badge/license-MIT-blue)](./LICENSE)


---

##  Table of Contents
1. [Project Overview](#project-overview)  
2. [Features](#features)  
3. [Installation](#installation)  
4. [Usage](#usage)  
5. [Demo](#demo)  
6. [Technologies Used](#technologies-used)  
7. [Contribution Guidelines](#contribution-guidelines)  
8. [License](#license)  

---

## Project Overview
The **Live Strategy Backtester** is a modular C++-based trading platform developed as part of an assignment.  
It implements a **moving average strategy** for BTC/USDT with robust support for **data ingestion, backtesting, live shadow trading, risk management, and performance analysis**.  

The project provides a foundation for both **backtesting historical market data** and simulating **real-time trading environments**. Binance WebSocket integration is under development, with HTTP-based injection currently implemented.

---

## Features
- **Data Management**
  - Ingest historical and real-time BTC/USDT data (Binance API or local files).  
  - Supports alternative data sources (e.g., sentiment/news).  

- **Trading Strategy**
  - Moving Average Crossover strategy (`short_window`, `long_window`).  
  - Modular design allows plugging in new strategies.  

- **Backtesting**
  - Simulates trading on historical datasets.  
  - Logs trades and evaluates strategy performance.  

- **Live Shadow Trading**
  - Shadow trade execution on simulated real-time data.  
  - Placeholder WebSocket (Binance live WebSocket integration in progress).  

- **Risk Management**
  - Real-time P&L monitoring.  
  - Value-at-Risk (VaR) calculation.  
  - Risk limit enforcement.  

- **Performance Analytics**
  - Calculates **Sharpe Ratio, Sortino Ratio, Maximum Drawdown**.  
  - Compares live vs. backtest results.  

- **Advanced Modules**
  - Order Matching with slippage & latency.  
  - Market Microstructure modeling & regime detection.  
  - ML-based analytics for strategy classification and optimization (placeholder).  

---

## Installation

### Prerequisites
- C++17 or higher  
- CMake (≥ 3.15)  
- vcpkg (for dependency management)  
- Dependencies: `cpprestsdk`, `curl`, `openssl`

## Steps

### Clone the repository
```bash
git clone https://github.com/your-username/live-strategy-backtester.git
cd live-strategy-backtester
```

### Install dependencies using vcpkg
```bash
./vcpkg install cpprestsdk curl openssl
```

### Build the project
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

---


## Usage

### Running a Backtest
```bash
./Release/backtester.exe
````

* Loads BTC/USDT data (`data/historical_data/BTC_USD.dat` or Binance API).
* Executes trades using Moving Average strategy.
* Outputs results in `data/historical_data/BTC_USDT_saved.dat`.

### Running Live Shadow Trading

```bash
./Release/live_engine.exe
```

* Simulates live trading with shadow trades.
* Outputs real-time trade logs and simulated P\&L.

### Configuration

* Modify strategy parameters in `main.cpp`:

```cpp
MovingAverage strategy(2, 3); // short=2, long=3
```

* Update Binance API keys in `data_manager.cpp`.

---

##  Demo

This project includes a **video demonstration** walkthrough. Key highlights:

* **Initialization**: System setup with DataManager, Strategy, BacktestEngine, LiveEngine, RiskManager, etc.
* **Backtest Run**: Executes trades from historical BTC/USDT data.
* **Live Shadow Trading**: Processes simulated live data and logs shadow trades.
* **Performance Analysis**: Calculates Sharpe, Sortino, and Max Drawdown.
* **Code Architecture**: Modular, thread-safe, and extensible system design.

[Click here for demo](https://youtu.be/1XtoS_2UhpI)  

---

##  Technologies Used

* **Programming Language**: C++17
* **Build System**: CMake
* **Dependency Management**: vcpkg
* **Libraries**:

  * `cpprestsdk` (Binance API integration via HTTP)
  * `curl` & `openssl` (networking & security)
* **Design Patterns**: Singleton, Strategy, Observer, Facade
* **Data Handling**: Thread-safe storage with `std::map` + `std::mutex`

---

##  Contribution Guidelines

Contributions are welcome!

1. Fork the repository
2. Create a feature branch

   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes

   ```bash
   git commit -m "Add feature"
   ```
4. Push to branch

   ```bash
   git push origin feature-name
   ```
5. Open a Pull Request

---
##  License

This project is licensed under the **MIT License**.  
See the [LICENSE](./LICENSE) file for details.  

---

## Future Roadmap

Planned enhancements for the Live Strategy Backtester:

- **Binance WebSocket Integration**  
  Replace the placeholder WebSocket with full real-time Binance streaming for BTC/USDT.  

- **Market Microstructure Simulation**  
  Model order book dynamics (bid/ask spread, liquidity impact, slippage).  

- **Machine Learning Analytics**  
  - Strategy classification (profitable/unprofitable).  
  - Market regime detection (e.g., trending, volatile).  

- **Additional Assets**  
  Extend support to other pairs (e.g., ETH/USDT).  

- **Advanced Risk Management**  
  - Dynamic Value-at-Risk (VaR) calculation.  
  - Automated risk limit enforcement with configurable thresholds.  

- **Performance Optimization**  
  - Multi-threading support for large datasets.  
  - Reduced latency in live execution pipeline.  

 *Target timeline: Q3 2025 – Q2 2026*  

---

##  Author & Contact

**Developed by:** Manohar Daripalli  

-  Email: [manohar6317@gmail.com]  
-  GitHub: [click ME!](https://github.com/manohar6317)  
-  LinkedIn: [click ME!](https://www.linkedin.com/in/d-manohar6317/)  

Feel free to reach out for collaboration, contributions, or discussions on trading systems, C++, and algorithmic strategies! 🚀  

---


