// Based on http://www.boost.org/doc/libs/1_52_0/libs/multi_index/example/complex_structs.cpp

#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <boost/foreach.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include "afxwin.h"

// Aliases

using boost::multi_index_container;
using namespace boost::multi_index;;

/* key_from_key is implemented so that access from an album to the strName field
 * of its associated Artist can be accomplished with
 *
 * key_from_key<
 *	member<stArtist, const CString, &stArtist::strName>,
 *	member<stAlbum, const stArtist*, stAlbum::pArtist>
 * >
 *
 * and similarly for song to album.
 * The reasoning behind this is so that redundant information isn't stored, for 
 * example, an Album can contain 16 songs, so each of those songs doesn't need to
 * store information about the Artist, merely a pointer to the artist, thus 
 * reducing redundant information
*/
template<class KeyExtractor1, class KeyExtractor2>
struct key_from_key
{
public:
	typedef typename KeyExtractor1::result_type result_type;

	key_from_key(
		const KeyExtractor1& _key1=KeyExtractor1(),
		const KeyExtractor2& _key2=KeyExtractor2()
		)
	: key1(_key1)
	, key2(_key2)
	{
	}

	template<typename Arg>
	result_type operator()(Arg& arg)const
	{
		return key1(key2(arg));
	}

private:
	KeyExtractor1 key1;
	KeyExtractor2 key2;
};

/* Tags for accessing the indices defined */
struct artist{};
struct album{};
struct song{};

/* The artist struct just holds the name of the artist */
struct stArtist
{
	// Attribute
	CString m_strName; // Artist's name

	// Constructor
	stArtist(const CString& strName)
	: m_strName(m_strName)
	{
	}
};

/* An album belonging to an artist */
struct stAlbum
{
	// Attributes
	CString m_strName; // Album's name
	const stArtist* m_pArtist; // Pointer to the Artist it belongs to

	// Constructor
	stAlbum(const CString& strName, const stArtist* pArtist)
	: m_strName(strName)
	, m_pArtist(pArtist)
	{
	}

	// Functions
	friend std::ostream& operator<< (std::ostream& os, const stAlbum& _album)
	{
		os<<_T("Artist")<<std::endl;
		os<<_album.m_pArtist->m_strName<<std::endl;
		os<<_T("Album")<<std::endl;
		os<<_album.m_strName<<std::endl;
		return os;
	}
};

/* A song belonging to an album */
struct stSong
{
	// Attributes
	CString m_strName; // Song's name
	const stAlbum* m_pAlbum; // Pointer to the song's Album
	unsigned int m_nTrack; // Song
	CString m_strGenre;

	// Constructor
	stSong(
		const CString& strName,
		const stAlbum* pAlbum,
		unsigned int nTrack,
		const CString& strGenre
		)
	: m_strName(strName)
	, m_pAlbum(pAlbum)
	, m_nTrack(nTrack)
	, m_strGenre(strGenre)
	{
	}

	// Functions
	friend std::ostream& operator<< (std::ostream& os, const stSong& _song)
	{
		os<<_T("Album")<<std::endl;
		os<<_song.m_pAlbum->m_strName<<std::endl;
		os<<_T("Song")<<std::endl;
		os<<_song.m_strName<<std::endl;
		return os;
	}
};

/* Artists are stored in a multi_index_container with one single
 * index on the name member. This is functionally equivalent to an std::set,
 * though in this latter case we woud have to define a non-default comparison
 * predicate (with multi_index_container, member<> does the work for us.)
 */
typedef multi_index_container
<
	stArtist,
	indexed_by
	<
		ordered_unique
		<
			BOOST_MULTI_INDEX_MEMBER(stArtist, CString, m_strName)
		>
	>
> __ArtistsTable;

/* Define a multi_index_container of albums with following indices:
 *   - a unique index sorted by stAlbum::m_strName,
 *   - a non-unique index sorted by stAlbum::m_pArtist; note the
 *     non-standard artist_extractor used.
 */
