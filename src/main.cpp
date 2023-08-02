#include <iostream> //
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> //
#include <stdexcept> //
#include <string> //


const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool load_media();
void close();

SDL_Surface* load_surface( const char* path );
SDL_Texture* load_texture( const char* path );

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

SDL_Surface* key_press_surfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface* png_surface = NULL;
SDL_Surface* current_surface = NULL;

void print_sdl_error(const char* msg) {
    std::cout << msg << SDL_GetError() << std::endl;
}

void print_img_error(const char* msg) {
    std::cout << msg << IMG_GetError() << std::endl;
}


bool init()
{
    // -1 means failure
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
        print_sdl_error("SDL could not initialize! SDL Error: ");
        return false;
	}

    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        print_sdl_error("Window could not be created! SDL Error: ");
        return false;
    }

    // create renderer for the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        print_sdl_error("unable to create renderer");
        return false;
    }

    // init renderer color?
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // init png loading
    int img_init_flags = IMG_INIT_PNG;
    bool img_init_worked = IMG_Init( img_init_flags ) & img_init_flags;
    if (!img_init_worked) {
        print_img_error("SDL_image could not initialize! SDL_image Error: ");
        return false;
    }

    //Get window surface
    screen_surface = SDL_GetWindowSurface( window );

    return true;
}

bool load_media()
{
    // only works since enum is [0-4]
    const char* paths[] = {"images/press.bmp", "images/up.bmp", "images/down.bmp", "images/left.bmp", "images/right.bmp"};
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        key_press_surfaces[ i ] = load_surface( paths[i] );
        if( key_press_surfaces[ i ] == NULL )
        {
            return false;
        }
    }

    // load the png
    png_surface = load_surface("images/wed.png");
    if (png_surface == NULL) {
        return false;
    }

    // load the png ... as a texture!
    texture = load_texture("images/wed.png");
    if (texture == NULL) {
        return false;
    }

    return true;
}

void close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( key_press_surfaces[ i ] );
		key_press_surfaces[ i ] = NULL;
	}

    // free png surface
    SDL_FreeSurface(png_surface);

    // free texture
    SDL_DestroyTexture(texture);

	//Destroy window
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );
    renderer = NULL;
	window = NULL;
    screen_surface = NULL; // it is auto freed

	//Quit SDL subsystems
    IMG_Quit();
	SDL_Quit();
}

SDL_Surface* load_surface( const char* path )
{
    SDL_Surface* optimized_surface = NULL;

	SDL_Surface* loaded_surface = IMG_Load( path );
	if( loaded_surface == NULL )
	{
        print_img_error("Unable to load image %s! SDL Error: ");
        return NULL;
	}

    optimized_surface = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);
    if (optimized_surface == NULL) {
        print_sdl_error("unable to optimize image");
        return NULL;
    }

    SDL_FreeSurface(loaded_surface);

	return optimized_surface;
}

SDL_Texture* load_texture( const char* path ) {
    SDL_Texture* final_texture = NULL;

    SDL_Surface* loaded_surface = IMG_Load( path );
    if (loaded_surface == NULL){
        print_img_error("unable to load img");
        return NULL;
    }

    final_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (final_texture == NULL) {
        print_sdl_error("unable to create texture from surface");
        return NULL;
    }

    // free surface
    SDL_FreeSurface(loaded_surface);

    return final_texture;
}

int main()
{
	//Start up SDL and create window
	if( !init() )
	{
        return 1;
	}

    //Load media
    if( !load_media() )
    {
        return 1;
    }

    bool done = false;
    SDL_Event e;
    current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_DEFAULT ];
    bool toggle_rendering = false;

    while( !done )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                done = true;
            }
            //User presses a key
            else if( e.type == SDL_KEYDOWN )
            {
                toggle_rendering = false;
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_UP ];
                        break;

                    case SDLK_DOWN:
                        current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_DOWN ];
                        break;

                    case SDLK_LEFT:
                        current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_LEFT ];
                        break;

                    case SDLK_RIGHT:
                        current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_RIGHT ];
                        break;

                    case SDLK_p:
                        current_surface = png_surface;
                        break;

                    case SDLK_r:
                        toggle_rendering = true;
                        break;

                    default:
                        current_surface = key_press_surfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                        break;
                }
            }
        }

        if (toggle_rendering) {
            // clear screen
            SDL_RenderClear( renderer);

            // render texture
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            SDL_RenderPresent(renderer);
        }
        else {
            //Apply the image stretched
            SDL_Rect stretch_rect;
            stretch_rect.x = 0;
            stretch_rect.y = 0;
            stretch_rect.w = SCREEN_WIDTH;
            stretch_rect.h = SCREEN_HEIGHT;
            SDL_BlitScaled( current_surface, NULL, screen_surface, &stretch_rect );

            //Update the surface
            SDL_UpdateWindowSurface( window );
        }
    }

	//Free resources and close SDL
	close();
}
