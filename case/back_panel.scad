$fn=64;
eps = 0.04;
inch = 25.4;

panel_x = 68.76;
panel_y = 19.84;
panel_z = 1.5;
panel_r = 0.05 * inch;

barrel_x = 0.354*inch;
barrel_y = 0.428*inch;

module dsub(c,e,a)
{
   r=3.35;
   h=3.96;
   md=3.05;
   hull() {
      translate([-c/2,h/2,0])
         circle(r=r);
      translate([c/2,h/2,0])
         circle(r=r);
      translate([-e/2,-h/2,0])
         circle(r=r);
      translate([e/2,-h/2,0])
         circle(r=r);
   }
   translate([-a/2,0,0])
      circle(d=md);
   translate([a/2,0,0])
      circle(d=md);
}

module dsub9() {
   dsub(c=13.77,e=12.01,a=24.99);
}

difference() {
   linear_extrude(height=panel_z) {
      hull() {
         translate([panel_r, panel_r, 0]) {
            circle(r=panel_r);
         }
         translate([panel_x-panel_r, panel_r, 0]) {
            circle(r=panel_r);
         }
         translate([panel_x-panel_r, panel_y-panel_r, 0]) {
            circle(r=panel_r);
         }
         translate([panel_r, panel_y-panel_r, 0]) {
            circle(r=panel_r);
         }
      }
   }
   translate([panel_x/2 - 12.015, panel_y/2, -eps] ) {
      linear_extrude(height=panel_z+2*eps) {
         dsub9();
      }
   }
   translate([panel_x/2+13.33,6.17+barrel_y/2,-eps]) {
      linear_extrude(height=panel_z+2*eps) {
         square([barrel_x, barrel_y],center=true);
      }
   }
}