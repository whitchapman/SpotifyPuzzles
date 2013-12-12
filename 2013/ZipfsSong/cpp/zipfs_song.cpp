#include <iostream>
#include <cstring>

using namespace std;

//////////////////////////////////////////////

class Buffer {
	string line;
	char buffer[200];
	char *first;
	char *second;
public:
	Buffer();
	void read_line();
	char *get_first();
	char *get_second();
};

Buffer::Buffer() {
	first = NULL;
	second = NULL;
}

void Buffer::read_line() {
	getline(cin, line);
	strcpy(buffer, line.c_str());
	first = buffer;
	second = strchr(buffer, ' ');
	*second = '\0';
	++second;
}

char *Buffer::get_first() {
	return first;
}

char *Buffer::get_second() {
	return second;	
}

//////////////////////////////////////////////

class Song {
	int _track;
	char _title[50];
	long _quality;
public:
	Song(int, char*, long);
	char *get_title();
	int compare(Song*);

	Song *next;
};

Song::Song(int track, char *title, long quality) {
	_track = track;
	strcpy(_title, title);
	_quality = quality;

	next = NULL;
}

char *Song::get_title() {
	return _title;
}

int Song::compare(Song *song) {
	if (_quality < song->_quality) {
		return 1;
	}
	
	if (_quality > song->_quality) {
		return -1;
	}
	
	if (_track < song->_track) {
		return -1;
	}
	
	return 1;
}

//////////////////////////////////////////////

class Songs {
	Song *head;
public:
	Songs();
	~Songs();
	void add(Song*);
	void display_titles(int);
};

Songs::Songs() {
	head = NULL;
}

Songs::~Songs() {
	Song *song = head;
	while (song != NULL) {
		Song *next = song->next;
		delete song;
		song = next;
	}
}

void Songs::add(Song *new_song) {
	if (head == NULL) {
		head = new_song;
	} else if (head->compare(new_song) > 0) {
		new_song->next = head;
		head = new_song;
	} else {

		Song *song = head;
		bool done = false;
		while (!done) {
			if (song->next == NULL) {
				song->next = new_song;
				done = true;
			} else if (song->next->compare(new_song) > 0) {
				new_song->next = song->next;
				song->next = new_song;
				done = true;
			} else {
				song = song->next;
			}
		}

	}
}

void Songs::display_titles(int num_outputs) {
	Song *song = head;
	while (num_outputs > 0) {
		cout << song->get_title() << endl;
		song = song->next;
		num_outputs--;
	}
}

//////////////////////////////////////////////

int main() {

	Buffer *buffer = new Buffer();
	buffer->read_line();
	int num_songs = atoi(buffer->get_first());
	int num_outputs = atoi(buffer->get_second());

	Songs *songs = new Songs();
	for (int i=1; i <= num_songs; i++) {
		buffer->read_line();
		long num_plays = atol(buffer->get_first());
		char *title = buffer->get_second();
		long quality = i * num_plays;
		songs->add(new Song(i, title, quality));
	}

	delete buffer;

	songs->display_titles(num_outputs);

	delete songs;
}
