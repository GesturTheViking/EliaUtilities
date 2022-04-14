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