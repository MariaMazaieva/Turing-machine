#include <iostream>
#include <stdio.h>
#include <vector>
#include <mutex>
#include <string.h>
#include <map>

#define DEBUG 1  // Comment this line out to disable printing

#ifdef DEBUG
#define LOG(x) std::cout << x 
#else
#define LOG(x)
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

};
bool read_input(void);

map <pair<int, int>, vector<Instruction>> rules;
map<char, int> symbols;// X -> 1; (char) 0 -> 1 (int)
vector<char> id_to_char;
vector<int> tape;
bool is_dtrmistic = true;


bool transform_tape(void){
    int state, symbl, counter, index=0;
    state = 1;
    for(int i = 0; i < K; i ++){
        symbl = tape[i];
        vector<Instruction>& instrs = rules[{state, symbl}];
        // cout << "size "<< instrs.size()<<endl;
        
        if (instrs.size() == 1)
        {   
            Instruction instr = instrs[0];
            cout << "instr " << instr.new_state<<endl;
            // tape[i] = symbols[instr.new_symb];
            tape[i] = instr.new_symb;

            if(instr.dir == 1)
                index++;
            else 
                index--;
            if(instr.new_state == 2)
                break;
        }else if (instrs.empty())
        {
            LOG("D");
            return true;
        }
        else
        {
            return false;

        }
    }
    if(is_dtrmistic)
        cout << 'D' << endl;
    for(int i = 0; i < K; i++)
         LOG(id_to_char[tape[i]] << " ");
    LOG(endl);
    return true;
}

bool read_line(void){
    string line;
    vector<int> rule_parts;
    int count_zero=0;

    cin >> line;
    
    for(int i = 3; i < line.size() - 2; i ++){
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
    c = getchar();
    LOG("First char " << c << endl);  
    while((c = getchar()) != '\n'){
        if(c == ' ')
            continue;
        // cout << "c is "<<c << endl;
        c = symbols[c];
        tape.push_back(c);
    }
    LOG( "Tape at [0] "<< tape[0] << endl);

    for(int i = 0; i < K; i++){
        LOG( tape[i] << endl);
    }

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
    id_to_char.push_back(' ');
    for (int i = 0; i < M ; i++){
        char c;
        cin >> c;
        symbols[c] = i+1;
        id_to_char.push_back(c);
    }
    cin >> B;
    symbols[B] = N + 1;

    for (auto const& symbol : symbols){
        char name = symbol.first;
        int value = symbol.second;
        LOG ("Znak: " << symbol.first << " -> ID: " << symbol.second << endl);
    }
    return true;
}






