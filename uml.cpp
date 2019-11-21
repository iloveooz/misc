#pragma once
#include <vector>
#include "Man.h"
#include "IdCard.h"
#include "Room.h"
#include "Department.h"

class Employee : public Man {
public:
	Employee(std::string& name, std::string& surname, std::string& position, IdCard& card, Department& department) {
		name_ = name;
		surname_ = surname;
		position_ = position;
		iCard_ = card;
		department_ = department;
	}
	void setPosition(std::string& position) {
		position_ = position;
	}
	std::string getPosition() const {
		return position_;
	}
	void setIdCard(IdCard& card) {
		iCard_ = card;
	}
	 IdCard getIdCard() const {
		return iCard_;
	}
	 void setRoom(Room newRoom) {
		 rooms_.push_back(newRoom);
	 }
	 Room getRoom(unsigned int r) {
		 return rooms_[r];
	 }
	 void deleteRoom(unsigned int r) {
		 rooms_.erase[r];
	 }
	 void setDepartment(Department d) {
		 department_ = d;
	 }
	 Department getDepartment() {
		 return department_;
	 }
private:
	std::string position_;
	IdCard iCard_;
	std::vector<Room> rooms_;
	Department department_;
};

#pragma once
#include <iostream>

class Date {
public:
	Date(int day = 0, int month = 0, int year = 0) {
		setDate(day, month, year);
	}

	Date(const Date &date) {
		setDate(date.day_, date.month_, date.year_);
	}

	int getDay() const {
		return day_;
	}

	int getMonth() const {
		return month_;
	}

	int getYear() const {
		return year_;
	}

	void setDay(int day) {
		this->day_ = day;
	}

	void setMonth(int month) {
		this->month_ = month;
	}

	void setYear(int year) {
		this->year_ = year;
	}

	void setDate(int day, int month, int year) {
		setDay(day);
		setMonth(month);
		setYear(year);
	}

	void print() const {
		std::cout << day_ << '/' << month_ << '/' << year_ << std::endl;
	}

private:
	int day_;
	int month_;
	int year_;
};
#pragma once
#include "Date.h"

class IdCard {
public:
	IdCard() {}

	IdCard(int n) {
		number_ = n;
	}
	void setNumber(int newNumber) {
		number_ = newNumber;
	}
	int getNumber() const {
		return number_;
	}
	void setDateExpire(Date& newDateExpire) {
		dateExpire_ = newDateExpire;
	}
	Date getDateExpire() const {
		return dateExpire_;
	}
private:
	Date dateExpire_;
	int number_;
};
#pragma once
#include <string>

class Man {
public:
	void setName(std::string& newName) {
		name_ = newName;
	}
	std::string getName() const {
		return name_;
	}
	void setSurname(std::string& newSurname) {
		name_ = newSurname;
	}
	std::string getSurname() const {
		return surname_;
	}
protected:
	std::string name_;
	std::string surname_;
};
#pragma once
#include <string>
#include "Emplyee.h"

class Department {
public:
	Department(std::string n) {
		name = n;
	}
	void setName(std::string newName) {
		name = newName;
	}
	std::string getName() {
		return name;
	}
	void addEmployee(Employee newEmployee) {
		employees.push_back(newEmployee);
		// связываем сотрудника с этим отделом
		newEmployee.setDepartment(*this);
	}
	std::vector<Employee> getEmployees() const {
		return employees;
	}
	void removeEmployee(Employee e) {
		employees.erase(r);
	}
private:
	std::string name;
	std::vector<Employee> employees;
};
#pragma once

class Room {
public:
	Room(int number) {
		number_ = number;
	}
	void setNumber(int newNumber) {
		number_ = newNumber;
	}
	int getNumber() const {
		return number_;
	}
private:
	int number_;
};
#include <iostream>
#include "Man.h"
#include "Emplyee.h"

int main() {
	setlocale(LC_ALL, "Russian");

	std::string name = "Sasha";
	std::string surname = "Sashin";
	std::string position = "IT";

	IdCard card1(777);
	Date date(31, 12, 2019);
	
	Employee sysEngineer(name, surname, position, card1);

	IdCard card2(888);
	card2.setDateExpire(date);

	sysEngineer.setIdCard(card2);

	Room room101(101);
	Room room321(321);

	std::cout << sysEngineer.getName() << ' ' << sysEngineer.getSurname() << " работает в должности " << sysEngineer.getPosition() << ".\n";
	std::cout << "Удостоверение действует до ";

	sysEngineer.getIdCard().getDateExpire().print();

	sysEngineer.setRoom(room101);
	sysEngineer.setRoom(room321);

	std::cout << "Может находиться в помещениях: ";

	std::vector<Room>::iterator iter = sysEngineer.getRoom();
	while (iter.hasNext()) {
		System.out.println(((Room)iter.next()).getNumber());
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
