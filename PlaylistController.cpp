#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "PlaylistController.h"
#include "SettingsController.h"

using std::cout;
using std::string;
using std::vector;

using boost::filesystem::ofstream;
using boost::filesystem::ifstream;
using namespace boost::filesystem;

extern SettingsController sc;

PlaylistController::PlaylistController() {
}

void PlaylistController::addplaylist(Playlist& pl, const int pos) {
	if(pos < 0) {
		playlists.push_back(pl);
		selection = begin() + offset;
		dispoffset = size() - 1;
		dispselection = begin() + dispoffset;
	}
	else if((size_t)pos < playlists.size()) {
		playlists.insert(begin() + pos, pl);
		selection = begin() + offset;
		dispoffset = pos;
		dispselection = begin() + dispoffset;
	}
}

auto PlaylistController::begin() -> decltype(playlists.begin()) {
	return playlists.begin();
}

auto PlaylistController::end() -> decltype(playlists.end()) {
	return playlists.end();
}

auto PlaylistController::getselection() -> decltype(selection) {
	selection = begin() + offset;
	return selection;
}

auto PlaylistController::getdispselection() -> decltype(selection) {
	dispselection = begin() + dispoffset;
	return dispselection;
}

void PlaylistController::go() {
	offset = dispoffset;
	selection = dispselection;
}

void PlaylistController::go(decltype(selection) pos) {
	//if(pos >= begin() && pos < end())
		selection = pos;
}

void PlaylistController::offsetselection(size_t o) {
	auto s = selection + o;
	if(s >= begin() && s < end()) {
		selection = s;
		offset += o;
	}
	return;
}

void PlaylistController::offsetdispselection(size_t o) {
	auto s = dispselection + o;
	if(s >= begin() && s < end()) {
		dispselection = s;
		dispoffset += o;
	}
	return;
}

/**
	Database loading and saving
*/
bool PlaylistController::loaddb() {
	bool ret = true;

	ifstream db;
	db.open(sc.data);

	size_t played, size;
	unsigned int watched;
	string name, type, file;
	
	//TODO: Better error checking
	while(db.good()) {
		db >> played >> size;
		db.ignore();
		getline(db, name);
		if(db.fail()) {
			goto cleanup;
		}

		Playlist p(name);
		for(size_t i = 0; i < size; ++i) {
			db >> watched >> type;
			db.ignore(100,'\n');
			getline(db, name);
			getline(db, file);
			if(db.fail()) {
				ret = false;
				goto cleanup;
			}

			Show s(file, name, Show::gettype(type), watched);
			p.add(s);
		}

		addplaylist(p);
	}

cleanup:
	selection = dispselection = begin();
	offset = dispoffset = 0;

	db.close();
	return ret;
}


bool PlaylistController::savedb() {
	ofstream db;
	db.open(sc.data);

	//TODO: Better error checking
	for(Playlist& p : playlists) {
		p.printdetail(db);
		db << '\n';
		for(Show& s : p) {
			s.printdetail(db);
			db<< '\n';
		}

	}

	db.close();
	return true;
}

size_t PlaylistController::size() { return playlists.size(); }
