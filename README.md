# AtariBrickBrock
This C++ game is coded within the Eclipse IDE, and is a knock-off of the classic Atari breakout game. 
I combined the name of that game with the name given to us for this project, namely BipBop, to get BrickBrock. 

The project is divided up in several header files, each for a separate class. 

## Ball
The ball is an object which moves around the window on its own, using the x_speed and y_speed to determine its direction. It bounces off objects by checking for collisions using the collision points (c_point) around its circumference.

## Brick and Bricks
The bricks are squares that have a hit point attribute to track their current hp. If their hp reaches 0, they 'die' and are deleted from the window. The Bricks class stores the bricks in a vector and uses that vector to easily iterate over all Brick objects and either display, return, modify, or delete them.

## Paddle
The paddle is either controlled by the player using the left and right arrow keys on the keyboard, or by the game itself. It cannot move outside the window's boundaries. The ball bounces off of it. The front and back ends of the paddle bounce the ball a little differently, by adding or subtracting 22.5 degrees to/from the ball's angle of incidence.

## Infobox
The infobox class houses all the information needed to create the various permanent or consistent pop-up boxes on-screen.

## GameWindow
The gamewindow class runs the entirety of the game. It contains the screen-refresh loop and all above mentioned objects.
