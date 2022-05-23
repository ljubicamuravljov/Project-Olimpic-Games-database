#include "OlimpicGames.h"
string FILEEVENTS = "test.txt";
string FILEATHLETES = "athletes.txt";

OlimpicGames* OlimpicGames::instance = nullptr;

void OlimpicGames::parse(bool group,int y)
{

	ifstream file(FILEEVENTS);
	string textLine;
	regex rx("(\\d*) ([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^\\n]*)");

	while (getline(file, textLine)) {
		smatch result;
		//cout << textLine;
		if (regex_match(textLine, result, rx)) {
			int year = atoi(result.str(1).c_str());

			if (group == 0 && year != y) { continue; }
			//	cout << year << endl;
			string type = result.str(2);
			string city = result.str(3);
			string sport = result.str(4);
			string discipline = result.str(5);
			string disctype = result.str(6);
			string compcountry = result.str(7);
			string ids = result.str(8);
			string medal = result.str(9);
			if (medal == "") medal = "none";

			//IF GAME NOT IN ALL GAMES ADD IT
			if (allgames.find(pair<int, string>(year, type)) == allgames.end()) {
				Game* newgame = new Game(year, type,city);
				allgames[pair<int, string>(year, type)] = newgame;
			}


			//IF SPORT NOT IN ALLSPORTS ADD IT,
			if (allsports.find(sport) == allsports.end()) {
				Sport* newsport = new Sport(sport);
				allsports[sport] = newsport;
			}

			//IF COUNTRY NOT IN ALLCOUNTRIES ADD IT 

			if (allcountries.find(compcountry) == allcountries.end()) {
				Country* newcountry = new Country(compcountry);
				allcountries[compcountry] = newcountry;

			}

			//IF DISCIPLINE NOT IN ALLDISCIPLIENS ADD IT
			if (alldisciplines.find(discipline) == alldisciplines.end()) {
				Discipline* newdiscipline = new Discipline(discipline);
				alldisciplines[discipline] = newdiscipline;

			}



			//CREATE NEW PARTICIPATION
			Part* p;
			if (disctype == "Individual") {
				vector<int> athlete;
				athlete.push_back(atoi(ids.c_str()));
				
				p = new Part(0, alldisciplines[discipline], medal, year, allsports[sport], allcountries[compcountry], athlete);

				//ADD ATHLETE ID
				allathletes[atoi(ids.c_str())] = new Athlete(compcountry,medal);
			}
			else {
				vector<int>athletes;

				regex rx1("(\\d+)");
				sregex_iterator begin(ids.begin(), ids.end(), rx1);
				sregex_iterator end;
				while (begin != end) {
					smatch sm = *begin;
					int id = atoi(sm.str(1).c_str());

					allathletes[id] = new Athlete(compcountry,medal);
					athletes.push_back(id);
					begin++;
				}

				p = new Part(1, alldisciplines[discipline], medal, year, allsports[sport], allcountries[compcountry], athletes);
			

			}

			//ADD PARTICIPATION
			allparticipations.push_back(p);
			allsports[sport]->addParticipation(p);
			allcountries[compcountry]->addParticipation(p);
			allgames[pair<int, string>(year, type)]->addParticipation(p);

			//cout << *p;
		}


	}
	//PARSE ATHLETES!!


	regex rx2("([\\d]*)!([^!]*)!([^!])!([^!]*)!([^!]*)!([^!]*)");
	ifstream file2(FILEATHLETES);

	while (getline(file2, textLine)) {
		smatch result;
		//cout << textLine;
		if (regex_match(textLine, result, rx2)) {
			int id = atoi(result.str(1).c_str());
			//if (!group && ( allathletes.find(id)== allathletes.end() ) ) continue;

			string name = result.str(2);
			string sex = result.str(3);
			int age;
			int height;
			int weight;
			if (result.str(4) != "NA") age = atoi(result.str(4).c_str());
			else age = 0;

			if (result.str(5) != "NA") height = atoi(result.str(5).c_str());
			else height = 0;

			if (result.str(6) != "NA") weight = atoi(result.str(6).c_str());
			else weight = 0;

			//Athlete* newathlete = new Athlete(id, name, sex, age, height, weight);
			Athlete* newathlete = allathletes[id];
			if(newathlete) newathlete->setparams(id, name, sex, age, height, weight);
			allathletes[id] = newathlete;

		}

	}



}

