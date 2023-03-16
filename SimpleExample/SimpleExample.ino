/*
 Name:		SimpleExample.ino
 Created:	3/16/2023 2:51:46 PM
 Author:	jiaji
*/

#include <SD.h>
#include "FileUtility.h"

void listFiles(FileUtility& testItem);

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(115200);
	SD.begin();

	Serial.println("Beginning SD tests...");

	FileUtility testItem(SD, SD.open("/"));

	listFiles(testItem);
}

// the loop function runs over and over again until power down or reset
void loop()
{
}

void listFiles(FileUtility& testItem)
{
	Serial.println("Listing all files:");
	uint64_t filesCount = 0;
	DirectoryIteratorCallback listDir = [&](File& entry)
	{
		++filesCount;
		Serial.printf("%llu : %s", filesCount, entry.path());
	};

	testItem.forEachFile(listDir);
	Serial.printf("-----Test End-----\n\n");
}
