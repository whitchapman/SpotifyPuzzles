#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

//////////////////////////////////////////////

class Buffer {
	string line;
	char buffer[200];
	char *first;
	char *second;
	char *third;
public:
	Buffer();
	void read_one();
	void read_two();
	void read_three();
	char *get_first();
	char *get_second();
	char *get_third();
};

Buffer::Buffer() {
	first = NULL;
	second = NULL;
	third = NULL;
}

void Buffer::read_one() {
	getline(cin, line);
	strcpy(buffer, line.c_str());
	first = buffer;
	second = NULL;
	third = NULL;
}

void Buffer::read_two() {
	getline(cin, line);
	strcpy(buffer, line.c_str());
	first = buffer;
	second = strchr(buffer, ' ');
	*second = '\0';
	++second;
	third = NULL;
}

void Buffer::read_three() {
	getline(cin, line);
	strcpy(buffer, line.c_str());
	first = buffer;
	second = strchr(buffer, ' ');
	*second = '\0';
	++second;
	third = strchr(second, ' ');
	*third = '\0';
	++third;
}

char *Buffer::get_first() {
	return first;
}

char *Buffer::get_second() {
	return second;
}

char *Buffer::get_third() {
	return third;
}

//////////////////////////////////////////////

class Edge {
	string id;
	bool matched;
	bool augmented;

public:
	Edge(string);
	string get_id();

	bool get_matched();
	void set_matched(bool);

	bool get_augmented();
	void set_augmented(bool);
};

Edge::Edge(string s) {
	id = s;
	matched = false;
	augmented = false;
}

string Edge::get_id() {
	return id;
}

bool Edge::get_matched() {
	return matched;
}

void Edge::set_matched(bool b) {
	matched = b;
}

bool Edge::get_augmented() {
	return augmented;
}

void Edge::set_augmented(bool b) {
	augmented = b;
}

//////////////////////////////////////////////

class Vertex {
	int index;
	string vote;
	int id1;
	int id2;
	vector<pair<Edge*, Vertex*> > pairs;
	bool matched;
	bool augmented;
	bool visited;

public:
	Vertex(int, string, int, int);
	int get_index();
	string get_vote();
	int get_id1();
	int get_id2();
	Edge *add_edge(Vertex*);
	vector<pair<Edge*, Vertex*> > *get_pairs();
	void temp();
	bool dfs(int, bool);

	bool get_matched();
	void set_matched(bool);

	bool get_augmented();
	void set_augmented(bool);

	bool get_visited();
	void set_visited(bool);
};

void Vertex::temp() {

	cout << "    Pairs:" << endl;
	for (int i=0; i < pairs.size(); i++) {
		Edge *edge = pairs[i].first;
		Vertex *vertex = pairs[i].second;

		cout << "      " << edge->get_id() << " -> " << vertex->get_vote() << "[" <<  vertex->get_index() << "]" << endl;

	}	
}

Vertex::Vertex(int i, string s, int x1, int x2) {
	index = i;
	vote = s;
	id1 = x1;
	id2 = x2;
	matched = false;
	augmented = false;
	visited = false;
}

int Vertex::get_index() {
	return index;
}

string Vertex::get_vote() {
	return vote;
}

int Vertex::get_id1() {
	return id1;
}

int Vertex::get_id2() {
	return id2;
}

Edge *Vertex::add_edge(Vertex *vertex) {

	//search if edge already exists
	for (int i=0; i < pairs.size(); i++) {
		Vertex *test = pairs[i].second;
		if (vertex == test) {
			return NULL;
		}
	}

	ostringstream convert;
	convert << index;
	string str1 = convert.str();

	ostringstream convert2;
	convert2 << vertex->index;
	string str2 = convert2.str();

	Edge *edge = new Edge(vote + "-" + vertex->vote + ":["+ str1 + "-" + str2 + "]");

	pair<Edge*, Vertex*> pair1 (edge, vertex);
	pairs.push_back(pair1);

	pair<Edge*, Vertex*> pair2 (edge, this);
	vertex->pairs.push_back(pair2);

	return edge;
}

vector<pair<Edge*, Vertex*> > *Vertex::get_pairs() {
	return &pairs;
}

bool Vertex::get_matched() {
	return matched;
}

void Vertex::set_matched(bool b) {
	matched = b;
}

bool Vertex::get_augmented() {
	return augmented;
}

void Vertex::set_augmented(bool b) {
	augmented = b;
}

bool Vertex::get_visited() {
	return visited;
}

void Vertex::set_visited(bool b) {
	visited = b;
}

