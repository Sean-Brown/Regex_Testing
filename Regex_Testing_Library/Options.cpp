#include "stdafx.h"
#include "Options.h"

COptions::COptions(
	const path& _LibPath, // The path to the library
	BOOL bWholeAlbums, // Keep albums whole (don't delete duplicates in different albums, only delete duplicates in the same album)
	BOOL bRemoveLive, // If a pair of songs is a duplicate and one is a "Live" version, remove the "Live" version
	BOOL bSetArtist, // Given song name, try to infer an artist from the song name and fill out the "Track Number" field for that song
	BOOL bSetTrack, // Given song name, try to infer a track number from the song name and fill out the "Track Number" field for that song
	BOOL bRemoveFeat, // Look for and remove "featuring" artist from a song name (e.g. "song name feat. artist" => "song name")
	CStringArray* pstrRemChars // The individual characters that are to be removed from the song's name (i.e. the underscore character '_')
	)
: m_LibPath(_LibPath)
, m_bWholeAlbums(bWholeAlbums)
, m_bRemoveLive(bRemoveLive)
, m_bSetArtistSong(bSetArtist)
, m_bSetTrackSong(bSetTrack)
, m_bRemFeat(bRemoveFeat)
, m_pstrRemChars(pstrRemChars)
{
}

COptions::COptions(const COptions& _Opts)
: m_LibPath(_Opts.m_LibPath)
, m_bWholeAlbums(_Opts.m_bWholeAlbums)
, m_bRemoveLive(_Opts.m_bRemoveLive)
, m_bSetArtistSong(_Opts.m_bSetArtistSong)
, m_bSetTrackSong(_Opts.m_bSetTrackSong)
, m_bRemFeat(_Opts.m_bRemFeat)
, m_pstrRemChars(_Opts.m_pstrRemChars)
{
}

COptions::~COptions(void)
{
	if ( m_pstrRemChars )
		delete [] m_pstrRemChars;
}

BOOL COptions::GetBOOL(eBOOLs eb)
{
	switch(eb)
	{
	case(ebWholeAlb):
		return m_bWholeAlbums;
	case(ebRemLive):
		return m_bRemoveLive;
	case(ebSetArt):
		return m_bSetArtistSong;
	case(ebSetTrack):
		return m_bSetTrackSong;
	case(ebRemFeat):
		return m_bRemFeat;
	default:
	#if defined(_DEBUG)
		throw;
	#endif
	}
}

