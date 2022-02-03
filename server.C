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
	int pwdLength, numberSymbols;
	string response;

	if(inputStr.compare("")==0){
		return string("");
	}
	if(sscanf(inputStr.c_str(),"makepwd[%i,%i]",&pwdLength,&numberSymbols)){
		if(pwdLength < 4){
			std::cout <<"Passlänge zu kurz! (min. 4)"<<std::endl;
			response="Passlänge zu kurz! (min. 4)";
			return response;
		}else if(pwdLength > 99){
			std::cout <<"Passlänge zu groß! (max. 100)"<<std::endl;
			response="Passlänge zu groß! (max. 100)";
			return response;
		}else if(numberSymbols < 1 || numberSymbols > 62){
			std::cout <<"Alphlänge falsch! (1-62)"<<std::endl;
			response="Alphlänge falsch! (1-62)";
			return response;
		}
		delete box;
		box=new TASK1::BlackBoxSafe(pwdLength,numberSymbols);
		response="Pwd erstellt";

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




