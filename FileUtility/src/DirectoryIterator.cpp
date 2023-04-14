/*
 Name:		DirectoryIterator.cpp
 Created:	4/3/2023 11:46:45 AM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#include "DirectoryIterator.h"
#include "FileUtility.h"

DirectoryIterator::DirectoryIterator(FileUtility& root, const char* openMode)
	:m_openMode(openMode), m_root(&root)
{
	File& internalFile = *m_root;

	if (!internalFile.isDirectory())
		throw std::runtime_error("Is not directory");

	m_entryFile = internalFile.openNextFile(m_openMode);
}

DirectoryIterator::DirectoryIterator()
{
}

DirectoryIterator::reference DirectoryIterator::operator*()
{
	m_entry = std::make_shared<FileUtility>(*m_root->m_fs, m_entryFile);
	return *m_entry;
}

DirectoryIterator& DirectoryIterator::operator++(int)
{
	DirectoryIterator temp(*this);
	operator++();
	return temp;
}

DirectoryIterator::pointer DirectoryIterator::operator->()
{
	return m_entry.get();
}

DirectoryIterator& DirectoryIterator::operator++()
{
	File& internalFile = *m_root;
	m_entryFile = internalFile.openNextFile(m_openMode);
	return *this;
}

bool DirectoryIterator::operator==(const DirectoryIterator& other) const
{
	return m_entryFile == other.m_entryFile;
}

bool DirectoryIterator::operator!=(const DirectoryIterator& other) const
{
	return !operator==(other);
}
