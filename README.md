# Black-Scholes Option Pricing Engine

A lightweight C++ project for pricing European options using the Black-Scholes model and calculating the main option Greeks.

The program loads option data from a CSV file, computes theoretical prices for calls and puts, and outputs risk metrics commonly used in quantitative finance and derivatives trading.

---

## Features

- European Call and Put option pricing
- Black-Scholes analytical model implementation
- Greeks calculation:
  - Delta
  - Gamma
  - Vega
  - Theta
  - Rho
- CSV-based input system
- Clean and modular C++ implementation
- Financial mathematics utilities:
  - Normal PDF
  - Normal CDF
  - d1 and d2 calculations

---

## Technologies

- C++
- Standard Template Library (STL)
- File handling with CSV parsing
- Mathematical modeling for quantitative finance

---

## Example Use Cases

- Quantitative finance projects
- Learning derivatives pricing
- Risk management simulations
- Academic and portfolio projects
- Financial engineering practice

---

## Input Format

The program reads option contracts from an `options.csv` file with the following structure:

```csv
S,K,T,r,sigma,type,marketPrice
100,105,1,0.05,0.2,C,8.5
```

Where:

- `S` = Spot price
- `K` = Strike price
- `T` = Time to maturity
- `r` = Risk-free interest rate
- `sigma` = Volatility
- `type` = `C` for Call or `P` for Put
- `marketPrice` = Observed market option price

---

## Output

For each option, the program prints:

- Theoretical option price
- Delta
- Gamma
- Vega
- Theta
- Rho
- Market price comparison

---

## Purpose

This project was developed to demonstrate practical applications of quantitative finance, numerical modeling, and C++ programming in derivatives pricing and risk analysis.
