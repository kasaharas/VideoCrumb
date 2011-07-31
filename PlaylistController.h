#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <vector>

#include "Playlist.h"

class PlaylistController {
	private:
		std::vector<Playlist> playlists;
		// selection - the selected playlist for playlistwindow
		// dispselection - the selection showed on showswindow
		// This allows you to do things in shows window without effecting the
		// playlist window.
		decltype(playlists.begin()) selection, dispselection;
		// selection = begin() + offset; dispselection = begin()+dispoffset
		size_t dispoffset, offset;

	public:
		PlaylistController();

		/**
		 * Add a new playlist.
		 * @param pl the playlist to add
		 * @param pos the position to add it to, -1 to add to end
		 */
		void addplaylist(Playlist& pl, const int pos = -1);

		/**
		 * Get an iterator to the beginning/end of the playlists.
		 */
		auto begin() -> decltype(playlists.begin());
		auto end() -> decltype(playlists.end());

		/**
		 * Get the current selected playlist.
		 * Used by playlist window.
		 */
		auto getselection() -> decltype(playlists.begin());

		/**
		 * Get the currently selected playlist.
		 * Used by shows window.
		 */
		auto getdispselection() -> decltype(playlists.begin());

		/**
		 * Sets the selected playlist for playlist window to be dispselection.
		 */
		void go();

		/**
		 * Sets the selected playlist for playlist window to be the passed iterator.
		 * @param pos iterator to set selection to.
		 */
		void go(decltype(selection) pos);

		/**
		 * Read the database and create data.
		 */
		bool loaddb();

		/**
		 * Move selection by a given amount.
		 * @param o the offset to add to selection
		 */
		void offsetselection(size_t o);

		/**
		 * Move dispselection by a given amount.
		 * @param o the offset to add to dispselection
		 */
		void offsetdispselection(size_t o);

		/**
		 * Save the database.
		 */
		bool savedb();

		/**
		 * Get the number of playlists.
		 */
		size_t size();
};

#endif