vector<Part*> OlimpicGames::filter(vector<Part*> participation, string sport, string country, int year, string type, string medal)
{

	vector<Part*> participationhelp = participation;

	//REMOVE ALL PARTICIPATIONS WHERE NOT SPORT
	if (sport != "") {
		Sport* s = new Sport(sport);
		auto itend = remove_if(participationhelp.begin(),participationhelp.end(), [&s](Part* p) {

			return *p->getSport() != *s;

			});
		participationhelp.erase(itend, participationhelp.end());

	}

	//REMOVE ALL PARTICIPATION WHERE NOT YEAR
	if (year != 0) {
		auto itend = remove_if(participationhelp.begin(), participationhelp.end(), [&year](Part* p) {

			return p->getYear() != year;

			});
		participationhelp.erase(itend, participationhelp.end());

	}
	//REMOVE ALL PARTICIPATION WHERE NOT COUNTRY
	if (country != "") {
		Country* c = new Country(country);
		auto itend = remove_if(participationhelp.begin(), participationhelp.end(), [&c](Part* p) {

			return *p->getCountry() != *c;

			});
		participationhelp.erase(itend, participationhelp.end());

	}
	//REMOVE ALL PARTICIPATION WHERE NOT TYPE
	if (type != "") {

		auto itend = remove_if(participationhelp.begin(), participationhelp.end(), [type](Part* p) {
			if (type == "Team") {
				return !p->getTeam();
			}
			else return p->getTeam();

			});
		participationhelp.erase(itend, participationhelp.end());

	}
	//REMOV ALL PARTICIPATION WHERE NOT MEDAL
	if (medal != "") {
		auto itend = remove_if(participationhelp.begin(), participationhelp.end(), [medal](Part* p) {

			return p->getMedal() != medal;

			});
		participationhelp.erase(itend, participationhelp.end());
	}

	return participationhelp;
}



int OlimpicGames::numOfContestants(string sport, string country, int year, string type, string medal)
{
	set<int> athletesset;

	vector<Part*> participationhelp=filter(allparticipations,sport,country,year,type,medal);
	

	for_each(participationhelp.begin(), participationhelp.end(), [&athletesset](Part* p) {
		vector<int> ath = p->getAthletes();
		for (int i : ath) {
			athletesset.insert(i);
		}
		

		});


	return athletesset.size();

}

int OlimpicGames::numOfDisciplines(string sport, string country, int year, string type, string medal)
{
	set<Discipline*> disciplinesset;
	vector<Discipline*> disciplineshelp;

	vector<Part*> participationhelp = filter(allparticipations, sport, country, year, type, medal);

	for_each(participationhelp.begin(), participationhelp.end(), [&disciplinesset](Part* p) {
		//vector<int> ath = p->getAthletes();
		disciplinesset.insert(p->getDiscipline());

		});



	return disciplinesset.size();

}

float OlimpicGames::avgHeight(string sport, string country, int year, string type, string medal)
{

	set<int> athletesset;

	vector<Part*> participationhelp = filter(allparticipations, sport, country, year, type, medal);


	for_each(participationhelp.begin(), participationhelp.end(), [&athletesset](Part* p) {
		vector<int> ath = p->getAthletes();
		for (int i : ath) {
			athletesset.insert(i);
		}


		});
	int d = athletesset.size();
	int height = 0;
	for (int i : athletesset) {
		Athlete* a= allathletes[i];
		height += a->getHeight();
		if (a->getHeight() == 0) d--;


	}
	return height*1.0/d;

}
float OlimpicGames::avgWeight(string sport, string country, int year, string type, string medal)
{

	set<int> athletesset;

	vector<Part*> participationhelp = filter(allparticipations, sport, country, year, type, medal);


	for_each(participationhelp.begin(), participationhelp.end(), [&athletesset](Part* p) {
		vector<int> ath = p->getAthletes();
		for (int i : ath) {
			athletesset.insert(i);
		}


		});
	int d = athletesset.size();
	int weight = 0;
	for (int i : athletesset) {
		auto it = allathletes.find(i);
		if (it != allathletes.end()) {
			weight += it->second->getWeight();

		}
		if (it->second->getWeight() == 0) d--;


	}
	return weight*1.0 / d;

}

int OlimpicGames::numOfSportsMedal(Country* c)
{

	set<Sport*> sports;

	vector<Part*> participationhelp = filter(allparticipations, "", c->getName());

	for (Part* p : participationhelp) {
		if (p->getMedal() != "none") sports.insert(p->getSport());

	}




	return sports.size();
}

