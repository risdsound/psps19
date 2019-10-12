WallThickness = 3;

CutoutWidth = 6;

length = 136;
Height = 8;
Width = CutoutWidth + (WallThickness * 2);



OverallWidth = CutoutWidth + (WallThickness * 4);
SideScrews = 3.5 / 2;
MountScrews = 5.125/ 2;



Resolution = 100;




//bracket ();

difference ()
{
    bracket ();
    //rotate ([40, 0, 0])
    SideScrew ();
    cutout ();
}

///////////////////////////////////////////
module bracket ()
{
    // top
    cube ([length, Width, Height + WallThickness]);
    
    // bottom 
    translate([0, - WallThickness , 0])
    cube ([length, OverallWidth, WallThickness]);
    
    // mounting brackets
    for (i = [[ MountScrews + WallThickness, MountScrews + OverallWidth - WallThickness, 0],
        [ length - (MountScrews + WallThickness), MountScrews + OverallWidth - WallThickness, 0]//,
        //
        ]) 
    {
        translate(i)
        screwBrackets (); 
    }
        
    // middle screw hole
    rotate ([0, 0, 180,])
    translate([ - length / 2, MountScrews + WallThickness, 0])
    screwBrackets ();  
}

///////////////////////////////////////////
module SideScrew ()
{
  // mounting brackets
    for (i = [[ MountScrews + WallThickness, 0, (Height / 2) + WallThickness],
        [ length - (MountScrews + WallThickness),0, (Height / 2) + WallThickness]
        ]) 
    {
        translate(i)
        rotate ([0,90,90])
        cylinder (h = Width, r = SideScrews, $fn = Resolution); 
    }
        
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
        
        cylinder (h = WallThickness, r = MountScrews , $fn = Resolution);
    }
}

//////////////////////////////////////////
module cutout ()
{
    // top
    translate ([0, (Width /2) -  (CutoutWidth/2) , WallThickness])
    cube ([length, CutoutWidth , Height * 2]);
}