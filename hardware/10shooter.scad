bottle_width = 5;
bottle_count = 10;

radius = 17.5;
dispenser_radius = 3;


translate([0,0,4])
cylinder(h = 2, r=radius);

translate([0,0,-17])
cylinder(h = 20, r=radius);

translate([0,0,20])
cylinder(h = 2, r=radius);

for ( i = [1 : bottle_count] )
{
    rotate( i * 360 / bottle_count+180/bottle_count, [0, 0, 1])
    translate([0, radius-2, 6])
	 cylinder(h = 20, r=1);

}

%for ( i = [1 : bottle_count] )
{
    rotate( i * 360 / bottle_count, [0, 0, 1])
    translate([0, radius+bottle_width, 14])
	 cylinder(h = 20, r=bottle_width);

}


%for ( i = [1 : bottle_count] )
{
    rotate( i * 360 / bottle_count, [0, 0, 1])
    translate([0, radius+bottle_width, 6])
	 cylinder(h=4, r=dispenser_radius);
}