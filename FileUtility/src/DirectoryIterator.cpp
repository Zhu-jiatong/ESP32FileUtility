/*
 Name:		DirectoryIterator.cpp
 Created:	4/3/2023 11:46:45 AM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#include "FileUtility.h"

FileUtility::DirectoryIterator::DirectoryIterator(FileUtility& root, const char* openMode)
	:m_openMode(openMode), m_root(root)
{
	File& internalFile = static_cast<File&>(m_root);

	if (!internalFile.isDirectory())
		throw std::runtime_error("Is not directory");

	m_entry = internalFile.openNextFile(m_openMode);
}

FileUtility::DirectoryIterator::DirectoryIterator(FileUtility& root)
	:m_root(root)
{
}

FileUtility::DirectoryIterator::value_type FileUtility::DirectoryIterator::operator*()
{
	return FileUtility(*m_root.m_fs, m_entry);
}

FileUtility::DirectoryIterator::value_type FileUtility::DirectoryIterator::operator->()
{
	return **this;
}

FileUtility::DirectoryIterator& FileUtility::DirectoryIterator::operator++()
{
	File& internalFile = static_cast<File&>(m_root);
	m_entry = internalFile.openNextFile(m_openMode);
	return *this;
}

bool FileUtility::DirectoryIterator::operator!=(const DirectoryIterator& other)const
{
	return m_entry != other.m_entry;
}

FileUtility::DirectoryIterator FileUtility::DirectoryIterator::begin()
{
	return *this;
}

FileUtility::DirectoryIterator FileUtility::DirectoryIterator::end()
{
	return DirectoryIterator(m_root);
}