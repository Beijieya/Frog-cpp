#include "Map.h"

Map::Map(int w,int h,int* r):W(w),H(h),R(r){
    g.resize(H, std::vector<char>(W,'.'));
    for(int i=0;i<H;++i) if(R[i]==1) g[i]=std::vector<char>(W,'=');
    g0 = g;
}

void Map::draw(int s,int lives,int t){
    std::cout<<"Score:"<<s<<"  Lives:"<<lives<<"  Time:"<<t<<"s\n";
    for(int i=0;i<W;++i){
        std::cout<<(i%10?' ':i/10);
    }
    std::cout<<"\n";
    for(auto& row:g){ for(char c:row) std::cout<<c; std::cout<<"\n"; }
    g = g0;
}

bool Map::setXY(int x,int y,char c){
    if(y>=0&&y<H&&x>=0&&x<W){
        if(c=='O') g0[y][x]=c;
        g[y][x]=c;
    }
    return true;
}
bool Map::isObstacle(int x,int y){ return g0[y][x]=='O'; }
