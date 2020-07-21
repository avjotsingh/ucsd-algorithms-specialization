#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    int unmatch_position = -1;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push({next, position});
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty() || !opening_brackets_stack.top().Matchc(next)) {
                unmatch_position = position;
                break;
            }
            else
                opening_brackets_stack.pop();
        }
    }

    if(opening_brackets_stack.empty() && unmatch_position == -1)
        std::cout << "Success\n";
    else {
        if(unmatch_position == -1)
            unmatch_position = opening_brackets_stack.top().position;
        std::cout << 1 + unmatch_position << '\n';
    }
    return 0;
}
