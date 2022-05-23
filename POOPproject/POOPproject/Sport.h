#pragma once
//#include "Participation.h"
class Part;
class Sport {

	string name;
	vector<Part*> participations;

public:
	Sport(string s) :name(s){}

	void addParticipation(Part* p) { participations.push_back(p); }

	friend ostream& operator<<(ostream& os,  Sport& s) {
		os << s.name;
		return os;
	}
	bool operator==(const Sport& s) {
		return name == s.name;
	}
	bool operator!=(const Sport& s) {
		return name != s.name;
	}
};