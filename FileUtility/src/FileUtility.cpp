/*
 Name:		FileUtility.cpp
 Created:	3/16/2023 2:49:45 PM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#include "FileUtility.h"

FileUtility::FileUtility(FS& fs, File* file)
	:m_fs(&fs), m_file(file)
{
}

FileUtility::FileUtility(FS& fs, File& file)
	:m_fs(&fs), m_file(&file, [](File* ptr) {})
{
}

FileUtility::FileUtility(FS& fs, const char* path)
	:m_fs(&fs)
{
	File temp = m_fs->open(path);

	if (!temp)
		throw std::runtime_error("File cannot be opened");

	m_file = std::make_shared<File>(temp);
}

FileUtility FileUtility::parent()
{
	String path = m_file->path();
	int lastIndex = path.lastIndexOf('/');
	if (lastIndex == -1)
		throw std::runtime_error(("\"" + path + "\" has no parent path").c_str());
	if (lastIndex == 0)
		return { *m_fs, "/" };
	return { *m_fs, path.substring(0, lastIndex).c_str() };
}

FileUtility::operator File& ()
{
	return *m_file;
}

FileUtility::DirectoryIterator& FileUtility::iterateDirectory(const char* openMode)
{
	m_DirectoryIterator.reset(new DirectoryIterator(*this, openMode));
	return *m_DirectoryIterator;
}
