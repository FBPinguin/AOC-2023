//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution{
    struct Position {
        int x;
        int y;
        int z;

        bool operator==(Position& other) {
            return x==other.x && y==other.y && z==other.z;
        }
    };

    struct SandBlock {
        Position pos1;
        Position pos2;
        bool operator==(SandBlock& other) {
            return this->pos1==other.pos1 && this->pos2 == other.pos2;
        }
    };



    struct sandblock_connection {
        std::vector<SandBlock*> connected;
        int resting_on_count{0};
        int at_z{0};
    };

public:
    std::unordered_map<SandBlock*, sandblock_connection> connection_map;
    std::unordered_map<SandBlock*, std::vector<SandBlock*>> directly_above;
    Position get_position(std::string pos_string);

    void init(std::ifstream& input);

    bool point_inside_square(SandBlock &pos, Position &point);

    bool same_sector(SandBlock &sb1, SandBlock &sb2);

    void init_sandblock_connections();

    int get_highest_y_of_sandblock(SandBlock &sb);

    void calculate_resting_on_count();

    int calculate_solution_1();

    void count_blocks_depending_on(SandBlock &block, std::unordered_set<SandBlock *>& amount, std::unordered_map<SandBlock *, sandblock_connection> &
                                   sand_block_conections);

    int calculate_solution_2();
private:
    std::vector<SandBlock> sand_blocks;
    std::vector<sandblock_connection> sand_block_connections;

};

#endif //SOLUTION_H
