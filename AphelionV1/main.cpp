#include "main.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <SFML/Audio.hpp>

#pragma comment(lib, "Winmm.lib")

using namespace std;

vector<string> loginText;
vector<string> mainMenuText;

int main() {
	login();
	mainmenu();

	//Program should never reach this point, this ends the program.
	return 0;
}

//Login screen
void login() {

	loginText.push_back("_______________________________________________________________________________");
	loginText.push_back("|     ___      .______    __    __   _______  __       __    ______   .__   __.|");
	loginText.push_back("|    /   \\     |   _  \\  |  |  |  | |   ____||  |     |  |  /  __  \\  |  \\ |  ||");
	loginText.push_back("|   /  ^  \\    |  |_)  | |  |__|  | |  |__   |  |     |  | |  |  |  | |   \\|  ||");
	loginText.push_back("|  /  /_\\  \\   |   ___/  |   __   | |   __|  |  |     |  | |  |  |  | |  . `  ||");
	loginText.push_back("| /  _____  \\  |  |      |  |  |  | |  |____ |  `----.|  | |  `--'  | |  |\\   ||");
	loginText.push_back("|/__/     \\__\\ |__|      |__|  |__| |_______||_______||__|  \\______/  |__| \\__||");
	loginText.push_back("|______________________________________________________________________________|");
	loginText.push_back("								     Version 0.1");

	textPrinter(loginText, 1, 0);

	string password;
	cout << "Please enter your password: ";
	char ch = _getch();

	//Get password characters, end when 13 (Enter) is pressed.
	while (ch != 13) {
		
		if (ch == 27) {
			exit(0);
		}

		password += ch;
		cout << "*";
		ch = _getch();
	}

	cout << endl;

	//Compare to encrypted password, do not store real password.
	if (passEncryptor(password) == "Vfzjpn~") {
		cout << "Access granted.";
	}
	else {
		cout << "Access denied.";
		while (_getch() != 13) {

		}
		exit(0);
	}
}

//Main menu
void mainmenu() {

	system("CLS");

	sf::Music mainMenuMusic;
	if (!mainMenuMusic.openFromFile("C:/Users/Arnoud/Documents/AphOS/Music/MainMenu.wav"))
		return;
	mainMenuMusic.setLoop(true);

	mainMenuText.push_back("________________________________________________________________________________");
	mainMenuText.push_back("|      @@@@@@@@        @          @@@@             @@@@@@@@         @@@@       |");
	mainMenuText.push_back("|     @@@@@@@@@      @@@    @@    @@@@@@@         @@@@@@@@         @@@@@       |");
	mainMenuText.push_back("|     @@@@@@@@@@     @@@   @@@@   @@@@@@@         @@@@@@          @@@@@        |");
	mainMenuText.push_back("|    @@@     @@@@  @@@@     @@@       @@@        @@@@@ @@@@@     @@@@          |");
	mainMenuText.push_back("|    @@       @@@  @@@@     @@@   @    @@        @@@@@ @@@@@@   @@@@      @@   |");
	mainMenuText.push_back("|                  @@@       @@   @@     @@@@          @@@@@@   @@@ @     @@   |");
	mainMenuText.push_back("|                  @@@ @@@@@ @@   @@@ @  @@@@          @@@@@@   @@@ @@    @@   |");
	mainMenuText.push_back("|    @@       @@@  @@@@@@@@ @@@   @@@@@   @@@    @@@@@ @@@@@@   @@@ @@@   @@   |");
	mainMenuText.push_back("|    @@@     @@@@  @@@@@@@@ @@@    @@@@    @@    @@@@@ @@@@@     @@@@@@@ @@@   |");
	mainMenuText.push_back("|     @@@@@@@@@@     @@@@@@@@@@      @@@   @@@   @@@@@@          @@@    @@@@   |");
	mainMenuText.push_back("|     @@@@@@@@@      @@@@@@@@@       @@@@  @@@   @@@@@@@@         @@@@@@@@     |");
	mainMenuText.push_back("|      @@@@@@@@        @@@@@          @@@@ @@@    @@@@@@@@         @@@@@@@     |");
	mainMenuText.push_back("|______________________________________________________________________________|");
	mainMenuText.push_back("|                                   MAIN MENU                                  |");
	mainMenuText.push_back("| m) Toggle music 					       Exit AphOS (esc |");
	mainMenuText.push_back("| c) Enter command");

	textPrinter(mainMenuText, 0, 100);

	char input = _getch();
	while (true) {

		switch (input) {

		case 27:
			cout << "Exiting AphOS.";
			exit(0);
			break;

		case 'c':
			commandPrompt();
			break;

		case 'm':
			if (mainMenuMusic.getStatus() == 2) {
				mainMenuMusic.pause();
			}
			else {
				mainMenuMusic.play();
			}

			break;
		}

		input = _getch();
	}
}

//Encrypts password with a simple displacement cypher and a scrambler.
string passEncryptor(string password) {

	string encryptedPass = "";
	int scrambler = 1;

	for (unsigned int i = 0 ; i < password.size() ; i++) {
		encryptedPass += password.at(i) + 3 + scrambler++;
	}

	return encryptedPass;
}

//Prints out text with custom char and line delay.
void textPrinter(vector<string> printed, int charTime, int lineTime) {

	unsigned int counter = 0;

	while (counter < printed.size()) {
		for (unsigned int i = 0; i < printed[counter].size(); i++) {
			cout << printed[counter].at(i);
			Sleep(charTime);
		}
		counter++;
		cout << endl;
		Sleep(lineTime);
	}

	cout << endl;
}

enum commands {
	exitConsole,
	displayCommands,
	startTwitchBot,
};

void commandPrompt() {

	system("CLS");
	cout << "Enter command: ";

	string command;
	cin >> command;
	
	char wait;

	switch (hashCommand(command)) {

	case exitConsole:
		cout << "Exiting AphOS. Press any key to continue.";
		wait = _getch();
		exit(0);
		break;

	case displayCommands:
		cout << "Available commands: aphelionbot, help, exit. Press any key to continue.";
		wait = _getch();
		break;

	case startTwitchBot:
		cout << "Starting Aphelionbot." << endl;
		system("C:/Users/Arnoud/Documents/AphOS/Aphelionbot/main.py");
		break;

	default:
		cout << "Command not recognised. Press any key to continue.";
		wait = _getch();
		break;
	}

	system("CLS");
	textPrinter(mainMenuText, 0, 50);
}

commands hashCommand(string const& inString) {
	if (inString == "exit") return exitConsole;
	if (inString == "help") return displayCommands;
	if (inString == "aphelionbot") return startTwitchBot;
}