#pragma once

//Texture wrapper class
class MyTexture {
private:
    //The actual hardware texture
    SDL_Texture* texture;

    //Image dimensions
    int width;
    int height;
public:
    //Initializes variables
    MyTexture();

    //Deallocates memory
    ~MyTexture();

    //Loads image at specified path
    bool load_from_file( const char* path );

    // set color modulation
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

    // alpha modulation stuff
    void set_blend_mode(SDL_BlendMode blending);
    void set_alpha(uint8_t alpha);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );

    //Gets image dimensions
    int get_width();
    int get_height();
};