bool Vertex::dfs(int k, bool follow_matched_edge) {
	if (!visited) {
		visited = true;
		k--;

		for (int i=0; i < pairs.size(); i++) {

			pair<Edge*, Vertex*> p = pairs[i];
			Edge *edge = p.first;
			Vertex *vertex = p.second;

			if ((!vertex->get_visited()) && (!vertex->get_augmented())) {

				if ((follow_matched_edge) && (edge->get_matched())) {

					if (vertex->dfs(k, false)) {
						edge->set_augmented(true);
						augmented = true;
						return true;
					}

				} else if ((!follow_matched_edge) && (!edge->get_matched())) {

					if (k == 0) {

						if (!vertex->get_matched()) {
							vertex->set_augmented(true);
							edge->set_augmented(true);
							augmented = true;
							return true;
						}

					} else if (vertex->dfs(k, true)) {
						edge->set_augmented(true);
						augmented = true;
						return true;
					}

				}
			}
		}
	}

	return false;
}

//////////////////////////////////////////////

void reset_visited(vector<Vertex*> &side1, vector<Vertex*> &side2, vector<Edge*> &edges) {

	for (int i=0; i < side1.size(); i++) {
		side1[i]->set_visited(false);
	}

	for (int i=0; i < side2.size(); i++) {
		side2[i]->set_visited(false);
	}
}

void process(vector<Vertex*> &side1, vector<Vertex*> &side2, vector<Edge*> &edges) {

	//cout << "FREE SIDE1:" << endl;

	//push all unmatched vertexes for side1 on to the queue
	queue<pair<Vertex*, bool> > q;
	for (int i=0; i < side1.size(); i++) {
		if (!side1[i]->get_matched()) {
			pair<Vertex*, bool> p (side1[i], false);
			q.push(p);
			//cout << "  " << side1[i]->get_vote() << "[" <<  side1[i]->get_index() << "]" << endl;
		}
	}

	//BFS
	vector<Vertex*> free_side2;
	int k =1;
	bool follow_matched_edge = false;
	bool collect_free_side2 = false;
	//cout << "BFS:" << endl;
	while (!q.empty()) {
		pair<Vertex*, bool> p = q.front();
		q.pop();
		Vertex *vertex = p.first;
		if (!vertex->get_visited()) {
			vertex->set_visited(true);
			//cout << "  " << v->get_vote() << "[" << v->get_index() << "] " << p.second << endl;

			if (p.second != follow_matched_edge) {
				if (collect_free_side2) {
					//cout << "  BREAK" << endl;
					break;
				} else {
					k++;
					follow_matched_edge = p.second;
				}
			}

			//return unvisited nodes that follow either a matched or unmatched edge
			//vertex will be marked as matched if it is not free

			vector<pair<Edge*, Vertex*> > *pairs = vertex->get_pairs();
			for (int i=0; i < pairs->size(); i++) {

				pair<Edge*, Vertex*> p = pairs->at(i);
				Edge *next_edge = p.first;
				Vertex *next_vertex = p.second;

				if (!next_vertex->get_visited()) {

					if ((follow_matched_edge) && (next_edge->get_matched())) {

						pair<Vertex*, bool> p (next_vertex, false);
						//cout << "   PUSH -> " << next_vertex->get_vote() << "[" << next_vertex->get_index() << "] 0" << endl;
						q.push(p);

					} else if ((!follow_matched_edge) && (!next_edge->get_matched())) {

						//check for free vertexes
						if (next_vertex->get_matched()) {

							pair<Vertex*, bool> p (next_vertex, true);
							//cout << "   PUSH -> " << next_vertex->get_vote() << "[" << next_vertex->get_index() << "] 1" << endl;
							q.push(p);

						} else {

							//free vertex found, stop at this level
							collect_free_side2 = true; //do not increment k (above)
							free_side2.push_back(next_vertex);
							//cout << "    COLLECT -> " << next_vertex->get_vote() << "[" << next_vertex->get_index() << "]" << endl;
							next_vertex->set_visited(true);

						}
					}
				}
			}
		}
	}

	reset_visited(side1, side2, edges);

/*
	cout << "FREE SIDE2 (" << free_side2.size() << ") [K=" << k << "]:" << endl;
	for (int i=0; i < free_side2.size(); i++) {
		cout << "  " << free_side2[i]->get_vote() << "[" <<  free_side2[i]->get_index() << "]" << endl;
		//free_side2[i]->temp();
	}
*/

	//DFS
	//cout << "DFS:" << endl;
	if (free_side2.size() > 0) {

		for (int i=0; i < free_side2.size(); i++) {
			Vertex *vertex = free_side2[i];
			//cout << "  " << vertex->get_vote() << "[" << vertex->get_index() << "]" << endl;
			if (vertex->dfs(k, false)) {
				//vertex->set_matched(true);
			}

			//reset after every free node is processed
			reset_visited(side1, side2, edges);
		}
	}
}

void setup_edges(vector<Vertex*> *side1, int size1, vector<Vertex*> *side2, vector<Edge*> &edges) {

	for (int i=0; i < size1; i++) {

		vector<Vertex*> vs1 = side1[i];

		for (int j=0; j < vs1.size(); j++) {
			Vertex *v = vs1[j];
			int lookup = v->get_id2();

			//cout << " Processing " << v->get_vote() << ": lookup " << lookup << endl;

			vector<Vertex*> vs2 = side2[lookup-1];
			for (int k=0; k < vs2.size(); k++) {

				Edge *edge = v->add_edge(vs2[k]);
				if (edge != NULL) {
					edges.push_back(edge);
				}
			}
		}
	}
}

