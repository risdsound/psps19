
bolt_thickness=3;
wall_thickness=5;
bracket_height=28;



resolution=80;

	difference(){
		union(){
 
			//outside wall
			 cylinder(r=(bolt_thickness+.5)/2+wall_thickness,h=bracket_height+2,center=true,$fn=resolution);					

		
				}	


				//inside bolt
				color ("blue")
				cylinder(r=(bolt_thickness+.5)/2,h=bracket_height+2,center=true,$fn=resolution);				
				
}


