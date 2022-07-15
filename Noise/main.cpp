#include <thread>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>


const int HEIGHT = 512;
const int WIDTH = 512;
int map[HEIGHT][WIDTH];
char mapChar[HEIGHT][WIDTH];
int AMH;

int min = 0;
int max = 99;

int numberOfWater = 40;
int numberOfLand = 49;

void genBase();
void heightGen(int passage);
void tileConvert();
void saveTerrain();
void loadTerrain();


int main() {
	srand(time(0));
	genBase();
	heightGen(4); //from 4 to 6 good result
	tileConvert();
	saveTerrain();
	return 0;
}

void genBase() {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			map[i][j] = min + rand() % (max - min + 1);
		}
	}
/* island generation
	for (int i = 50; i < HEIGHT - 50; ++i) {
		for (int j = 50; j < WIDTH - 50; ++j) {
			map[i][j] = min + rand() % (max - 20 - min + 1);
		}
	}

	for (int i = 100; i < HEIGHT - 100; ++i) {
		for (int j = 100; j < WIDTH - 100; ++j) {
			map[i][j] = min + rand() % (max - min + 1);
		}
	}*/
}

void heightGen(int passage) {
	for (int passageMade = 0; passageMade < passage; ++passageMade) {
			for (int i = 0; i < HEIGHT; ++i) {
				for (int j = 0; j < WIDTH; ++j) {
					AMH = (map[i][j] + map[i-1][j] + map[i+1][j] + map[i][j-1] + map[i][j+1] + map[i-1][j-1] + map[i+1][j+1] + map[i-1][j+1] + map[i+1][j-1]) / 9;
					if (AMH > max) { AMH = max; }
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
			if (map[i][j] < numberOfWater) { mapChar[i][j] = '~';}
			if (map[i][j] >= numberOfWater && map[i][j] < numberOfLand) { mapChar[i][j] = ' '; }
			if (map[i][j] >= numberOfLand) { mapChar[i][j] = '#'; }
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
