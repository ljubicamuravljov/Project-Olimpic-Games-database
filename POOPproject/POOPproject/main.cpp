#include "OlimpicGames.h"


#include "OlimpicGames.h"

int main() {
	OlimpicGames& OG = *OlimpicGames::getInstance();

	//OG.parse(1);

	//cout << "Num of Team competitors " << OG.numOfContestants()<<endl;

	////set<string> cities = OG.cities();

	////for (string s : cities) {

	////	cout << s << endl;

	////}
	//cout<<"Avg height: " << OG.avgHeight() << endl;
	//cout<<"Avg weight: " << OG.avgWeight() << endl;
	//cout << "Num of disciplines: " << OG.numOfDisciplines() << endl;
	//OG.tenYoungest();

	//for (auto a : OG.participatedInPairOfGames(1988, "Summer", 2016, "Summer")) {
	//	cout << *a;
	//}
	//cout << "Three Besto 1948" << endl;
	//OG.threeBestCountries(1948,"Winter");
	//cout << "Best at least once:" << endl;
	//OG.countriesBestAtLeastOnce();
	//OG.pairsMedalIndGroup();
	//cout << "Num of disciplines for Taekwondo " << OG.numOfDisciplines();
	while (1) {
		cout << "Chose input mode (type Group or Individual) :" << endl;
		string s;
		cin >> s;
		if (s == "Group") {
			OG.parse(1);
			break;
		}
		else if (s == "Individual") {
			cout << "Input wanted year: " << endl;
			int y;
			cin >> y;
			OG.parse(0, y);

			break;
		}
		else {
			cout << "ERROR: Invalid input mode"<<endl;
		}
	}
	int a;
	while (53) {

		cout << "\nMain Menu" << endl;
		cout << "------------" << endl;
		cout << "1.Number of competitors"<<endl;
		cout << "2.Number of disciplines"<<endl;
		cout << "3.Average Height"<<endl;
		cout << "4.Average Weight"<<endl;
		cout<< "5.Number of sports where given country won a medal" << endl;
		cout<< "6.Three best countries on given Olimpic Games" << endl;
		cout<< "7.Countries which were in best at leas once" << endl;
		cout << "8.Ten youngest competitors which won a medal at first participation" << endl;
		cout << "9.All pairs country-athlete for all athletes which won a medal in individual and team" << endl;
		cout << "10.All athletes which participated in both Olimpic Games" << endl;
		cout << "11.All teams which given country had at given Olimpic Games" << endl;
		cout << "12.All cities where Olimpic Games were held at least once" << endl;
		cout << "13.EXIT" << endl;
	
		cout << "Input choice: ";
		cin >> a;
		//cout << endl;
		set<string> cities;
		string helpstring;
		string helpstring1;
		vector<Athlete*> athletevector;
		int year;
		int year1;
		
		string sport;
		string country;
		string type;
		string medal;

		vector<pair<Country*, tuple<int, int, int>>> result;
		switch (a) {
		case 1:case 2: case 3: case 4:
			cout << "Filters:\n";

			cout << "\nSport: ";
			cin.ignore();
			getline(cin, sport);
			
			cout << "\nCountry: ";
			//cin.ignore();
			getline(cin, country);

			cout << "\nYear(Enter 0 if you don't want to filter by year): ";
			cin >> year;

			cout << "\nType(Individual/Team): ";
			cin.ignore();
			getline(cin, type);
			if (type != "Individual" && type != "Team" && type!="") { cout << "Invalid type!"; continue; }

			cout << "\nMedal(Gold,Silver,Bronze,none): ";
			//cin.ignore();
			getline(cin, medal);
			if (medal !="" && medal != "Gold" && medal != "Silver" && medal != "Bronze" && medal != "none") { cout << "Invalid medal! "; continue; }

			if (a == 1) {
				cout << "Number of contestants: ";
				cout << OG.numOfContestants(sport, country, year, type, medal);
			}
			else if (a == 2) {
				cout << "Number of disciplines: ";
				cout << OG.numOfDisciplines(sport, country, year, type, medal);
			}
			else if (a == 3) {
				cout << "Average height: ";
				cout << OG.avgHeight(sport, country, year, type, medal);
			}
			else if (a == 4) {
				cout << "Average weight: ";
				cout << OG.avgWeight(sport, country, year, type, medal);
			}
			break;
		
		case 5:
			cout << "\nInput country: " << endl;
			cin.ignore();
			getline(cin, helpstring, '\n');
			cout << "Number of sports where " << helpstring << " won a medal: " << OG.numOfSportsMedal(new Country(helpstring)) << endl;

			break;
		case 6:
			cout << "\nInput year of Olimpic Games: ";
			cin >> year;
			cout << "\nInput type of Olimpic Games (Summer/Winter): ";
			cin >> helpstring;
			if (helpstring != "Summer" && helpstring != "Winter") {
				cout << "Invalid Olimpic Game type" << endl;
				continue;
			}


			result = OG.threeBestCountries(year, helpstring);
			cout << "Three best countries: " << endl;
			for (auto a : result) {
				cout << *a.first;
			}

			break;
		case 7:
			cout << "\nCountries which were best at least once: " << endl;
			OG.countriesBestAtLeastOnce();

			break;
		case 8:
			cout << "\nTen youngest competitors: " << endl;
			OG.tenYoungest();
			break;
		case 9:
			cout << "\nCountries and Athletes which won at least 1 medal in group and individuals:" << endl;
			OG.pairsMedalIndGroup();

			break;
		case 10:
			cout << "\nInsert year of first Olimpic Game: ";
			cin >> year;

			cout << "\nInsert type of first Olimpic Game (Summer/Winter): ";
			cin >> helpstring;

			if (helpstring != "Winter" && helpstring != "Summer") { cout << "Invalid Olimpic Game type!\n"; continue; }

			cout << "\nInsert year of second Olimpic Game: ";
			cin >> year1;

			cout << "\nInsert type of second Olimpic Game (Summer/Winter): ";
			cin >> helpstring1;

			if (helpstring1 != "Winter" && helpstring1 != "Summer") { cout << "Invalid Olimpic Game type!\n"; continue; }

			athletevector = OG.participatedInPairOfGames(year, helpstring, year1, helpstring1);

			for (auto a : athletevector) {
				cout << *a;
			}


			break;
		case 11:

			cout << "Input country: ";
			cin.ignore();
			getline(cin, country);
			cout << "Input Olimpic year: ";
			cin >> year;
			cout << "Input Olimpic type(Summer/Winter): ";
			cin >> type;

			OG.allTeams(new Country(country), year, type);

			
			break;

		case 12:

			cout << "All cities: \n";
			cities = OG.cities();

			for (auto s : cities) {
				cout << s << endl;
			}

			break;
		case 13:
			exit(0);
		
			break;
		default:
			cout << "Invalid choice\n";

			break;
		
		}


	}
}