map<Country*, Athlete*> OlimpicGames::pairsMedalIndGroup()
{
	set <Athlete*> athletes1;
	set<int>athletesint1;
	set<int>athletesint2;
	set <Athlete*> athletes2;
	vector<Part*> participationhelp1g = filter(allparticipations, "", "", 0,"Team","Gold");
	vector<Part*> participationhelp1s = filter(allparticipations, "", "", 0,"Team","Silver");
	vector<Part*> participationhelp1b = filter(allparticipations, "", "", 0,"Team","Bronze");


	vector<Part*> participationhelp2g = filter(allparticipations, "", "",0,"Individual","Gold");
	vector<Part*> participationhelp2s = filter(allparticipations, "", "",0,"Individual","Silver");
	vector<Part*> participationhelp2b = filter(allparticipations, "", "",0,"Individual","Bronze");
	//ADD ALL ATHLETES THAT WON MEDAL TEAM
	for (auto p : participationhelp1g) {
		for (int i : p->getAthletes()) {
			vector<int> ath = p->getAthletes();
			for (int i : ath) {
				athletesint1.insert(i);
			}
			//athletesint1.insert(allathletes[i]);
		}

	}
	for (auto p : participationhelp1s) {
		for (int i : p->getAthletes()) {
			vector<int> ath = p->getAthletes();
			for (int i : ath) {
				athletesint1.insert(i);
			}
		}

	}
	for (auto p : participationhelp1b) {
		for (int i : p->getAthletes()) {
			vector<int> ath = p->getAthletes();
			for (int i : ath) {
				athletesint1.insert(i);
			}
		}

	}

	//ADD ALL ATHLETES THAT WON MEDAL INDIVIDUAL
	for (auto p : participationhelp2g) {
		for (int i : p->getAthletes()) {
			vector<int> ath = p->getAthletes();
			for (int i : ath) {
				athletesint2.insert(i);
			}
		}

	}
	for (auto p : participationhelp2s) {
		for (int i : p->getAthletes()) {
			vector<int> ath = p->getAthletes();
			for (int i : ath) {
				athletesint2.insert(i);
			}
		}

	}
	for (auto p : participationhelp2b) {
		for (int i : p->getAthletes()) {
			vector<int> ath = p->getAthletes();
			for (int i : ath) {
				athletesint2.insert(i);
			}
		}

	}

	set<int> finalint;
	set<Athlete*> final;
	set_intersection(athletesint1.begin(), athletesint1.end(), athletesint2.begin(), athletesint2.end(), inserter(finalint, finalint.begin()));

	for (int i : finalint) {
		if(allathletes[i]) final.insert(allathletes[i]);
	}

	map<Country*, Athlete*> result;
	cout << "--------------------------" << endl;
	for (auto a : final) {
		//result.insert(pair<Country*, Athlete*>(new Country(a->getcountry()), a));
		result[new Country(a->getcountry())] = a;
		//cout << a->getcountry()<<" - ";
		//cout << *a <<endl;
	}

	for (auto a : result) {
		cout << a.first->getName() << " - " << *a.second<<endl;
	}
	cout << "--------------------------" << endl;
	

	return result;
}

bool comparePart(Part* p1, Part* p2)
{
	return p1->getYear()<p2->getYear();
}

bool compareAthletes(Athlete* a1, Athlete* a2) {
	return a1->getAge() < a2->getAge();

}
vector<Athlete*> OlimpicGames::tenYoungest()
{
	set<int> athleteshelp;
	vector<Athlete*> athletes;
	map<Athlete*, string> athlmedal;

	vector<Part*> participhelp(allparticipations);
	sort(participhelp.begin(), participhelp.end(), comparePart);

	for (auto p : participhelp) {
		
		vector<int> ath = p->getAthletes();
		for (int i : ath) {

			//if(athleteshelp.find(i)==athleteshelp.end()) athleteshelp.insert(i);
			if (athlmedal.find(allathletes[i]) == athlmedal.end()) {
				athlmedal[allathletes[i]] = p->getMedal();
			}
		
		}

	}

	for (auto p : athlmedal) {
		if (p.first->getAge()!=0 && p.second != "none") {
			athletes.push_back(p.first);
		}

	}
	
	sort(athletes.begin(), athletes.end(), compareAthletes);
	int i = 0;
	for (auto a : athletes) {
		if (a->getAge() && i != 10) cout << *a, i++;
		if (i == 10) break;
	}

	return athletes;
}

