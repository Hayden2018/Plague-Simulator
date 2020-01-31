#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include "header.hpp"
using namespace std;

float COUGHT_MARGIN;
float PROGRESS_RATE;
float TRANSFER_PROB;
float MASKED_RATIO;
float JUMP_PROB;

int MAP_SIZE;
int POPULATION_SIZE;
int RANGE;

bool CORPSE_HANDLE;
bool AIRBRONE;
bool RANDOM_PROGRESS;

default_random_engine generator;
normal_distribution<float> normal;

Person::Person(){
    coughing = false;
    fever = false;
    antibody = false;
    jump = JUMP_PROB;
    hp = 100.0;
    disease = nullptr;
    x = rand() % MAP_SIZE;
    y = rand() % MAP_SIZE;
    if (rand() % 1000 < (int) (MASKED_RATIO * 1000))
        masked = true;
    else 
        masked = false;
}

inline void Person::get(Pathogen* p){
    disease = p;
    p->host = this;
}

inline void Person::cure(){
    antibody = true;
    delete disease;
    disease = nullptr;
}

void Person::act(){
    if( rand() % 1000 < (int) (jump * 1000)){
        x = rand() % MAP_SIZE;
        y = rand() % MAP_SIZE;
    }
    else{
        x += 4 * (rand() % 2) - 2;
        y += 4 * (rand() % 2) - 2;
    }
    if (disease)
        disease->locked = false; 
} 

Pathogen::Pathogen(){
    locked = true;
    random = RANDOM_PROGRESS;
    host = nullptr;
    severity = 0.0;
    r = RANGE;
    transfer = TRANSFER_PROB;
    coughing = COUGHT_MARGIN;
    progress = PROGRESS_RATE;
    airbrone = AIRBRONE;
}

void Pathogen::act(Person* population){

    if (locked)
        return;

    if (random)
        severity += normal(generator);
    else
        severity += progress;
    if (severity > coughing)
        host->coughing = true;
    if (severity < 0.0){
        host->cure();
        return;
    }
    host->hp -= severity;
    
    for(int i = 0; i < POPULATION_SIZE; ++i){
        Person& p = population[i];
        if (p.disease)
            continue;
        else{
            bool close = within(range(), *host, p);
            bool hit = rand() % 1000 < (int) (transfer * 1000);
            bool vulnerable = !p.antibody;
            if (close && hit && vulnerable)
                p.get(new Pathogen());
        }            
    }
} 

inline int Pathogen::range(){
    if ((severity > coughing) && airbrone)
        return r * 2;
    else
        return r;
}

inline bool Pathogen::within(int r, Person& a, Person& b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    if ((a.masked || b.masked) && (rand() % 1000 <500))
        return false;
    else
        return (dx * dx) + (dy * dy) <= r * r;
}

inline string position(Person* p){
    return to_string(p->x) + '_' + to_string(p->y) + '_';
}

int main(int argc, char* argv[]){

    COUGHT_MARGIN = stof(argv[1]);
    PROGRESS_RATE = stof(argv[2]);
    TRANSFER_PROB = stof(argv[3]);
    MASKED_RATIO = stof(argv[4]);
    JUMP_PROB = stof(argv[5]);

    MAP_SIZE = stoi(argv[6]);
    POPULATION_SIZE = stoi(argv[7]);
    RANGE = stoi(argv[8]);

    CORPSE_HANDLE = stoi(argv[9]);
    AIRBRONE = stoi(argv[10]);
    RANDOM_PROGRESS = stoi(argv[11]);

    srand(time(nullptr));
    normal = normal_distribution<float>(PROGRESS_RATE, PROGRESS_RATE);

    Person* population = new Person[POPULATION_SIZE];

    int source = rand() % POPULATION_SIZE;
    population[source].get(new Pathogen());

    while(true){
        int i = 0;
        Person* person = population;
        string death = "";
        string infected = "";
        string healthy = "";
        while(i < POPULATION_SIZE){
            if (person->hp > 0)
                person->act();
            if (person->disease)
                if (!CORPSE_HANDLE || person->hp > 0)
                    person->disease->act(population);
            if (person->disease && person->hp > 0)
                infected += position(person);
            if (person->hp <= 0)
                death += position(person);
            if (!person->disease)
                healthy += position(person);
            ++person;
            ++i;
        }
        cout << infected << endl;
        cout << death << endl;
        cout << healthy << endl;
        cin.get();  
    }
}