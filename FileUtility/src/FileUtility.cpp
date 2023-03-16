/*
 Name:		FileUtility.cpp
 Created:	3/16/2023 2:49:45 PM
 Author:	jiaji
 Editor:	http://www.visualmicro.com
*/

#include "FileUtility.h"

FileUtility::FileUtility(FS& fs, File file) :m_fs(fs)
{
	m_isInitialised = static_cast<bool>(file);

	if (m_isInitialised)
		m_file = file;
}

FileUtility::~FileUtility()
{
}

FileUtility::operator File& ()
{
	return m_file;
}

FileUtility::operator bool() const
{
	return m_isInitialised;
}

void FileUtility::forEachFile(DirectoryIteratorCallback f)
{
	for (File entry = m_file.openNextFile(); entry; entry.openNextFile())
		f(entry);
}

void FileUtility::forEachFileRecursive(DirectoryIteratorCallback f)
{
	std::stack<const char*> directories({ m_file.path() });

	DirectoryIteratorCallback recursiveIteratorCallback = [&](File& entry)
	{
		if (entry.isDirectory())
			directories.emplace(entry.path());

		f(entry);
	};

	while (!directories.empty())
	{
		const char* currentEntryPath = directories.top();
		File currentEntryFile = m_fs.open(currentEntryPath);
		directories.pop();

		FileUtility currentEntry(m_fs, currentEntryFile);
		currentEntry.forEachFile(recursiveIteratorCallback);
	}
}

bool FileUtility::renameTo(const String& newName)
{
	const String pathFrom = m_file.path();
	int seperatorIndex = pathFrom.lastIndexOf("/");
	String parentPath = pathFrom.substring(0, seperatorIndex);
	String pathTo = parentPath + "/" + newName;
	return m_fs.rename(pathFrom, pathTo);
}

bool FileUtility::moveTo(const String& pathTo)
{
	String pathFrom = m_file.path();
	return m_fs.rename(pathFrom, pathTo);
}

bool FileUtility::del()
{
	if (!m_file.isDirectory())
		return m_fs.remove(m_file.path());

	// from this point onwards, m_file can only be a directory
	bool result = true;
	DirectoryIteratorCallback recursiveDelete = [&](File& entry)
	{
		if (entry.isDirectory())
			result &= m_fs.rmdir(entry.path());
		else
			result &= m_fs.remove(entry.path());
	};
	forEachFileRecursive(recursiveDelete);

	// from this point onwards, m_file can only be an EMPTY directory
	result &= m_fs.rmdir(m_file.path());
	return result;
}
