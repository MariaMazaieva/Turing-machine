#include <iostream>
#include <stdio.h>
#include <vector>
#include <mutex>
#include <string.h>
#include <map>

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
vector<int> tape;

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

        cout << "Klíč [Stav " << state_in << ", Čte " << read_sym << "] -> ";

        // 2. Získej hodnotu (Seznam instrukcí)
        // entry.second je typu vector<Instruction>
        vector<Instruction> targets = entry.second;

        // Protože to může být nedeterministické, může tam být více instrukcí
        for (auto const& instr : targets) {
            cout << "{Kam: " << instr.new_state 
                 << ", Píše: " << instr.new_symb 
                 << ", Směr: " << (instr.dir == 1 ? "R" : "L") << "} ";
        }
        
        cout << endl; // Odřádkování za jedním klíčem
    }

    return true;
}

void read_tape(void){
    char c;
    c = getchar();
    cout <<"First char " << c << endl;
    while((c = getchar()) != '\n'){
        if(c == ' ')
            continue;
        // cout << c << endl;
        c = symbols[c];
        tape.push_back(c);
    }
    cout << "Tape at [0] "<< tape[0] << endl;

    for(int i = 0; i < K; i++){
        cout << tape[i] << endl;
    }

}
int main (int argc, char * argv[]){
    cin >> N >> M >> K;
    read_input();  
    read_line();
    read_tape();

    return 0;
}

bool read_input(void){
      
    for (int i = 0; i < M ; i++){
        char c;
        cin >> c;
        symbols[c] = i+1;
    }
    cin >> B;
    symbols[B] = N + 1;

    for (auto const& symbol : symbols){
        char name = symbol.first;
        int value = symbol.second;
        cout << "Znak: " << symbol.first << " -> ID: " << symbol.second << endl;
    }
    return true;
}






