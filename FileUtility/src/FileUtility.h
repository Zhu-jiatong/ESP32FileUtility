/*
 Name:		FileUtility.h
 Created:	3/16/2023 2:49:45 PM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#ifndef _FileUtility_h
#define _FileUtility_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <FS.h>
#include <functional>
#include <stack>

using DirectoryIteratorCallback = std::function<void(File&)>;

class FileUtility
{
public:
	FileUtility(FS& fs, File file);
	~FileUtility();

	operator File& ();
	operator bool() const;

	void forEachFile(DirectoryIteratorCallback f);
	void forEachFileRecursive(DirectoryIteratorCallback f);
	bool renameTo(const String& newName);
	bool moveTo(const String& pathTo);
	bool del();

private:
	FS& m_fs;
	File m_file;
	bool m_isInitialised;
};

#endif

