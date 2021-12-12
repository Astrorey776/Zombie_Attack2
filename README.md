# Zombie_Attack

## TEAM MEMBERS:

  * Pau Olmos
  * Adrián Martín

## CONTROLS:

Normal:

 * D: Move right
 * A: Move Left
 * K: Eat (attack)
 * SPACE: Jump

While on God Mode:
  
 * D: Move right
 * A: Move Left
 * W: Move up
 * S: Move Down
  
## DEBUG FEATURES:

  * F1: Show/Hide hitboxes
  * F3: Respawn at the beggining
  * F5: Save position
  * F6: Load position
  * F10: Activate/disable God Mode
  
## GAME DESCRIPTION:
  
  Run across the city avoiding the obstacles and unleash the caos killing as many peaople as possible until the zombie arrives to the end of the map or dies.

## DEVELOPMENT PROCESS:

The game has a gravity that pulls the character to the ground, that by the moment, hasd no hitbox and it is a fix int. The jump gives the character some vertical velocity so it goes up and down smoothly. The gravity disappears with the God Mode so the player can move freely at any direction and stay in the mid of the air if it is wanted.

When pressing F1, the red squares indicate the places where the character will be able to walk through and the green ones, where he will die, otherwise, if the character arrives at the end of the map, he will get blocked and win.

The camera is programmed in a way that it gets blocked if the character is arriving at the end of the map so it does not show the blank after the map

Saving and loading the game works on the same session or even after closing the game.

The program has "FPS limiter", "Frame Counter" and the "Vsync" is on.

## IMPROVEMENTS:

* Colisions (both lateral, down vertical and up vertical that allows to jump from the bottom to the top)
* Pop ups explaining the controls of the game
* Improvement on the design of the first and unique level
* Health system that sums hearts if the player touches any heart distributed on the map and substracts one if the character recieves damage
* Damage recieved and response of the character if it touches the spikes
* Ability to eat people around the map pressing the key K
* Two kinds of enemies (land and air)
* The land enemy (soldier) spawns when the player gets nearvy to its area and has a patrol route which disapears when the player gets nearby. When this happens, the enemy has more velocity and red eyes. The enemy has also colliders and is able to jump over "stairs". The enemy can be killed jumping on him while pressing K.
* The air enemy (helicopter) spawns too when the character arrives to a certain area and follows the player untill it dies. Touching the razors of the helicopter or being crushed by him will kill the player instantly, however, touching the helicopter from the sides will substract one heart. The helicopter can be killed jumping at his bottom.
* There are now two checkpoints (graves), which change when they are activated.
* When killing anything on the map, a dead version of it will appear on the right top of the screen to be able to measure the amount of destruction and death.
* F1 now shows a lot more of colliders

## DEVELOPMENT PROCESS II:

The main issues durning the development of the second assignement have been with files rather than with the code, the Optick program difficulted working on the project some days, the pathfing files also slowed down the coding rithm so we skipped the taught pathfinding and developed an alternative enemy movement based on the player coordinates (screen).

It was intentioned to put some audio and fx to the game but did not know at all how to do it so it does not have nothing new.

The testing has been essencial to improve mechanics, solve bugs and crushes and find a good distribution of each elemnt to try to make funny and interesting the game.

While coding the checkpoints, applying the same function as F5 (save) did not gave us the same resultand because of the deadline, we were not able to find a solution so, sadly, the graves (checkpoints) are just aesthetic by the moment.

We did not have a lot of trouble neither finding assets nor modifing them. 

The other game features had a normal level of difficulty and did not felt frustated while coding them.

## LINK TO OUR GITHUB:

https://github.com/Astrorey776/Zombie_Attack
