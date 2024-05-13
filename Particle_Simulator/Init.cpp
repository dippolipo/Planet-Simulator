#include "Init.hpp"

int modelsNum = 0;
std::vector <Model> models;
std::string timeUnit[8] = { "secondo", "minuto", "ora", "giorno", "settimana", "mese", "anno", "congratulazioni"};
unsigned int timeUnitValue[8] = { 1, 60, 3600, 24 * 3600, 24 * 3600 * 7, 24 * 3600 * 7 * 4, 24 * 3600 * 365, UINT_MAX };
int timeUnitIndex = 0; // valore di default (secondo)

int setPrecision() {
    int dTime;
    std::string answer;
    std::cout << "----------------------------------------------\n";

    while (true) {
        std::cout << "Precisione del tempo (s): ";
        std::getline(std::cin, answer);

        if (isIntNumber(answer)) {
            dTime = stoi(answer);
            if (dTime > 0) {
                return dTime;
            }
        }
        
        std::cout << " * Errore: '" << answer << "' non e' un numero valido\n";
    }
}

int setFrequencyOfPrinting() {
    int f;
    std::string answer;

    while (true) {
        std::cout << "Frequenza visualizzazione dati: ";
        std::getline(std::cin, answer);
        
        if (answer == "mai") {

            timeUnitIndex = 7;
            std::cout << "----------------------------------------------\n";
            return 1;
        }
        
        std::string num = "";
        std::string unit = "";

        for (int i = 0; i < answer.length(); i++) {
            
            if (answer[i] == ' ' || unit != "") {
                
                unit += answer[i];

                if (i >= 3 && answer[i - 3] == ' ') {
                    unit.erase(unit.begin());
                    break;
                }
            }
            else {
                num += answer[i];
            }
        }

        if (unit == "min") {
            timeUnitIndex = 1;
        }
        else if (unit == "ora" || unit == "ore") {
            timeUnitIndex = 2;
        }
        else if (unit == "gio") {
            timeUnitIndex = 3;
        }
        else if (unit == "set") {
            timeUnitIndex = 4;
        }
        else if (unit == "mes") {
            timeUnitIndex = 5;
        }
        else if (unit == "ann") {
            timeUnitIndex = 6;
        }
        else if (unit != "") {
            std::cout << " * Errore: '" << unit << "' non e' un'unita' di misura valida\n";
            continue;
        }
        else {
            std::cout << " - L'unita' di misura e' stata automaticamente impostata sui secondi\n";
        }

        if (isIntNumber(num)) {
            f = stoi(num);
            
            if (f > 0) {
                
                std::cout << "----------------------------------------------\n";
                
                return f;
            }
            else {
                std::cout << " * Errore: '" << num << "' non e' un numero valido\n";
            }
        }
        else {
            std::cout << " * Errore: '" << num << "' non e' un numero valido\n";
        }
    }
}

void saveModel() {
    std::fstream file("Models.txt", std::ios::app);

    std::string answer;
    std::cout << "Aggiungere titolo: ";
    std::getline(std::cin, answer);
    
    int lastModel = models.size() - 1;
    file << "\n\n¶" << answer;
    for (int i = 0; i < models[lastModel].particles.size(); i++) {
        answer = models[lastModel].particles[i].name + "¶" + std::to_string(models[lastModel].particles[i].pos.x) + "¶" + std::to_string(models[lastModel].particles[i].pos.y) + "¶" + std::to_string(models[lastModel].particles[i].mass) + "¶" + std::to_string(models[lastModel].particles[i].radius) + "¶" + std::to_string(models[lastModel].particles[i].v.x) + "¶" + std::to_string(models[lastModel].particles[i].v.y) + "¶";
        file << std::endl << answer;
    }
    file.close();
}

void loadModels(std::fstream& file) {
    
    int dataSubject; // riferisce a quale dato della classe Particle si sta inserendo l'input
    std::string currentString = "";
    
    for (std::string line; getline(file, line);) {
        
        if (line == "") {
            modelsNum++;
            models.push_back({});
        }
        else if (line[0] == '¶') {
            for (int c = 1; c < line.length(); c++) {
                models.back().title += line[c];
            }
        }
        else {
            
            dataSubject = 0;
            models.back().particles.push_back({});
            
            for (int c = 0; c < line.length(); c++) {
                
                if (line[c] == '¶') {
                    switch (dataSubject) {
                    case 0:
                        models.back().particles.back().name = currentString;
                        break;
                    case 1:
                        models.back().particles.back().pos.x = stod(currentString);
                        break;
                    case 2:
                        models.back().particles.back().pos.y = stod(currentString);
                        break;
                    case 3:
                        models.back().particles.back().mass = stod(currentString);
                        break;
                    case 4:
                        models.back().particles.back().radius = stod(currentString);
                        break;
                    case 5:
                        models.back().particles.back().v.x = stod(currentString);
                        break;
                    case 6:
                        models.back().particles.back().v.y = stod(currentString);
                        break;
                    }
                    currentString = "";
                    dataSubject++;
                }
                else {
                    currentString += line[c];
                }
            }
        }
    }
}

