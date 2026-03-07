#include <iostream>
#include <array>
#include "include/Example.h"
// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"
#include <ostream>
#include <vector>

class icon {
    std::string m_icon_id;
    std::string m_col1;
    std::string m_col2;
    bool m_glow;
    std::string m_glow_col;
public:
    // void set_icon_id(int icon_id) {
    //     this->m_icon_id = icon_id;
    // }
    // void set_col(std::string col1, std::string col2) {
    //     this->m_col1 = col1;
    //     this->m_col2 = col2;
    // }
    // int get_icon_id() {
    //     return m_icon_id;
    // }
    // std::string get_col_1() {
    //     return m_col1;
    // }
    // std::string get-col_2() {
    //     return m_col2;
    // }
    // void set_glow(bool glow) {
    //     this->m_glow = glow;
    // }
    // bool get_glow() {
    //     return m_glow;
    // }
    icon(std::string id="001", std::string col1="GREEN", std::string col2="BLUE", bool glow=false, std::string glow_col="WHITE") :
    m_icon_id(id), m_col1(col1), m_col2(col2), m_glow(glow), m_glow_col(glow_col) {
    }
    friend std::ostream & operator<<(std::ostream &os, const icon &obj) {
        if (obj.m_glow) {
            std::cout<<"Icon ID: "<<obj.m_icon_id<<"\nColor 1/2: "<<obj.m_col1<<"/"<<obj.m_col2
            <<"\nGlow: ON\nGlow color: "<<obj.m_glow_col<<"\n";
        }
        else {
            std::cout<<"Icon ID: "<<obj.m_icon_id<<"\nColor 1/2: "<<obj.m_col1<<"/"<<obj.m_col2
            <<"\nGlow: OFF\n";
        }
        return os;
    }
};

class player {
    float m_x;
    float m_y;
    icon m_icon;
public:
    player(float x, float y, icon &ic) : m_x(x), m_y(y), m_icon(ic) {
    }
    friend std::ostream& operator<<(std::ostream& os, const player p) {
        std::cout<<"--Player Coordinates--\nX: "<<p.m_x<<"\nY: "<<p.m_y<<"\n";
        std::cout<<"--Player Icon Info--\n"<<p.m_icon<<"\n";
        return os;
    }
};

class obstacle {
    std::string obs_id;
    float m_x;
    float m_y;
    int m_layer;
public:
    obstacle(std::string id, float x, float y, int layer=0) : obs_id(id), m_x(x), m_y(y), m_layer(layer) {
    }
    friend std::ostream& operator<<(std::ostream& os, const obstacle obs) {
        std::cout<<"This object is an obstacle. Its ingame ID is "<<obs.obs_id<<
        ". It will be placed at X: "<<obs.m_x<<" and Y: "<<obs.m_y<<
        " on Layer #"<<obs.m_layer<<".\n";
        return os;
    }
};

class other_obj {
    std::string obj_id;
    float m_x;
    float m_y;
    int m_layer;

public:
    other_obj(std::string obj_id, float x, float y, int layer)
        : obj_id(obj_id),
          m_x(x),
          m_y(y),
          m_layer(layer) {
    }
    friend std::ostream& operator<<(std::ostream& os, const other_obj& obj) {
        std::cout<<"The object's ingame ID is "<<obj.obj_id<<
        ". The object will be placed at X: "<<obj.m_x<<" and Y: "<<
        obj.m_y<<" on Layer #"<<obj.m_layer<<".\n";
        return os;
    }
};

class level {
    std::string m_lvl_id;
    std::vector<obstacle> m_layout={};
    std::vector<other_obj> m_other_objs={};
public:
    level(std::string lvl_id, const std::vector<obstacle> &layout, const std::vector<other_obj> &other_objs)
        : m_lvl_id(lvl_id),
          m_layout(layout),
          m_other_objs(other_objs) {
    }
    level(const level& other) :
    m_lvl_id(other.m_lvl_id), m_layout(other.m_layout), m_other_objs(other.m_other_objs) {
        std::cout<<"Level has been copied!\n";
    }
    level& operator=(const level& other) {
        m_lvl_id = other.m_lvl_id;
        m_layout = other.m_layout;
        m_other_objs = other.m_other_objs;
        std::cout<<"Level has been copied! (using operator=)\n";
        return *this;
    }
    ~level() {
        std::cout<<"Level has been deleted. Bye bye!\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const level& lvl) {
        std::cout<<"Level ID is "<<lvl.m_lvl_id<<". The number of objects is "<<size(lvl.m_layout) + size(lvl.m_other_objs)<<"\n";
        if (size(lvl.m_layout) + size(lvl.m_other_objs) >= 1000) {
            std::cout<<"Level has a large amount of objects.";
        }
        return os;
    }
};

