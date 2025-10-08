# 📊 Portfolio Analyzer

The **Portfolio Analyzer** is a C++ program designed to read historical stock prices from a CSV file and perform basic **quantitative finance analysis**. The program computes **logarithmic returns, mean, variance, covariance**, and calculates the **expected return and risk of a portfolio**.  

This tool is useful for understanding **portfolio construction, diversification, and risk management**.

---

## Problem Statement

Investors often hold multiple stocks or assets in a portfolio. To make informed decisions, they need to know:

1. **Expected returns** of individual stocks  
2. **Risk (variance/volatility)** of each stock  
3. **Relationship between stocks** (covariance)  
4. **Portfolio expected return** and **portfolio risk**, based on allocation  

The challenge is to compute these **quantitative measures** using historical stock price data efficiently in C++.

---

## Solution Approach

The solution is implemented in **C++** and follows these steps:

### 1️⃣ Reading Stock Price Data

- Reads a CSV file (`stock_prices.csv`) with format:

Date,StockA,StockB,StockC
2025-01-01,100,200,50
2025-01-02,102,198,52
2025-01-03,101,201,51


- Each column after `Date` represents a stock’s historical price.  
- Parsed using `ifstream` and `stringstream`.

---

### 2️⃣ Calculating Logarithmic Returns

For stock \(i\), the **logarithmic return** \(R_t\) is:

$$
R_t = \ln \frac{S_t}{S_{t-1}}
$$

- \(S_t\) = stock price at time \(t\)  
- Log returns are **time-additive** and handle compounding better than simple returns.

---

### 3️⃣ Calculating Mean and Variance

- **Mean (Expected Return):**

$$
\mu_i = \frac{1}{n} \sum_{t=1}^{n} R_{i,t}
$$

- **Variance (Risk of Stock):**

$$
\sigma_i^2 = \frac{1}{n-1} \sum_{t=1}^{n} (R_{i,t} - \mu_i)^2
$$

- Variance measures the **volatility** of the stock.

---

### 4️⃣ Calculating Covariance Between Stocks

$$
\text{Cov}(R_i, R_j) = \frac{1}{n-1} \sum_{t=1}^{n} (R_{i,t}-\mu_i)(R_{j,t}-\mu_j)
$$

- Covariance measures how two stocks **move together**:
  - **Positive covariance** → move in the same direction  
  - **Negative covariance** → move in opposite directions  

- The program builds a **covariance matrix** for all stocks.

---

### 5️⃣ Portfolio Analysis

- Portfolio weights are **equally distributed** by default:

$$
w_i = \frac{1}{n}, \quad \text{for each stock } i
$$

- **Expected Portfolio Return:**

$$
R_p = \sum_{i=1}^{n} w_i \mu_i
$$

- **Portfolio Variance:**

$$
\sigma_p^2 = \sum_{i=1}^{n} \sum_{j=1}^{n} w_i w_j \text{Cov}(R_i, R_j)
$$

- **Portfolio Standard Deviation (Risk):**

$$
\sigma_p = \sqrt{\sigma_p^2}
$$

> Accounts for both individual stock volatility and how stocks move together.

---

### 6️⃣ Output

The program prints:

1. **Mean and variance** of log returns for each stock  
2. **Covariance matrix** of all stocks  
3. **Portfolio expected return**  
4. **Portfolio risk (variance and standard deviation)**  

**Sample Output:**

Stock Statistics (Log Returns):
StockA - Mean: 0.0045 , Variance: 0.0001
StockB - Mean: 0.0020 , Variance: 0.0002
StockC - Mean: 0.0030 , Variance: 0.00015

Covariance Matrix
0.0001 0.00005 0.00002
0.00005 0.0002 0.00003
0.00002 0.00003 0.00015

Portfolio Expected Return: 0.00316
Portfolio Risk (Variance): 0.00013
Portfolio Risk (Std Dev): 0.0114



---

### 7️⃣ Key Concepts Used

- **Logarithmic Returns** → additive over time, handles compounding  
- **Mean** → average return  
- **Variance** → risk of individual stocks  
- **Covariance** → how stocks move together  
- **Portfolio Return & Risk** → weighted combination of mean and covariance  

---


<img width="596" height="880" alt="Screenshot 2025-10-08 181640" src="https://github.com/user-attachments/assets/e0a03029-903b-4f6e-a800-5a9fa4df313f" /> 
<img width="592" height="728" alt="Screenshot 2025-10-08 181623" src="https://github.com/user-attachments/assets/5cd18bd4-4080-40ca-b6f8-79f7f327be3d" />

