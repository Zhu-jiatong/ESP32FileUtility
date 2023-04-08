/*
 Name:		DirectoryIterator.cpp
 Created:	4/3/2023 11:46:45 AM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#include "FileUtility.h"

FileUtility::DirectoryIterator::DirectoryIterator(const FileUtility& root, const char* openMode)
	:m_root(root)
{
	File rootInternal = root;
	if (!root)
		throw (std::string(root.path()) + " is invalid");
	if (!root.isDirectory())
		throw std::runtime_error(std::string(root.path()) + " is not a directory");

	m_openMode = openMode;
	m_entry = root.openNextFile(m_openMode);
}

FileUtility::DirectoryIterator& FileUtility::DirectoryIterator::operator++()
{
	m_entry = m_root.openNextFile(m_openMode);
	return *this;
}

FileUtility::DirectoryIterator FileUtility::DirectoryIterator::operator++(int)
{
	DirectoryIterator temp(*this);
	++(*this);
	return temp;
}

bool FileUtility::DirectoryIterator::operator==(const DirectoryIterator& rhs)
{
	return m_entry == rhs.m_entry;
}

FileUtility::DirectoryIterator::reference FileUtility::DirectoryIterator::operator*()
{
	return m_entry;
}