int main() {
    icon icon1{};
    icon icon2{"002", "GREEN", "BLACK", true, "PURPLE"};
    player p1{215.5, 0, icon1};
    std::cout<<p1<<"\n"<<icon2;
    level lvl1{"001", {}, {}};
    std::cout<<lvl1;
    level lvl2(lvl1);
    std::cout<<lvl2;
    obstacle ob1{"001", 10, 1, 1};
    obstacle ob2{"001", 11, 1};
    obstacle ob3{"001", 12, 1};
    level lvl3{"003", {ob1, ob2, ob3}, {}};
    std::cout<<ob1<<"\n"<<ob2<<"\n"<<ob3<<"\n"<<"LEVEL 3\n"<<lvl3;
    return 0;
}

/// Facute in clasa

// class Facultate {
//
// };
// class PanouIluminare {
//     bool aprins;
//     int brighness;
//     std::string firma;
// };
// class GrupIluminare {
//     std::vector<PanouIluminare> panouri;
// };
// // Atribute publice == PICAT!
//
// class Cuier {
// //public:
//     int m_nr_haine;
//     int m_nr_randuri;
// public:
    // int get_nr_randuri() {
    //     return nr_randuri;
    // }
    // int get_nr_haine() {
    //     if (nr_randuri==0) {
    //         return -1;
    //     }
    //     return nr_haine;
    // }
    // void set_nr_randuri(int nr) {
    //     if (nr<1) {
    //         return;
    //     }
    //     nr_randuri=nr;
    // }
    // void set_nr_haine(int nr) {
    //     nr_haine = nr;
    // }
//     Cuier(int nr_haine, int nr_randuri) : m_nr_haine(nr_haine), m_nr_randuri(nr_randuri) {
//
//     }
//     ~Cuier() {
//         std::cout << "~Cuier mr_randuri: "<<m_nr_randuri<<"\n";
//     }
//     Cuier(const Cuier& other) : m_nr_haine(other.m_nr_haine), m_nr_randuri(other.m_nr_randuri) {
//         std::cout<< "Constructor de copiere baby\n";
//     }
//     friend std::ostream& operator<<(std::ostream &os, const Cuier &obj) {
//
//     }
// [[nodiscard]] int get_nr_haine() const {
//     return m_nr_haine;
// }
//
// void set_nr_haine(int nr_haine) {
//     this->m_nr_haine = nr_haine;
// }
//
// [[nodiscard]] int get_nr_randuri() const {
//     return m_nr_randuri;
// }
//
// void set_nr_randuri(int nr_randuri) {
//     this->m_nr_randuri = nr_randuri;
// }
// };
// class Sala {
//     std::vector<GrupIluminare> grupLumine;
//     int numar;
//     double zgomot;
//     Cuier m_cuier;
// public:
//     Sala(Cuier cuier) : m_cuier(cuier)
//     [[nodiscard]] std::vector<GrupIluminare> get_grup_lumine() const {
//         return grupLumine;
//     }
//
//     void set_grup_lumine(const std::vector<GrupIluminare> &grup_lumine) {
//         grupLumine = grup_lumine;
//     }
//
//     [[nodiscard]] int get_numar() const {
//         return numar;
//     }
//
//     void set_numar(int numar) {
//         this->numar = numar;
//     }
//
//     [[nodiscard]] double get_zgomot() const {
//         return zgomot;
//     }
//
//     void set_zgomot(double zgomot) {
//         this->zgomot = zgomot;
//     }
//
//     [[nodiscard]] Cuier get_cuier() const {
//         return m_cuier;
//     }
//
//     void set_cuier(const Cuier &cuier) {
//         this->m_cuier = cuier;
//     }
// };

// int main() {
//     Cuier c1{2, 2}, c2{6, 7};
//     c1.set_nr_randuri(2);
//     std::cout << c1.get_nr_randuri();
//     Sala sala109{c1};
//     sala109.set_cuier(c1);
//     sala109.set_grup_lumine({});
//     sala109.set_zgomot(1000);
//     Sala sala106{c2};
//     sala106.set_zgomot(70);
    // std::cout << "Hello, world!\n";
    // Example e1;
    // e1.g();
    // std::array<int, 100> v{};
    // int nr;
    // std::cout << "Introduceți nr: ";


    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////


    // std::cin >> nr;
    // /////////////////////////////////////////////////////////////////////////
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "v[" << i << "] = ";
    //     std::cin >> v[i];
    // }
    // std::cout << "\n\n";
    // std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "- " << v[i] << "\n";
    // }


    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
//     return 0;
// }
