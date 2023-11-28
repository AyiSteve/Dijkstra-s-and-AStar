#pragma once


constexpr unsigned int Window_Length = 700;
constexpr unsigned int Window_Width = 1000;
constexpr unsigned int Resize = 2;

constexpr unsigned int NumBlock = 38;
constexpr unsigned int BlockSize = 10;
constexpr unsigned int BlockSpace = 5;

constexpr unsigned int ButtonSizeX = 147;
constexpr unsigned int ButtonSizeY = 48;
constexpr float DCharacterSize = 40;
constexpr float ACharacterSize = 26;
constexpr float CCharacterSize = 25;
constexpr float DLine = 0;
constexpr float ALine = 1;
constexpr float CLine = 2;


constexpr float ratio_text = 3;


enum BlockType
{
	empty,
	wall,
	home,
	end,
	searched,
	path
};

enum ButtonType
{
	BDijkstra,
	BAStar
};

struct Position
{

		int x;
		int y;

		Position(int initialX, int initialY) :x(initialX), y(initialY) {}

};

//this struct saves the location of one cell (within a created array) and it's mother cell. I tried to do pointers instead but there is a memory lost
struct Node {
	Position id;
	int distance;
	// Constructor
	int distanceReal;
	int previousNode;
	int currentNode;

	Node(Position id, int distance, int distanceReal, int previousNode, int currentNode) : id(id), distance(distance), distanceReal(distanceReal), previousNode(previousNode), currentNode(currentNode){}
	// Overloading comparison for priority_queue
	bool operator>(const Node& other) const {
		return distance > other.distance;
	}

	bool operator<(const Node& other) const {
		return distance < other.distance;
	}

};
