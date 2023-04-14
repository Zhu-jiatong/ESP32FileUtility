#pragma once

#include <iterator>
#include <memory>
#include <FS.h>

class FileUtility;

class DirectoryIterator
{
public:
	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = FileUtility;
	using pointer = value_type*;
	using reference = value_type&;

	DirectoryIterator(FileUtility& root, const char* openMode);
	DirectoryIterator();
	DirectoryIterator& operator++();
	DirectoryIterator& operator++(int);
	bool operator==(const DirectoryIterator& other) const;
	bool operator!=(const DirectoryIterator& other) const;
	reference operator*();
	pointer operator->();

private:
	FileUtility* m_root = nullptr;
	File m_entryFile;
	std::shared_ptr<FileUtility> m_entry;
	const char* m_openMode = nullptr;
};
