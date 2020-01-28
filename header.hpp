struct Pathogen;
struct Person;

struct Person {

    float hp;
    int x;
    int y;
    Pathogen* disease;
    bool coughing;
    bool fever;
    bool masked;

    Person();
    void get(Pathogen* p);
    void act();

};

struct Pathogen{

    int incubation;
    float severity;
    float coughing;
    float fever;
    float transfer;
    float progress;
    Person* host;
    bool airbrone = true;
    bool locked = true;

    Pathogen();
    void act(Person* population);

    private:

    int range();
    bool within(int r, Person& a, Person& b);

};