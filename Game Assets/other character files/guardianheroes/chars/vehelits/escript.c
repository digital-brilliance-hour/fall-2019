
void anichange(void Ani)
{ // Animation changer
    void self = getlocalvar("self");

    changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
}

void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");

    setidle(self, openborconstant("ANI_IDLE"));
}

void offscreenkill( float dx, int E )
{// Check position relative to screen. If enemy is offscreen, suicide!
//  dx : Distance to screen edge
//  E  : Edge selection, 0 = left, 1 = right

    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int XPos = openborvariant("xpos"); //Get screen edge's position

    if( (x > XPos + 320 + dx) && (E == 1) ){ // Offscreen to the right?
      killentity(self); //Suicide!
    } else if( (x < XPos - dx) && (E == 0) ){ // Offscreen to the left?
      killentity(self); //Suicide!
    }
}

void groundkill()
{// Check altitude. If bomb is on ground, suicide!

    void self = getlocalvar("self");
    int y = getentityproperty(self,"a"); //Get bomb's altitude

    if( y <= 5 ){ // On ground?
      killentity(self); //Suicide!
    }
}

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}

void suicidePar()
{ // Suicide if Parent dies
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    int  Health = getentityproperty(Parent, "health");

    if (Health <= 0){
//    if (Parent == NULL()){
      damageentity(self, self, 1000, 0, openborconstant("ATK_NORMAL"));
    }
}

void mapPar()
{ // Match remap with Parent's
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    int  Map = getentityproperty(Parent, "map");

    changeentityproperty(self, "map", Map); //Adjust remap
}

void looper(int Frame, int Limit)
{// Loops current animation
    void self = getlocalvar("self");
    void loop = getlocalvar("Loop" + self);

    if(loop==NULL()){ // Localvar empty?
      setlocalvar("Loop" + self, 0);
      loop = 0;
    } 
   
    if(loop < Limit){ // loops reach limit?
      setlocalvar("Loop" + self, loop+1); // Increment number of loops
      updateframe(self, Frame); //Change frame
    } else if(loop==Limit){ // loops reach limit?
      setlocalvar("Loop" + self, NULL());
    }
}

void move(int dx, int dz,int da)
{ // Moves entity freely or ignores obstacles
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int a = getentityproperty(self,"a"); //Get character's a coordinate
    int dir = getentityproperty(self,"direction"); //Get character's facing direction

     if(dir==0){ // Facing left?
      changeentityproperty(self, "position", x-dx, z+dz, a+da); //Move
     }
     else if(dir==1){ // Facing right?
      changeentityproperty(self, "position", x+dx, z+dz, a+da); //Move
     }
}

void ground()
{ // Drops enemy to ground instantly
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate

    changeentityproperty(self, "position", x, z, 0); //Ground
}

void changemap(int iMap)
{// Change remap
    void self = getlocalvar("self");

    changeentityproperty(self, "map", iMap); //Change remap
}

void degravity(int Ratio)
{// Changes antigravity effect
    void self = getlocalvar("self");
    changeentityproperty(self, "antigravity", Ratio);
}

void clearL()
{ // Clears all local variables
     clearlocalvar();
}

void spawn01(void vName, float fX, float fY, float fZ)
{
	//spawn01 (Generic spawner)
	//Damon Vaughn Caskey
	//07/06/2007
	//
	//Spawns entity next to caller.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    
	return vSpawn; //Return spawn.
}

void spawner(void vName, float fX, float fY, float fZ)
{	//Spawns entity next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}

void spawner2(void vName, float fX, float fY, float fZ)
{//Spawns entity next to caller with same remap as spawner's.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iMap = getentityproperty(self, "map");
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "map", iMap); //Use same remap as spawner's.
    
	return vSpawn; //Return spawn.
}

void spawnChainPoint(void vName, float fX, float fY, float fZ)
{	//Spawns chain point next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

      setentityvar(self, 0, vSpawn); // Stores spawned chain point for chain links
	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}

