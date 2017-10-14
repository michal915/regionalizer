/**
 * \file VectorOfCities
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "VectorOfCities.hpp"

namespace VectorOfCities {

void setDistanceToTheFarthestInTheWholeVector(std::vector<City>& vec) {
    for (City& i : vec) {
	double farthestDistanceSoFar{};
        for (City j : vec) {
	    double tmp = i.distanceFrom(j);
	    if (tmp > farthestDistanceSoFar) {
                farthestDistanceSoFar = tmp;
	    }
	}
        i.setDistanceToTheFarthest(farthestDistanceSoFar);	
    }
}

std::size_t getPopulationOfTheWholeVector(const std::vector<City>& vec) {
    std::size_t result{};
    for (const auto & i : vec) {
        result += i.getPopulation();
    }
    return result;
}

void calculateHappinessLevelForOneRegionByBruteForce(std::vector<City> vec){ 
    std::string bestCapitalSoFar{};
    std::size_t bestHLsoFar{};
    for (City i : vec) {
        std::cout << " " << i.getName() << "\t";
	std::size_t hl{}; // happiness level
        for (City j : vec) {
	    std::size_t tmp = (10.0 - ((static_cast<double>(j.distanceFrom(i)) / 
                    static_cast<double>(j.getDistanceToTheFarthest()))*10.0));
	    hl += (j.getPopulation() * tmp);
	}
	std::cout << "Happiness level = " << hl;
        std::cout << std::endl;
        if (hl > bestHLsoFar) {
	    bestHLsoFar = hl;
	    bestCapitalSoFar = i.getName();
	}
    }
    std::cout << std::endl;
    std::cout << "The best capital would be  " << bestCapitalSoFar;
    std::cout << std::endl;
    std::cout << "Happiness level = " << bestHLsoFar;
    std::cout << std::endl;
    std::cout << "Population = " << getPopulationOfTheWholeVector(vec);
    std::cout << std::endl;
    std::cout << "Percentage = " << static_cast<double>(10.0 * bestHLsoFar) 
        / getPopulationOfTheWholeVector(vec) << "%";
    std::cout << std::endl;

}

void calculateHappinessLevelForOneRegionByBruteForceAndMakeMap
        (const std::vector<City>& vec){ 
    std::ofstream data;
    std::size_t populationOfState = getPopulationOfTheWholeVector(vec);
    std::string bestCapitalSoFar{};
    std::size_t bestHLsoFar{};
    data.open("hl.dat");
    for (City i : vec) {
        std::cout << " " << i.getName() << "\t";
	std::size_t hl{}; // happiness level
        for (City j : vec) {
	    std::size_t tmp = (10.0 - ((static_cast<double>(j.distanceFrom(i)) / 
                    static_cast<double>(j.getDistanceToTheFarthest()))*10.0));
	    hl += (j.getPopulation() * tmp);
	}
	std::cout << "Happiness level = " << (static_cast<double>(hl)/static_cast<double>(populationOfState));
        std::cout << "\tPercentage = " << static_cast<std::size_t>(static_cast<double>(10.0 * hl) / populationOfState);
        std::cout << std::endl;

        data << i.getLongitude();
	data << " ";
        data << i.getLatitude();
	data << " ";
        data << static_cast<std::size_t>(static_cast<double>(10.0 * hl) / populationOfState);
	data << std::endl;

        if (hl > bestHLsoFar) {
	    bestHLsoFar = hl;
	    bestCapitalSoFar = i.getName();
	}
    }
    data.close();

    std::ofstream script;
    script.open("hl.gnu");
    script << "set terminal pngcairo  transparent enhanced font \"arial,10\" fontscale 1.0 size 2000, 1400";
    script << std::endl;
    script << "set output 'hl.png'";
    script << std::endl;
    script << "set key inside left top vertical Right noreverse enhanced autotitles box linetype -1 linewidth 1.000";
    script << std::endl;
    script << "set title \"HL\"";
    script << std::endl;
    script << "set ylabel \"latitude\"";
    script << std::endl;
    script << "set xlabel \"longitude\"";
    script << std::endl;
    script << "set xrange [14 : 25] reverse nowriteback";
    script << std::endl;
    script << "set yrange [49 : 56] noreverse nowriteback";
    script << std::endl;
    script << "plot 'hl.dat' with points palette pt 7 ps 5 ";
    script << std::endl;
    script << "set output";
    script << std::endl;

    script.close();
    system( "gnuplot hl.gnu" );
//    system( "rm -f hl.gnu" );
//    system( "rm -f hl.dat" );


    std::cout << std::endl;
    std::cout << "The best capital would be  " << bestCapitalSoFar;
    std::cout << std::endl;
    std::cout << "Happiness level = " << bestHLsoFar;
    std::cout << std::endl;
    std::cout << "Population = " << populationOfState;
    std::cout << std::endl;
    std::cout << "Percentage = " << static_cast<double>(10.0 * bestHLsoFar) 
        / getPopulationOfTheWholeVector(vec) << "%";
    std::cout << std::endl;

}

} // namespace
