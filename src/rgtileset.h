#ifndef RGTILESET_H
#define RGTILESET_H

#include <vector>
#include <Godot.hpp>
#include <Reference.hpp>

namespace godot {

//! Class that stores a library of tiles for a RGMap
class RGTileset: public Reference {
    GODOT_CLASS(RGTileset, Reference)
    
    // Structure that stores data about one type of tile
    struct RGTile {
        String name;
        String display_name;
        bool passable;
        bool transparent;
    };

private:
    std::vector<RGTile> tiles;



public:
    /** @name Standard methods */
    ///@{
    static void _register_methods();
    RGTileset();
    ~RGTileset();
    void _init();
    ///@}

    //! Add new tile
    void add_tile(String name, String display_name, bool passable, bool transparent);
    //! Get number of tiles
    int get_tiles_count();
    //! Get tile index by name
    int get_index(String name);
    //! Get tile name (unique)
    String get_name(int index);
    //! Get tile display name
    String get_display_name(int index);
    //! Check if tile is passable
    bool is_passable(int index);
    //! Check if tile is transparent
    bool is_transparent(int index);

};

}

#endif