typedef multi_index_container
<
	stAlbum,
	indexed_by
	<
		ordered_unique
		< // Index on the Album's name
			tag<album>,
			BOOST_MULTI_INDEX_MEMBER(stAlbum, CString, m_strName)
		>,
		ordered_non_unique
		< // Index on the Artist's name
			tag<artist>,
			key_from_key
			<
				BOOST_MULTI_INDEX_MEMBER(stArtist, const CString, m_strName), 
				BOOST_MULTI_INDEX_MEMBER(stAlbum, const stArtist*, m_pArtist)
			> // The key_from_key extracts an Artist's name from the given Album and sorts by it.
		>,
		ordered_non_unique
		< // Index on the Song's name
			tag<song>,
			BOOST_MULTI_INDEX_MEMBER(stSong, CString, m_strName) 
		>
	>
> __AlbumsTable;

/* Don't know if needed
 * Define a multi_index_container of songs with the following indicies:
 *   - a non-unique index sorted by stAlbum::m_strName (the Album's name)
 *   - a non-unique index sorted by stArtist::m_pAlbum, which is further indexed
 *	   by a unique index sorted by stArtist::m_pAlbum::m_pArtist
 */
typedef multi_index_container
<
	stSong,
	indexed_by
	<
		ordered_non_unique
		<
			tag<song>, // Index on the Song's name
			BOOST_MULTI_INDEX_MEMBER(stSong, CString, m_strName)
		>,
		ordered_non_unique
		<
			tag<album>, // Index on the Album's name
			key_from_key
			<
				BOOST_MULTI_INDEX_MEMBER(stAlbum, const CString, m_strName), 
				BOOST_MULTI_INDEX_MEMBER(stSong, const stAlbum*, m_pAlbum)
			>
		>,
		ordered_unique
		<
			tag<artist>, // Index on the Artist's name
			key_from_key
			<
				BOOST_MULTI_INDEX_MEMBER(stArtist, const CString, m_strName),
				key_from_key // Used to get the pointer to the Album's Artist from the song
				<
					BOOST_MULTI_INDEX_MEMBER(stAlbum, const stArtist*, m_pArtist), 
					BOOST_MULTI_INDEX_MEMBER(stSong, const stAlbum*, m_pAlbum)
				>
			>
		>
	>
> __SongsTable;

/* We call a *view* to a multi_index_container storing pointers instead of
 * actual objects. These views are used in the complex search performed
 * in the program. Resorting to multi_index of pointers eliminates
 * unnecessary copying of objects, and provides an opportunity to show how 
 * BOOST_MULTI_INDEX_MEMBER can be used with pointer type elements.
 * __AlbumsBySong indexes (pointers to) Albums by Song
 */
typedef multi_index_container
<
	const stAlbum*,
	indexed_by
	<
		ordered_non_unique
		<
			BOOST_MULTI_INDEX_MEMBER(stSong, const CString, m_strName)
		>
	>
> __AlbumsBySong;

/* __AlbumsByArtist indexes (pointers to) Albums by Artist */
typedef multi_index_container
<
	const stAlbum*,
	indexed_by
	<
		ordered_non_unique
		<
			key_from_key
			<
				BOOST_MULTI_INDEX_MEMBER(stArtist, const CString, m_strName),
				BOOST_MULTI_INDEX_MEMBER(stAlbum, const stArtist* const, m_pArtist)
			>
		>
	>
> __AlbumsByArtist;

/* __ArtistsByAlbumBySong indexes (pointers to) Artists by Album by Song */
typedef multi_index_container
<
	const stArtist*,
	indexed_by
	<
		ordered_unique
		< // Index by unique Artist name
			BOOST_MULTI_INDEX_MEMBER(stArtist, const CString, m_strName)
		>,
		ordered_non_unique
		< // Then index by Album name
			BOOST_MULTI_INDEX_MEMBER(stAlbum, const CString, m_strName)
		>,
		ordered_non_unique
		< // Then index by Song name
			BOOST_MULTI_INDEX_MEMBER(stSong, const CString, m_strName)
		>
	>
> __ArtistsByAlbumsBySongs;
