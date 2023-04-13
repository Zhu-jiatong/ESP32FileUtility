/*
 Name:		SimpleExample.ino
 Created:	3/16/2023 2:51:46 PM
 Author:	jiaji
*/

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
	rootDir.initDirectoryIterator();
	for (auto it = rootDir.begin(); it != rootDir.end(); ++it)
		Serial.println(static_cast<File&>(*it).path());

	Serial.println("RANGE");
	rootDir.initDirectoryIterator();
	for (auto& entry : rootDir)
		Serial.println(static_cast<File&>(entry).path());

	Serial.println("EACH");
	rootDir.initDirectoryIterator();
	std::for_each(rootDir.begin(), rootDir.end(),
		[](FileUtility& entry) {Serial.println(static_cast<File&>(entry).path()); });

	Serial.println("Range & parent directory");
	File subFolder=SD.open("/Private/Video");
	FileUtility subDir(SD, subFolder);
	subDir.initDirectoryIterator();
	for (auto& entry : subDir)
	{
		File& a = entry;
		Serial.println(a.path());

		File b = entry.parent().parent();
		Serial.println(b.path());
	}
	Serial.println("END TEST");
}

// the loop function runs over and over again until power down or reset
void loop()
{
}
