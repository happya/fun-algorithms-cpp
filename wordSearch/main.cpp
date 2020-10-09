#include <iostream>
#include <vector>
#include "WordSearch.h"

using namespace std;

void testWordSearch(vector<vector<char>>& board, vector<string>& words){
    auto wordSearch = new WordSearch(board, words);
    wordSearch->printRes();
    delete wordSearch;

}
int main() {
    vector<vector<char>> board = {{'o','a','a','n'},
                                  {'e','t','a','e'},
                                  {'i','h','k','r'},
                                  {'i','f','l','v'}};
    vector<string> words = {"oath","pea","eat","rain"};
    testWordSearch(board, words);
}
