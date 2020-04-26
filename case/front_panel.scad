$fn=64;
eps = 0.04;
inch = 25.4;

panel_x = 68.76;
panel_y = 19.84;
panel_z = 1.5;
panel_r = 0.05 * inch;

lens_x = 2.363 * inch;
lens_y = 0.592 * inch;
lens_z = 0.062 * inch;

bezel_x = 2.258 * inch;
bezel_y = 0.487 * inch;
bezel_r = 1/16 * inch;

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
   translate([panel_x/2,panel_y-1.27-lens_y/2,0.4]) {
      linear_extrude(height=panel_z+2*eps) {
         square([lens_x+2*eps, lens_y+2*eps],center=true);
      }
   }
   translate([panel_x/2,panel_y-1.27-lens_y/2,-eps]) {
      linear_extrude(height=panel_z+2*eps) {
         hull() {
            translate([-bezel_x/2+bezel_r, -bezel_y/2+bezel_r, 0]) {
               circle(r=bezel_r);
            }
            translate([bezel_x/2-bezel_r, -bezel_y/2+bezel_r, 0]) {
               circle(r=bezel_r);
            }
            translate([bezel_x/2-bezel_r, bezel_y/2-bezel_r, 0]) {
               circle(r=bezel_r);
            }
            translate([-bezel_x/2+bezel_r, bezel_y/2-bezel_r, 0]) {
               circle(r=bezel_r);
            }
         }
      }
   }
}
