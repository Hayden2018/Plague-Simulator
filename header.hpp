struct Pathogen;
struct Person;

struct Person {

    float hp;
    float jump;
    int x;
    int y;
    Pathogen* disease;
    bool coughing;
    bool fever;
    bool masked;
    bool antibody;

    Person();
    void get(Pathogen* p);
    void cure();
    void act();

};

struct Pathogen{

    float severity;
    float coughing;
    float transfer;
    float progress;
    Person* host;
    int r;
    bool random;
    bool airbrone = true;
    bool locked = true;

    Pathogen();
    void act(Person* population);

    private:

    int range();
    bool within(int r, Person& a, Person& b);

};