/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <iostream>

#include "SIMPLESOCKET.H"
#include "TASK1.H"

class MyServer : public TCPserver{
public:
	MyServer(int portNmb, int maxSizeData) : TCPserver(portNmb,maxSizeData){
		box=new TASK1::BlackBoxSafe(4,4);
	};

protected:
	string myResponse(string inputStr);
	TASK1::BlackBoxSafe *box;


};

int main(){
	srand(time(nullptr));
	MyServer srv(2026,25);
	srv.run();
}

string MyServer::myResponse(string inputStr){
	char pwd[101];
	int pwdLength = 4, numberSymbols=4;
	string response;


	if(sscanf(inputStr.c_str(),"makepwd[%i,%i]",&pwdLength,&numberSymbols)){
		if(pwdLength < 4){
			std::cout <<"Mindest Passwordtlänge ist gleich 4!"<<std::endl;
			response="Mindest Passwordtlänge ist gleich 4!";
		}else if(pwdLength > 99){
			std::cout <<"Maximale Passwortlänge überschritten (max. 100)!"<<std::endl;
			response="Maximale Passwortlänge überschritten (max. 100)!";
		}else if(numberSymbols <= 0 || numberSymbols >= 63){
			std::cout <<"Fehler! Anzahl der Symbole muss zwischen 1 und 62 sein!"<<std::endl;
			response="Fehler! Anzahl der Symbole muss zwischen 1 und 62 sein!";
		}
		delete box;
		box=new TASK1::BlackBoxSafe(pwdLength,numberSymbols);

	}else if(sscanf(inputStr.c_str(),"pwd[%s]",pwd)){

		response=box->input(pwd);


	}else{
		response="Unknown Command!\n";
	}

	return response;
	/*
	if(inputStr.compare(0,4,"eins") == 0){
		return string("1");
	}else if(inputStr.compare(0,4,"zwei") == 0){
		return string("2");
	}else if(inputStr.compare(0,4,"drei") == 0){
		return string("3");
	}else if(inputStr.compare(0,4,"vier") == 0){
		return string("4");
	}else if(inputStr.compare(0,5,"fuenf") == 0){
		return string("5");
	}else if(inputStr.compare(0,5,"sechs") == 0){
		return string("6");
	}else if(inputStr.compare(0,6,"sieben") == 0){
		return string("7");
	}else if(inputStr.compare(0,4,"acht") == 0){
		return string("8");
	}else if(inputStr.compare(0,4,"neun") == 0){
		return string("9");
	}else if(inputStr.compare(0,4,"null") == 0){
		return string("0");
	}else{
		return string("UC");
	}
*/


}




