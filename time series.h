#ifndef TIMESERIES_H
#define TIMESERIES_H

#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

class TimeSeries
{
    public:
        TimeSeries(std::string filename);
        virtual ~TimeSeries();
        std::vector<std::string> getSPDate();
        std::vector<std::string> getDaxDate();
        std::vector<double> getDaxPrice();
        std::vector<double> getSPPrice();
        double toNumber(const std::string &str);
        double annualisedRtrn(std::vector<double> pricelist, int period);
        double subsetRtrn(std::string startdate, std::string enddate, std::vector<std::string> datelist, std::vector<double>pricelist, std::vector<std::string>&subDate, std::vector<double> &subPrice);
        void createSubset(std::string startdate, std::string enddate, std::vector<std::string> datelist, std::vector<double> pricelist, std::vector<std::string>&subDate, std::vector<double> &subPrice);
        void printSubset(std::string startdate, std::string enddate, std::vector<std::string> datelist, std::vector<double> pricelist);
        double preCreatedSubRtrn(std::vector<double> subPrice);

    protected:

    private:
    std::vector<std::string> spdate, daxdate;
    std::vector<double> pricessp, pricesdax;
    double dtempsp, dtempdax;
    std::string tempspdate,tempdaxdate, tempsp, tempdax, dummy1, line;
};

#endif // TIME SERIES_H