void setup(Buffer *buffer) {

	buffer->read_three();
	int num_cats = atoi(buffer->get_first());
	int num_dogs = atoi(buffer->get_second());
	int num_votes = atoi(buffer->get_third());

	//cout << "CATS=" << num_cats << " DOGS=" << num_dogs << " VOTERS=" << num_voters << endl;

	vector<Vertex*> *cats = new vector<Vertex*>[num_cats];
	vector<Vertex*> *dogs = new vector<Vertex*>[num_dogs];

	vector<Vertex*> cat_lovers;
	vector<Vertex*> dog_lovers;

	for (int i=0; i < num_votes; i++) {
		buffer->read_two();
		char *cs1 = buffer->get_first();
		char *cs2 = buffer->get_second();

		char *p = cs1;
		int x1 = atoi(++p);
		p = cs2;
		int x2 = atoi(++p);

		string s1 = string(cs1);
		string s2 = string(cs2);

		Vertex *vertex = new Vertex(i, s1+s2, x1, x2);

		if (s1.substr(0, 1) == "C") {
			//cout << "CAT " << s1 << "  DOG " << s2 << endl;
			cats[x1-1].push_back(vertex);
			cat_lovers.push_back(vertex);
		} else {
			//cout << "DOG " << s1 << "  CAT " << s2 << endl;
			dogs[x1-1].push_back(vertex);
			dog_lovers.push_back(vertex);
		}
	}

	vector<Edge*> edges;
	setup_edges(cats, num_cats, dogs, edges);
	setup_edges(dogs, num_dogs, cats, edges);

/*
	cout << "CAT LOVERS (" << cat_lovers.size() << "):" << endl;
	for (int i=0; i < cat_lovers.size(); i++) {
		cout << "  " << cat_lovers[i]->get_vote() << "[" <<  cat_lovers[i]->get_index() << "]" << endl;
		cat_lovers[i]->temp();
	}

	cout << "DOG LOVERS (" << dog_lovers.size() << "):" << endl;
	for (int i=0; i < dog_lovers.size(); i++) {
		cout << "  " << dog_lovers[i]->get_vote() << "[" <<  dog_lovers[i]->get_index() << "]" << endl;
		dog_lovers[i]->temp();
	}

	cout << "EDGES (" << edges.size() << "):" << endl;
	for (int i=0; i < edges.size(); i++) {
		cout << "  " << edges[i]->get_id() << endl;
	}
*/

	bool done = false;
	while (!done) {

		process(cat_lovers, dog_lovers, edges);

		for (int i=0; i < cat_lovers.size(); i++) {
			if (cat_lovers[i]->get_augmented()) {
				cat_lovers[i]->set_matched(true);
				cat_lovers[i]->set_augmented(false);
			}
		}

		for (int i=0; i < dog_lovers.size(); i++) {
			if (dog_lovers[i]->get_augmented()) {
				dog_lovers[i]->set_matched(true);
				dog_lovers[i]->set_augmented(false);
			}
		}

		//cout << "TESTING EDGES:" << endl;
		//symmetric difference
		bool augmented_path = false;
		for (int i=0; i < edges.size(); i++) {
			Edge *edge = edges[i];
			bool augmented = edge->get_augmented();
			if (augmented) {
				augmented_path = true;				
			}

			bool matched = edge->get_matched();
			matched = (matched || augmented) && (!(matched && augmented));

			//if (!matched) {
			//	cout << "  ";
			//}
			//cout << "  " << edge->get_id() << "  matched[" << edge->get_matched() << "] augmented[" << edge->get_augmented() << "] result[" << matched << "]" << endl;

			edge->set_matched(matched);
			edge->set_augmented(false);
		}
		
		if (!augmented_path) {
			done = true;
		}
	}

	int result = num_votes;
	for (int i=0; i < edges.size(); i++) {
		if (edges[i]->get_matched()) {
			//cout << "MATCH!!!" << endl;
			result--;
		}
	}
	cout << result << endl;

	//cleanup

	for (int i=0; i < edges.size(); i++) {
		delete edges[i];
	}
	edges.erase(edges.begin(), edges.end());

	for (int i=0; i < dog_lovers.size(); i++) {
		delete dog_lovers[i];
	}
	dog_lovers.erase(dog_lovers.begin(), dog_lovers.end());

	for (int i=0; i < cat_lovers.size(); i++) {
		delete cat_lovers[i];
	}
	cat_lovers.erase(cat_lovers.begin(), cat_lovers.end());

	delete [] dogs;
	delete [] cats;
}

int main() {

	Buffer *buffer = new Buffer();

	buffer->read_one();
	int num_test_cases = atoi(buffer->get_first());

	for (int i=0; i < num_test_cases; i++) {
		setup(buffer);
	}

	delete buffer;
}
