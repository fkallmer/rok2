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


#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;

class MyClient : public TCPclient{
public:
	void makepwd();
	void guess(int l);
	~MyClient();
	int getpwdlength();

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
	string msg;
	string pwdLength,numberSymbols,pwd;



	//connect to host
	c.conn(host , 2026);
	c.makepwd();
	c.guess(c.getpwdlength());

}

void MyClient::makepwd(){
	string msg;
	char pwdLength[100],numberSymbols[100];
	std::cout<<"Passwortlänge: ";
	std::cin>>pwdLength;
	pwdlength = atoi(pwdLength);
	std::cout<<"Alphabethlänge: ";
	std::cin>>numberSymbols;
	msg = "makepwd[,]";
	msg.insert(8,pwdLength);
	msg.insert(10,numberSymbols);
	//cout<<"msg: "<<msg<<endl;
	sendData(msg);

	delete [] charSymbArray_;
	lengthSymbArray_ = atoi(numberSymbols);
	charSymbArray_ = new char [lengthSymbArray_ + 1];
	strncpy(charSymbArray_, TASK1::SYMBOLS.c_str(), lengthSymbArray_);
}
void MyClient::guess(int l){
	string msg,pwd;
	string response ="ACCESS ACCEPTED";


	/*
	std::cin>>pwd;
	msg.insert(4,pwd);
	msg.insert(strlen(msg.c_str())-1," ");
	cout<<"msg: "<<msg<<endl;
	sendData(msg);
	*/
	int symbolIdx;
	while(true){
		msg="pwd[]";
		pwd= string("");
		for(int i=0; i < l; i++){
			symbolIdx = rand() % lengthSymbArray_;
			pwd+= charSymbArray_[symbolIdx];
		}
		msg.insert(4,pwd);
		msg.insert(strlen(msg.c_str())-1," ");
		sendData(msg);
		versuche++;
		msg=receive(32);
		std::cout<<"got response: "<<msg<<std::endl;
		if(msg.compare(response)==0){
			std::cout<<"Anzahl der Versuche: "<<versuche<<std::endl;
			break;
		}
	}

}



MyClient::~MyClient(){
	delete [] charSymbArray_;
}

int MyClient::getpwdlength(){
	return pwdlength;
}



