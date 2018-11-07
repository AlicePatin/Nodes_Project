#include <map>
#include <vector>
#include <iterator>
#include <iostream>
#include "random.h"
#include "network.h"




void Network::resize(const size_t& n) {
	values.resize(n); 
	RNG.normal(values); 
}

bool Network::add_link(const size_t& n1, const size_t& n2) { 
	std::multimap<size_t, size_t>::const_iterator it;
	if (n1<values.size() and n2<values.size() and n1!=n2) {
		for (it = links.begin(); it != links.end(); ++it) {
			if ((it->first)==n1 and (it->second)==n2) { return false; }  //nodes already linked_Bidirectionnality => only one direction to test
		}
		links.insert (std::pair<size_t, size_t> (n1,n2));
		links.insert (std::pair<size_t, size_t> (n2,n1));
		return true;
		
	} else {
		return false; //nodes do not exists
	}
}

//choose neighbors in a vector of possible neighbors, randomly shuffled
size_t Network::random_connect(const double& mean)  {
	int count(0);
	links.clear(); 
	size_t nb_voisins(0);
	std::vector<size_t> voisins_potentiels;
	for (size_t i(0); i<values.size(); ++i) { voisins_potentiels.push_back(i); }
	
	for (size_t key=0; key<values.size(); ++key) {
		nb_voisins = RNG.poisson(mean);
		if (nb_voisins < 0) { nb_voisins = 0; }
		RNG.shuffle(voisins_potentiels); 
		for (size_t val=0; val<nb_voisins; ++val) {
			if (add_link(key, voisins_potentiels[val])){ ++count; }
		}	
	}
	return count;  
}

 
size_t Network::set_values(const std::vector<double>& new_values){ 
	size_t size = this->size();
	int count (0);
	for (size_t i=0; i< std::min(size, new_values.size()); ++i) {   
		values[i]= new_values[i];
		++ count;
	}
	return count;
}

size_t Network::size() const {
	return values.size();
}

size_t Network::degree(const size_t &_n) const {
	return links.count (_n);
}
	

double Network::value(const size_t &_n) const {
	return values[_n];
}

std::vector<double> Network::sorted_values() const { 
	std::vector<double> sorted = values;
	std::sort(sorted.begin(), sorted.end(), std::greater<double>());
	return sorted;
}

std::vector<size_t> Network::neighbors(const size_t& n) const {
	std::vector<size_t> neighbors;
	typedef std::multimap<size_t, size_t> mmap;
	mmap::const_iterator it;
	std::pair<mmap::const_iterator, mmap::const_iterator> result = links.equal_range(n); 
	for (it= result.first ; it != result.second; ++it) {  
		neighbors.push_back(it->second);
	}
	return neighbors;
}


	



