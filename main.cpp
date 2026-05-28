#include <iostream>
#include <string>

using namespace std;

// =======================
// BASE CLASS: GameObject
// =======================

class GameObject
{
protected:
    string objectName;

public:
    GameObject(string name) : objectName(name) {}

    virtual void draw()
    {
        cout << objectName << " is being rendered on screen." << endl;
    }

    virtual ~GameObject()
    {
        cout << "GameObject destroyed." << endl;
    }
};

// =======================
// COMPOSITION: Stats
// =======================

class Stats
{
public:
    int health;
    int mana;

    Stats(int h = 100, int m = 50) : health(h), mana(m)
    {
        cout << "Stats created." << endl;
    }

    ~Stats()
    {
        cout << "Stats destroyed." << endl;
    }
};

// =======================
// COMPOSITION: SoulMark
// =======================

class SoulMark
{
public:
    string symbol;

    SoulMark(string s = "Dragon") : symbol(s)
    {
        cout << "SoulMark created." << endl;
    }

    ~SoulMark()
    {
        cout << "SoulMark destroyed." << endl;
    }
};

// =======================
// AGGREGATION: Guild
// =======================

class Guild
{
private:
    string guildName;

public:
    Guild(string name) : guildName(name)
    {
        cout << "Guild created: " << guildName << endl;
    }

    void showGuild()
    {
        cout << "Guild still exists: " << guildName << endl;
    }

    ~Guild()
    {
        cout << "Guild destroyed." << endl;
    }
};

// =======================
// BASE CLASS: Weapon
// =======================

class Weapon
{
protected:
    string name;
    int baseDamage;

public:
    Weapon(string n, int dmg)
        : name(n), baseDamage(dmg) {}

    virtual void attack()
    {
        cout << "Generic weapon attack with "
             << name << endl;
    }

    virtual ~Weapon()
    {
        cout << "Weapon destroyed." << endl;
    }
};

// =======================
// DERIVED CLASS: Sword
// =======================

class Sword : public Weapon
{
private:
    int sharpness;

public:
    Sword(string n, int dmg, int sharp)
        : Weapon(n, dmg), sharpness(sharp) {}

    void attack() override
    {
        int totalDamage = baseDamage + sharpness;

        cout << "Slashed with "
             << name
             << " dealing "
             << totalDamage
             << " damage!"
             << endl;
    }

    ~Sword()
    {
        cout << "Sword destroyed." << endl;
    }
};

// =======================
// DEPENDENCY: Potion
// =======================

class Potion
{
public:
    string potionType;

    Potion(string type)
        : potionType(type) {}

    void consume()
    {
        cout << "Potion used: "
             << potionType
             << endl;
    }
};

// =======================
// HERO CLASS
// =======================

class Hero : public GameObject
{
private:
    // Composition
    Stats stats;
    SoulMark soulMark;

    // Aggregation
    Guild *guild;
    Weapon *weapon;

public:
    Hero(string name)
        : GameObject(name),
          stats(120, 80),
          soulMark("Phoenix"),
          guild(nullptr),
          weapon(nullptr)
    {

        cout << "Hero created." << endl;
    }

    void joinGuild(Guild *g)
    {
        guild = g;

        cout << objectName
             << " joined a guild."
             << endl;
    }

    void equipWeapon(Weapon *w)
    {
        weapon = w;

        cout << objectName
             << " equipped a weapon."
             << endl;
    }

    void usePotion(Potion *potion)
    {
        cout << objectName
             << " uses potion -> ";

        potion->consume();
    }

    void attack()
    {
        if (weapon != nullptr)
        {
            weapon->attack();
        }
        else
        {
            cout << "No weapon equipped."
                 << endl;
        }
    }

    ~Hero()
    {
        cout << "Hero destroyed." << endl;
    }
};

// =======================
// MAIN
// =======================

int main()
{

    cout << "=== GAME START ==="
         << endl
         << endl;

    // External objects
    Guild *guild = new Guild("Guardians");

    Sword *sword = new Sword(
        "Excalibur",
        40,
        15);

    // Hero creation
    Hero *hero = new Hero("Arthas");

    // Relationships
    hero->joinGuild(guild);

    hero->equipWeapon(sword);

    // Dependency
    Potion healthPotion("Mega Health");

    hero->usePotion(&healthPotion);

    // Attack
    hero->attack();

    cout << endl;
    cout << "=== HERO DIES ==="
         << endl;

    // Delete hero
    delete hero;

    cout << endl;

    // Guild survives
    guild->showGuild();

    cout << endl;

    // Cleanup remaining objects
    delete sword;
    delete guild;

    cout << endl;
    cout << "=== GAME END ==="
         << endl;

    return 0;
}