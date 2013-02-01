#pragma once
#include "Aliases.h"

using namespace fs;

enum eBOOLs
{
	ebWholeAlb = 0,
	ebRemLive,
	ebSetArt,
	ebSetTrack,
	ebRemFeat
};

class COptions
{
public: // Constructor/Destructor
	COptions(
		const path& _LibPath, // The path to the library
		BOOL bWholeAlbums, // Keep albums whole (don't delete duplicates in different albums, only delete duplicates in the same album)
		BOOL bRemoveLive, // If a pair of songs is a duplicate and one is a "Live" version, remove the "Live" version
		BOOL bSetArtist, // Given song name, try to infer an artist from the song name and fill out the "Track Number" field for that song
		BOOL bSetTrack, // Given song name, try to infer a track number from the song name and fill out the "Track Number" field for that song
		BOOL bRemoveFeat, // Look for and remove "featuring" artist from a song name (e.g. "song name feat. artist" => "song name")
		CStringArray* pstrRemChars // The individual characters that are to be removed from the song's name (i.e. the underscore character '_')
		);
	COptions(const COptions& _Opts); // Copy-Constructor
	~COptions(void);
private: // Member variables
	const path& m_LibPath; // The path to the music library
	BOOL m_bWholeAlbums; // TRUE = delete duplicates ONLY within an album, FALSE = delete all duplicates
	BOOL m_bRemoveLive; // TRUE = permanently delete the duplicates, FALSE = store the deleted duplicates
	BOOL m_bSetArtistSong; // TRUE = extract artist(s) and song name from just a song name and try to set that data in the music file
	BOOL m_bSetTrackSong; // TRUE = extrackt track number and song name from just a song name and try to set that data in the music file
	BOOL m_bRemFeat; // TRUE = find any "featuring" artists in a song name and remove it
	CStringArray* m_pstrRemChars; // The list of characters to be removed from song names
public: // Accessors
	const path& GetLibPath(void){ return m_LibPath; }
	BOOL GetBOOL(eBOOLs eb);
	const CStringArray* GetRemChars(void){ return m_pstrRemChars; }
};

