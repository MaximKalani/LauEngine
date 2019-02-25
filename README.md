# LauEngine
C++ 2D Game Engine based on SDL2 
Fork of carlbirch's [BirchEngine](https://github.com/carlbirch/BirchEngine)

# Made changes:
- Map's function LoadMap() now takes one additional argument - int destTileSize. It will set every tile's destRect height and width to desired value without need to hardcode it into TileComponent constructor.
- Removed KeyboardComponent, EventHandler added instead. EventHandler is not a Componet, so it will not update durning update() function of game loop. It has function handleInput(), which takes reference of player as an argument. It is called during handleEvents() function of game loop. This allows to poll all pending events in one game frame, but not one event per frame, as earlier.
- Added [this bug solution](https://github.com/carlbirch/BirchEngine/pull/4).

# TODO:
- Better Camera
- Relative player position
- Projectiles
- Enemies
- Combat System
- Interact Mechanic
- Animated Tiles
- Level Manager
