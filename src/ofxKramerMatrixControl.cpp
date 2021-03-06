#include "ofxKramerMatrixControl.h"

void ofxKramerMatrixControl::logEverywhere(string logMessage)
{
	cout << logMessage << endl;

	ofLogNotice() << logMessage << endl;
}

//--------------------------------------------------------------
ofxKramerMatrixControl::ofxKramerMatrixControl()
{
	logEverywhere("KRAMER CONTROL: class created");
}

//--------------------------------------------------------------
ofxKramerMatrixControl::~ofxKramerMatrixControl()
{

}

//--------------------------------------------------------------
void ofxKramerMatrixControl::setupKramerConnection(string path)
{
	cout << "KRAMER CONTROL: setupKramerConnection" << endl;

	cout << "KRAMER CONTROL: connecting to " << kramerIP << endl;

	loadXmlSettings(path);

	bool connected = kramerConnection.setup(kramerIP, port);

	if (!connected)
	{
		logEverywhere("Kramer couldn't connect");
	}

}

//--------------------------------------------------------------
//TODO: Check all possible string based Kramer commands
//--------------------------------------------------------------
void ofxKramerMatrixControl::sendSwitchPresetCommand(int commandIndex)
{

	bool connected = false;
	bool send = false;

	string command = "#PRST-RCL " + ofToString(commandIndex) + "\r\n";

	const char toSend[4] = {0x04,0x81,0x80,0x81};

	connected = kramerConnection.isConnected();

	if (connected)
	{		
	//	send = kramerConnection.sendRaw(command);
	//  send = kramerConnection.sendRaw("#PRST-RCL 2\r\n");
		send = kramerConnection.sendRawBytes(toSend,4);
	}
	else
	{
		connected = kramerConnection.setup(kramerIP, port);

		send = kramerConnection.sendRaw(command);
	}


	if (!connected)
	{
		logEverywhere("Couldn't connect to Kramer matrix");
	}
	if (!send)
	{
		logEverywhere("Couldn't send commands to Kramer matrix");
	}

}

//--------------------------------------------------------------
//TODO: Find an alternative for the hardcoded commands
//--------------------------------------------------------------
void ofxKramerMatrixControl::sendPresetHexadecimalCommands(int presetHexIndex)
{
	bool connected = false;
	bool send = false;

	connected = kramerConnection.isConnected();

	const char toSendPresetOne[4] = { 0x04,0x81,0x80,0x81 };
	const char toSendPresetTwo[4] = { 0x04,0x82,0x80,0x81 };
	
	switch (presetHexIndex)
	{
		case 1:
			 
			if (connected)
			{
				send = kramerConnection.sendRawBytes(toSendPresetOne, 4);
			}
			else
			{
				connected = kramerConnection.setup(kramerIP, port);

				send = kramerConnection.sendRawBytes(toSendPresetOne, 4);
			}
			break;
		case 2:
			
			if (connected)
			{
				send = kramerConnection.sendRawBytes(toSendPresetTwo, 4);
			}
			else
			{
				connected = kramerConnection.setup(kramerIP, port);

				send = kramerConnection.sendRawBytes(toSendPresetTwo, 4);
			}
			break;

	}

	if (!connected)
	{
		logEverywhere("Couldn't connect to Kramer matrix");
	}
	if (!send)
	{
		logEverywhere("Couldn't send commands to Kramer matrix");
	}

}

//--------------------------------------------------------------
void ofxKramerMatrixControl::sendCommand(int commmandIndex)
{

	//bool send = kramerConnection.sendRaw("#PRST-RCL 2\r\n");
	
	bool connected = false;
	bool send = false;
	if (!krammerCommands.empty())
	{
		string command = krammerCommands[commmandIndex] + "\r\n";

		if (kramerConnection.isConnected())
		{
			send = kramerConnection.sendRaw(command);
		}
		else
		{
			connected = kramerConnection.setup(kramerIP, port);

			send = kramerConnection.sendRaw(command);
		}


		if (!connected)
		{
			logEverywhere("Couldn't connect to Kramer matrix");
		}
		if (!send)
		{
			logEverywhere("Couldn't send commands to Kramer matrix");
		}
	}
	else
	{
		logEverywhere("No commands set in the settings file");
	}
	
}

//--------------------------------------------------------------
void ofxKramerMatrixControl::loadXmlSettings(string path)
{
	bool _isLoaded = xml.load(path);
	logEverywhere("Loading " + path);
	if (_isLoaded)
	{
		// load the communication port the standard one for Kramer matrix is 5000
		port = xml.getValue("Settings::port", 5000);
		logEverywhere("Port: " + ofToString(port));
		kramerIP = xml.getValue("Settings::kramerIP", "0");

		xml.pushTag("Settings");
		xml.pushTag("commands");

		int numberCommands = xml.getNumTags("command");
		krammerCommands.clear();

		for (int i = 0; i< numberCommands; i++)
		{
			xml.pushTag("command", i);
			string _IP = xml.getValue("commandString", "fail");
			krammerCommands.push_back(_IP);
			xml.popTag(); // pop command
		}
		xml.popTag(); // pop commands
		xml.popTag(); // pop Settings

	}
	else
	{
		string errMsg = "[ERROR] Projector Control - cannot load settings xml";
		logEverywhere(errMsg);
	}

}


