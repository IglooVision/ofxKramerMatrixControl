#pragma once

#include "ofxNetwork\src\ofxNetwork.h"
#include "ofxXmlSettings.h"


class ofxKramerMatrixControl
{

public:
	//A log function that prints in the console window and saves on a log file
	static void logEverywhere(string logMessage);

	ofxKramerMatrixControl();
	~ofxKramerMatrixControl();

	//Sets up the connections by directly connecting to the Kramer matrix
	//It uses a direct Ethernet connection with the Kramer matrix
	void setupKramerConnection();

	//Loads the XML settings from KramerMatrixSettings.xml
	void loadXmlSettings(string path);

	//A function to switch between different commands set in the XML file
	void sendCommand(int commmandIndex);

	//A function to switch between presets in the Kramer Matrix
	void sendSwitchPresetCommand(int presetIndex);

private:




	ofxXmlSettings			xml;
	ofxTCPClient			kramerConnection;
	int						port;

	string					kramerIP;

	vector<string>			krammerCommands;

};