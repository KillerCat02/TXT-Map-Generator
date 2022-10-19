#include <thread>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

const int HEIGHT = 1028;
const int WIDTH = 1028;
int map[HEIGHT][WIDTH];
char mapChar[HEIGHT][WIDTH];
int AMH;

const int sizeSmooth = 15;

int min = 0;
int max = 100;

int numberOfWater = 35;
int numberOfLand = 55;

void genBase();
void hillGen(int amount, int sizeX, int sizeY, int chance, int maxAdd);
void lakeGen(int amount, int sizeX, int sizeY, int chance, int maxRem);
void lineGen(int amount, int maxWidth, int add);
void heightGen(int passage);
void tileConvert();
void saveTerrain();
void loadTerrain();


int main() {
	unsigned int start_time =  clock();
	genBase();
	hillGen(10, 512, 512, 80, 16);
	lakeGen(10, 512, 512, 80, 16);
	hillGen(20, 256, 256, 80, 64);
	lakeGen(20, 256, 256, 80, 64);
	lineGen(128, 3, -10);
	lineGen(64, 5, 15);

	heightGen(3); //from 4 to 6 good result
	tileConvert();
	saveTerrain();

	unsigned int end_time = clock();
	std::cout << end_time - start_time;
	return 0;
}

void genBase() {
	srand(time(0));
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			map[i][j] = min + rand() % (max - min + 1);
		}
	}
}

void hillGen(int amount, int sizeX, int sizeY, int chance, int maxAdd) {
	for (int k = 0; k < amount; ++k) {
		int x1 = rand() % WIDTH;
		int y1 = rand() % HEIGHT;
		int x2 = x1 + (rand() % sizeX);
		int y2 = y1 + (rand() % sizeY);

		for (int i = y1; i < y2; ++i) {
			for (int j = x1; j < x2; ++j) {
				if (i < HEIGHT && j < WIDTH && rand() % 100 > chance) {
					if (rand() % 100 > 80) {
						map[i][j] = 42;
					} else {
						map[i][j] += rand() % maxAdd;
					}
				}
			}
		}
	}
}

void lakeGen(int amount, int sizeX, int sizeY, int chance, int maxRem) {
	for (int k = 0; k < amount; ++k) {
		int x1 = rand() % WIDTH;
		int y1 = rand() % HEIGHT;
		int x2 = x1 + (rand() % sizeX);
		int y2 = y1 + (rand() % sizeY);

		for (int i = y1; i < y2; ++i) {
			for (int j = x1; j < x2; ++j) {
				if (i < HEIGHT && j < WIDTH && rand() % 100 > chance) {
					map[i][j] -= rand() % maxRem;
				}
			}
		}
	}
}

void lineGen(int amount, int maxWidth, int add) {
	for (int currentRiver = 0; currentRiver < amount; ++currentRiver) {
		int width = 1 + rand() % maxWidth;
		int currentX = rand() % WIDTH;
		int currentY = rand() % HEIGHT;
		int dirX = rand() % 3;
		int dirY = rand() % 3;
		for (int i = 0; i < 512; ++i) {
			if (rand() % 100 > 95) dirX = rand() % 3;
			if (rand() % 100 > 95) dirY = rand() % 3;
			if (dirX == 2) dirX = -1;
			if (dirY == 2) dirY = -1;
			currentX += dirX;
			currentY += dirY;
			for (int i = currentY - width; i < currentY + width + 1; ++i) {
				for (int j = currentX - width; j < currentX + width + 1; ++j) {
					if (j > 0 && i > 0 && j < WIDTH && i < HEIGHT) {
						map[i][j] += add;
					}
				}
			}
		}
	}
}

void heightGen(int passage) {
	for (int passageMade = 0; passageMade < passage; ++passageMade) {
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
				int div = 0;
				for (int k = i - sizeSmooth / 2; k < i + sizeSmooth / 2 + 1; ++k) {
					for (int d = j - sizeSmooth / 2; d < j + sizeSmooth / 2+ 1; ++d) {
						if (k > 0 && d > 0 && k < HEIGHT && d < WIDTH) {
							AMH += map[k][d];
							++div;
						}
					}
				}
				AMH = AMH / div;
				//if (AMH > max) { AMH = max; }
				//if (AMH < min) { AMH = min; }
				map[i][j] = AMH;
				AMH = 0;
			}
		}
	}
}

void tileConvert() {
	int *ptr = &map[0][0];
	char *ptrChar = &mapChar[0][0];
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (*ptr < numberOfWater) { *ptrChar = '~';}
			if (*ptr >= numberOfWater && *ptr < numberOfLand) { *ptrChar = ' '; }
			if (*ptr >= numberOfLand) { *ptrChar = '#'; }
			++ptr;
			++ptrChar;
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
		//std::cout << "Saving line: " << i << std::endl;
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
