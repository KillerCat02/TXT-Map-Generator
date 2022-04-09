#include <thread>
#include <iostream>
#include <fstream>
#include <ctime>

const int HEIGHT = 256;
const int WIDTH = 256;
int map[HEIGHT][WIDTH];
char mapChar[HEIGHT][WIDTH];
int AMH;

void baseGen();
void heightGen(int passage);
void tileConvert();
void barierGen();
void saveTerrain();
void loadTerrain();


int main() {
	srand(time(0));
	heightGen(6); //from 4 to 6 good result
	tileConvert();
	saveTerrain();
	return 0;
}


void heightGen(int passage) {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			map[i][j] = 0;
		}
	}

	for (int i = 3; i < HEIGHT - 3; ++i) {
		for (int j = 3; j < WIDTH - 3; ++j) {
			map[i][j] = rand() % 10;
		}
	}

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


void tileConvert() {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (map[i][j] >= 0 && map[i][j] < 4) { mapChar[i][j] = '~';}
			if (map[i][j] > 3 && map[i][j] < 7) { mapChar[i][j] = ' '; }
			if (map[i][j] > 6) { mapChar[i][j] = '#'; }
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
			fout << mapChar[i][j];
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
			mapChar[i][j] = buff;
		}
		std::cout << "Loading line: " << i << std::endl;
	}
	fin.close();
}
