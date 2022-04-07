#include <thread>
#include <iostream>
#include <fstream>
#include <ctime>

const int HEIGHT = 256;
const int WIDTH = 256;
int map[HEIGHT][WIDTH];
int AMH;

void baseGen();
void terrainGen(int passage);
void barierGen();
void saveTerrain();
void loadTerrain();


int main() {
	baseGen();
	terrainGen(4);
	barierGen();
	saveTerrain();
	return 0;
}


void baseGen() {
	srand(time(0));
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			map[i][j] = rand() % 10;
		}
	}
}


void terrainGen(int passage) {
	for (int passageMade = 0; passageMade < passage; ++passageMade) {
			for (int i = 0; i < HEIGHT; ++i) {
				for (int j = 0; j < WIDTH; ++j) {
					AMH += map[i][j] * 2;
					if (i - 1 >= 0) { AMH += map[i-1][j]; }
					if (i + 1 < HEIGHT) { AMH += map[i+1][j]; }
					if (j - 1 >= 0) { AMH += map[i][j-1]; }
					if (j + 1 < WIDTH) { AMH += map[i][j+1]; }
					if (i - 1 >= 0 && j - 1 >= 0) { AMH += map[i-1][j-1]; }
					if (i + 1 < HEIGHT && j + 1 < HEIGHT ) { AMH += map[i+1][j+1]; }
					if (i - 1 >= 0 && j - 1 < WIDTH) { AMH += map[i-1][j+1]; }
					if (i + 1 < HEIGHT && j - 1 >= 0) { AMH += map[i+1][j-1]; }
					AMH = AMH / 9;

					if (AMH >= 9) { AMH = 8; }
					if (AMH < 0) { AMH = 0; }
					map[i][j] = AMH;
					AMH = 0;
				}
			}
	}
}


void barierGen() {
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
					if (i - 1 < 0) { map[i][j] = 9; }
					if (i + 1 == HEIGHT) { map[i][j] = 9; }
					if (j - 1 < 0) { map[i][j] = 9; }
					if (j + 1 == WIDTH) { map[i][j] = 9; }
			}
		}
}


void saveTerrain() {
	std::ofstream fout("MapCreator/map.save");
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			fout << map[i][j];
		}
		fout << std::endl;
		std::cout << "Saving line: " << i << std::endl;
	}
	
	fout.close();
}


void loadTerrain() {
	std::ifstream fin("MapCreator/map.save");
	char buff;
	for(int i = 0; i < HEIGHT; ++i) {
		for(int j = 0; j < WIDTH; ++j) {
			fin >> buff;
			map[i][j] = buff;
		}
		std::cout << "Loading line: " << i << std::endl;
	}
	fin.close();
}
