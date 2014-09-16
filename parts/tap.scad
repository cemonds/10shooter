	

module hexagram(size, height) {
  boxWidth=size/1.75;
  for (v = [[0,1],[0,-1],[1,-1]]) {
    union() {
      rotate([0,0,60*v[0]]) cube([size, boxWidth, height], true);
      rotate([0,0,60*v[1]]) cube([size, boxWidth, height], true);
    }
  }
}

module ring(radius, width, height)  {
	w = width/2;
   h = height/2;
	rotate_extrude(convexity = 10, $fn = 100)
	translate([radius, 0, 0])
//	circle(r = thickness/2, $fn = 100);
   polygon(points=[[-w,-h],[-w,h],[w,h],[w,-h]]);
}

tap_width = 9;
tap_height = 6;
tap_outer_radius = 30;
mount_radius = 32;
mount_width = 5;
mount_height = 5;


module tap() {
	rotate([0,0,90])
	difference() {
		ring(tap_outer_radius - tap_width/2, tap_width, tap_height);
		translate([tap_outer_radius-tap_width/2,0,-4.5])
			hexagram(10, 5);
		translate([-(tap_outer_radius-tap_width/2),0,-4.5])
			hexagram(10, 5);
		translate([tap_outer_radius-14,-1,-1])
			cube([15,2,2]);
		translate([-tap_outer_radius,-1,-1])
			cube([15,2,2]);
	}
}

tap();

module mount() {
	translate([0,0,mount_height/2])
	difference() {
		union() {
			translate([26.3,18,-13])
			leverage_mount();
			mirror([0,1,0])
			translate([26.3,18,-13])
			leverage_mount();
			translate([0,0,-mount_height])
			difference() {
				cylinder(h = mount_height, r = mount_radius+mount_width,$fn=200);
				cylinder(h = mount_height, r = mount_radius, $fn=200);	
			}
		}
		translate([-54,-50,-10])
		cube([50,100,20]);
		translate([0,-18,-10])
		cube([50,36,20]);
		translate([-1,-mount_radius-13,-1-mount_height/2])
			cube([2,15,2]);
		translate([-1,mount_radius-2,-1-mount_height/2])
			cube([2,15,2]);
	}
}

module leverage_mount() {
	difference() {
		cube([15,9.2,13]);
		translate([5,4.4,0])
			cube([10,1.4,2.1]);
		translate([5,4.4,13-2.1])
			cube([10,1.4,2.1]);
	}
}

mount();