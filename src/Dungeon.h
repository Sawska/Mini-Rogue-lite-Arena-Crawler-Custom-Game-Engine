#pragma once
#include <vector>
#include <random>
#include <utility>

enum class Tile { Wall, Floor, StairsDown };

struct Rect { int x,y,w,h; };

class Dungeon {
public:
    int W{40}, H{20};
    std::vector<Tile> tiles;
    std::vector<std::pair<int,int>> roomCenters;

    explicit Dungeon(uint32_t seed=1234, int w=40, int h=20)
        : W(w), H(h), tiles(w*h, Tile::Wall), rng(seed) {}

    void generate(int roomCount=6) {
        std::uniform_int_distribution<int> rw(4,8), rh(4,6);
        std::uniform_int_distribution<int> rx(1, W-10), ry(1, H-8);
        rooms.clear(); roomCenters.clear();
        std::fill(tiles.begin(), tiles.end(), Tile::Wall);

        for (int i=0;i<roomCount;i++) {
            Rect r{rx(rng), ry(rng), rw(rng), rh(rng)};
            carveRoom(r);
            rooms.push_back(r);
            roomCenters.emplace_back(r.x + r.w/2, r.y + r.h/2);
            if (i>0) connectCenters(roomCenters[i-1], roomCenters[i]);
        }
        // place stairs on last room center
        auto [sx, sy] = roomCenters.back();
        tiles[idx(sx,sy)] = Tile::StairsDown;
    }

    bool isWalkable(int x,int y) const {
        if (x<0||y<0||x>=W||y>=H) return false;
        auto t = tiles[idx(x,y)];
        return t==Tile::Floor || t==Tile::StairsDown;
    }
    bool isStairs(int x,int y) const {
        if (x<0||y<0||x>=W||y>=H) return false;
        return tiles[idx(x,y)]==Tile::StairsDown;
    }

private:
    std::vector<Rect> rooms;
    std::mt19937 rng;

    int idx(int x,int y) const { return y*W+x; }

    void carveRoom(const Rect& r) {
        for (int y=r.y; y<r.y+r.h; ++y)
            for (int x=r.x; x<r.x+r.w; ++x)
                tiles[idx(x,y)] = Tile::Floor;
    }
    void connectCenters(std::pair<int,int> a, std::pair<int,int> b) {
        int x=a.first, y=a.second;
        while (x!=b.first) { tiles[idx(x,y)] = Tile::Floor; x += (b.first>x)?1:-1; }
        while (y!=b.second){ tiles[idx(x,y)] = Tile::Floor; y += (b.second>y)?1:-1; }
    }
};
