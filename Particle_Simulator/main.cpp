#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <vector>

#include "Init.hpp"

int main() {

    const double G = 6.67e-11;// Constante di della gravitazione universale

    std::fstream file("Models.txt");

    loadModels(file);

    std::vector<Particle> particles = models[chooseModel()].particles;

    file.close();

    int n = particles.size();

    bool collision = false;
    long unsigned int iteration = 1;

    int dTime = setPrecision();
    std::cout << "----------------------------------------------\n";

    // ogni quanto stampare a schermo
    unsigned int frequencyOfPrinting = setFrequencyOfPrinting();

    // Loop principale
    while (!collision) {

        // per ogni particella
        for (int i = 0; i < (n - 1); i++) {

            // ogni altra particella, ignorando quelle gia' studiate
            for (int j = i + 1; j < n; j++) {

                Vector2D dist = particles[j].pos - particles[i].pos;
                
                // Equazione della gravitazione universale
                double strVal = G * ((particles[i].mass * particles[j].mass) / (dist.modulus() * dist.modulus()));
                
                particles[i].str += dist.normalize() * strVal;
                particles[j].str -= dist.normalize() * strVal; // 2a legge di Newton

                // in caso di collisione collisione
                if (dist.modulus() <= particles[i].radius + particles[j].radius) {
                    collision = true;
                    std::cout << "Collisione occorsa al secondo: " << iteration * dTime << std::endl << "Iterazione numero: " << iteration << std::endl << std::endl;
                }

            }

        }

        for (int i = 0; i < n; i++) {
            particles[i].update_pos(dTime);
        }

        // stampa delle particelle
        if ((iteration * dTime) % (frequencyOfPrinting * timeUnitValue[timeUnitIndex]) == 0) {

            std::cout << timeUnit[timeUnitIndex] << " numero: " << (iteration * dTime) / timeUnitValue[timeUnitIndex] << std::endl << std::endl;

            for (int i = 0; i < n; i++) {

                std::cout << " " << particles[i].name << ":\n";
                std::cout << "  - Velocita': " << particles[i].v << std::endl;
                std::cout << "  - Posizione(in metri) : " << particles[i].pos << std::endl << std::endl;

            }

            system("pause");
            std::cout << std::endl;

        }

        iteration++;
    }

    system("pause");

    return 0;
}