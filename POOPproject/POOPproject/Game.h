#pragma once
#include "Participation.h"


class Game {

	int year;
	string type;
	string city;

	vector <Part*> participations;

public:
	Game(int y,string t,string c):year(y),type(t),city(c){}

	void addParticipation(Part* p) { participations.push_back(p); }


	vector<Part*> getParticipations() const { return participations; }
	int getYear() const { return year; }
	string getType() const { return type; }
	string getCity() const { return city; }
};