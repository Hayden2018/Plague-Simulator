#include <random>
#include <ctime>
#include <iostream>
#include "header.hpp"
using namespace std;


int infected;
int death;

float COUGHT_MARGIN;
float FEVER_MARGIN;
float PROGRESS_RATE;
float TRANSFER_PROB;
float MASKED_RATIO;

int MAP_SIZE;
int POPULATION_SIZE;
int INCUBATION;
int SPEED;

bool COPS_HANDLE;
bool INCUBATION_TRANSFER;
bool AIRBRONE;
bool RANDOM_PROGRESS;

Person::Person(){
    coughing = false;
    fever = false;
    masked = false;
    speed = SPEED;
    hp = 100.0;
    disease = nullptr;
    x = rand() % MAP_SIZE;
    y = rand() % MAP_SIZE;
}

void Person::get(Pathogen* p){
    disease = p;
    p->host = this;
    infected += 1;
}

void Person::act(){
    x += (int) (2.5 * (rand() % speed) - speed);
    y += (int) (2.5 * (rand() % speed) - speed);
    if ( disease && disease->locked )
        disease->locked = false;
} 

Pathogen::Pathogen(){
    locked = true;
    host = nullptr;
    severity = 0.0;
    incubation = INCUBATION;
    transfer = TRANSFER_PROB;
    coughing = COUGHT_MARGIN;
    fever = FEVER_MARGIN;
    progress = PROGRESS_RATE;
    airbrone = AIRBRONE;
}

void Pathogen::act(Person* population){

    if(locked)
        return;

    severity += progress;
    host->hp -= severity;
    if( host->hp <= 0 )
        death += 1;

    for(int i = 0; i < POPULATION_SIZE; ++i){
        Person& p = population[i];
        if( p.disease )
            continue;
        else 
            if( within(range(), *host, p) ){
                float draw = (float) (rand() % 1000);
                if ( draw / 1000 < transfer ){
                    Pathogen* v = new Pathogen();
                    p.get(v);
                }
            }
    }
} 

int Pathogen::range(){
    if( (severity > coughing) && airbrone )
        return 8;
    else
        return 4;
}

bool Pathogen::within(int r, Person& a, Person& b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return (dx * dx) + (dy * dy) <= r * r;
}

int main(int argc, char* argv[]){

    srand(time(nullptr));

    infected = 0;
    death = 0;

    COUGHT_MARGIN = 0.1;
    FEVER_MARGIN = 0.4;
    PROGRESS_RATE = 0.05;
    TRANSFER_PROB = 0.2;

    MAP_SIZE = 800;
    POPULATION_SIZE = 10000;
    INCUBATION = 10;
    SPEED = 5;

    COPS_HANDLE = true;
    INCUBATION_TRANSFER = false;
    AIRBRONE = true;
    RANDOM_PROGRESS = false;

    Person* population = new Person[POPULATION_SIZE];

    int source = rand() % POPULATION_SIZE;
    Pathogen* virus = new Pathogen();
    population[source].get(virus);

    while(infected < POPULATION_SIZE){
        for(int i = 0; i < POPULATION_SIZE; ++i)
            if( population[i].hp > 0 )
                population[i].act();
        for(int i = 0; i < POPULATION_SIZE; ++i)
            if( population[i].disease )
                if ( !COPS_HANDLE || population[i].hp > 0 )
                    population[i].disease->act(population);
        for(int i = 0; i < POPULATION_SIZE; ++i)
            if( population[i].disease && population[i].hp > 0 )
                cout << population[i].x << '_' << population[i].y << '_';
        cout << endl;
        for(int i = 0; i < POPULATION_SIZE; ++i)
            if( population[i].hp <= 0 )
                cout << population[i].x << '_' << population[i].y << '_';
        cout << endl;
        for(int i = 0; i < POPULATION_SIZE; ++i)
            if( population[i].disease == nullptr )
                cout << population[i].x << '_' << population[i].y << '_';
        cout << endl;
        cin.get();    
    }

}