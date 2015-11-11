#include "sprite.h"


struct sprite_s
{
  uint8		inuse;
  uint32	ref_count;
  uint8		dynamic;
  char		*file_name;
  SDL_Texture	*texture;
  SDL_Surface	*image;
  
  uint32	num_frames;
  uint32	num_cols;
  uint32	num_rows;
  
  uint32	frame_w;
  uint32	frame_h;
};


static Sprite	_sprite_list[ MAX_SPRITES ];
static uint32	_num_sprites = 0;


static Sprite*	_find_in_sprite_list( char *name );


void init_sprite_system()
{
  Log( INFO, "Initializing Sprite System" );
  
  memset( _sprite_list, 0, sizeof( struct sprite_s ) * MAX_SPRITES );
  
  Log( INFO, "Sprite System Initialized" );
}


Sprite*	_find_in_sprite_list( char *name )
{
  int i, c;  
  
  if( !name ) return NULL;
  
  c = 0;
  
  for( i = 0; i < MAX_SPRITES; i++ )
  {
    if( _sprite_list[ i ].inuse )
    {
      if( strcmp( _sprite_list[ i ].file_name, name ) == 0 )
	return &_sprite_list[ i ];
    
      c++;
      if( c >= _num_sprites )
	return NULL;
    }
  }
  
  return NULL;
}


Sprite* load_sprite_from_config( char *file )
{
  Dict *config;
  uint32 c, r, f, d;
  
  config = Parse( file );
  if( !config )
  {
    Log( ERROR, "%s sprite config file couldn't be parsed", file );
    return NULL;
  }
  
  Str_As_UInt( Find_In_Dict( config, "columns" ), &c );
  Str_As_UInt( Find_In_Dict( config, "rows" ), &r );
  Str_As_UInt( Find_In_Dict( config, "frames" ), &f );
  Str_As_UInt( Find_In_Dict( config, "dynamic" ), &d );
  
  return load_sprite( Find_In_Dict( config, "image_file" ), c, r, f, d );      
}


Sprite* load_sprite( char *image_file, uint32 cols, uint32 rows, uint32 frames, uint8 dynamic )
{
  int i;
  Sprite *tmp;
  
  Log( TRACE, "Loading image %s", image_file );
  if( !image_file ) return NULL;
  
  /* check if the sprite is already loaded */
  tmp = _find_in_sprite_list( image_file );
  if( tmp )
  {
    tmp->ref_count++;
    return tmp;
  }
  
  if( _num_sprites + 1 >= MAX_SPRITES )
  {
    Log( WARN, "No more sprites can be made" );
    return NULL;
  }
  
  for( i = 0; i < MAX_SPRITES; i++ )
  {
    if( !_sprite_list[ i ].inuse )
    {
      _sprite_list[ i ].image = IMG_Load( image_file );
      if( !_sprite_list[ i ].image )
      {
	Log( ERROR, "Failed to load image" );
	return NULL;
      }
      
      _sprite_list[ i ].texture = SDL_CreateTextureFromSurface( Get_Renderer(), _sprite_list[ i ].image );
      if( _sprite_list[ i ].texture )
      {
	SDL_SetTextureBlendMode( _sprite_list[ i ].texture, SDL_BLENDMODE_BLEND );        
	SDL_UpdateTexture( _sprite_list[ i ].texture, NULL, _sprite_list[ i ].image->pixels, _sprite_list[ i ].image->pitch);
      }
      else
      {
	Log( ERROR, "Failed to create image texture" );
	SDL_FreeSurface( _sprite_list[ i ].image );
	return NULL;
      }
        
      _sprite_list[ i ].file_name = strdup( image_file );
      _sprite_list[ i ].num_cols = cols;
      _sprite_list[ i ].num_rows = rows;
      _sprite_list[ i ].num_frames = frames;
      _sprite_list[ i ].dynamic = dynamic;
      _sprite_list[ i ].ref_count = 1;
      _sprite_list[ i ].inuse = 1;
      _sprite_list[ i ].frame_w = _sprite_list[ i ].image->w / cols;
      _sprite_list[ i ].frame_h = _sprite_list[ i ].image->h / rows;
      
      _num_sprites++;
      
      return &_sprite_list[ i ];
    }
  }
  
  Log( WARN, "Sprite %s did not load.", image_file );
  return NULL;
}


void draw_sprite( Sprite *sprite, vec2_t position, vec2_t scale, vec2_t rotation, uint32 frame )
{
  SDL_Rect cell, target;
  
  if( !sprite ) return;
  
  set_rect( &cell, frame % sprite->num_cols * sprite->frame_w, frame / sprite->num_cols * sprite->frame_h, sprite->frame_w, sprite->frame_h );
  set_rect( &target, position[ 0 ], position[ 1 ], sprite->frame_w, sprite->frame_h );
  
  SDL_RenderCopyEx( Get_Renderer(), sprite->texture, &cell, &target, 0, NULL, SDL_FLIP_NONE );
}


void free_sprite( Sprite *sprite )
{
  if( !sprite ) return;
  
  free( sprite->file_name );
  SDL_DestroyTexture( sprite->texture );
  SDL_FreeSurface( sprite->image );
  memset( sprite, 0, sizeof( struct sprite_s ) );
}


void close_sprite_system()
{
  int i;
  
  Log( INFO, "Closing Sprite System" );
  
  for( i = 1; i < MAX_SPRITES; i++ )
  {
    free_sprite( &_sprite_list[ i ] );
  }
  
  Log( INFO, "Sprite System Closed" );
}


/* eof */