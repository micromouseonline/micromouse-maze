### Mouse Move Commands
	
When the micromouse performs a speed run, it is executing a series of individual moves that, together, make up the complete path. This move list is just an array of bytes where each byte describes a single move. Individual moves tell the mouse to do things like run straight for a given number of cells, turn in-place by a specific angle and perform a smoth turn.
 
 The move list is normally created from maze data by a path generator. The user is also able to create move lists manually by creating an array of moves which can be passed to the interpreter for execution. In this way it is easy to create test paths that can be repeatedly run by the mouse.
 
 Some move commands are used as markers to indicate the start and finish of a path, to tell the mouse to change its behaviour or to indicate errors in the path generation.
 
 Each move command is represented by a single byte. The move is encoded by specific bit patterns in the byte so that the interpreted can more easily do its job. There are four main categories of move command.
 
 All the move commands have symbolic names.
 
#####  Movement along orthogonal straights

The command byte encodes the number of cells in the straight using the bottom 6 bits. Thus, up to 63 cells could be run. Since there should never be a zero length move, it is convenient to also use the value 0x00 (CMD_END) as an end marker for the move list to bring the mouse to a halt.

	 Straights:
	   00LLLLLL
	   ||||||||
	   ||++++++-- Run Length in Cells (0-63)
	   ||
	   ++-------- 00 => straight (orthogonal)

Symbolic names for these moves are of the form FWD01, FWD02 . . . FWD31 
 
##### Movement along diagonals

Like the orthonoal move, diagonals encode the number of cells to traverse in the bottom 6 bits. There should be no zero length diagonal moves in a path.

	 Diagonals:
	   01LLLLLL
	   ||||||||
	   ||++++++-- Run Length in Cells (0-63)
	   ||
	   ++-------- 01 => diagonal



Symbolic names for these moves are of the form DIA01, DIA02 . . . DIA31 

##### Turns
 
 A micromouse can turn either in-place or with a smooth, integrated turn.
 
###### In-place Turns 

 An in-place, or pivot, turn leaves the mouse in the same position but facing in a different direction. There is no forward motion during a pivot turn. For the purpose of generating and running paths in the maze, all turns are multiples of 45 degrees and ay be left or right. Any other turning motion by the mouse, for example for attitude adjustment, are handled in the low level control functions and do not form part of the path generation or execution.

As with straight line motion, in-place turns have their parameters encoded as bit patterns in the command byte:

	 Turns - In Place
	   10000TTD
	   ||||||||
	   |||||||+--  0 => Turn Right
	   |||||||     1 => Turn Left
	   |||||||
	   |||||++--- 00 => IP45  Turn
	   |||||      01 => IP90  Turn
	   |||||      10 => IP135 Turn
	   |||||      11 => IP180 Turn
	   |||||
	   |||||
	   +++++----- 1000 => Turn In Place
	 
In-place turns have symbolic names like IP90R and IP180L and you will see there is a close relationship between the sumbolic name and the bit-level encoding. Not also that the numeric value of left turns is always an odd number. With eight possible in-place turns, it will be convenient to use the bottom three bits of the command byte as an index into a simple array or turn parameters if desired
 
###### Smooth Turns 

These turn types are a little more complex. Smooth turns take place while the mouse is moving forward.  The method of encoding the move in a command byte is the similar to that for in-place turns.  

	 Turns - Smooth
	   101TTTTD
	   ||||||||
	   |||||||+--  0 => Turn Right
	   |||||||     1 => Turn Left
	   |||||||
	   |||++++--- 0000 => SS90  Turn
	   |||        0001 => SS180 Turn
	   |||        0010 => SD45  Turn
	   |||        0011 => SD135 Turn
	   |||        0100 => DS45 Turn
	   |||        0101 => DS135 Turn
	   |||        0110 => DD90 Turn
	   |||        0111 => SS90E Turn
	   |||        1xxx => unused (available for complex turns)
	   |||
	   +++------- 101 => Turn Smooth
	 
As before, the turn direction is held in the bottom bit so that all left turn command bytes are odd numbers. Four bits are used to describe the turn details and there are currently eight turn types represented with the possibility of adding up to eight additional types for future expansion.

Although turns are all multiples of 45 degrees, there is no benefit to encoding the angle as individual bits. Instead, the turns are just given sequential values so that it is still possible to extract an index value into a table of turn parameters if desired. The bottom five bits provide the index.

Smooth turn symbolic names indicate whether the turn starts or finished on a straight or diagonal, the angle and the direction. For example, SD135R is a turn from a straight to a diagonal through 135 degrees, turning right. The SS90E turn is a special, small radius turn used when exploring the maze. It is guaranteed to start and finish within the same cell whereas the SS90 has a larger radius needed for speed runs. 	 
	 
 
##### Messages and Flags
  
A list of move commands may include additional entries that are not directly associated with moves. These are not essential but may find some utility for various uses. Markers can be used to change mouse behaviour. For example, when exploring the maze, a path generator may create a move list that will take the mouse rapidly to a target cell using smooth turns and diagonals. At the end of that run, the mouse may come to a halt - perhaps it is now at the start cell. Alternatively, the mouse may want to continue moving but switch back to its normal exploring state. In the first case, the move list might end with a CMD_STOP instruction and in the latter, it might end with CMD_EXPLORE.

It may also be convenient to have a special command to represent the start of the list (CMD_BEGIN) so that the interpreter can prepare the mouse for executing the remaining commands.   

Finally, the path generator may need to indicate error conditions - perhaps it is unable to properly determine a path. Provision is made for adding error codes if this is required. 

	 Messages/Flags:
	   11MMMMMM
	   ||||||||
	   ||++++++-- Message Code
	   ||         000000 => CMD_STOP
	   ||         000001 => CMD_BEGIN
	   ||         000010 => CMD_EXPLORE
	   ||         01xxxx => unused
	   ||         10xxxx => unused
	   ||         11xxxx => Error Codes
	   ||
	   ++-------- 11 => Message


