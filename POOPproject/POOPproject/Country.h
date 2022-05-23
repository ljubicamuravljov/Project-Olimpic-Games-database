#pragma once
#include "Participation.h"



class Country {

	string name;
	vector<Part*> participations;

public:
	Country(string s):name(s){}

	void addParticipation(Part* p) { participations.push_back(p); }

	bool operator==(const Country& c) {
		return name == c.name;
	}	
	bool operator!=(const Country& c) {
		return name != c.name;
	}

	friend ostream& operator<<(ostream& os, const Country& c) {
		os << c.name << endl;
		return os;
	}

	string getName()const { return name; }
};