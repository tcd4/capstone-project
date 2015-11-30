#include "level.h"


static Entity	*_player;
static Sprite	*_ground_sprite;
static Sprite	*_platform_sprite;
static Sprite	*_small_platform_sprite;


void load_level_objects( char *name, vec2_t pos, vec2_t off, vec2_t size, void ( *draw )( Entity *ent ) );
void draw_ground( Entity *ground );
void draw_platform( Entity *platform );
void draw_small_platform( Entity *platform );


Level* load_level( char *file )
{
  Level *level;
  Dict *config;
  vec2_t size, offset, pos;
  
  config = Parse( file );
  if( !config )
  {
    Log( ERROR, "Couldn't parse the level %s", file );
    return NULL;
  }
  
  level = g_new0( Level, 1 );
  if( !level )
  {
    Log( ERROR, "Couldn't allocate memory for level %s", file );
    Free_Dict( &config );
    return NULL;
  }
  
  level->bg = load_sprite_from_config( "../cfg/level_bg.def" );
  _ground_sprite = load_sprite_from_config( Find_In_Dict( config, "ground" ) );
  _platform_sprite = load_sprite_from_config( Find_In_Dict( config, "platform" ) );
  _small_platform_sprite = load_sprite_from_config( Find_In_Dict( config, "small_platform" ) );
  
  Vec2_Set( level->scale, 1, 1 );
  
  /* load ground */
  Str_As_Vec2( Find_In_Dict( config, "ground_size" ), size );
  Str_As_Vec2( Find_In_Dict( config, "ground_offset" ), offset );
  Str_As_Vec2( Find_In_Dict( config, "ground_position" ), pos );
  load_level_objects( "ground", pos, offset, size, draw_ground );
  
  /* load platforms */
  Str_As_Vec2( Find_In_Dict( config, "platform_size" ), size );
  Str_As_Vec2( Find_In_Dict( config, "platform_offset" ), offset );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_0_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform0", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_1_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform1", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_2_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform2", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_3_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform3", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_4_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform4", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_5_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform5", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_6_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform6", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_7_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform7", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_8_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform8", pos, offset, size, draw_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "platform_9_position" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "platform9", pos, offset, size, draw_platform );
  
  /* load small platforms */
  Str_As_Vec2( Find_In_Dict( config, "small_platform_size" ), size );
  Str_As_Vec2( Find_In_Dict( config, "small_platform_offset" ), offset );
  
  Str_As_Vec2( Find_In_Dict( config, "small_platform_0" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "small_platform_0", pos, offset, size, draw_small_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "small_platform_1" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "small_platform_1", pos, offset, size, draw_small_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "small_platform_2" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "small_platform_2", pos, offset, size, draw_small_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "small_platform_3" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "small_platform_3", pos, offset, size, draw_small_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "small_platform_4" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "small_platform_4", pos, offset, size, draw_small_platform );
  
  Str_As_Vec2( Find_In_Dict( config, "small_platform_5" ), pos );
  Vec2_Add( pos, offset, pos );
  load_level_objects( "small_platform_5", pos, offset, size, draw_small_platform );
  
  /* load player */
  _player = create_player( Find_In_Dict( config, "player" ) );
  
  /* load enemies */
  Str_As_Vec2( Find_In_Dict( config, "enemy0_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  Str_As_Vec2( Find_In_Dict( config, "enemy1_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  Str_As_Vec2( Find_In_Dict( config, "enemy2_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  Str_As_Vec2( Find_In_Dict( config, "enemy3_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  Str_As_Vec2( Find_In_Dict( config, "enemy4_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  Str_As_Vec2( Find_In_Dict( config, "enemy5_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  Str_As_Vec2( Find_In_Dict( config, "enemy6_spawn" ), pos );
  create_enemy( Find_In_Dict( config, "enemy" ), pos );
  
  return level;
}


void free_level( Level **level )
{
  Level *tmp;
  
  if( !level ) return;
  if( !*level ) return;

  tmp = *level;
  free_sprite( tmp->bg );
  free( tmp );
  *level = NULL;
}


void load_level_objects( char *name, vec2_t pos, vec2_t off, vec2_t size, void ( *draw )( Entity *ent ) )
{
  Entity *new;
  vec2_t body_pos;
  
  new = create_entity();
  if( !new )
  {
    Log( ERROR, "couldn't make ent %s", name );
    return;
  }
  
  new->name = strdup( name );
  new->ent_type = ENT_WORLD;
  new->visible = 1;
  Vec2_Set( new->scale, 1, 1 );
  
  Vec2_Copy( off, new->offset );
  Vec2_Copy( pos, new->position );
  Vec2_Add( pos, off, body_pos );
  
  new->body = create_body( new, NO_GROUP, size, body_pos, NULL );
  add_ent_to_space( new );
  
  new->Draw = draw;
}


void draw_level( Level *level )
{
  draw_sprite( level->bg, level->position, level->scale, level->rotation, 0 );
}


void draw_ground( Entity *ground )
{
  draw_sprite( _ground_sprite, ground->position, ground->scale, ground->rotation, 0 );
}


void draw_platform( Entity *platform )
{
  draw_sprite( _platform_sprite, platform->position, platform->scale, platform->rotation, 0 );
}


void draw_small_platform( Entity *platform )
{
  draw_sprite( _small_platform_sprite, platform->position, platform->scale, platform->rotation, 0 );
}


Entity* get_player()
{
  return _player;
}


/* eof */