#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>  

using namespace std;

// --------- Statistical Functions ---------

// Compute mean of a vector
double mean(const vector<double>& data) {
    if(data.empty()) return 0.0;
    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Compute sample variance
double variance(const vector<double>& data) {
    if(data.size() < 2) return 0.0;
    double m = mean(data);
    double sum = 0.0;
    for(double x : data) sum += (x - m) * (x - m);
    return sum / (data.size() - 1);
}

// Compute covariance between two vectors
double covariance(const vector<double>& x, const vector<double>& y) {
    if(x.size() != y.size() || x.size() < 2) return 0.0;
    double meanX = mean(x);
    double meanY = mean(y);
    double sum = 0.0;
    for(size_t i = 0; i < x.size(); i++)
        sum += (x[i] - meanX) * (y[i] - meanY);
    return sum / (x.size() - 1);
}

// Compute logarithmic returns from prices
vector<double> computeLogReturns(const vector<double>& prices) {
    vector<double> logReturns;
    for(size_t i = 1; i < prices.size(); i++)
        logReturns.push_back(log(prices[i] / prices[i - 1]));
    return logReturns;
}


// --------- Portfolio Functions ---------

// Compute expected portfolio return given returns and weights
double portfolioReturn(const vector<vector<double>>& returns, const vector<double>& weights) {
    double portReturn = 0.0;
    for(size_t i = 0; i < returns.size(); i++)
        portReturn += mean(returns[i]) * weights[i];
    return portReturn;
}

// Compute portfolio variance given returns and weights
double portfolioVariance(const vector<vector<double>>& returns, const vector<double>& weights) {
    double portVar = 0.0;
    for(size_t i = 0; i < returns.size(); i++) {
        for(size_t j = 0; j < returns.size(); j++)
            portVar += weights[i] * weights[j] * covariance(returns[i], returns[j]);
    }
    return portVar;
}



// Main

int main() {
    string filename = "stock_prices.csv";
    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string line;
    vector<string> headers;
    vector<vector<double>> prices;

    // Read header
    if(getline(file, line)) {
        stringstream ss(line);
        string col;
        while(getline(ss, col, ',')) headers.push_back(col);
    } else {
        cerr << "Error: Empty file." << endl;
        return 1;
    }

    int nStocks = headers.size() - 1;
    if(nStocks < 1) {
        cerr << "Error: No stock columns found." << endl;
        return 1;
    }
    prices.resize(nStocks);

    // Read CSV data
    while(getline(file, line)) {
        stringstream ss(line);
        string val;
        getline(ss, val, ','); // Skip date
        for(int i = 0; i < nStocks; i++) {
            if(!getline(ss, val, ',')) {
                cerr << "Error: Missing value in row." << endl;
                return 1;
            }
            prices[i].push_back(stod(val));
        }
    }
    file.close();

    // Compute log returns for each stock
    vector<vector<double>> returns(nStocks);
    for(int i = 0; i < nStocks; i++)
        returns[i] = computeLogReturns(prices[i]);

    // Print stock statistics
    cout << "Stock Statistics (Log Returns):\n";
    for(int i = 0; i < nStocks; i++)
        cout << headers[i + 1] << " - Mean: " << mean(returns[i])
             << ", Variance: " << variance(returns[i]) << endl;

    // Covariance matrix
    cout << "\nCovariance Matrix:\n";
    for(int i = 0; i < nStocks; i++) {
        for(int j = 0; j < nStocks; j++)
            cout << covariance(returns[i], returns[j]) << "\t";
        cout << endl;
    }

    // --- Portfolio weights ---
    vector<double> weights(nStocks, 1.0 / nStocks); // Default equal weights

    // Optionally, you could ask user for custom weights:
    /*
    cout << "\nEnter portfolio weights (sum to 1): ";
    for(int i = 0; i < nStocks; i++) cin >> weights[i];
    */

    // Portfolio calculations
    double portReturn = portfolioReturn(returns, weights);
    double portVar = portfolioVariance(returns, weights);

    cout << "\nPortfolio Expected Return: " << portReturn << endl;
    cout << "Portfolio Risk (Variance): " << portVar << endl;
    cout << "Portfolio Risk (Std Dev): " << sqrt(portVar) << endl;

    return 0;
}
