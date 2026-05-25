#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <fstream>

struct Option {
    double S;
    double K;
    double T;
    double r;
    double sigma;
    char type;
    double marketPrice;
};


double normalCDF(double x) {
    return 0.5 * erfc(-x / sqrt(2.0));
}

double calcD1(Option opt) {
    return ((log(opt.S/opt.K)) + (opt.r + opt.sigma * opt.sigma / 2) * opt.T) / (opt.sigma * std::sqrt(opt.T));
}

double calcD2(Option opt) {
    return calcD1(opt) - opt.sigma * std::sqrt(opt.T);
}

double blackScholes(Option opt) {
    auto d1 = calcD1(opt);
    auto d2 = calcD2(opt);

    if (opt.type == 'C') {
        double call = opt.S * normalCDF(d1) - opt.K * std::exp(-opt.r * opt.T) * normalCDF(d2);
        return call;
    } else {
        double put = opt.K * std::exp(-opt.r * opt.T) * normalCDF(-d2) - opt.S * normalCDF(-d1);
        return put;
    }
}

double normalPDF(double x) {
    return std::exp(-x * x / 2.0) / std::sqrt(2.0 * M_PI);
}

double delta(Option opt) {
    auto d1 = calcD1(opt);

    if (opt.type == 'C') {
        return normalCDF(d1);
    } else {
        return normalCDF(d1) - 1;
    }
}

double vega(Option opt) {
    auto d1 = calcD1(opt);
    return opt.S * normalPDF(d1) * std::sqrt(opt.T) / 100;
}

double gamma(Option opt) {
    auto d1 = calcD1(opt);
    auto d2 = calcD2(opt);
    return normalPDF(d1) / (opt.S * opt.sigma * std::sqrt(opt.T));
}

double theta(Option opt) {
    auto d1 = calcD1(opt);
    auto d2 = calcD2(opt);

    double common = (-opt.S * normalPDF(d1) * opt.sigma) / (2 * std::sqrt(opt.T));

    if (opt.type == 'C') {
        return (common - opt.r * opt.K * std::exp(-opt.r * opt.T) * normalCDF(d2)) / 365.0;
    } else {
        return (common + opt.r * opt.K * std::exp(-opt.r * opt.T) * normalCDF(-d2)) / 365.0;
    }
}

double rho(Option opt) {
    auto d1 = calcD1(opt);
    auto d2 = calcD2(opt);

    if (opt.type == 'C') {
        return opt.K * opt.T * std::exp(-opt.r * opt.T) * normalCDF(d2) / 100;
    } else {
        return -opt.K * opt.T * std::exp(-opt.r * opt.T) * normalCDF(-d2) / 100;
    }
}

void printResults(Option opt) {
    std::cout << "Spot Price:    " << opt.S     << std::endl;
    std::cout << "Strike Price:  " << opt.K     << std::endl;
    std::cout << "Time to Expiry:" << opt.T     << std::endl;
    std::cout << "Risk-free Rate:" << opt.r     << std::endl;
    std::cout << "Volatility:    " << opt.sigma << std::endl;
    std::cout << "Type:          " << opt.type  << std::endl;

    double price = blackScholes(opt);
    std::cout << "Prezzo opzione: " << price << std::endl;
    
    std::cout << "Delta: " << delta(opt) << std::endl;

    std::cout << "Gamma: " << gamma(opt) << std::endl;

    std::cout << "Vega: " << vega(opt) << std::endl;

    std::cout << "Theta: " << theta(opt) << std::endl;

    std::cout << "Rho: " << rho(opt) << std::endl;

    std::cout << "Market Price: " << opt.marketPrice << std::endl;
}

std::vector<Option> loadCSV(std::string filename) {
    std::vector<Option> options;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);

    if (!file.is_open()) {
        std::cerr << "Errore: impossibile aprire il file " << filename << std::endl;
        return options;
    }

    while (std::getline(file, line)) {
        Option o;
        std::stringstream ss(line);
        std::string token;
        int i = 0;

        while (std::getline(ss, token, ',')) {
            if (i == 0) o.S     = std::stod(token);
            if (i == 1) o.K     = std::stod(token);
            if (i == 2) o.T     = std::stod(token);
            if (i == 3) o.r     = std::stod(token);
            if (i == 4) o.sigma = std::stod(token);
            if (i == 5) o.type  = token[0];
            if (i == 6) o.marketPrice = std::stod(token);
            i++;
        }

        options.push_back(o);
    }

    return options;
}

int main() {
    auto options = loadCSV("options.csv");
    for (auto o : options) {
        printResults(o);
        std::cout << "---\n\n";
    }

    return 0;
}