void spawnChainLink(void vName, float Ratio, float fX, float fY, float fZ)
{	//Spawns chain link next to caller, set them as child, give it the other chain point and set chain ratio
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
      void vCPoint = getentityvar(self, 0);
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
      setentityvar(vSpawn, 0, vCPoint); // Gives chain point to chain link
      setentityvar(vSpawn, 2, Ratio); // Gives chain point its chain ratio
    
	return vSpawn; //Return spawn.
}

void shoot(void Shot, float dx, float dy, float Vx, float Vy)
{ // Shooting projectile with speed control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z, y+dy, Direction, 0, 0, 0);
   changeentityproperty(vShot, "velocity", Vx, 0, Vy);
   changeentityproperty(vShot, "speed", Vx);
}

void shooter(void Shot, float dx, float dy, float Vx, float Vy)
{ // Shooting special projectile with speed control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = spawn01(Shot, dx, dy, 0);
   changeentityproperty(vShot, "velocity", Vx, 0, Vy);

   return vShot;
}

void shoot2(void Shot, float dx, float dy)
{ // Shooting targetted projectile
   void self = getlocalvar("self");
   int Map = getentityproperty(self, "map");
   float Vx = getlocalvar("x"+self);
   float Vy = getlocalvar("y"+self);
   void vShot;

   if( Vx!=NULL() && Vy!=NULL() ){
     vShot = shooter(Shot, dx, dy, Vx, Vy);
     changeentityproperty(vShot, "velocity", Vx, 0, 2*Vy); //Move projectile towards target!
     changeentityproperty(vShot, "map", Map); //Set map.
   }
}

void shoot3(void vName, float fX, float fY, float fZ, float Vy)
{//Spawns projectile next to caller. Used for shooting targetted and diving projectiles.
//Used by Belial
 //vName: Model name of entity to be spawned in.
 //fX: X location adjustment.
 //fZ: Y location adjustment.
 //fY: Z location adjustment.
 //Vy: Dive speed.

	void self = getlocalvar("self"); //Get calling entity.
      int Direction = getentityproperty(self, "direction");
	void vSpawn; //Spawn object.
      float Vx = getlocalvar("x"+self);
      float Vz = getlocalvar("z"+self);
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in projectile.

      if( Vx!=NULL() && Vy!=NULL() && Vz!=NULL() ){
        changeentityproperty(vSpawn, "velocity", Vx, Vz, Vy); //Move projectile towards target!

        if (Direction == 0){ //Is entity facing left?                  
          changeentityproperty(vSpawn, "speed", -Vx);
        } else {changeentityproperty(vSpawn, "speed", Vx);}
      }

	return vSpawn; //Return spawn.
}

void shootF(void Shot, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{ // Shooting projectile with speed control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
   changeentityproperty(vShot, "velocity", Vx, Vz, Vy);
   changeentityproperty(vShot, "speed", Vx);
}

void shootD(void vName, float fX, float fY, float fZ, float Vx, float Vy, float Vz)
{//Spawns projectile next to caller. Used for shooting diving projectiles.
//Used by Belial
 //vName: Model name of entity to be spawned in.
 //fX: X location adjustment.
 //fZ: Y location adjustment.
 //fY: Z location adjustment.
 //Vx: X speed.
 //Vy: Dive speed.
 //Vz: Z speed.

   void self = getlocalvar("self"); //Get calling entity.
   int Direction = getentityproperty(self, "direction");
   void vSpawn; //Spawn object.
	
   vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in projectile.
   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   changeentityproperty(vSpawn, "velocity", Vx, Vz, Vy);
   changeentityproperty(vSpawn, "speed", Vx);

   return vSpawn; //Return spawn.
}

void toss(void Bomb, float dx, float dy)
{ // Tossing bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   projectile(Bomb, x+dx, z, y+dy, Direction, 0, 1, 0);
}

void toss2(void Bomb, float dx, float dy, float Vy)
{ // Tossing targetted bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float Vx = getlocalvar("x"+self)/2;
   float Vz = getlocalvar("z"+self)/2;
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Bomb, x+dx, z, y+dy, Direction, 0, 1, 0);

   if( Vx!=NULL() && Vz!=NULL() ){
     tossentity(vShot, Vy, Vx, Vz); //Toss projectile towards target!
     if (Vx < 0 && Direction == 1){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 0);
     } else if(Vx > 0 && Direction == 0){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 1);
     }
     if ( Vx < 0 ){ //Is Vx negative?
       Vx = -Vx;
     }
     changeentityproperty(vShot, "speed", Vx);
   }
}