int chooseModel() {
    int chosen;
    while (true) {
        std::string answer;
        std::cout << "Usare un modello preesistente o crearne uno? [ crea / usa ] ";
        std::getline(std::cin, answer);

        answer = stringToLower(answer);

        if (answer == "crea" || answer == "c") {

            models.push_back({ });
            chosen = models.size() - 1;

            while (true) {
                answer = "";
                std::cout << "----------------------------------------------\nNome pianeta (inserire 'fasking' per concludere la creazione): ";
                std::getline(std::cin, answer);
                answer = stringToLower(answer);

                if (answer == "fasking") {
                    std::cout << "Do you want to save the file? [ Y / N ] ";
                    std::getline(std::cin, answer);
                    if (stringToLower(answer) == "y") {
                        saveModel();
                    }
                    break;
                }
                else {
                    std::string name = answer;
                    Vector2D pos;
                    Vector2D v;
                    double mass;
                    double radius;

                    while (true) { // dichiarazione della massa
                        std::cout << " - Massa di " << name << " (kg): ";
                        std::getline(std::cin, answer);

                        if (isScientificNumber(answer)) {
                            mass = stod(answer);
                            if (mass <= 0) {
                                std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                        }
                    }

                    while (true) { // dichiarazione del raggio
                        std::cout << " - Raggio di " << name << " (m): ";
                        std::getline(std::cin, answer);

                        if (isScientificNumber(answer)) {
                            radius = stod(answer);
                            if (radius <= 0) {
                                std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                        }
                    }

                    while (true) { // dichiarazione della posizione x
                        std::cout << " - Posizione x di " << name << " (m): ";
                        std::getline(std::cin, answer);

                        if (isScientificNumber(answer)) {
                            pos.x = stod(answer);
                            break;
                        }
                        else {
                            std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                        }
                    }

                    while (true) { // dichiarazione della posizione y
                        std::cout << " - Posizione y di " << name << " (m): ";
                        std::getline(std::cin, answer);

                        if (isScientificNumber(answer)) {
                            pos.y = stod(answer);
                            break;
                        }
                        else {
                            std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                        }
                    }

                    while (true) { // dichiarazione della componente x della velocita'
                        std::cout << " - Componente x della velocita' di " << name << " (m/s): ";
                        std::getline(std::cin, answer);

                        if (isScientificNumber(answer)) {
                            v.y = stod(answer);
                            break;
                        }
                        else {
                            std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                        }
                    }

                    while (true) { // dichiarazione della componente y della velocita'
                        std::cout << " - Componente y della velocita' di " << name << "(m/s): ";
                        std::getline(std::cin, answer);

                        if (isScientificNumber(answer)) {
                            v.y = stod(answer);
                            break;
                        }
                        else {
                            std::cout << "   * Errore: '" << answer << "' non e' un numero valido\n";
                        }
                    }

                    models.back().particles.push_back(Particle(name, pos, mass, radius, v));
                }
            }

            break;
        }

        else if (answer == "usa" || answer == "u") {

            printModels();

            while (true) {
                std::string selected;
                std::cout << "Selezionare un modello: ";
                std::getline(std::cin, selected);

                if (isIntNumber(selected)) {
                    int toNum = stoi(selected) - 1;
                    if (toNum >= 0 && toNum < modelsNum) {
                        chosen = toNum;
                        break;
                    }
                    else {
                        std::cout << "Errore: non esiste il modello " << toNum + 1 << std::endl;
                    }

                }
                else {
                    std::cout << "Errore: '" << selected << "' non e' un numero intero\n";
                }

            }

            break;
        }

        std::cout << "Errore: digitare 'usa'/'u' o 'crea'/'c'\n";
    }
    return chosen;
}

void printModels() {

    for (int i = 0; i < (modelsNum); i++) {
        
        std::cout << "----------------------------------------------\nModello numero " << i + 1 << ": " << models[i].title << std::endl << std::endl;
        
        for (int j = 0; j < models[i].particles.size(); j++) {
        
            std::cout << " " << models[i].particles[j].name << ":\n";
            std::cout << "  - Massa (kg): " << models[i].particles[j].mass << std::endl;
            std::cout << "  - Raggio (m): " << models[i].particles[j].radius << std::endl;
            std::cout << "  - Velocita' (m/s): " << models[i].particles[j].v << std::endl;
            std::cout << "  - Posizione (m): " << models[i].particles[j].pos << std::endl << std::endl;

            std::cout << std::endl;
        }
    }
}