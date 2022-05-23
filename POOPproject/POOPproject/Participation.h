#pragma once

#include <iostream>
#include <vector>
#include <map>
using namespace std;

//class Sport;
#include"Sport.h"
class Country;
//.class Discipline;
#include "Discipline.h";
//class Sport;
//class Country;

class Part{

	vector<int> athletes;
	bool team;
	Discipline* discipline;
	string medal;
	Sport* sport;
	int year;
	Country* country;

public:
	Part(bool t, Discipline* disc, string med, int y, Sport* s, Country* c, vector<int> a) :team(t), discipline(disc), medal(med), year(y), sport(s), country(c),athletes(a) {
	}


	friend ostream& operator<<(ostream& os, const Part& p) {
		os << p.year << " " << p.team << " ";
		os << *p.sport;
		os << " ";
		os<< *p.discipline << endl;
		return os;

	}

	//bool operator<(const Part* p) {
	//	return year < p.year;
	//}
	//bool operator>(const Part& p) {
	//	return year > p.year;
	//}
	Sport* getSport() const { return sport; }
	int getYear() const { return year; }
	Country* getCountry() const { return country; }
	string getMedal() const { return medal; }
	Discipline* getDiscipline() const { return discipline; }
	bool getTeam() const { return team; }
	vector<int> getAthletes() const { return athletes; }
};