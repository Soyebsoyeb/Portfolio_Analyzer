#include <iostream>
#include <fstream>  // To read from files
#include <sstream>  // To parse strings
#include <vector>  
#include <string>   // For handling text
#include <cmath>    

using namespace std;

// (1) Mean
double mean(const vector<double>& data){
    double sum = 0.0;
    for(double x: data) sum += x;
    return sum/data.size();
}

// (2) Variance
double variance(const vector<double>& data){
    double m = mean(data);
    double sum = 0.0;
    for(double x: data) sum += (x-m) * (x-m);

    return sum / (data.size() - 1);     // Sample variance 
}

// (3) Covariance
double covariance(const vector<double>& x, const vector<double>& y){
    double meanX = mean(x);
    double meanY = mean(y);

    double sum = 0.0;

    for(size_t i=0; i<x.size() ; i++){
        sum += (x[i] - meanX) * (y[i] - meanY);
    }
    return sum / (x.size() - 1);
}

// Logarithmic daily returns

vector<double> computeLogReturns(const vector<double> &prices){
    vector<double> logReturns;

    for(size_t i=1; i<prices.size() ; i++){
        logReturns.push_back(log(prices[i] / prices[i-1]));
    }

    return logReturns;
}


int main(){
    string filename = "stock_prices.csv"; // CSV File with columns: Date,Stock1,Stock2,...
    ifstream file(filename);

    if(!file.is_open()){
        cerr << "Could not open file" << filename << endl;
        return 1;
    }

    // Preparing to read the data
    string line;
    vector<vector<double>> prices; // Each vector is prices for one stock


    // Read header to know number of stocks
    getline(file , line);    
    // getline reads the first line from CSV    // "Date,StockA,StockB,StockC"
    stringstream ss(line);   
    // Converts string into stream so we can read each column indiviually using comma as a delimeter

    string col;
    vector<string> headers;

    while(getline(ss,col,','))  headers.push_back(col);
    // headers = ["Date", "StockA", "StockB", "StockC"]

    int nStocks = headers.size()-1;
    prices.resize(nStocks);


    // Reading each row of the CSV


    // Reads entire line as string
    while(getline(file,line)){
        stringstream ss(line);
        string val;
    
        getline(ss,val,',');  // Skip date

        for(int i=0; i<nStocks ; i++){
            getline(ss,val,',');
            prices[i].push_back(stod(val));   // string to decimal
        }       
    }
    file.close();

    // Compute log returns for each stock
    vector<vector<double>> returns(nStocks);

    for(int i=0; i<nStocks ; i++){
        returns[i] = computeLogReturns(prices[i]);
    }

    // Compute  mean,variance,covariance
    cout << "Stock Statistics (Log Returns) : " << endl;
    for(int i=0; i<nStocks; i++){
        cout << headers[i+1] << " - Mean: " << mean(returns[i]) << " , Variance: " << variance(returns[i]) << endl;
    }

 
    cout << endl << "Covariance Matrix" << endl;
    for(int i=0; i<nStocks;i++){
        for(int j=0;j<nStocks;j++){
            cout << covariance(returns[i] , returns[j]) << "\t";
        }
        cout << endl;
    }


    // Portfolio calculation equally weighted 

    vector<double> weights(nStocks , 1.0/nStocks);

    // Expected portfolio return 
    double portReturn = 0.0;
    
    for(int i=0; i<nStocks;i++) 
        portReturn += weights[i]*mean(returns[i]);

    // Portfolio Variance

    double portVariance = 0.0;

    for(int i=0; i<nStocks; i++){
        for(int j=0; j<nStocks ; j++){
            portVariance += weights[i]*weights[j]* covariance(returns[i],returns[j]);
        }
    }

    cout << "\nPortfolio Expected Return: " << portReturn << endl;
    cout << "Portfolio Risk (Variance): " << portVariance << endl;
    cout << "Portfolio Risk (Std Dev): " << sqrt(portVariance) << endl;

    return 0;

}