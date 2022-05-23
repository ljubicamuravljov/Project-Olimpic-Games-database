#pragma once


class Athlete {

	int id;
	string name;
	string sex;
	int age;
	int height;
	int weight;
	string country;
	string medal;

public:
	Athlete(string country,string medal):country(country),medal(medal) {}
	//Athlete(int i,string n,string s,int a,int h,int w): id(i),name(n),sex(s),age(a),height(h),weight(w){}
	void setparams(int i, string n, string s, int a, int h, int w) {
		id = i;
		name = n;
		sex = s;
		age = a;
		height = h;
		weight = w;

	}
	friend ostream& operator<<(ostream& os, const Athlete& a) {
		os << a.id << " " << a.name << " " << a.age << " " << a.height << " " << a.weight ;
		return os;

	}

	bool operator==(const Athlete& a) {
		return id = a.id;
	}
	int getHeight() const { return height; }
	int getWeight() const { return weight; }
	int getAge() const { return age; }
	string getmedal() const { return medal; }
	string getcountry() const { return country; }

};