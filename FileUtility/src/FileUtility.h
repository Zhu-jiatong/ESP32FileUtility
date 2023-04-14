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
#include <memory>
#include "DirectoryIterator.h"

class FileUtility
{
public:
	FileUtility(FS& fs, File* file);
	FileUtility(FS& fs, File& file);
	FileUtility(FS& fs, const char* path);

	FileUtility parent();
	operator File& ();

	friend class DirectoryIterator;
	void initDirectoryIterator(const char* openMode = FILE_READ);
	DirectoryIterator begin();
	DirectoryIterator end();

private:
	FS* m_fs = nullptr;
	std::shared_ptr<File> m_file;
	std::unique_ptr<DirectoryIterator> m_DirectoryIterator;
};

#endif
