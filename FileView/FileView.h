/*
* FileViewR
*
* Creates a file mapping and maps a view of the file into address space.
* For fast reading of binary files.
* 
* Requirements: Win32
*/

#pragma once

#include <stdint.h>

class FileViewR
{
public:
	FileViewR();
	FileViewR(const char* const aPath);
	FileViewR(const wchar_t* const aPath);

	~FileViewR();

	FileViewR(const FileViewR& anotherView) = delete;
	FileViewR(FileViewR&& anotherView) noexcept;
	FileViewR& operator=(const FileViewR& anotherView) = delete;
	FileViewR& operator=(FileViewR&& anotherView) noexcept;

	const void* const Get() const;
	bool IsOpen() const;
	size_t GetFileSize() const;

private:
	void* myView;
	size_t myFileSize;
};