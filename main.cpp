#include "Time Series.h"
#include<iostream>

int main() {

TimeSeries t1("TimeSeries.csv");
std::vector<std::string>spdatesub, daxdatesub;
std::vector<double> sppricesub, daxpricesub;
t1.createSubset("01-01-18", "06-06-18", t1.getSPDate(), t1.getSPPrice(), spdatesub, sppricesub);



double totreturnsp = t1.annualisedRtrn(t1.getSPPrice(), 731);

double totreturndax = t1.annualisedRtrn(t1.getDaxPrice(), 731);

std::cout << totreturnsp << " " << totreturndax << "\n";
for(int i = 0; i < sppricesub.size(); ++i){
    std::cout << spdatesub[i] << "  " << sppricesub[i] << std::endl;
}


}
