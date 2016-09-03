#pragma once
#include <string>
#include <vector>

int main();

void login();

void mainmenu();

void textPrinter(std::vector<std::string> printed, int charTime, int lineTime);

void commandPrompt();

enum commands;

commands hashCommand(std::string const& inString);

std::string passEncryptor(std::string password);