vector<Athlete*> OlimpicGames::participatedInPairOfGames(int y1,string t1,int y2,string t2)
{
	set<int> athletesset1;
	set<int> athletesset2;

	vector<Athlete*> result;


	Game* g1 = allgames[pair<int,string>(y1,t1)];
	Game* g2 = allgames[pair<int,string>(y2,t2)];
	if (!g1 || !g2) { cout << "Invalid Olimpic Games!"; return result; }
	vector<Part*> participationhelp1 = filter(allparticipations,"", "", g1->getYear());
	vector<Part*> participationhelp2 = filter(allparticipations,"", "", g2->getYear());
	
	for_each(participationhelp1.begin(), participationhelp1.end(), [&athletesset1](Part* p) {
		vector<int> ath = p->getAthletes();
		for (int i : ath) {
			athletesset1.insert(i);
		}


		});

	for_each(participationhelp2.begin(), participationhelp2.end(), [&athletesset2](Part* p) {
		vector<int> ath = p->getAthletes();
		for (int i : ath) {
			athletesset2.insert(i);
		}


		});

	set<int> finalathletesset;
	set_intersection(athletesset1.begin(), athletesset1.end(), athletesset2.begin(), athletesset2.end(), inserter(finalathletesset, finalathletesset.begin()));


	for (int i : finalathletesset) {
		for (auto p : allathletes) {
			if (p.first == i) result.push_back(p.second);
		}


	}


	return result;
}

set<string> OlimpicGames::cities()
{
	set<string> cities;

	for (auto p : allgames) {
		cities.insert(p.second->getCity());
	}

	return cities;
}

vector<pair<Country*, tuple<int, int, int>>> OlimpicGames::threeBestCountries(int y, string t)
{
	pair<int, string> game(y, t);
	Game* g = allgames[game];
	map<Country*, tuple<int, int, int>> medals;
	vector < pair<Country*, tuple<int, int, int>>> resvector;
	if (!g) {
		cout << "Olimpic game not valid" << endl;
		return resvector ;
	}
	vector<Part*> parts = g->getParticipations();

	
	for (auto p : parts) {
		string med = p->getMedal();
		if (med == "Gold") {
			get<0>(medals[p->getCountry()])++;
		}
		else if (med == "Silver") {
			get<1>(medals[p->getCountry()])++;
		}
		else if (med == "Bronze") {
			get<2>(medals[p->getCountry()])++;
		}
	}



	for (auto a : medals) {
		resvector.push_back(a);
	}
	sort(resvector.begin(), resvector.end(), [](auto p1, auto p2) {

		tuple<int, int, int> t1 = p1.second, t2 = p2.second;
		if (get<0>(t1) == get<0>(t2))
			if (get<1>(t1) == get<1>(t2))
				return get<2>(t1) > get<2>(t2);

			else return get<1>(t1) > get<1>(t2);

		else return get<0>(t1) > get<0>(t2);

		});
	resvector.erase(resvector.begin() + 3, resvector.end());

	return resvector;
}

void OlimpicGames::allTeams(Country* c, int year, string t)
{
	pair<int, string> game(year, t);
	Game* g = allgames[game];
	if (!g) { cout << "Invalid game"; return; }
	vector<Part*> parts = filter(g->getParticipations(),"",c->getName(),0,"Team");

	sort(parts.begin(), parts.end(), [](Part* p1, Part* p2) {return *p1->getDiscipline() < *p2->getDiscipline(); });
	sort(parts.begin(), parts.end(), [](Part* p1, Part* p2) {return p1->getAthletes().size() > p2->getAthletes().size(); });
	
	for (auto p : parts) {
		for (auto a : p->getAthletes()) {
			cout << a<<" ";
		}
		cout << p->getAthletes().size();
		cout << " ";
		cout << *p->getDiscipline();
		cout << endl;

	}


}

void OlimpicGames::countriesBestAtLeastOnce()
{

	set<Country*> countries;
	vector<pair<Country*, tuple<int, int, int>>> winners;
	for (auto a : allgames) {
		winners = threeBestCountries(a.first.first, a.first.second);
		
		countries.insert(winners[0].first);
		if (winners[1].second == winners[0].second) countries.insert(winners[1].first);
		if (winners[2].second == winners[0].second) countries.insert(winners[2].first);


	}

	for (auto c : countries) {
		cout << *c;
	}

}
