#include "FileView.h"

#include <Windows.h>
#include <minwindef.h>
#include <WinBase.h>

FileViewR::FileViewR()
    : myView(nullptr)
    , myFileSize(0Ui64)
{}

FileViewR::FileViewR(const char* const aPath)
    : myView(nullptr)
    , myFileSize(0Ui64)
{
    char pathBuf[MAX_PATH];
    if (!GetShortPathNameA(aPath, pathBuf, MAX_PATH))
        return;

    OFSTRUCT of;
    of.cBytes = sizeof of;

    const HANDLE file = (HANDLE)OpenFile(pathBuf, &of, OF_READ);
    if (!file)
        return;

    LARGE_INTEGER sizeTarget;
    DWORD result = GetFileSizeEx(file, &sizeTarget);

    const HANDLE map = CreateFileMapping(file, 0, PAGE_READONLY, 0, 0, 0);

    CloseHandle(file);
    if (!result)
        return;
    if (!map)
        return;
        
    myView = MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(map);

    myFileSize = sizeTarget.QuadPart;
}

FileViewR::FileViewR(const wchar_t* const aPath)
    : myView(nullptr)
    , myFileSize(0Ui64)
{
    wchar_t pathBuf[MAX_PATH];
    if (!GetShortPathNameW(aPath, pathBuf, MAX_PATH))
        return;

    const HANDLE file = (HANDLE)CreateFileW(pathBuf, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (!file)
        return;

    LARGE_INTEGER sizeTarget;
    DWORD result = GetFileSizeEx(file, &sizeTarget);

    const HANDLE map = CreateFileMapping(file, 0, PAGE_READONLY, 0, 0, 0);

    CloseHandle(file);
    if (!result) return;
    if (!map) return;

    myView = MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(map);

    myFileSize = sizeTarget.QuadPart;
}

FileViewR::~FileViewR()
{
    if (myView)
    {
        UnmapViewOfFile(myView);
    }
}

FileViewR::FileViewR(FileViewR&& anotherView) noexcept
    : myView(nullptr)
    , myFileSize(0Ui64)
{
    myView = anotherView.myView;
    anotherView.myView = nullptr;

    myFileSize = anotherView.myFileSize;
}

FileViewR& FileViewR::operator=(FileViewR&& anotherView) noexcept
{
    myView = anotherView.myView;
    anotherView.myView = nullptr;

    myFileSize = anotherView.myFileSize;

    return *this;
}

const void* const FileViewR::Get() const
{
    return myView;
}

bool FileViewR::IsOpen() const
{
    return myView;
}

size_t FileViewR::GetFileSize() const
{
    return myFileSize;
}