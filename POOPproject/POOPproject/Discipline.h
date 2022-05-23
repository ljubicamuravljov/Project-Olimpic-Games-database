#pragma once

class Part;
class Discipline {

	string name;
	vector<Part*> participations;

public:
	Discipline(string s) :name(s) {}

	void addParticipation(Part* p) { participations.push_back(p); }

	friend ostream& operator<<(ostream& os,const Discipline& s) {
		os << s.name;
		return os;
	}
	bool operator==(const Discipline& s) {
		return name == s.name;
	}
	bool operator!=(const Discipline & s) {
		return name != s.name;
	}
	bool operator<(const Discipline& s) {
		return name < s.name;
	}	
	bool operator>(const Discipline& s) {
		return name > s.name;
	}
};