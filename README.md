# LauEngine
SDL2 C++ 2D Game Engine
Fork of carlbirch's [BirchEngine](https://github.com/carlbirch/BirchEngine)

# Made changes:
- Map's function LoadMap now takes one additional argument - int destTileSize. It will set every tile's destRect height and width to desired value without need to hardcode it into TileComponent constructor.
- Removed KeyboardComponent, EventHandler added instead. EventHandler is not a Componet, so it will not update durning update() function of game loop. It has function handleInput, which takes reference of player as an argument. It is called during handleEvents() function of game loop. This allows to poll all pending events in one game frame, but not one event per frame, as earlier.

# TODO:
- Better Animations
- Enemies
- Level Manager
- Smooth Camera Movement
