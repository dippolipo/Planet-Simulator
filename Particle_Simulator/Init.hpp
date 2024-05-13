#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Generic.hpp"
#include "Particle.hpp"

struct Model {
	std::string title = "";
	std::vector<Particle> particles;
};

extern int modelsNum;
extern std::vector <Model> models;
extern std::string timeUnit[];
extern unsigned int timeUnitValue[];
extern int timeUnitIndex;

void printModels();
int setPrecision();
int setFrequencyOfPrinting();
void loadModels(std::fstream &file);
void saveModel();
int chooseModel();