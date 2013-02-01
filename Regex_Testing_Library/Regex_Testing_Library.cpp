#include "StdAfx.h"
#include "Regex_Testing_Library.h"
#include "Logger.h"
#include "Constants.h"

using namespace fs;

CRegex_Testing_Library::CRegex_Testing_Library(const COptions& __options)
: m_Options(__options)
{
}

CRegex_Testing_Library::~CRegex_Testing_Library(void)
{
}

// The starting point for finding duplicates
void CRegex_Testing_Library::Begin(void)
{
	// 1. Get the music library directory, specified in the options
	const path& __libPath = m_Options.GetLibPath();
	LINF_ << _T("Library directory given: ") << __libPath.string();

	// 2. Recursively crawl subdirectories
	sys::error_code ec;
	recursive_directory_iterator iter(__libPath, ec);
	for ( fs::recursive_directory_iterator end, dir(__libPath.string());
		  dir != end;
		  ++dir )
	{
		LINF_ << _T("Found Directory: ") << *dir;
		//std::cout << _T("Found Directory: ") << *dir << std::endl;
	}
}

// Recursively crawl subdirectories, find music files and parse them
void CRegex_Testing_Library::Crawl(const CString)
{
}
