#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <regex>
#include <map>
#include <vector>
#include <set>


#include"Game.h"
#include "Country.h"
#include "Athlete.h"
#include "Sport.h"
#include "Participation.h"
#include"Discipline.h"
using namespace std;


class OlimpicGames {

	static OlimpicGames* instance;

	map<pair<int, string>, Game* > allgames;
	map<string, Sport*> allsports;
	map<string, Country*> allcountries;
	map<string, Discipline*> alldisciplines;
	map<int, Athlete*> allathletes;
	//vector<int>athleteids;
	vector<Part*> allparticipations;
	OlimpicGames(){}


public:
	static OlimpicGames* getInstance() {
		if (instance == nullptr) {
			instance = new OlimpicGames();
		}
		return instance;
	}

	void parse(bool group,int y=0);

	vector<Part*> filter(vector<Part*> participation,string sport = "", string country = "", int year = 0, string type = "", string medal = "");

	int numOfContestants(string sport="",string country="",int year=0,string type="",string medal="");
	int numOfDisciplines(string sport="",string country="",int year=0,string type="",string medal="");
	float avgHeight(string sport="",string country="",int year=0,string type="",string medal="");
	float avgWeight(string sport="",string country="",int year=0,string type="",string medal="");
	int numOfSportsMedal(Country* c);
	map<Country*, Athlete*> pairsMedalIndGroup();
	vector<Athlete*> tenYoungest();
	vector<Athlete*> participatedInPairOfGames(int y1,string t1,int y2,string t2);
	set<string> cities();
	vector<pair<Country*, tuple<int, int, int>>> threeBestCountries(int y, string t);
	void allTeams(Country* c, int year, string t);
	void countriesBestAtLeastOnce();
};



