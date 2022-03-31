#include <thread>
#include <iostream>
#include <fstream>
#include <ctime>


const int HEIGHT = 256, WIDTH = 256;
int map[HEIGHT][WIDTH];


void genMapBase() {
	srand(1);
	int randInt = 0;
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			randInt = rand() % 10;
			map[i][j] = randInt;
		}
	}
}


void genMapTerrain(int passage) {
	int AMH = 0;
	for (int passageMade = 0; passageMade < passage; ++passageMade) {
			for (int i = 0; i < HEIGHT; ++i) {
				for (int j = 0; j < WIDTH; ++j) {

					AMH = (map[i][j] * 2 + map[i-1][j] + map[i+1][j] + map[i][j-1] + map[i][j+1] + map[i-1][j-1] + map[i+1][j+1] + map[i-1][j+1] + map[i+1][j-1]) / 9;
					if (AMH > 9) { AMH = 9; }
					if (AMH < 0) { AMH = 0; }
					map[i][j] = AMH;

					AMH = (map[j][i] * 2 + map[j-1][i] + map[j+1][i] + map[j][i-1] + map[j][i+1] + map[j-1][i-1] + map[j+1][i+1] + map[j-1][i+1] + map[j+1][i-1]) / 9;
					if (AMH > 9) { AMH = 9; }
					if (AMH < 0) { AMH = 0; }
					map[j][i] = AMH;

				}
			}
	}
}


void showMap() {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}


void saveMap() {
	std::ofstream fout("Noise/map.save");
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			fout << map[i][j];
		}
		fout << std::endl;
		std::cout << "Saving line: " << i << std::endl;
	}
	
	fout.close();
}


void loadMap() {
	std::ifstream fin("Noise/map.save");
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

int main() {
	genMapBase();
	std::thread tA(genMapTerrain, 3);
	std::thread tB(genMapTerrain, 3);
	tA.join();
	tB.join();
	saveMap();
	return 0;
}
