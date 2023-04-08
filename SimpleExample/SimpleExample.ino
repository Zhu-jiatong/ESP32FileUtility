/*
 Name:		SimpleExample.ino
 Created:	3/16/2023 2:51:46 PM
 Author:	jiaji
*/

#include "DirectoryIterator.h"
#include "DirectoryIterator.h"
#include <SD.h>
#include "FileUtility.h"

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(115200);
	SD.begin();

	Serial.println("Beginning SD tests...");
	Serial.println("RAW");
	FileUtility rootDir(SD, "/");
	for (auto it = rootDir.iterateDirectory().begin(); it != rootDir.iterateDirectory().end(); ++it)
		Serial.println(static_cast<File&>(*it).path());
	static_cast<File&>(rootDir).rewindDirectory();
	Serial.println("RANGE");
	for (auto entry : rootDir.iterateDirectory())
	{
		Serial.println(static_cast<File&>(entry).path());
	}
	static_cast<File&>(rootDir).rewindDirectory();
	Serial.println("EACH");
	auto& iterator = rootDir.iterateDirectory();
	std::for_each(iterator.begin(), iterator.end(),
		[](FileUtility entry) {Serial.println(static_cast<File&>(entry).path()); });
	Serial.println("END TEST");
}

// the loop function runs over and over again until power down or reset
void loop()
{
}
