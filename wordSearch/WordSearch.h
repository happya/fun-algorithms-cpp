//
// Created by yyi on 2020/2/19.
//

#ifndef WORDSEARCH_WORDSEARCH_H
#define WORDSEARCH_WORDSEARCH_H

#include <vector>
#include <iostream>
#include <set>
using namespace std;

/**
 * define the trie node in the preTrie tree
 * children[i]: not NULL means this character is occupied
 */
class TrieNode{
public:
    bool is_end;
    vector<TrieNode*> children;
    TrieNode(){
        is_end = false;
        children = vector<TrieNode*>(26, NULL);
    }
};
/**
 * define the pretrie tree
 */
class Trie{
private:
    TrieNode* root;
    void addWord(const string& word){
        TrieNode* cur = root;
        for(auto& c : word){
            int idx = c - 'a';
            if(cur->children[idx] == NULL)
                cur->children[idx] = new TrieNode();
            cur = cur->children[idx];
        }
        cur->is_end = true;
    }
public:
    Trie(vector<string>& words){
        root = new TrieNode();
        for(auto& word : words)
            addWord(word);
    }
    TrieNode* getRoot() { return root;}

};
class WordSearch {
private:
    vector<vector<char>>& board;
    vector<string> words;
    TrieNode* root;
    int R, C;
    set<string> res;
    bool inArea(int x, int y){
        return (x >= 0 && y >= 0 && x < R && y < C);
    }
    int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    /**
     * dfs to find a valid word
     * @param x : row number
     * @param y : col number
     * @param word : word index
     * @param idx : character index
     * @return true if find a word
     */
    void dfs(int x, int y, TrieNode* node, string word){
        char cur = board[x][y];
//        if(cur < 'a' || cur > 'z')
//            return;
        if(!isalpha(cur))
            return;
        if(node->children[cur - 'a']){
            word += cur;
            node = node->children[cur - 'a'];
            if(node->is_end)
                res.insert(word);

            board[x][y] ^= 255;
            for(int i = 0; i < 4; i++){
                int newX = x + d[i][0];
                int newY = y + d[i][1];
                if(inArea(newX, newY)){
                    dfs(newX, newY, node, word);
                }
            }
            board[x][y] ^= 255;
        }

    }
    void findWords(){
        Trie* trie = new Trie(words);
        root = trie->getRoot();
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                dfs(i, j, root, "");
            }
        }
    }

public:
    WordSearch(vector<vector<char>> _board, vector<string> _words) : board(_board), words(_words){
        R = board.size();
        C = board[0].size();
        findWords();
    }

    void printRes(){
        cout<<"[";
        for(auto& s : res)
            cout<<s<<", ";
        cout<<"]"<<endl;
    }
};


#endif //WORDSEARCH_WORDSEARCH_H