void tosser(void Bomb, float dx, float dy, float Vx, float Vy)
{ // Tossing bomb with desired speed
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void Shot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   Shot = projectile(Bomb, x+dx, z, y+dy, Direction, 0, 1, 0);
   tossentity(Shot, Vy, Vx, 0);
   changeentityproperty(Shot, "speed", Vx); 
}

void tosser2(void Bomb, float dx, float dy, float Vx, float Vy)
{ // Tossing special bomb with desired speed
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void Shot;

   Shot = spawn01(Bomb, dx, dy, 0);
   tossentity(Shot, Vy, Vx);
}

void target(float Velx, float Velz, float dx, float dz, int Stop)
{// Targetting opponent before leaping or dashing.
// Velx = x Velocity
// Velz = z Velocity
// dx = x added distance
// dz = z added distance
// Stop = flag to stop moving if no target is found

    void self = getlocalvar("self");

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    setlocalvar("x"+self, target1(target, Velx, Velz, dx, dz, Stop, "x") );
    setlocalvar("z"+self, target1(target, Velx, Velz, dx, dz, Stop, "z") );

    setlocalvar("T"+self, NULL()); //Clears variable
}

void targetdash(float Velx, float Velz, float dx, float dz, int Stop)
{// Targetting opponent then dash
// Velx = x Velocity
// Velz = z Velocity
// dx = x added distance
// dz = z added distance
// Stop = flag to stop moving if no target is found

    void self = getlocalvar("self");
    float Vx;
    float Vz;

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    Vx = target1(target, Velx, Velz, dx, dz, Stop, "x");
    Vz = target1(target, Velx, Velz, dx, dz, Stop, "z");

    changeentityproperty(self, "velocity", Vx, Vz); //Move towards target!
    setlocalvar("T"+self, NULL()); //Clears variable
}

void targetdashT(float Time, float dx, float dz)
{// Targetting opponent then dash
// Entity will reach opponent within specified time
// Time = specified time
// dx = x added distance
// dz = z added distance

    void self = getlocalvar("self");
    float Vx;
    float Vz;

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    Vx = target1T(target, Time, dx, dz, "x");
    Vz = target1T(target, Time, dx, dz, "z");

    changeentityproperty(self, "velocity", Vx, Vz); //Move towards target!
    setlocalvar("T"+self, NULL()); //Clears variable
}

void targetPar(float Velx, float Velz, float dx, float dz, int Stop)
{// Targetting parent before dashing
// Velx = x Velocity
// Velz = z Velocity
// dx = x added distance
// dz = z added distance
// Stop = flag to stop moving if there's no parent

    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");

    setlocalvar("x"+self, target1(Parent, Velx, Velz, dx, dz, Stop, "x") );
    setlocalvar("z"+self, target1(Parent, Velx, Velz, dx, dz, Stop, "z") );
}

void targetParT(float Time, float dx, float dz)
{// Targetting parent before dashing
// Produced velocity will be required speed to get to target within specified time
// Time = Specified time
// dx = x added distance
// dz = z added distance

    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");

    setlocalvar("x"+self, target1T(Parent, Time, dx, dz, "x") );
    setlocalvar("z"+self, target1T(Parent, Time, dx, dz, "z") );
}

void chain(void Pos)
{// Find coordinate between 2 coordinates based on Ratio 
// The 2 entities are Parent's coordinates and chain point
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    void CPoint = getentityvar(self, 0);
    float Ratio = getentityvar(self, 2);
    float Px = getentityproperty(Parent, "x");
    float Pz = getentityproperty(Parent, "z");
    float Py = getentityproperty(Parent, "a");
    float Ox = getentityproperty(CPoint, "x");
    float Oz = getentityproperty(CPoint, "z"); 
    float Oy = getentityproperty(CPoint, "a"); 
    float Tx;
    float Tz; 
    float Ty; 

//Get in between coords based on Ratio
    Tx = (Ox-Px)*Ratio + Px;
    Tz = (Oz-Pz)*Ratio + Pz;
    Ty = (Oy-Py)*Ratio + Py;

    if(Pos == "x"){
      return Tx;
    } else if(Pos == "z"){
      return Tz;
    } else if(Pos == "y"){
      return Ty;
    }
}

