#include <iostream>
#include <fstream>
#include "unistd.h"
#include "cstring"

using namespace std;
void exec(string command);

int main(int argc, char* argv[]){
	string k2 = "Supersecretpassword";
	if (access("config.txt.nc", F_OK) == -1){
		exec(" rm pin.txt pin.txt.nc");
		if (argc!=4){
			cout << "need 3 parameters to init: keystorepath, keyid, passphrase" << endl;
			return -1;
		}

		string pin;
		cout << "enter new pin" << endl;
		cin >> pin;
		
		
		ofstream of("config.txt");
		of << argv[1] << endl << argv[2] << endl << argv[3];
		of.close();
		string c = "mcrypt -k " + k2 + pin +" -u config.txt"; 
		exec(c);

		ofstream of2("pin.txt");
		of2 << pin;
		of2.close();
		c = "mcrypt -k " + k2 + pin +" -u pin.txt"; 
		exec(c);
		exec(" rm pin.txt");
	}else{
		string pin;
		cout << "enter pin" << endl;
		cin >> pin;
		
		string c = "mcrypt -k " + k2 + pin +" -d pin.txt.nc"; 
		exec(c);
		ifstream file ("pin.txt");
		string truePin;
		getline(file, truePin);
		file.close();
		if(truePin.compare(pin)!=0){
			cout << "entered wrond pin" << endl;
			exec(" rm pin.txt");
			return -1;
		}
		exec("rm pin.txt");
		string songPath;
		cout << "write path to encrypted music file" << endl;
		cin >> songPath;
		

		c = "mcrypt -k " + k2 + pin +" -d config.txt.nc"; 
		exec(c);
		ifstream file2("config.txt");
		string kspath, keyid, pass;
		getline(file2, kspath);
		getline(file2, keyid);
		getline(file2, pass);
		file2.close();
		exec("rm config.txt");
		
		c = "";
		c+="mcrypt -k ";
		c+=pass;
		c+=" -d ";
		c+=kspath;
		c+="/";
		c+=keyid;
		c+=".nc  >/dev/null 2>&1 && ";
		c+="openssl enc -d -aes-256-cbc ";
		c+="-in ";
		c+= songPath ;
		c+= " -out ";
		c+= "./song.mp3" ;
		c+= " -pass file:"; 
		c+= kspath;
		c+= "/"; 
		c+= keyid;
		c+= "  >/dev/null 2>&1 && rm ";
		c+=kspath;
		c+="/";
		c+=keyid;

		//cout << c << endl;
		exec(c);

		system("play ./song.mp3");
		exec("rm ./song.mp3");

	}
}

void exec(string command){
	string com = command+" >/dev/null 2>&1";
	const char* c = com.c_str();
	system(c);
}
