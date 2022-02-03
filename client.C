/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <string.h>
#include <cmath>
#include <cstring>


#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;

class MyClient : public TCPclient{
public:
	void makepwd(int len, int sym);
	void makepwdinput();
	void guessZufaellig();
	void guessSystematisch();
	void guess();
	~MyClient();

private:
	char * charSymbArray_;
	int lengthSymbArray_;
	int pwdlength;
	int versuche=0;

};

int main() {
	srand(time(NULL));
	MyClient c;
	string host = "localhost";
	char in;
	//connect to host
	c.conn(host , 2026);



	while(true){
		c.makepwdinput();
		c.guess();
		cout<<"Neues Passwort [1] \t Beenden [2]\n";
		do{
			cout<<"Eingabe: ";
			cin >>in;
			if(in != '1' && in != '2'){
				cout<<"Falscher Input!\n";
			}
		}while(in != '1' && in != '2');
		if(in == '2'){
			cout<<"send: "<<"BYEBYE";
			c.sendData(string("BYEBYE"));

			break;
		}
	}

}

void MyClient::makepwd(int len, int sym){
	string msg;
	int c;
	string pwdLength, numberSymbols;
	pwdLength = to_string(len);
	numberSymbols = to_string(sym);
	msg = "makepwd[,]";
	msg.insert(8,pwdLength);
	c= msg.find(',');
	msg.insert(c+1,numberSymbols);
	sendData(msg);

	pwdlength=len;
	delete [] charSymbArray_;
	lengthSymbArray_ = sym;
	charSymbArray_ = new char [lengthSymbArray_ + 1];
	strncpy(charSymbArray_, TASK1::SYMBOLS.c_str(), lengthSymbArray_);
}
void MyClient::guessZufaellig(){
	string msg,pwd;
	string response ="ACCESS ACCEPTED";

	int symbolIdx;
	while(true){
		msg="pwd[]";
		pwd= string("");
		for(int i=0; i < pwdlength; i++){
			symbolIdx = rand() % lengthSymbArray_;
			pwd+= charSymbArray_[symbolIdx];
		}
		cout<<"send: "<<pwd<<endl;
		msg.insert(4,pwd);
		msg.insert(strlen(msg.c_str())-1," ");
		sendData(msg);
		versuche++;
		msg=receive(32);
		std::cout<<"got response: "<<msg<<std::endl;
		if(msg.compare(response)==0){
			std::cout<<"Anzahl der Versuche: "<<versuche<<std::endl;
			return;
		}
	}

}
void MyClient::guessSystematisch()
{
	string s;
	char pwd [pwdlength];
	int szs = lengthSymbArray_;
	int szp = pwdlength;
	int g = pow(szs,szp);
	string response ="ACCESS ACCEPTED";
	string msg;

	for(int i = 0; i<g;i++)
	{

		for (int e = 0; e<szp;e++)
		{
			int o = pow(szs,szp-1-e);
			int mod = (i/o)%szs;
			pwd[e]= charSymbArray_[mod];

		}
		pwd[pwdlength]='\0';
		s = string(pwd);
		std::cout<<"send: "<<s<<std::endl;
		msg="pwd[]";

		msg.insert(4,s);
		msg.insert(strlen(msg.c_str())-1," ");
		sendData(msg);
		versuche++;
		msg=receive(32);
		std::cout<<"got response: "<<msg<<std::endl;
		if(msg.compare(response)==0){
			std::cout<<"Anzahl der Versuche: "<<versuche<<std::endl;
			return;
		}

	}
}

void MyClient::guess(){
	bool run=true;
	char in;
	versuche=0;
	cout<<"Welche Methode?\n1: Zufällig \t 2: Systematisch\n";
	cin>>in;
	while(run){
		if(in== '1' || in == '2'){
			run =false;
		}else{
				cout<<"Falscher Input!\n";
				cin>>in;
		}
	}
	if(in== '1'){
		guessZufaellig();
	}else{
		guessSystematisch();
	}
}

void MyClient::makepwdinput(){
	string msg, response ="Pwd erstellt";
	int x,y;
	char pwdLength[100],numberSymbols[100],numbers[]="1234567890";
	bool run = true;
	while(run){
		cout<<"Passwortlänge: ";
		cin>>pwdLength;
		x=strlen(pwdLength);
		y=strspn(pwdLength,numbers);
		while(x != y){
			cout<<"Falscher Input!\nPasswortlänge: ";
			cin>>pwdLength;
			x=strlen(pwdLength);
			y=strspn(pwdLength,numbers);
		}
		cout<<"Alphabethlänge: ";
		cin>>numberSymbols;
		x=strlen(numberSymbols);
		y=strspn(numberSymbols,numbers);
		while(x != y){
			cout<<"Falscher Input!\nAlphabethlänge: ";
			cin>>numberSymbols;
			x=strlen(numberSymbols);
			y=strspn(numberSymbols,numbers);
		}
		x = atoi(pwdLength);
		y = atoi(numberSymbols);

		makepwd(x,y);
		msg=receive(32);
		cout<<"got response: "<<msg<<endl;
		if(msg.compare(response)==0){
			run = false;
		}

	}

	return;
}

MyClient::~MyClient(){
	delete [] charSymbArray_;
}
