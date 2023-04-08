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

class FileUtility
{
public:
	FileUtility(FS& fs, File* file);
	FileUtility(FS& fs, File& file);
	FileUtility(FS& fs, const char* path);

	FileUtility parent();
	operator File& ();

	class DirectoryIterator;
	DirectoryIterator& iterateDirectory(const char* openMode = FILE_READ);

private:
	FS* m_fs = nullptr;
	std::shared_ptr<File> m_file;
	std::unique_ptr<DirectoryIterator> m_DirectoryIterator;
};

class FileUtility::DirectoryIterator
{
public:
	using iterator_category = std::input_iterator_tag;
	using value_type = FileUtility;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;

	DirectoryIterator(FileUtility& root, const char* openMode);
	DirectoryIterator(FileUtility& root);
	DirectoryIterator begin();
	DirectoryIterator end();
	DirectoryIterator& operator++();
	bool operator!=(const DirectoryIterator& other) const;
	value_type operator*();
	value_type operator->();

private:
	FileUtility& m_root;
	File m_entry;
	const char* m_openMode = nullptr;
};

#endif
