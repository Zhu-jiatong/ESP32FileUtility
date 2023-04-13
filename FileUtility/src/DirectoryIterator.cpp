/*
 Name:		DirectoryIterator.cpp
 Created:	4/3/2023 11:46:45 AM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#include "FileUtility.h"

FileUtility::DirectoryIterator::DirectoryIterator(FileUtility& root, const char* openMode)
	:m_openMode(openMode), m_root(&root)
{
	File& internalFile = *m_root;

	if (!internalFile.isDirectory())
		throw std::runtime_error("Is not directory");

	m_entryFile = internalFile.openNextFile(m_openMode);
}

FileUtility::DirectoryIterator::DirectoryIterator()
{
}

FileUtility::DirectoryIterator::reference FileUtility::DirectoryIterator::operator*()
{
	m_entry = std::make_shared<FileUtility>(*m_root->m_fs, m_entryFile);
	return *m_entry;
}

FileUtility::DirectoryIterator& FileUtility::DirectoryIterator::operator++(int)
{
	DirectoryIterator temp(*this);
	operator++();
	return temp;
}

FileUtility::DirectoryIterator::pointer FileUtility::DirectoryIterator::operator->()
{
	return m_entry.get();
}

FileUtility::DirectoryIterator& FileUtility::DirectoryIterator::operator++()
{
	File& internalFile = *m_root;
	m_entryFile = internalFile.openNextFile(m_openMode);
	return *this;
}

bool FileUtility::DirectoryIterator::operator==(const DirectoryIterator& other) const
{
	return m_entryFile == other.m_entryFile;
}

bool FileUtility::DirectoryIterator::operator!=(const DirectoryIterator& other) const
{
	return !operator==(other);
}

FileUtility::DirectoryIterator FileUtility::DirectoryIterator::begin()
{
	return *this;
}

FileUtility::DirectoryIterator FileUtility::DirectoryIterator::end()
{
	return DirectoryIterator();
}