void telechain()
{// Targetting coordinate between 2 coordinates
    void self = getlocalvar("self");
    float Tx = chain("x");
    float Tz = chain("z");
    float Ty = chain("y");

    changeentityproperty(self, "position", Tx, Tz, Ty); //Teleport!
}

void target0(float Velx, float Velz, float Tx, float Tz, float dx, float dz, void Vel)
{// Basic Targetting certain coordinate before dashing
// Velx = Desired x Velocity
// Velz = Desired z Velocity
// Tx = target x coordinate
// Tz = target z coordinate
// dx = x added distance
// dz = z added distance
// Vel = Desired output

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
    float Vx;
    float Vz;

    if(Tx < x){
      changeentityproperty(self, "direction", 0);
    } else {
      changeentityproperty(self, "direction", 1);
    }

    x = x+dx;
    z = z+dz;
    float Disx = Tx - x;
    float Disz = Tz - z;

//Set both distance as positive value
    if(Disx < 0){
      Disx = -Disx;
    }

    if(Disz < 0){
      Disz = -Disz;
    }

// Calculate velocity for targetting
    if(Disz < Disx)
    {
      if(Tx < x){
        Vx = -Velx;
      } else { Vx = Velx; }

      Vz = Velx*(Tz-z)/Disx;
    } else {
      if(Tz < z){
        Vz = -Velz;
      } else { Vz = Velz; }

      Vx = Velz*(Tx-x)/Disz;
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "z"){
      return Vz;
    }
}

void target0T(float Time, float Tx, float Tz, float dx, float dz, void Vel)
{// Basic Targetting certain coordinate before dashing
// Produced velocity will be required speed to get to target within specified time
// Time = specified time
// Tx = target x coordinate
// Tz = target z coordinate
// dx = x added distance
// dz = z added distance
// Vel = Desired output

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
    float Vx;
    float Vz;

    if(Tx < x){
      changeentityproperty(self, "direction", 0);
    } else {
      changeentityproperty(self, "direction", 1);
    }

    x = x+dx;
    z = z+dz;
// Calculate velocity for targetting

    Vx = (Tx-x)/Time;
    Vz = (Tz-z)/Time;

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "z"){
      return Vz;
    }
}

void target1(void Target, float Velx, float Velz, float dx, float dz, int Stop, void Vel)
{// Targetting certain entity before dashing
// Target = Targetted entity
// Velx = Desired x Velocity
// Velz = Desired z Velocity
// dx = x added distance
// dz = z added distance
// Stop = flag to stop moving if there's no target

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
    float Vx;
    float Vz;

    if (dir == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
    }

    if( Target != NULL()){
      float Tx = getentityproperty(Target, "x");
      float Tz = getentityproperty(Target, "z");

      Vx = target0(Velx, Velz, Tx, Tz, dx, dz, "x");
      Vz = target0(Velx, Velz, Tx, Tz, dx, dz, "z");
    } else {
      if(Stop == 1)
      {
        Vz = 0;
        Vx = 0;
      } else {
        Vz = 0;
        if(dir==0){
          Vx = -Velx;
        } else { Vx = Velx; }
      }
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "z"){
      return Vz;
    }
}

void target1T(void Target, float Time, float dx, float dz, void Vel)
{// Targetting certain entity before dashing
// Produced velocity will be required speed to get to target within specified time
// Target = Targetted entity
// Time = Specified time
// dx = x added distance
// dz = z added distance

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
    float Vx;
    float Vz;

    if (dir == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
    }

    if( Target != NULL()){
      float Tx = getentityproperty(Target, "x");
      float Tz = getentityproperty(Target, "z");

      Vx = target0T(Time, Tx, Tz, dx, dz, "x");
      Vz = target0T(Time, Tx, Tz, dx, dz, "z");
    } else {
      Vz = 0;
      Vx = 0;
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "z"){
      return Vz;
    }
}

