#include "Time Series.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include<cmath>

//ctor loads the file for manipulation
TimeSeries::TimeSeries(std::string filename) //specify filename when intialising
{
    std::ifstream file(filename);
    getline(file, line); //ignore the headers
    while( getline(file, line)){ // read current line
        std::istringstream iss(line); // construct string stream from line

        // read line up until comma, dummy1 ignores the empty column
        getline(iss, tempspdate, ',');
        getline(iss, tempsp, ',');
        getline(iss, dummy1, ',');
        getline(iss, tempdaxdate, ',');
        getline(iss, tempdax, ',');

        //converting the numerical values from str to double
         dtempsp = toNumber(tempsp);
         dtempdax = toNumber(tempdax);
        // pushing the values into the corresponding vectors
         spdate.push_back(tempspdate);
         daxdate.push_back(tempdaxdate);
         pricessp.push_back(dtempsp);
         pricesdax.push_back(dtempdax);

}
// fixing the first date so it matches (originally 06-Jun-16)
spdate[0] = "06-06-16";
daxdate[0] = "06-06-16";
}

//retrieving the prices & dates
std::vector<double> TimeSeries::getDaxPrice(){
        return pricesdax;
        }
std::vector<double> TimeSeries::getSPPrice()
{
        return pricessp;
        }

std::vector<std::string> TimeSeries::getSPDate(){
return spdate;
}
std::vector<std::string> TimeSeries::getDaxDate(){
return daxdate;
}
//function to convert the stringstream to a double
double TimeSeries::toNumber(const std::string & str)
{
    std::istringstream iss(str);
    double num;
    iss >> num;
    return num;


}
//creates a subset of the timeseries, puts them into new vectors
void TimeSeries::createSubset(std::string startdate, std::string enddate, std::vector<std::string> datelist, std::vector<double> pricelist, std::vector<std::string> &subDate, std::vector<double> &subPrice){
subDate.clear();
subPrice.clear();
std::ptrdiff_t  beginning = distance(datelist.begin(), find(datelist.begin(), datelist.end(), startdate)); //gets distance from beginning of vector to supplied start date
std::ptrdiff_t  ending = distance(datelist.begin(), find(datelist.begin(), datelist.end(), enddate)); //gets distance from beginning to supplied end date
if(beginning>ending){
    std::cerr << "Error: Trying to go backwards in time! \n";
}

if(std::find(datelist.begin(), datelist.end(), startdate)!= datelist.end() && std::find(datelist.begin(), datelist.end(), enddate)!= datelist.end()){

for(int i = beginning; i<=ending; ++i){ //loops from the index of the start date up to the end date, adding the values to the new vectors
subDate.push_back(datelist[i]);
subPrice.push_back(pricelist[i]);
}
}
else{
    std::cerr << "Error: date not in time series! \n";
}

}

//function that simply prints out subsets
void TimeSeries::printSubset(std::string startdate, std::string enddate, std::vector<std::string> datelist, std::vector<double> pricelist){
std::ptrdiff_t  beginning = distance(datelist.begin(), find(datelist.begin(), datelist.end(), startdate));
std::ptrdiff_t  ending = distance(datelist.begin(), find(datelist.begin(), datelist.end(), enddate));

for(int i = beginning; i<=ending; ++i){

    std::cout<<datelist[i] << "  " << pricelist[i] << "\n";
}

}



//function to print total annualised return of the time series
double TimeSeries::annualisedRtrn(std::vector<double> pricelist, int period){

return pow((pricelist.back()/pricelist.front()), (365.0/period)) - 1;
}

//function which prints out the annualised return of a subset of the time series
double TimeSeries::subsetRtrn(std::string startdate, std::string enddate, std::vector<std::string> datelist, std::vector<double> pricelist, std::vector<std::string> &subDate, std::vector<double> &subPrice)
{
createSubset(startdate, enddate, datelist,pricelist, subDate, subPrice); //invokes previous create subset function for new vectors
double period = subDate.size()-1; //obtains the number of days from beginning to end
return pow((subPrice.back()/subPrice.front()), (365.0/period)) - 1;
}

//calculates the subset return of a time series assuming you are already using a vector of subset
double TimeSeries::preCreatedSubRtrn(std::vector<double> subPrice)
{
double period = subPrice.size()-1; //obtains the number of days from beginning to end
return pow((subPrice.back()/subPrice.front()), (365.0/period)) - 1;
}

TimeSeries::~TimeSeries()
{
    //dtor
}
