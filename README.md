# TempleLib
A C Library that aims provides a graphics interface similar to TempleOS. It is built with GTK.

## Goals
 - Custom window borders.
 - Support for DolDoc formatting commands.
 - Support for all the basic Gr and Doc commands.
 - Implement the input interface.
 - User applications should not have to interact with any GTK/dependancies data structures or functions.
 - Thread Safety (CURRENTLY NOT).

## Future Things
 - Use a library that is more lightweight than GTK. I feel like GTK is a bit too much bloat for the size
   of the project. I understand that it can be dynamically linked, but the overhead on the code is a bit
   annoying.
