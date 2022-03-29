#include <iostream>
#include <fstream>
#include <ctime>

const int HEIGHT = 256, WIDTH = 256;
int map[HEIGHT][WIDTH];


void genMap() {
	srand(time(0));
	int randInt = 0;
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			randInt = rand() % 10;
			map[i][j] = randInt;
		}
	}
	
	int AMH = 0;
	int passage = 6;
	for (int j = 0; j < passage; ++j) {
			for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
				AMH = ((map[i][j] * 2) + map[i-1][j] + map[i+1][j] + map[i][j-1] + map[i][j+1] + map[i-1][j-1] + map[i+1][j+1] + map[i-1][j+1] + map[i+1][j-1]) / 9;
				while (AMH > 9) {
					--AMH;
				}
					map[i][j] = AMH;
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

    }
    fin.close();
}

int main() {
	genMap();
	saveMap();
	return 0;
}