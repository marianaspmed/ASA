#include <iostream>
#include <vector> 
#include <sstream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

vector<int> input1;
vector<int> input2;

void problema1(int x);
void problema2(int x, int y);

int main() {
    int x = 0, y = 0;
    int problem = 0;

    // Get input - problem
    if(scanf("%d", &problem)){
        switch (problem) {
            case 1:
            {
                int elem = 0;
                // Get input - vector
                while (1 == scanf("%d", &elem)) {
                    (input1).push_back(elem);
                    if (cin.peek() == '\n')
                        break;
                }
                x = input1.size();
                problema1(x);
                break;
            }
            case 2:
            {
                int elem = 0;
                string text_line;
                int i = 0;
                for (int n_elems = 0; i < 3; n_elems++) {
                    if(cin.peek() == EOF) {
                        break;
                    }
                    getline(cin, text_line);

                    istringstream line_stream(text_line);
                    while (line_stream >> elem) {
                        if (i == 1) {
                            input1.push_back(elem);
                        } else {
                            input2.push_back(elem);
                        }
                    }
                    i++;
                }
                x = input1.size();
                y = input2.size();
                problema2(x, y);
                break;
            }
        }
    }
    return 0;
}

void problema1(int x) {
    
    if (input1.size() != 0) {
        int l = input1.size(), maximum = 0, num = 0;;
        vector<int> v1(l, 1);
        vector<int> v2(l, 1);
 
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < i; j++) {
                if (input1[i] <= input1[j]) {
                    continue;
                }
                if (v1[j] + 1 > v1[i]) {
                    v1[i] = v1[j] + 1;
                    v2[i] = v2[j];
                } else if (v1[j] + 1 == v1[i]) {
                    v2[i] += v2[j];
                }
            }
        }
        for (int i : v1) {
            maximum = max(i,maximum);
        }
        for(int i = 0; i < l; i++) {
            if (v1[i] == maximum) {
                num += v2[i];
            }
        }
    
    printf("%d %d\n", maximum, num);
    }
}

void problema2(int x, int y) {
    int table[y]; 

    for (int j=0; j < y; j++) 
        table[j] = 0; 
    for (int i=0; i < x; i++) { 
        int current = 0; 
        for (int j=0; j < y; j++) { 
            if (input1[i] == input2[j]) {
                if (current + 1 > table[j]) {
                    table[j] = current + 1; 
                } 
            }        
            if (input1[i] > input2[j]) {
                if (table[j] > current) {
                    current = table[j];
                }
            }
        } 
    } 
  
    int num = 0; 
    for (int i=0; i < y; i++) 
        if (table[i] > num) {
            num = table[i];
        }

    printf("%d\n", num);
} 