#include <iostream>
#include <stdio.h>
#include <vector>
#include <mutex>
#include <string.h>
#include <map>
#include <deque>

// #define DEBUG 1  // Comment this line out to disable printing
#define TEST 1

#ifdef DEBUG
#define LOG(x) std::cout << x 
#else
#define LOG(x)
#endif

#ifdef TEST
#define TST(x) std::cout << x 
#else
#define TST(x)
#endif

using namespace std; 
/*
    N - pocet stavu
    M - 
    K - delka vstupniho slova reprezetujici pocatecny stav 

*/
int N, M, K;
char B;


struct Instruction{
    // int cur_state;
    // int read_char;
    int new_state;
    int new_symb;
    int dir;
    int id;

};
bool read_input(void);

map <pair<int, int>, vector<Instruction>> rules;
map<char, int> symbols;// X -> 1; (char) 0 -> 1 (int)
vector<char> id_to_char;
deque <int> tape;
bool is_dtrmistic = true;


bool transform_tape(void){
    int state, symbl, counter, index=0;
    state = 1;
    // for(int i = 0; i < K; i ++){
    while(true){
        if (index < 0) {
            // Vloží Blank (ID M+1) na začátek vektoru
            tape.push_front(symbols[B]); 
            index = 0; // Hlava je teď na novém prvním políčku (což je ten Blank)
        }
        // Pokud jsme vyjeli vpravo (index >= size) -> Přidáme Blank na konec
        else if (index >= tape.size()) {
            tape.push_back(symbols[B]);
        }
        symbl = tape[index];
        vector<Instruction>& instrs = rules[{state, symbl}];
        // cout << "size "<< instrs.size()<<endl;
        
        if (instrs.size() == 1)
        {   
            Instruction instr = instrs[0];
            // LOG( "instr " << instr.new_state<<endl);
            tape[index] = instr.new_symb;
            state = instr.new_state;
            if(instr.dir == 1)
                index++;
            else 
                index--;
            if(state == 2){
                LOG("KOnec "<<endl);
                break;
            }

        }
        // else if (instrs.empty())
        // {
        //     TST("D" << endl);
        //     return true;
        // }
        else if (instrs.empty()) {
            LOG("CHYBA: Zadna instrukce pro -> Stav: " << state 
            << ", Symbol ID: " << symbl 
            << " (" << id_to_char[symbl] << ")" << endl);
        }
        else
        {
            LOG("Hello " << endl);
            return false;

        }
    }
    if(is_dtrmistic)
        TST('D' << endl);
    int first_nonblank = -1;
    int last_nonblank = -1;
    int blank_id = symbols[B];
    
    for(int i = 0; i < tape.size(); i++){
        if(tape[i] != blank_id){
            if(first_nonblank == -1)
                first_nonblank = i;
            last_nonblank = i;
        }
    }
    if(first_nonblank != -1){
        for(int i = first_nonblank; i <= last_nonblank; i++){
            TST(id_to_char[tape[i]]);
            if(i < last_nonblank) 
                TST(" ");
        }
        TST(endl);
    }

    // for(int i = 0; i < tape.size(); i++)
    //     TST(id_to_char[tape[i]] << " ");

    // TST(endl);
    return true;
}

bool read_line(void){
    string line;
    vector<int> rule_parts;
    int count_zero=0;

    cin >> line;
    
    for(int i = 0; i < line.size(); i ++){
        char c = line[i];
        if (c == '0')
            count_zero++;
        else if (c == '1'){
            if(count_zero > 0)
            {
                rule_parts.push_back(count_zero);
                count_zero=0;
            }
            if(rule_parts.size() == 5)
            {
                Instruction instr;
                // instr.cur_state = rule[0];
                // instr.read_char = rule[1];
                instr.new_state = rule_parts[2];
                instr.new_symb = rule_parts[3];
                instr.dir = rule_parts[4];

                int curr_state = rule_parts[0];
                int read_symb = rule_parts[1];

                rules[{curr_state, read_symb}].push_back(instr);
                rule_parts.clear();
            }
        }
    }

  // Projdi každou položku v mapě 'rules'
    // 'entry' je dvojice: Key (klíč) a Value (hodnota)
    for (auto const& entry : rules) {
        
        // 1. Získej klíč (Odkud a co čtu)
        // entry.first je typu pair<int, int>
        int state_in = entry.first.first;
        int read_sym = entry.first.second;

        LOG( "Klíč [Stav " << state_in << ", Čte " << read_sym << "] -> ");

        // 2. Získej hodnotu (Seznam instrukcí)
        // entry.second je typu vector<Instruction>
        vector<Instruction> targets = entry.second;

        // Protože to může být nedeterministické, může tam být více instrukcí
        for (auto const& instr : targets) {
            LOG("{Kam: " << instr.new_state 
                 << ", Píše: " << instr.new_symb 
                 << ", Směr: " << (instr.dir == 1 ? "R" : "L") << "} "
                );
        }
        
        LOG(endl); // Odřádkování za jedním klíčem
    }

    return true;
}

void read_tape(void){
    char c;
    // c = getchar();
    // LOG("First char " << c << endl);  
    // while((c = getchar()) != '\n'){
    //     if(c == ' ')
    //         continue;
    //     // cout << "c is "<<c << endl;
    //     c = symbols[c];
    //     tape.push_back(c);
    // }
    for(int i = 0; i < K; i++){
        string s; 
        if(cin >> s) {
            // Pokud symbol známe, převedeme na ID, jinak Error (nebo Blank)
            if(symbols.find(s[0]) != symbols.end()) {
                tape.push_back(symbols[s[0]]);
            } else {
                tape.push_back(symbols[B]);
            }
        }
    }
    LOG( "Tape at [0] "<< tape[0] << endl);

    // for(int i = 0; i < K; i++){
    //     LOG( tape[i] << endl);
    // }

}
int main (int argc, char * argv[]){
    cin >> N >> M >> K;
    read_input();  
    read_line();
    read_tape();
    transform_tape();

    return 0;
}

bool read_input(void){
    id_to_char.push_back('?');
    for (int i = 0; i < M ; i++){
        char c;
        cin >> c;
        symbols[c] = i+1;
        id_to_char.push_back(c);
    }
    cin >> B;
    symbols[B] = M + 1;
    id_to_char.push_back(B);
    // symbols[B] = ' ';

    for (auto const& symbol : symbols){
        char name = symbol.first;
        int value = symbol.second;
        LOG ("Znak: " << symbol.first << " -> ID: " << symbol.second << endl);
    }
    return true;
}






