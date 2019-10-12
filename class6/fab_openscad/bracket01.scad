WallThickness = 3;

CutoutWidth = 10;

length = 150;
Height = 10;
Width = CutoutWidth + WallThickness;



BracketThickness = 4;
BracketScrews = 3.125;
MountScrews = 4;



Resolution = 100;




//bracket ();

difference ()
{
    
    screwBrackets ();
    //bracket ();
    //cutout ();
}

///////////////////////////////////////////
module bracket ()
{
    // top
    cube ([length, Width, Height * 2]);
    
    // bottom 
    translate([0, - Width /2, 0])
    cube ([length, Width * 2, WallThickness]);
    
    // mounting brackets
    for (i = [[ MountScrews + WallThickness, MountScrews + (WallThickness *2) + CutoutWidth, 0],
        [ length - (MountScrews + WallThickness) , MountScrews + (WallThickness *2) + CutoutWidth, 0],
        [ length /2, MountScrews - WallThickness - CutoutWidth, 0 ]]) 
    
        translate(i)
        cylinder (h = WallThickness, r = MountScrews + WallThickness , $fn = Resolution);  
}

///////////////////////////////////////////
module screwBrackets ()
{
    difference ()
    {
        union ()
        {
            translate([- (MountScrews + WallThickness) , - (MountScrews + WallThickness) * 2, , 0])
            cube ( [(MountScrews + WallThickness) * 2, (MountScrews + WallThickness) * 2, WallThickness]);     
            cylinder (h = WallThickness, r = MountScrews + WallThickness , $fn = Resolution); 
        }
        
        cylinder (h = WallThickness + 50, r = MountScrews , $fn = Resolution);
    }
}

//////////////////////////////////////////
module cutout ()
{
    // top
    translate ([0, (Width /2) -  (CutoutWidth/2) , WallThickness])
    cube ([length, CutoutWidth , Height * 2]);
    
    
    // mounting bracket holes
    for (i = [[ MountScrews + WallThickness, MountScrews + (WallThickness * 4), 0], 
        [ length - (MountScrews + WallThickness) , MountScrews + (WallThickness * 4), 0], 
        [ length /2, - CutoutWidth, 0 ]]) 

    {
        translate(i)
        cylinder (h = WallThickness, r = MountScrews , $fn = Resolution);
    }   
    
    /* Bracket Screws holes
    for ( r= [[ MountScrews + WallThickness, MountScrews + (WallThickness * 4), 0],
        [ length - (MountScrews + WallThickness), MountScrews + (WallThickness * 4), 0],
        [ length /2, - MountScrews - 2, 0 ]])
    
    {
        translate (r)
        rotate ([0, 0, 0])
        cylinder (h = (WallThickness * 2) + CutoutWidth , r = BracketScrews , $fn = Resolution);
    }*/
}