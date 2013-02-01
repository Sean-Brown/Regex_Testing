#pragma once
#include "Aliases.h"
#include "Options.h"
#include "Tables.h"

class CRegex_Testing_Library
{
public:
	CRegex_Testing_Library(const COptions& __options);
	~CRegex_Testing_Library(void);
private:
	COptions m_Options; // The options specified by the user
	__ArtistsTable m_Artists; // The table of artists, sorted by artist name
	__AlbumsByArtist m_Albums; // Pointers to albums by artists, sorted by artist
public:
	// The starting point for finding duplicates
	void Begin(void);
	// Recursively crawl subdirectories, find music files and parse them
	void Crawl(const CString);
};

