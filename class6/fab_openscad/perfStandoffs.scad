//how many boards?
board_number=2;

//base hight: 
base_height=3;

//space between boards:
perf_board_spacing=38;



/////////////////////////////////////////////


horz_space=2;

wall_hight= perf_board_spacing*(board_number-1);

bolt_thickness=3;

wall_thickness=2;

wall_width=50;

perf_thickness=2;

wall_hole_hight=perf_board_spacing-wall_thickness;

resolution=80;

	difference()
{
		union()
	{
 
	
//main wall board hights
			translate([0, 1,0])
				cube([wall_width, wall_thickness+2, wall_hight + base_height+perf_thickness]);	

//bolt post 
			color ("orange")
			translate([wall_width/2,0, 0])
				cylinder(r=(bolt_thickness/2)+wall_thickness,h=wall_hight + base_height+perf_thickness,$fn=resolution);			

		
	
}
//bolt post cutout
			color ("blue")
			translate([wall_width/2,0,-1])
				cylinder(r=(bolt_thickness+.75)/2,h=wall_hight + base_height+perf_thickness+2,$fn=resolution);
	

//perfboard cutout slot
	for (i = [0:(board_number-1)])
	{
			color ("purple")
			translate([0, -bolt_thickness*2 ,base_height+perf_board_spacing*i])
				cube([wall_width,(bolt_thickness*2)+(wall_thickness*2),perf_thickness]);
	}

//wall holes
	for (i = [0:(board_number-2)])
	{
			color ("cyan")
			translate([2.50,0,base_height+perf_board_spacing*i])
				cube([19,bolt_thickness+wall_thickness,wall_hole_hight]);

			color ("cyan")
			translate([28.5,0,base_height+perf_board_spacing*i])
				cube([19,bolt_thickness+wall_thickness,wall_hole_hight]);
	}

			
}