void dash()
{// Dash with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    if( Vx!=NULL() && Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx, Vz); //Move towards target!
    }
}

void dasher( float Vx, float Vz, float Vy)
{// Dash with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move!
}

void PdashX()
{// Dash with previously attained speed but only X one!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    if( Vx!=NULL() ){
      changeentityproperty(self, "velocity", Vx);
    }
}

void PdashZ()
{// Dash with previously attained speed but only Z one!
    void self = getlocalvar("self");
    float Vz = getlocalvar("z"+self);
    if( Vz!=NULL() ){
      changeentityproperty(self, "velocity", 0, Vz);
    }
}

void dashF()
{// Dash with previously attained speed + Parent's speed!
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    float PVx = getentityproperty(Parent, "xdir");
    float PVy = getentityproperty(Parent, "tossv");
    float PVz = getentityproperty(Parent, "zdir");

    if( Vx!=NULL() && Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx+PVx, Vz+PVz, PVy); //Move together!
    }
}

void leaper( float Vx, float Vy)  // !!
{// Leap with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    tossentity(self, Vy, Vx); //Leap!
}

void dodgez( float Vx, float Vy, float Vz )
{// Dodge by moving up or down depending on z location
    void self = getlocalvar("self");
    int z = getentityproperty(self, "z");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    if(z > (openborconstant("PLAYER_MIN_Z") + openborconstant("PLAYER_MAX_Z")) / 2 ) {
      Vz = -Vz ;
    }

    if( Vx!=NULL() && Vy!=NULL() && Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx, Vz, Vy); //Dodge away!
    }
}

void teledodgez( float dx, float dy, float dz )
{// Dodge by teleporting up or down depending on z location
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int a = getentityproperty(self,"a"); //Get character's a coordinate
    int dir = getentityproperty(self,"direction"); //Get character's facing direction
    float H;
    int FZ;

    if(z > (openborconstant("PLAYER_MIN_Z") + openborconstant("PLAYER_MAX_Z")) / 2 ) {
      dz = -dz ;
    }
    FZ = z+dz;

    if(dir==0){ // Facing left?
      dx = -dx ;
    }

    if((z + dz) > openborconstant("PLAYER_MAX_Z")) {
      FZ = openborconstant("PLAYER_MAX_Z");
    } else if((z + dz) < openborconstant("PLAYER_MIN_Z")) {
      FZ = openborconstant("PLAYER_MIN_Z");
    }

    H = checkwall(x+dx,FZ);

    if(H > 0){ // Is there a wall on teleport destination?
      dx = -dx ;
    }

    changeentityproperty(self, "position", x+dx, FZ, a+dy); //Teleport away!
}

void teletarget(int dx, int dy, int dz)
{// Targetting opponent then teleport to target
    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");

    if(dir==0){ // Facing left?
      dx = -dx ;
    }

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    if( getlocalvar("T"+self) != NULL()){
      void target = getlocalvar("T"+self);
      int Tx = getentityproperty(target, "x");
      int Tz = getentityproperty(target, "z");

      changeentityproperty(self, "position", Tx+dx, Tz+dz, dy); //Teleport to target!
    } 
}

void leap(float Vely)
{// Leap with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    if( Vx!=NULL() && Vz!=NULL() ){
      tossentity(self, Vely, Vx, Vz); //Leap towards target!
    }
}

void stop()
{// Stop enemy's movement!
    void self = getlocalvar("self");
    changeentityproperty(self, "velocity", 0, 0, 0); //Stop moving!
}

void attack0(void Ani)
{// Attack interruption 
    void self = getlocalvar("self");

    performattack(self, openborconstant(Ani)); //Change the animation
}

void attack1(int RxMin, int RxMax, int RzMin, int RzMax, void Ani)
{// Attack interruption with range check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Tz = getentityproperty(target, "z");
      float Disx = Tx - x;
      float Disz = Tz - z;

      if( Disx >= RxMin && Disx <= RxMax && Disz >= RzMin && Disz <= RzMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -RxMax && Disx <= -RxMin && Disz >= RzMin && Disz <= RzMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}
