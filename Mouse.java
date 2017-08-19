/*
    Program do obsługi myszy komputera.
 */
package mouse;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
/*
    <applet code="Mouse" width=300 height=100> </applet>
 */

public class Mouse extends Applet implements MouseListener, MouseMotionListener  {
    String msg = "";
    int mouseX = 0, mouseY = 0;
    
    public void init() {
        addMouseListener(this);
        addMouseMotionListener(this);
    }
    
    public void mouseClicked(MouseEvent me) {
        mouseX = 0;
        mouseY = 10;
        msg = "Kliknięcie myszy";
        repaint();
    }
    
    public void mouseEntered(MouseEvent me) {
        mouseX = 0;
        mouseY = 10;
        msg = "Mysz w obszarze komponentu";
        repaint();
    }
     
    public void mouseExited(MouseEvent me) {
        mouseX = 0;
        mouseY = 10;
        msg = "Mysz opuściłą komponent";
        repaint();
    }
     
    public void mousePressed(MouseEvent me) {
        mouseX = me.getX();
        mouseY = me.getY();
        msg = "Dół";
        repaint();
    }
    
    public void mouseReleased(MouseEvent me) {
        mouseX = me.getX();
        mouseY = me.getY();
        msg = "Góra";
        repaint();
    }
    
    public void mouseDragged(MouseEvent me) {
        mouseX = me.getX();
        mouseY = me.getY();
        msg = "*";
        showStatus("Mysz przeciągana, pozycja" + mouseX + ", " + mouseY);
        repaint();
    }
    
    public void mouseMoved(MouseEvent me) {
         showStatus("Przesunięcie myszy, pozycja" + mouseX + ", " + mouseY);
    }
    
    public void paint(Graphics g) {
        g.drawString(msg, mouseX, mouseY);
    }
    
    
}
